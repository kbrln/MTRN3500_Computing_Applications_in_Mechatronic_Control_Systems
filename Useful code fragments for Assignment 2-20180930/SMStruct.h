#ifndef SMSTRUCT_H
#define SMSTRUCT_H

//Gps data 
struct GPS
{
	double Northing;
	double Easting;
	double height;
	double Heading;
	unsigned char GPSQuality;
	double GPSTimeStamp;
};

//Laser data 
struct Laser
{
	double x[1100];
	double y[1100];
	int NumPoints;
	double LaserTimeStamp;
};

//Plot data 
struct Plotting
{
	double X;
	double Y;
	double Heading;
	double PlotTimeStamp;
};

//set of flags for each process, will be used for status and heartbeat 
struct UnitFlags 
{
	unsigned short PM : 1,
		Laser : 1,
		Plot : 1,
		Remote : 1,
		Simulator : 1,
		UGV : 1,
		GPS : 1,
		SM : 1,
		Hlevel : 1,
		Unused : 7;
};

//create a union so that flags can be accessed individually or collectively 
union ExecFlags 
{
	UnitFlags Flags;
	unsigned short Status;
};

struct ProcessManagement
{
	ExecFlags Heartbeat; //PM:Laser:Plot:Remote:Simulator:UGV:GPS:SM:Hlevel:Unused
	ExecFlags Shutdown;
	double PMTimeStamp;
};

//remote data 
struct Remote
{
	double setSteering;
	double setSpeed;
	unsigned char UGV_SIM;	//choose UGV or simulator
	int Terminate;
};

//simulator data 
struct Simulator
{
	double X;
	double Y;
	double Heading;
};

//ugv data 
struct UGV
{
	double X;
	double Y;
	double Heading;
};

#endif