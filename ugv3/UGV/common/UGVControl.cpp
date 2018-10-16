#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <UGVControl.h>
#include <stdio.h>


UGVControl::UGVControl() :EthernetClient()	//default constructor, set speed, steering to 0 and flag to 1 
{
	Speed = 0;
	Steering = 0;
	flag = 1;
}

UGVControl::UGVControl(char* portaddress, char* port):EthernetClient(portaddress, port)	//pass the portaddress and port to the ethernet client parent class
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
	char Buffer[128];		//create char buffer
	Speed = speed;
	Steering = steering;
	//how to initialise to 0 if the controller isnt inputting anything, perhaps initialise in xbox instead
	flag = 1 - flag;	//alternate flag
	sprintf_s(Buffer, "# %10.3f %10.3f %1d #", Steering, Speed, flag);	//create command string 
	SendData(Buffer, strlen(Buffer)); // send command string 
}
