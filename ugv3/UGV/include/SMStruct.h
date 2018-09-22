#ifndef SMSTRUCT_H
#define SMSTRUCT_H

struct GPS
{
	double Northing;
	double Easting;
	double height;
	double Heading;
	unsigned char GPSQuality;
	double GPSTimeStamp;
};

struct Laser
{
	double x[1100];
	double y[1100];
	int NumPoints;
	double LaserTimeStamp;
};

struct Plotting
{
	double X;
	double Y;
	double Heading;
	double PlotTimeStamp;
};

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

union ExecFlags 
{
	UnitFlags Flags;
	unsigned short Status;
};

struct ProcessManagement
{
	ExecFlags Heartbeat;
	ExecFlags Shutdown;
	double PMTimeStamp;
};

struct Remote
{
	double setSteering;
	double setSpeed;
	unsigned char UGV_SIM;	//choose UGV or simulator
	int Terminate;
};

struct Simulator
{
	double X;
	double Y;
	double Heading;
};

struct UGV
{
	double X;
	double Y;
	double Heading;
};

#endif