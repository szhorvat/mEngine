/*
 * get.c
 *
 * Wrapper of the MatLab Engine API engGetVariable
 * for call from Mathematica
 *
 * Revision 2003.3.11
 *
 * Robert
 *	
 */

#include "mathlink.h"
#include "engine.h"

#include <stdio.h>

extern Engine* Eng;
extern void msg(const char* m);

void engget(const char* VarName)
{
	mxArray*		MxVar = NULL;	//pointer for the variable to get
	const mwSize*	dimlab = NULL;	//MATLAB dimension
	int*			dimma = NULL;	//Mathematica dimension
	int				Depth = 0;		//depth
	double*			Pr = NULL;		//pointer to real
	double*			Pi = NULL;		//pointer to imaginary
	bool			SUCCESS = true;	//status flag
	int				i;				//for loop
    
	if (NULL == Eng)	//if MATLAB not opened
	{
		msg("eng::noMLB");	//message no start
		SUCCESS = false;
		goto epilog;
	}

	if (NULL == (MxVar = engGetVariable(Eng, VarName)))	//get variable
	{
		msg("engGet::erget");
		SUCCESS = false;
		goto epilog;
	}

	if(!mxIsDouble(MxVar))
	{
		msg("engGet::ertp");
		SUCCESS = false;
		goto epilog;
	}

	//retrive size information
	Depth = mxGetNumberOfDimensions(MxVar);
	dimlab = mxGetDimensions(MxVar);

	//translate dimension information to Mathematica
	dimma = malloc(Depth * sizeof(int));
	for(i=0; i<Depth; ++i)
		dimma[i] = dimlab[Depth - 1 - i];
	//data pointer
	Pr = (double*)mxGetPr(MxVar);
	Pi = (double*)mxGetPi(MxVar);

epilog:
	if(SUCCESS)
	{

		if(mxIsComplex(MxVar))
		{
			//output re+im*I
			MLPutFunction(stdlink, "Plus", 2);
			MLPutReal64Array(stdlink, Pr, dimma, NULL, Depth);
			MLPutFunction(stdlink, "Times", 2);
			MLPutReal64Array(stdlink, Pi, dimma, NULL, Depth);
			MLPutSymbol(stdlink, "I");
		}
		else {
			MLPutReal64Array(stdlink, Pr, dimma, NULL, Depth);
		}
		//clean
		mxDestroyArray(MxVar);
		free(dimma);
	}
	else
	{
		if(NULL != MxVar)
			mxDestroyArray(MxVar);		
		if(NULL != dimma)
			free(dimma);
		MLPutSymbol(stdlink, "$Failed");
	}
}

