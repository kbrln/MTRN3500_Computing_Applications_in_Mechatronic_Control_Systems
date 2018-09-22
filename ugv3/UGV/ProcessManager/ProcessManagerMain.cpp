#include <iostream>
#include <conio.h>
#include <SMObject.h>
#include <SMStruct.h>
#include <stdio.h>
#include <Windows.h>
#include <Tlhelp32.h> 


using namespace std;

//#define CRITICAL_MASK 0x63 normal one
#define CRITICAL_MASK 0x03 //laser testing
#define NONCRITICAL_MASK 0x1C
#define NUM_UNITS 2

//unused:hlevel:sm:gps:ugv:simulator:remote:plot:laser:pm

TCHAR* Units[10] = //
{
	TEXT("Laser.exe"),
	TEXT("Plotting.exe"),
	TEXT("GPS.exe"),
	TEXT("Xbox.exe"),
	TEXT("UGV.exe"),
	TEXT("Simulator.exe"),
	
};

bool IsProcessRunning(const char *processName)
{
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (!_stricmp(entry.szExeFile, processName))
				exists = true;

	CloseHandle(snapshot);
	return exists;
}

int  main()
{

	__int64 Frequency, HPC;
	double PMTimeStamp;
	int NonCriticalMaskCount = 0;
	int CriticalMaskCount = 0;


	STARTUPINFO s[10];
	PROCESS_INFORMATION p[10];


	SMObject PMObj(TEXT("ProcessManagement"), sizeof(ProcessManagement));
	SMObject GPSObj(TEXT("GPS"), sizeof(GPS));
	SMObject LaserObj(TEXT("Laser"), sizeof(Laser));
	SMObject PlotObj(TEXT("Plotting"), sizeof(Plotting));
	SMObject SimObj(TEXT("Simulation"), sizeof(Simulator));
	SMObject UGVObj(TEXT("UGV"), sizeof(UGV));
	SMObject XBoxObj(TEXT("Xbox"), sizeof(Remote));

	PMObj.SMCreate();
	GPSObj.SMCreate();
	LaserObj.SMCreate();
	PlotObj.SMCreate();
	SimObj.SMCreate();
	UGVObj.SMCreate();
	XBoxObj.SMCreate();

	PMObj.SMAccess();
	XBoxObj.SMAccess();
	//setup shared memory
	//get access to shared memory
	//start other modules in specified order

	
	for (int i = 0; i < NUM_UNITS; i++)
	{
		// Check if each process is running
		if (!IsProcessRunning(Units[i]))
		{
			ZeroMemory(&s[i], sizeof(s[i]));
			s[i].cb = sizeof(s[i]);
			ZeroMemory(&p[i], sizeof(p[i]));
			// Start the child processes.

			if (!CreateProcess(NULL,   // No module name (use command line)
				Units[i],        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				FALSE,          // Set handle inheritance to FALSE
				CREATE_NEW_CONSOLE,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory
				&s[i],            // Pointer to STARTUPINFO structure
				&p[i])           // Pointer to PROCESS_INFORMATION structure
				)
			{
				printf("%s failed (%d).\n", Units[i], GetLastError());
				//_getch();
				//return -1;
			}
		}
		cout << "Started: " << Units[i] << endl;
		Sleep(100);		// Any other initialization
	}
	

	//cout << "yeh bruh testing" << endl;

	cout << "PM Module Started" << endl;

	QueryPerformanceFrequency((LARGE_INTEGER *)&Frequency);

	
	ProcessManagement * PM = (ProcessManagement*)PMObj.pData;
	Remote *pXBox = (Remote*)XBoxObj.pData;

	PM->Shutdown.Status = 0;

	while (!PM->Shutdown.Flags.PM)
	{
		//get HPC (high performance count) count and calculate timestamp
		QueryPerformanceCounter((LARGE_INTEGER *)&HPC);
		PM->PMTimeStamp = (double)HPC / (double)Frequency;

		PM->Heartbeat.Flags.PM = 1;

		cout << "PM Running - TimeStamp is " << PM->PMTimeStamp << endl;
		Sleep(500);

		//non crit restart
		if ((PM->Heartbeat.Status & NONCRITICAL_MASK) != NONCRITICAL_MASK)
		{
			NonCriticalMaskCount++;
				if (NonCriticalMaskCount > 100)
				{
					//initiate restart
					NonCriticalMaskCount = 0;
				}
		}

		else
		{
			NonCriticalMaskCount = 0;
		}

		//crit mask shutdown
		if ((PM->Heartbeat.Status & CRITICAL_MASK) != CRITICAL_MASK)
		{
			CriticalMaskCount++;
			if (CriticalMaskCount > 100)
			{
				//initiate shutdown
				//PM->Shutdown.Status = 0xFF;
				NonCriticalMaskCount = 0;
			}
		}

		else
		{
			CriticalMaskCount = 0;
		}



		if (_kbhit())
			break;

		PM->Heartbeat.Status = 0;

		if (pXBox->Terminate)
		{
			break;
		}
	}

	//keep track of live execution of all modules
		//if module has failed
			//restart if not critical
			//otherwise	enter into safe mode if critical failure (could mean shut down)
	//keep looping


	//at termination
		//shut down modules in specified order
		//release allocated memory
		//exit
	PM->Shutdown.Flags.UGV = 1;
	Sleep(200);
	PM->Shutdown.Flags.Laser = 1;
	Sleep(200);
	PM->Shutdown.Status = 0xFF;


	cout << "Everything Shutdown" << endl;

	return 0;
}