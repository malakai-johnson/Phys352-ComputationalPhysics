#include <stdio.h>
#include <stdlib.h>
#include <math.h> //requires compiling with -lm flag

#define NUM_ARGS 2
#define USAGE "USAGE: %s [inputData] [outputFile]\n"
#define COMMAND "annealing"

#define NUM_PARAMS 4
#define NUM_SIMULATIONS

void varyParam(double init[NUM_PARAMS], trial[NUM_PARAMS], minParams[NUM_PARAMS], maxParams[NUM_PARAMS])
{
	for(int i = 0; i < NUM_PARAMS; ++i)
	{
		alpha = -4.5;
		trial[i] = init[NUM_PARAMS] + (rand()/RAND_MAX - 0.5) * (maxParams[i] - minParams[i]) * exp(alpha * t);
	}
}

void optimize(data, numData)
{
	double minParams[NUM_PARAMS];
	double maxParams[NUM_PARAMS];
	double init[NUM_PARAMS];
	double trial[NUM_PARAMS];

	for(int i = 0; i < NUM_SIMULATIONS; ++i)
	{
		
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

	double* data[2]
	data[0] = (double*) malloc(numData * sizeof(double));
	data[1] = (double*) malloc(numData * sizeof(double));


	printf("Processing Data...\n");
	for(int i = 0; i < numData; ++i)
	{
		fscanf(inputData, "%lf\n", &data[i]);
	}
	printf("Done Processing.\n");

	int numOutput = numData;

	printf("Transforming...\n");
	optimize(data, numData, numParamaters);
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

	fclose(inputData);
	fclose(outputFile);

	// printf("Reading from %s...\n", argv[2]);
	// FILE* inputFile2 = fopen(argv[2],"r");
	// for (int i = 0; i < numData; ++i)
	// {
	// 	fscanf(inputData2,"%lf\t%lf\n", &dataTransformed[0][i], &dataTransformed[1][i]);
	// }

	free(data);
	return 0;
}