#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define GRAV_CONST 39.478 //?
#define DELTA_TIME 1.0e-4 // in years
#define END_TIME 1 // in years


// m mass in units of solar masses, Sun is one, earth is like 3e-6 or so.
#define NUM_OF_CELESTIALS 3  //Number of things in our solar system we wish to track.
const double distances[NUM_OF_CELESTIALS]={0.0, 1.0, 4.1};         // note we need to match NUM_OF_CELESTIALS things, defined above.
const double masses[NUM_OF_CELESTIALS] = {1.0, 3.3e-6, 1.1e-6};

struct Celestial{  //celestial object structure; Sun will be object 0, planets are 1,2,3 but we could use for moons, asteriods, etc.
	double position[2]; // in uniits of AU
	double velocity[2]; // in units of AU per year
	double acceleration[2]; // in units of AU per year^2
	double mass;// in units of solar masses, Sun is one, earth is like 3e-6 or so.

};

void printCelestial(struct Celestial celestial)
{
	printf("Position:\t%lg, %lg\n", celestial.position[0], celestial.position[1]);
	printf("Velocity:\t%lg, %lg\n", celestial.velocity[0], celestial.velocity[1]);
	printf("Acceleration:\t%lg, %lg\n", celestial.acceleration[0], celestial.acceleration[1]);
	printf("Mass:\t%lg\n", celestial.mass);
}

void printAllCelestials(struct Celestial* celestials, int numCelestials)
{
	for(int i = 0; i < numCelestials; ++i)
	{
		printf("Celestial %d\n", i);
		printCelestial(celestials[i]);
	}
}

int initCelestials(struct Celestial* celestial, int i)
{
	double period; //period of orbit

	celestial->position[0] = distances[i];
	celestial->position[1] = 0.0;

	period = sqrt(celestial->position[0]*celestial->position[0]*celestial->position[0]); // This assumes the Sun's mass is one!
	celestial->velocity[0]=0.0;
	if(period > DELTA_TIME)
	{
		celestial->velocity[1]=2.0*M_PI*distances[i]/period;
	}
	else
	{
		celestial->velocity[1] =  0.0; //its so small.
	}

	celestial->acceleration[0] = 0.0;
	celestial->acceleration[1] = 0.0;

	celestial->mass = masses[i];
}

double getMagnitude(double vector[2])
{
	return sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]));
}

void normalize(double vector[2])
{
	double magnitude = getMagnitude(vector);
	vector[0] = vector[0] / magnitude;
	vector[1] = vector[1] / magnitude;
}

void gravitationalForce(double forceVector[2], struct Celestial object1, struct Celestial object2)
{
	double direction[2], magnitude, distance;

	direction[0] = object2.position[0] - object1.position[0];
	direction[1] = object2.position[1] - object1.position[1];

	distance = getMagnitude(direction);

	normalize(direction);

	magnitude = (GRAV_CONST * object1.mass * object2.mass) / (distance * distance);

	forceVector[0] = direction[0] * magnitude;
	forceVector[1] = direction[1] * magnitude; 
}

void updateAcceleration(struct Celestial* system, int i, int numCelestials)
{
	system[i].acceleration[0] = 0;
	system[i].acceleration[1] = 0;


	for(int j = 0; j < numCelestials; ++j)
	{
		if(j == i)
			continue;

		double forceVector[2];
		gravitationalForce(forceVector, system[i], system[j]);
		system[i].acceleration[0] += forceVector[0] / system[i].mass;
		system[i].acceleration[1] += forceVector[1] / system[i].mass;
	}
}

void updateVelocity(struct Celestial* celestial)
{
	celestial->velocity[0] += celestial->acceleration[0] * DELTA_TIME;
	celestial->velocity[1] += celestial->acceleration[1] * DELTA_TIME;
}

void updatePosition(struct Celestial* celestial)
{
	celestial->position[0] += celestial->velocity[0] * DELTA_TIME;
	celestial->position[1] += celestial->velocity[1] * DELTA_TIME;
}

void orbits1(struct Celestial* celestials)
{ //Only updates celectials[1] (i.e. Earth)
	for(int t = 0; t < END_TIME; t += DELTA_TIME)
	{
		updateAcceleration(celestials, 1, 2);
		updateVelocity(&celestials[1]);
		updatePosition(&celestials[1]);

		printf("%f,%f", celestials[1].position[0], celestials[1].position[1]);

		printf("\n");
	}

}

void orbits2(struct Celestial* celestials)
{ //does not update celectials[0] (i.e. the sun)
	for(int t = 0; t < END_TIME; t += DELTA_TIME)
	{
		for(int i = 1; i < NUM_OF_CELESTIALS; ++i)
		{
			updateAcceleration(celestials, i, NUM_OF_CELESTIALS);
		}
		for(int i = 1; i < NUM_OF_CELESTIALS; ++i)
		{
			updateVelocity(&celestials[i]);
		}
		for(int i = 1; i < NUM_OF_CELESTIALS; ++i)
		{
			updatePosition(&celestials[i]);
		}

		for(int i = 0; i < NUM_OF_CELESTIALS; ++i)
		{
			printf("%f,%f\t", celestials[i].position[0], celestials[i].position[1]);
		}
		printf("\n");
	}
}

void orbits3(struct Celestial* celestials)
{ //Updates all celestials
	for(double t = 0; t < END_TIME; t += DELTA_TIME)
	{
		for(int i = 0; i < NUM_OF_CELESTIALS; ++i)
		{
			updateAcceleration(celestials, i, NUM_OF_CELESTIALS);
		}
		for(int i = 0; i < NUM_OF_CELESTIALS; ++i)
		{
			updateVelocity(&celestials[i]);
		}
		for(int i = 0; i < NUM_OF_CELESTIALS; ++i)
		{
			updatePosition(&celestials[i]);
		}

		for(int i = 0; i < NUM_OF_CELESTIALS; ++i)
		{
			// printf("%f,%f\t", celestials[i].position[0], celestials[i].position[1]);
		}
		// printf("fmod(t, DELTA_TIME): %lg\n", fmod(t, DELTA_TIME));
		// printf("\nt: %lg\n", t);
		// printf("t/DELTA_TIME: %lg\n", t/DELTA_TIME);
		// printf("t/DELTA_TIME MOD 100: %d\n", (int)(t/DELTA_TIME) % 100);
		if( (int)(t/DELTA_TIME) % 1000 == 0)
		{
			printf("\nt = %lg\n", t);
			printCelestial(celestials[1]);
			// printAllCelestials(celestials, NUM_OF_CELESTIALS);
		}
	}
}


void main(int argc, char **argv)
{
	struct Celestial celestials[NUM_OF_CELESTIALS];
	for(int i = 0; i < NUM_OF_CELESTIALS; ++i)
	{
		printf("Celestial %d\n", i);
		initCelestials(&celestials[i], i);
		printCelestial(celestials[i]);
	}

	int assignment;

	if(argc < 2)
	{
		assignment = 3;
	}
	else
	{
		assignment = atoi(argv[1]);
	}

	switch(assignment)
	{
		case 1:
			orbits1(celestials);
			break;
		case 2:
			orbits2(celestials);
			break;
		case 3:
			orbits3(celestials);
			break;
	}

}
