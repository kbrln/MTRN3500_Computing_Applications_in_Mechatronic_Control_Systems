//#define _WINSOCKAPI_
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <SMObject.h>
#include <SMStruct.h>


#include <UGVControl.h>

using namespace std;

int  main()
{
	__int64 Frequency, HPC;
	double PMTimeStamp, UGVTimeStamp;


	UGVControl UGV("192.168.5.140", "25000");

	SMObject PMObj(TEXT("ProcessManagement"), sizeof(ProcessManagement));
	//SMObject GPSObj(TEXT("GPS"), sizeof(GPS));
	//SMObject LaserObj(TEXT("Laser"), sizeof(Laser));
	//SMObject PlotObj(TEXT("Plotting"), sizeof(Plotting));
	//SMObject SimObj(TEXT("Simulation"), sizeof(Simulator));
	//SMObject UGVObj(TEXT("UGV"), sizeof(UGV));
	SMObject XBoxObj(TEXT("Xbox"), sizeof(Remote));

	PMObj.SMAccess();
	//GPSObj.SMAccess();
	//LaserObj.SMAccess();
	//PlotObj.SMAccess();
	//SimObj.SMAccess();
	//UGVObj.SMAccess();
	XBoxObj.SMAccess();

	ProcessManagement * PM = (ProcessManagement*)PMObj.pData;
	Remote *pXBox = (Remote*)XBoxObj.pData; //accessing the xbox data to send commands to the ugv 

	if (UGV.ConnectToServer() != 0)
	{
		cout << "connection unsuccessful (UGV)" << endl;
		return -1;
	}

	cout << "UGV Module Started" << endl;

	QueryPerformanceFrequency((LARGE_INTEGER *)&Frequency);

	PM->Shutdown.Flags.UGV = 0;

	while (!PM->Shutdown.Flags.UGV) //start main loop 
	{
		//get time stamp from PM
		PMTimeStamp = PM->PMTimeStamp;
		PM->Heartbeat.Flags.UGV = 1;

		//local timestamp
		QueryPerformanceCounter((LARGE_INTEGER *)&HPC);
		UGVTimeStamp = (double)HPC / (double)Frequency;


		UGV.Drive(pXBox->setSpeed, pXBox->setSteering);	//send the drive commands 

		//calculate delay in transfer data
		//terminate


		if (_kbhit())
			
			break;
	}
	return 0;
}