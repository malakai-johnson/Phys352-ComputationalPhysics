#include <stdio.h>
#include <stdlib.h>
#include <math.h> //requires compiling with -lm flag

#define NUM_ARGS 3
#define USAGE "USAGE: %s [inputData] [outputFile] [outputFile2]\n"
#define COMMAND "fourier"

double CosSum(double k, double* data, double numData)
{
	double cosSum = 0;
	for (int n = 0; n < numData; ++n)
	{
		cosSum += data[n] * cos(2 * M_PI * k * (double)n / numData);
	}
	return cosSum;
}

double SinSum(double k, double* data, double numData)
{
	double sinSum = 0;
	for (int n = 0; n < numData; ++n)
	{
		sinSum += data[n] * sin(2 * M_PI * k * (double)n / numData);
	}
	return sinSum;
}

double phaseAngle(double cosSum, double sinSum)
{
	return atan(sinSum / cosSum);
}

double magnitude(double cosSum, double sinSum)
{
	double power = sqrt( (cosSum * cosSum) + (sinSum * sinSum) );
	return power;
} 

void fourierTransform(double* data, int numData, double** dataTransformed)
{
	for(int k = 0; k < numData; ++k)
	{
		double cosSum = CosSum(k, data, numData);
		double sinSum = SinSum(k, data, numData);
		dataTransformed[0][k] = magnitude(cosSum, sinSum);
		dataTransformed[1][k] = phaseAngle(cosSum, sinSum);
		dataTransformed[2][k] = cosSum;
		dataTransformed[3][k] = sinSum;
	}
}

void inverseFourierTransform(double** dataTransformed, int numData, double* dataUntransformed)
{
	//The reverse DFT for the i-th element of data is one over N times the sum over all k C(k) times cos(2 pi k i /N) plus S(k) times sin(2 pi k i /N).
	for(int i = 0; i < numData; ++i)
	{
		dataUntransformed[i] = 0;
		for(int k = 0; k < numData; ++k)
		{
			double cosSum = dataTransformed[2][k];
			double sinSum = dataTransformed[3][k];

			dataUntransformed[i] += 
				(1 / (double) numData) * (
					(cosSum * cos(2 * M_PI * k * i / (double) numData)) + 
					(sinSum * sin(2 * M_PI * k * i / (double) numData))
				);
		}
	}
}

int getNumData(FILE* inputData)
{
	int linesCount = 0;
	char nextChar;

	while((nextChar=fgetc(inputData))!=EOF) {
		if(nextChar=='\n')
			++linesCount;
   }
   ++linesCount;


   rewind(inputData);
   return linesCount;
}

int main(int argc, char **argv){
	if( argc != NUM_ARGS +1)
	{
		printf("ERROR: Not %d arguments\n", NUM_ARGS);
		printf(USAGE, COMMAND);
		return 1;
	}

	printf("Reading: %s\n", argv[1]);

	FILE *inputData = fopen(argv[1], "r");

	int numData = getNumData(inputData);
	// --numData;
	printf("The file contained %d data points\n", numData);

	double* data = (double*) malloc(numData * sizeof(double));

	printf("Processing Data...\n");
	for(int i = 0; i < numData; ++i)
	{
		fscanf(inputData, "%lf\n", &data[i]);
	}
	printf("Done Processing.\n");

	int numOutput = numData;
	double* dataTransformed[4]; 
	dataTransformed[0] = (double*) malloc(numOutput * sizeof(double));
	dataTransformed[1] = (double*) malloc(numOutput * sizeof(double));
	dataTransformed[2] = (double*) malloc(numOutput * sizeof(double));
	dataTransformed[3] = (double*) malloc(numOutput * sizeof(double));


	printf("Transforming...\n");
	fourierTransform(data, numData, dataTransformed);
	printf("Done transforn.\n");

	if (!dataTransformed)
	{
		printf("fourierTransform did not return a valid pointer");
		return -1;
	}

	printf("Writing to %s...\n", argv[2]);
	FILE* outputFile = fopen(argv[2], "w");
	for(int i = 0; i < numOutput; ++i)
	{
		fprintf(outputFile, "%f\t%f\n", dataTransformed[0][i], dataTransformed[1][i]);
	}
	printf("All done.\n");

	double* dataUntransformed = (double*) malloc(numData * sizeof(double));

	printf("Untransforming...\n");
	inverseFourierTransform(dataTransformed, numData, dataUntransformed);
	printf("Done Untransforming.\n");

	printf("Writing to %s...\n", argv[3]);
	FILE* outputFile2 = fopen(argv[3], "w");
	for(int i = 0; i < numOutput; ++i)
	{
		fprintf(outputFile2, "%f\n", dataUntransformed[i]);
	}
	printf("All done.\n");

	fclose(inputData);
	fclose(outputFile);
	fclose(outputFile2);

	// printf("Reading from %s...\n", argv[2]);
	// FILE* inputFile2 = fopen(argv[2],"r");
	// for (int i = 0; i < numData; ++i)
	// {
	// 	fscanf(inputData2,"%lf\t%lf\n", &dataTransformed[0][i], &dataTransformed[1][i]);
	// }

	free(data);
	free(dataTransformed[0]);
	free(dataTransformed[1]);
	free(dataTransformed[2]);
	free(dataTransformed[3]);
	free(dataUntransformed);
	return 0;
}