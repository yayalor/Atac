#include <Windows.h>
#include <stdio.h>
typedef struct _UNICODE_STRING { // UNICODE_STRING structure
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;


typedef NTSTATUS(WINAPI *fLdrLoadDll) //LdrLoadDll function prototype
(
IN PWCHAR PathToFile OPTIONAL,
IN ULONG Flags OPTIONAL,
IN PUNICODE_STRING ModuleFileName,
OUT PHANDLE ModuleHandle
);


//NtQueryInformationToken function prototype
typedef NTSTATUS(WINAPI *fNtQueryInformationToken)(
	HANDLE                  TokenHandle,
	TOKEN_INFORMATION_CLASS TokenInformationClass,
	PVOID                   TokenInformation,
	ULONG                   TokenInformationLength,
	PULONG                  ReturnLength
	);

typedef NTSTATUS(WINAPI *fNtOpenProcessToken)(
	HANDLE      ProcessHandle,
	ACCESS_MASK DesiredAccess,
	PHANDLE     TokenHandle
	);

typedef NTSTATUS(WINAPI *fNtClose)(
	HANDLE Handle
	);


HMODULE hntdll;
fLdrLoadDll _LdrLoadDll;
fNtClose _NtClose;
fNtOpenProcessToken _NtOpenProcessToken;
fNtQueryInformationToken _NtQueryInformationToken;


void GetFuncAddr()
{
	if (hntdll == NULL) { hntdll = GetModuleHandleA("ntdll.dll"); }
	if (_LdrLoadDll == NULL) { _LdrLoadDll = (fLdrLoadDll)GetProcAddress(hntdll, "LdrLoadDll"); }
	
	if (_NtQueryInformationToken == NULL)
	{
		_NtQueryInformationToken = (fNtQueryInformationToken)GetProcAddress(hntdll, "NtQueryInformationToken");
	}
	if (_NtOpenProcessToken == NULL)
	{
		_NtOpenProcessToken = (fNtOpenProcessToken)GetProcAddress(hntdll, "NtOpenProcessToken");
	}
	if (_NtClose == NULL)
	{
		_NtClose = (fNtClose)GetProcAddress(hntdll, "NtClose");
	}

}

bool IsCurrentProcessElevated()
{
	HANDLE token;
	ULONG ReturnLength;
	LPVOID TokenInformation;
	ULONG size = 0x4;
	TokenInformation = VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_READWRITE);

	if (_NtOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token) < 0)
	{
		printf("OpenProcessToken error %d", GetLastError());
		return FALSE;
	}
	else
	{
		/*	
			TokenElevationDefault (1)：表示 UAC 已禁用。
			TokenElevationTypeFull (2)：表示当前进程正在运行提升。
			TokenElevationTypeLimited (3)：表示进程没有运行提升。
		*/
		_NtQueryInformationToken(token, TokenElevationType, &TokenInformation, size, &ReturnLength);
		_NtClose(token);
		if ((DWORD)TokenInformation != 3) return TRUE;
		else return FALSE;
	}

}
int main()
{
	GetFuncAddr();
	if (IsCurrentProcessElevated())
	{
		printf("current process is Elevated");
	}
}