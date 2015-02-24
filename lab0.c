/*
 ============================================================================
 Name        : lab0.c
 Author      : Amir Patel
 Version     :
 Copyright   : Your copyright notice
 Description : First lab for EEE3074W
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Include files */
#include "lab0.h"

/* Any MACROS you want to define go here */
#define ARRAYLENGTH(x) (sizeof (x) / sizeof *(x)) // Only use this on statically define arrays !!!
#define sampleT 1 /* sample time of data set in seconds */
int readData(char *cpFilename, float **fpFlightData);
int take_off(float * data,  int size);
float maxVal(float* fpData, int iSizeData);
float max_rate(float * data, int size);
float climbrate(float a, float b);

/* This is the Main function */
int main(void)
{
	float fFirst;
	float fMinAlt;
	fFirst = fpTestData[0];

	/* Print some stuff */
	printf("Welcome to EEE3074W - Lab0 \n"); /* prints EEE3074W: Lab0 */

	/* Determine the runway altitude */
	fMinAlt = minVal( fpTestData, ARRAYLENGTH(fpTestData));

	/* Print Minimum Altitude */
	printf("The runway altitude of the test data is = %f m\n", fMinAlt);


	//Insert your function calls and related code here...
	char * fileName = "FlightData.bin";
	float * data;
	
	int msize = readData(fileName,&data);
	int i= 0;
	for(i=0; i< msize; i++){
		printf("%f\n",data[i]);
	}
	printf("%d\n", take_off(data, msize));
	printf("%f\n", maxVal(data, msize));
	printf("%f\n", max_rate(data, msize));
	/* End of Main */
	return 0;
}

/**
 * Function determines and returns the minimum value in an array.
 * @param data - data array
 * @param sizeData - size of the data array
 */
float minVal(float* fpData, int iSizeData)
{
	/* Initialise Variables */
	int i = 0;
	float fMinVal;

	/* Do a for loop to search for the min value */
	for ( i = 0; i < iSizeData; i++ )
	{
		/* If it is the first element */
		if ( i == 0 )
		{
			/* Set to first value */
			fMinVal = fpData[i];
		}
		else
		{
			/* If current min value is smaller than current element */
			if ( fpData[i] < fMinVal )
			{
				/* Found a new min value */
				fMinVal = fpData[i];
			}
		}
	}

	/* Return the minimum value */
	return fMinVal;
}

int readData(char *cpFilename, float **fpFlightData)
{
		FILE *fp = fopen(cpFilename,"rb");
		
		if(fp!=NULL)
		{			
			fseek(fp, 0, SEEK_END);
			int size = ftell(fp);
			rewind(fp);
			printf("%d",size);
			*fpFlightData = (float*) malloc(size);
			fread(*fpFlightData, sizeof(float), size/sizeof(float), fp);
			fclose(fp);
			return size/sizeof(float);

		}else{
			fclose(fp);
			return -1;
		}
		
		
}


float max_rate(float * data, int size){
	float tmp[size-1];
	int i;
	for(i=0;i<size-1;i++){
		tmp[i]=climbrate(data[i],data[i+1]);
	}
	return maxVal(tmp,size);
}

float climbrate(float a, float b){return (b-a);}

int take_off(float * data,  int size){
	int j = 1;
	int time;

	/* Do a for loop to search for the min value */
	for ( j = 1; j < size; j++ )
	{
		/* If it is the first element */
		if ( data[j] > data[1])
		{
			time = j-1;
			break;
		
		}
	}
		return time;
}

float maxVal(float* fpData, int iSizeData)
{
	/* Initialise Variables */
	int i = 0;
	float fMaxVal;

	/* Do a for loop to search for the min value */
	for ( i = 0; i < iSizeData; i++ )
	{
		/* If it is the first element */
		if ( i == 0 )
		{
			/* Set to first value */
			fMaxVal = fpData[i];
		}
		else
		{
			/* If current min value is smaller than current element */
			if ( fpData[i] > fMaxVal )
			{
				/* Found a new min value */
				fMaxVal = fpData[i];
			}
		}
	}

	/* Return the minimum value */
	return fMaxVal;
}



/**
 *  - Write a function determine the take-off time
 * 
 *  - Write a function that determines the maximum height
 *  - Write a function that determines the maximum climb rate (hint, use the derivative )
 *
 */
