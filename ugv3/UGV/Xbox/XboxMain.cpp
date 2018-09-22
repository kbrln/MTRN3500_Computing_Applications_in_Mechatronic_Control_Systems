#include <windows.h>
#include <iostream>
#include <conio.h>
#include <SMObject.h>
#include <SMStruct.h>
//#include <UGVControl.h>
#include <XBox.h>

using namespace std;

int  main()
{
	__int64 Frequency, HPC;
	double XBoxTimeStamp;

	XBox GameController;

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
	Remote *pXBox = (Remote*)XBoxObj.pData;


	//xbox stuff
	GameController.SetDeadZone(6000);


	PM->Shutdown.Flags.Remote = 0;
	pXBox->Terminate = 0;

	while (!PM->Shutdown.Flags.Remote)
	{
		//set heartbeat
		PM->Heartbeat.Flags.Remote = 1;

		//chuck in speed and steering data from controller
		pXBox->setSteering = GameController.LeftY(1.0);
		pXBox->setSpeed = GameController.RightX(40.0);

		//terminate everything
		if (GameController.X() == 1)
			pXBox->Terminate = 1;

		//manual exit
		if (_kbhit())
			break;
	}

	return 0;
}