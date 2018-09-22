#ifndef SMOBJECT_H
#define SMOBJECT_H

#include <Windows.h>
#include <tchar.h>
#include <SMfcn.h>

class SMObject
{
	HANDLE CreateHandle;		//handle to created memory
	HANDLE AccessHandle;		//handle to accessed memory
	TCHAR *szName;				//a global tag name to the memory block (similar to file names)
	int Size;					//size of shared mem in bytes
public:
	void *pData;				//pointer to the shared memory block
	int SMCreateError;			//create error flag
	int SMAccessError;			//access error flag
public:
	SMObject();					//def constructor
	SMObject(TCHAR* szname, int size);	//constructor take in tag name and mem block size

	~SMObject();	//destructor
	int SMCreate();	//creating shared memory block
	int SMAccess(); //grant access to shared memory block
};
#endif


