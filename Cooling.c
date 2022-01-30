//Phys 352
//Malakai Johnson
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// T(t) = ExessTempurature * e^(-t/tao) + RoomTempurature
// dT/dt = -ExcessTempurature/tao * e^(-t/tao)
//tao is the Time for ExTemp to fall to 1/e of initial

// t += dt;
// rate = dT/dt = -r * (T - Troom);
// T += rate * dt;

void cooling(double objectTempurature, double roomTempurature, double rate)
{
	int time = 0;
	int timeStep = 1;
	while (time < 2700)
	{
		objectTempurature += -rate * (objectTempurature - roomTempurature) * timeStep;
		// printf("%d\t%lf\n", time, objectTempurature);
		time += timeStep;
		if(time % 60 == 0)
		{
			// printf("Time: %02d\tTempurature: %lf\n", time / 60, objectTempurature);
			printf("%d\t%lf\n", time / 60, objectTempurature);
		}
	}
}

void main()
{
	cooling(82.9, 21.6, 0.0004);	
}