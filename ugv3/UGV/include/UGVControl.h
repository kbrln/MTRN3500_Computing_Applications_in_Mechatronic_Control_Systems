#ifndef UGVControl_H
#define UGVCONTROL_H

#include <EthernetClient.h>

class UGVControl : public EthernetClient
{
private:
	double Speed;
	double Steering;
	int flag;
public:
	UGVControl();
	UGVControl(char * portaddress, char* port);
	~UGVControl() {}
	void SetSpeed(double setSpeed);
	void SetSteering(double setSteering);
	double GetSpeed();
	double GetSteering();
	void Drive(double speed, double steering);
};
#endif