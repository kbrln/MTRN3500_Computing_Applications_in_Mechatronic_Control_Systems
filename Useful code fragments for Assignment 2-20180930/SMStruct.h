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
	//critical mask		0000 0000 0111 1011 
	//non-critical mask	0000 0000 0000 0100
	unsigned short PM : 1, //critical
		Laser : 1, //critical
		GPS : 1, //non-critical
		Camera : 1, //critical 
		VehicleControl : 1,//critical
		Remote : 1, //critical
		Visualisation : 1, // (critical?)
		Unused : 9;
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