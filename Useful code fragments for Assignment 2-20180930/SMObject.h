#ifndef SMLASER_H
#define SMLASER_H

#include <Windows.h>
#include <tchar.h>
#include <SMfcn.h>



class SMObject	//shared memory object 
{
	HANDLE CreateHandle;	//default private 
	HANDLE AccessHandle;	//handles are pointers to an object located on the gc heap 
	TCHAR *szName;		//type + char, just some type that supports multiple character set types
	int Size;			//integer for size of object
public:
	void *pData; //pointer to the data for the current  shared memroy object 
	int SMCreateError; //error ints
	int SMAccessError;
public:
	SMObject();						//default constructor 
	SMObject(TCHAR* szname, int size);	//overload constructor defining szname and size. 

	~SMObject();	//destructor 
	int SMCreate();	//create shared memory function 
	int SMAccess(); //access shared memory function 
};
#endif


