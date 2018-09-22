#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <UGVControl.h>
#include <stdio.h>


UGVControl::UGVControl() :EthernetClient()
{
	Speed = 0;
	Steering = 0;
	flag = 1;
}

UGVControl::UGVControl(char* portaddress, char* port):EthernetClient(portaddress, port)
{
	Speed = 0;
	Steering = 0;
	flag = 1;
}

void UGVControl::SetSpeed(double setSpeed)
{
	Speed = setSpeed;
}

void UGVControl::SetSteering(double setSteering)
{
	Steering = setSteering;
}

double UGVControl::GetSpeed()
{
	return Speed;
}

double UGVControl::GetSteering()
{
	return Steering;
}

void UGVControl::Drive(double speed, double steering)
{
	char Buffer[128];
	Speed = speed;
	Steering = steering;
	//how to initialise to 0 if the controller isnt inputting anything, perhaps initialise in xbox instead
	flag = 1 - flag;
	sprintf_s(Buffer, "# %10.3f %10.3f %1d #", Steering, Speed, flag);
	SendData(Buffer, strlen(Buffer));
}
