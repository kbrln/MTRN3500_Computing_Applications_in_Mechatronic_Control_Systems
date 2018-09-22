#include <iostream>
#include <conio.h>
#include <SMObject.h>
#include <SMStruct.h>
#include <stdio.h>
#include <Windows.h>

#include <engine.h>

/**** Specify include files from Matlab/extern and also lib files
libmx.lib, libmex.lib and libeng.lib from Matlab/extern/lib/microsoft
*******/
//h = findall(gca, 'type', 'line', 'color', 'b')
//h = findall(gca, 'type', 'line', 'marker', '+') ???
//delete(h)

using namespace std;

int  main()
{
	cout << "yeh testin" << endl;

	//__int64 Frequency, HPC;
	//double PlotTimeStamp;

	double x[181], y[181];

	cout << "yeh testin2" << endl;

	// Declarations for MATLAB
	Engine *ep;
	mxArray *X = NULL, *Y = NULL;

	SMObject PMObj(TEXT("ProcessManagement"), sizeof(ProcessManagement));
	SMObject LaserObj(TEXT("Laser"), sizeof(Laser));
	SMObject PlotObj(TEXT("Plotting"), sizeof(Plotting));


	PMObj.SMAccess();
	LaserObj.SMAccess();
	PlotObj.SMAccess();

	ProcessManagement * PM = (ProcessManagement*)PMObj.pData;
	Laser *pLaser = (Laser*)LaserObj.pData;
	Plotting *pPlot = (Plotting*)PlotObj.pData;

	cout << "yeh testin3" << endl;

	
	//Start local MATLAB engine
	if (!(ep = engOpen("\0")))
	{
		cout << "MATLAB engine failure" << endl;
		return 1;
	}
	


	//QueryPerformanceFrequency((LARGE_INTEGER *)&Frequency);

	//engEvalString(ep, "figure(1)");
	//engEvalString(ep, "axis([-3 3 -1 5]); hold on;");

	while (!PM->Shutdown.Flags.Plot)
	{

		PM->Heartbeat.Flags.Plot = 1;

		//QueryPerformanceCounter((LARGE_INTEGER *)&HPC);
		//PlotTimeStamp = (double)HPC / (double)Frequency;
		//pPlot->PlotTimeStamp = PlotTimeStamp;



		for (int i = 0; i < 182; i++)
		{
			x[i] = pLaser->x[i];
			y[i] = -(pLaser->y[i]);
			cout << x[i] << "	" << y[i] << endl;
		}


		

		//matlab stuff
		X = mxCreateDoubleMatrix(181, 1, mxREAL);
		Y = mxCreateDoubleMatrix(181, 1, mxREAL);
		//fill in matlab space
		memcpy((void *)mxGetPr(X), (void *)&x, sizeof(x));
		memcpy((void *)mxGetPr(Y), (void *)&y, sizeof(y));
		//transfer to matlab
		engPutVariable(ep, "X", X);
		engPutVariable(ep, "Y", Y);
		//plot in matlab

		//engEvalString(ep, "h = findall(gca, 'type', 'line', 'color', 'b');");
		//chuck in to delet stuff if ur using the hold on earlier
		//engEvalString(ep, "delete(h);");
		

		engEvalString(ep, "plot(X,Y,'-r');");

		

		if (_kbhit())
			break;

	}

	
	cout << "terminatin normally" << endl;
	mxDestroyArray(X);
	mxDestroyArray(Y);
	engClose(ep);
	

	return 0;
}

