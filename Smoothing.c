#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void smoothData(double* data, int numData, double* dataSmoothed, int numOutput, int smoothingFactor) //assumes smoothing factor of 3
{
	int* coeficients;
	switch(smoothingFactor)
	{
		default:
			printf("Only smoothing factor 2 & 3 currently supported.\nUsing 2...");
		case 2:
			coeficients = (int[]){-3, 12, 17, 12, -3};
			break;
		case 3:
			coeficients = (int[]){-2, 3, 6, 7, 6, 3, -2};
			break;

	}
	double coeficientSum = 0;
	for(int i = 0; i < (smoothingFactor*2)+1; ++i)
	{
		coeficientSum += coeficients[i];
	}
	// printf("coeficientSum: %f\n", coeficientSum);

	for(int smoothedIndex = 0; smoothedIndex < numOutput; ++smoothedIndex)
	{
		double sum = 0;
		for(int coeficientIndex = 0; coeficientIndex < (smoothingFactor*2)+1; ++coeficientIndex)
		{
			sum += data[smoothedIndex + coeficientIndex] * coeficients[coeficientIndex];
		}
		dataSmoothed[smoothedIndex] = sum / coeficientSum;
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

   rewind(inputData);
   return linesCount;
}

int main(int argc, char **argv){
	if( argc != 4)
	{
		printf("ERROR: Not 3 arguments\n");
		printf("USAGE: Smoothing [inputData] [smoothingFactor] [outputFile]\n");
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

	int smoothingFactor = atoi(argv[2]);

	printf("Smoothing factor is: %d\n", smoothingFactor);

	int numOutput = numData - (smoothingFactor * 2);
	double* dataSmoothed = (double*) malloc(numOutput * sizeof(double));

	printf("Smoothing...\n");
	smoothData(data, numData, dataSmoothed, numOutput, smoothingFactor);
	printf("Done smoothing.\n");

	if (!dataSmoothed)
	{
		printf("smoothData did not return a valid pointer");
		return -1;
	}

	printf("Writing to %s...\n", argv[3]);
	FILE* outputFile = fopen(argv[3], "w");
	for(int i = 0; i < numOutput; ++i)
	{
		fprintf(outputFile, "%f\n", dataSmoothed[i]);
	}
	printf("All done.\n");


	fclose(inputData);
	fclose(outputFile);
	free(data);
	free(dataSmoothed);
	return 0;
}