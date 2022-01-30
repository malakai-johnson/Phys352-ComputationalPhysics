//Phys 352: Computational Physics
//Ising Model
//Malakai Johnson

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h> //requires compiling with -lm flag
#include <time.h>

#define SEED 4512345
#define NUM_OF_TIME_SWEEPS 10000

#define SIZE0 50
#define SIZE1 50
#define TEMPURATURE 0.001 // At tempuratures below ~0.0015, the magnitazation tends to fluctate near some particular non-zero value

double computeMagnetization(int spins[SIZE0][SIZE1]);
void fillSpins(int spins[SIZE0][SIZE1]);
void fillRelations(double relationsVert[SIZE0][SIZE1], double relationsHorz[SIZE0][SIZE1]);
int monteCarloSweep(int spins[SIZE0][SIZE1], double relationsVert[SIZE0][SIZE1], double relationsHorz[SIZE0][SIZE1], double tempurature);
bool updateSpin(int spins[SIZE0][SIZE1], double relationsVert[SIZE0][SIZE1], double relationsHorz[SIZE0][SIZE1], double tempurature, int coordinate[2]);
double energy_calc(int spins[SIZE0][SIZE1], double relationsVert[SIZE0][SIZE1], double relationsHorz[SIZE0][SIZE1], int coordinate[2]);
void generateGaussianNoise(double mean, double deviation, double output[2]);

void main ()
{
	// srand(SEED);
	srand(time(0));
	static int spins[SIZE0][SIZE1];
	static double relationsVert[SIZE0][SIZE1]; //JijX  
	static double relationsHorz[SIZE0][SIZE1]; //JijY
	double tempurature = TEMPURATURE;

	fillSpins(spins);
	fillRelations(relationsVert, relationsHorz);

	double magnetization = 0;
	int flipCount = 0;

	for(int i = 0; i < NUM_OF_TIME_SWEEPS; ++i)
	{
		flipCount = monteCarloSweep(spins, relationsVert, relationsHorz, tempurature);
		magnetization = computeMagnetization(spins);
		printf("%d\t%f\t%d\n", i, magnetization, flipCount);
	}
}

double computeMagnetization(int spins[SIZE0][SIZE1])
{
	double sum = 0;
	for(int row = 0; row < SIZE0; ++row)
	{
		for(int column = 0; column < SIZE1; ++column)
		{
			sum += spins[row][column];
		}
	}

	return sum / (SIZE0 * SIZE1);
}

int monteCarloSweep(int spins[SIZE0][SIZE1], double relationsVert[SIZE0][SIZE1], double relationsHorz[SIZE0][SIZE1], double tempurature)
{
	int coordinate[2];
	int flipCount = 0;

	for(int i = 0; i < SIZE0*SIZE1; ++i)
	{
		coordinate[0] = random() % SIZE0;
		coordinate[1] = random() % SIZE1;

		if(updateSpin(spins, relationsVert, relationsHorz, tempurature, coordinate))
		{
			++flipCount;
		}
	}
	return flipCount;
}

bool updateSpin(int spins[SIZE0][SIZE1], double relationsVert[SIZE0][SIZE1], double relationsHorz[SIZE0][SIZE1], double tempurature, int coordinate[2])
{
	double initialEnergy = energy_calc(spins, relationsVert, relationsHorz, coordinate);
	spins[coordinate[0]][coordinate[1]] *= -1;//flip
	bool isFlipped = true;
	double finalEnergy = energy_calc(spins, relationsVert, relationsHorz, coordinate);

	double deltaEnergy = finalEnergy - initialEnergy;

	if(deltaEnergy > 0)
	{
		if( random()/RAND_MAX >= exp(-1 * deltaEnergy / tempurature) )
		{
			spins[coordinate[0]][coordinate[1]] *= -1;//reject flip
			isFlipped = false;
		}
	}

	return isFlipped;
}

double energy_calc(int spins[SIZE0][SIZE1], double relationsVert[SIZE0][SIZE1], double relationsHorz[SIZE0][SIZE1], int coordinate[2])
{
	int i = coordinate[0];
	int j = coordinate[1];

	int spinUp		= spins[ (i + 1) % SIZE0][j];
	int spinDown	= spins[ (i - 1 + SIZE0) % SIZE0][j];
	int spinRight	= spins[i][ (j + 1) % SIZE1];
	int spinLeft	= spins[i][ (j - 1 + SIZE1) % SIZE1];

	double relationUp 		= relationsVert[i][j];
	double relationDown		= relationsVert[(i-1+SIZE0) % SIZE0][j];
	double relationRight	= relationsHorz[i][j];
	double relationLeft		= relationsHorz[i][(j-1+SIZE1) % SIZE1];


	//Goal \SumNearestNeighbors Jij Sij S
	//Jij is interactions of spins
	double energy =  spinUp * relationUp;
	energy += spinDown * relationDown;
	energy += spinRight * relationRight;
	energy += spinLeft * relationLeft;

	return energy * spins[i][j];
}

void fillSpins(int spins[SIZE0][SIZE1])
{
	for(int row = 0; row < SIZE0; ++row)
	{
		for(int column = 0; column < SIZE1; ++column)
		{
			int spin = rand() % 2;
			if (spin == 0) spin = -1;
			spins[row][column] = spin;
		}
	}
}

void fillRelations(double relationsVert[SIZE0][SIZE1], double relationsHorz[SIZE0][SIZE1])
{
	double randomPair[2];

	for(int row = 0; row < SIZE0; ++row)
	{
		for(int column = 0; column < SIZE1; ++column)
		{
			generateGaussianNoise(0, (double)1/3, randomPair);
			relationsVert[row][column] = randomPair[0];
			relationsHorz[row][column] = randomPair[1];
			// printf("[%.5f,%.5f] ", randomPair[0], randomPair[1]);
		}
		// printf("\n");
	}
}

void generateGaussianNoise(double mean, double deviation, double output[2])
{
    double two_pi = 2.0 * M_PI;

    //create two random numbers, make sure u1 is greater than 0
    double u1, u2;
    do
    {
        u1 = (double) rand() / RAND_MAX;
        u2 = (double) rand() / RAND_MAX;
    }
    while (u1 <= 0);

    //compute z0 and z1
    double mag = deviation * sqrt(-2.0 * log(u1));
    double z0  = mag * cos(two_pi * u2) + mean;
    double z1  = mag * sin(two_pi * u2) + mean;

    output[0] = z0;
    output[1] = z1;
}