//Malakai Johnson

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_TRIALS 99999

double sumMonteCarlo(double start, double finish, double f(double));
double sumLeft(double start, double finish, double f(double));
double sumRight(double start, double finish, double f(double));
double sumCenter(double start, double finish, double f(double));


double square(double x)
{
	return x*x;
}

void main()
{
	double start = 0;
	double finish = 9; // integrate function fx from begin to end.
	srand(time(0));
	
	printf("\n***Monte Carlo SUM***\n");
	double integral = sumMonteCarlo(start, finish, square);
	printf("Integral of f(x) from %.2lf to %.2lf with %d trials is about %.4lf\n", start, finish, NUM_OF_TRIALS, integral);

	printf("\n***LEFT SUM***\n");
	integral = sumLeft(start, finish, square);
	printf("Integral of fx from %lf to %lf is about %lf\n", start, finish, integral);

	printf("\n***RIGHT SUM***\n");
	integral = sumRight(start, finish, square);
	printf("Integral of fx from %lf to %lf is about %lf\n", start, finish, integral);

	printf("\n***CENTER SUM***\n");
	integral = sumCenter(start, finish, square);
	printf("Integral of f(x) from %.2lf to %.2lf is about %.4lf\n\n", start, finish, integral);


}

double sumMonteCarlo(double start, double finish, double f(double))
{
	double fValues[NUM_OF_TRIALS];
	double min = f(start);
	double max = f(start);
	double x;

	for(int i = 0; i < NUM_OF_TRIALS; ++i)
	{
		x = ( (double)rand()/RAND_MAX * (finish - start)) + start;
		fValues[i] = f(x);
		if(fValues[i] < min)
		{
			min = fValues[i];
		}
		if(fValues[i] > max)
		{
			max = fValues[i];
		}
		// printf("x: %f\tf(x): %f\n", x, fValues[i]);
	}

	double countHits = 0;
	double y;
	for(int i = 0; i < NUM_OF_TRIALS; ++i)
	{
		y = ( (double)rand()/RAND_MAX * (max - min) ) + min;
		if (y <= fValues[i])
		{
			++countHits;
		}
	}

	// printf("start: %f\nfinish: %f\nmin: %f\nmax: %f\ncountHits: %f", start, finish, min, max, countHits);
	return ((finish - start) * min) + (finish - start) * (max - min) * (countHits / NUM_OF_TRIALS);

}

double sumLeft(double start, double finish, double f(double))
{
	double x = start;
	double sum = 0.0;
	double epsilon = (finish - start) / NUM_OF_TRIALS;


	for(int i = 0; i < NUM_OF_TRIALS - 1; ++i)
	{
		sum += f(x);
		x += epsilon;
	}
	
	return sum * epsilon;
}

double sumRight(double start, double finish, double f(double))
{
	double x = start;
	double sum = 0.0;
	double epsilon = (finish - start) / NUM_OF_TRIALS;



	for(int i = 0; i < NUM_OF_TRIALS; ++i)
	{
		x += epsilon;
		sum += f(x);
	}
	
	return sum * epsilon;
}

double sumCenter(double start, double finish, double f(double))
{
	double x = start;
	double sum = 0.0;
	double epsilon = (finish - start) / NUM_OF_TRIALS;


	for(int i = 0; i < NUM_OF_TRIALS; ++i)
	{
		sum += f(x + (epsilon/2) );
		x += epsilon;
	}
	
	return sum * epsilon;
}