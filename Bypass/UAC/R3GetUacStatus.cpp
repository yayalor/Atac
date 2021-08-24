#include <windows.h>
#include <stdio.h>
using namespace std;


DWORD GetCurrentUacStatus()
{
	typedef NTSTATUS(CALLBACK *LPFNDLLCHECKUAC)(DWORD* pflag);

	HMODULE hModule = LoadLibraryA("ntdll");
	if (hModule)
	{
		DWORD UACFlag = 0;
		LPFNDLLCHECKUAC lpfndllcheckuac;

		lpfndllcheckuac = (LPFNDLLCHECKUAC)GetProcAddress(hModule, "RtlQueryElevationFlags");
		
		if (!lpfndllcheckuac)
		{
			// handle the error
			DWORD LastError = GetLastError();
			FreeLibrary(hModule);
			return LastError;

		}
		else
		{
			//UACFlag

			/*	ELEVATION_UAC_ENABLED(0x1)
					UAC is enabled
				ELEVATION_VIRTUALIZATION_ENABLED(0x2)
					File and registry virtualization is enabled
				ELEVATION_INSTALLER_DETECTION_ENABLED(0x4)
					Install and setup programs are detected and automatically elevated
			*/
			// call the function
			NTSTATUS state = lpfndllcheckuac(&UACFlag);
			if (state >= 0)
			{
				if (UACFlag & 0x1)
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
				
			}
			else
			{

				DWORD LastError = GetLastError();
				return LastError;
			}
			
		}

	}
}


void main()
{
	DWORD uacFlag = GetCurrentUacStatus();
	if (uacFlag > 1)
	{
		printf("lasterror: %d", uacFlag);
	}
	else
	{
		if (uacFlag)
		{
			printf("UAC enabled");
		}
		else
		{
			printf("UAC disabled");
		}
	}
}