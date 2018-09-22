#define _WINSOCKAPI_
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <conio.h>
#include <SMObject.h>
#include <SMStruct.h>
#include <Windows.h>

#include <LMS151.h>

using namespace std;



int  main()
{

	__int64 Frequency, HPC;
	double LaserTimeStamp;

	//create laser object
	//LMS151 LMS151Laser("192.168.5.150", "2112");
	LMS151 LMS151Laser("192.168.5.140", "23000"); //real one


	SMObject PMObj(TEXT("ProcessManagement"), sizeof(ProcessManagement));
	//SMObject GPSObj(TEXT("GPS"), sizeof(GPS));
	SMObject LaserObj(TEXT("Laser"), sizeof(Laser));
	//SMObject PlotObj(TEXT("Plotting"), sizeof(Plotting));
	//SMObject SimObj(TEXT("Simulation"), sizeof(Simulator));
	//SMObject UGVObj(TEXT("UGV"), sizeof(UGV));
	//SMObject XboxObj(TEXT("Xbox"), sizeof(Remote));

	PMObj.SMAccess();
	//GPSObj.SMAccess();
	LaserObj.SMAccess();
	//PlotObj.SMAccess();
	//SimObj.SMAccess();
	//UGVObj.SMAccess();
	//XboxObj.SMAccess();

	ProcessManagement * PM = (ProcessManagement*)PMObj.pData;
	Laser *pLaser = (Laser*)LaserObj.pData;

	

	//laser specific initialisation
	//connect to laser
	
	//if (LMS151Laser.ConnectToServer() == 0)
	//{
	//	cout << "connection successful" << endl;
	//}
	//Sleep(5000);
	
	//log in to laser
	//LMS151Laser.Login();
	//configure laser
	//LMS151Laser.Configure(45, 135, HALF_DEGREE);
	//start laser
	//LMS151Laser.Logout();
	//start measurement

	QueryPerformanceFrequency((LARGE_INTEGER *)&Frequency);
	

	while (!PM->Shutdown.Flags.Laser)
	{
		//Set Heartbeat
		PM->Heartbeat.Flags.Laser = 1;

		

		QueryPerformanceCounter((LARGE_INTEGER *)&HPC);			
		LaserTimeStamp  = (double)HPC / (double)Frequency;
		pLaser->LaserTimeStamp = LaserTimeStamp;

		//read laser data

		LMS151Laser.GetRangeCoords();
		//and put data to shared memory
		

		for (int i = 0; i < LMS151Laser.NumPoints; i++)
		{
			//cout << LMS151Laser.NumPoints << endl;
			pLaser->x[i] = LMS151Laser.RangeData[i][0];						//also problematic code
			pLaser->y[i] = LMS151Laser.RangeData[i][1];
			pLaser->NumPoints = LMS151Laser.NumPoints;
			//cout << "yeh" << endl;
			//cout << pLaser->x[i] << "	" << pLaser->y[i] << endl;				//this as wel
			cout << pLaser->NumPoints << endl;
			//cout << LMS151Laser.RangeData[i][0] << "	" << LMS151Laser.RangeData[i][1] << endl;
		}
		Sleep(5000);

		if (_kbhit())
			break;
	}

	cout << "terminated laser module normally" << endl;

	return 0;
}