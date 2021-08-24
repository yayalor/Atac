#include <windows.h>
#include <stdio.h>

typedef NTSTATUS(CALLBACK *LPFNDLLCHECKUAC)(DWORD* pflag);

void main()
{
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

			printf("GetProcAddress fail,lastError: %d", LastError);

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

			// call the RtlQueryElevationFlags
			NTSTATUS state = lpfndllcheckuac(&UACFlag);
			if (state >= 0)
			{
				if (UACFlag & 0x1)
				{
					printf("UAC enabled");
				}
				else
				{
					printf("UAC disabled");
				}
				
			}
			else
			{
				// handle the error
				DWORD LastError = GetLastError();
				printf("RtlQueryElevationFlags error: %d", LastError);
			}
			
			
		}

	}
}