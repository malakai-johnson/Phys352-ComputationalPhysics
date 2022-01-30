#include <stdio.h>

void simFalling(double mass/*in grams*/, double resistenceConstant, double height/*in cm*/){
	
	double gravityConstant = 9.8*100;//in cm/s^2
	double timeStep = 0.001; //in seconds

	double time = 0; //in seconds
	double velocity = 0; //in cm/2
	double acceleration = 0; //in cm/s^2

	printf("\n**START SIM**\nMass: %lf\tResistenceConstant: %lf\tHeight: %lf\n", mass, resistenceConstant, height);

	int step = 0;
	while(height > 0){
		acceleration = ((resistenceConstant/mass)*(velocity*velocity)) - gravityConstant;
		velocity = velocity + (acceleration*timeStep);
		height = height + (velocity*timeStep);
		time = time + timeStep;
		if (step % 100 == 0){
			printf("Time: %lf\tHeight: %lf\n", time, height);
		}
		step++;
	}

	printf("Time: %lf\tHeight: %lf\n**End SIM**\n\n", time, height);
}

void main()
{
	simFalling(0.96, 0, 100); //Theoretical coffee filter
	simFalling(0.96, 0.098, 100); //Single coffee filters
	simFalling(3.70, 0.098, 100); //Nested coffee filter
}

/*
Experimental times for dropping coffee filters 1 meter:
	at 0.96g
		1.09
		1.15
		1.00
		1.08
		1.12
		1.08
		1.12
		1.10
		1.05
		1.05
	Average 1.09

at 3.7g
	.63
	.61
	.65
	.63
	.63
	Average 0.63
*/