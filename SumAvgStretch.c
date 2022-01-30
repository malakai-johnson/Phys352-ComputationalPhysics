#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LONG 999
int main()
{
	char line[LONG];
	int inp, i, total;
	int low, high;
	int[10000] values;
	i=0;
	total=0;  //if you do not set these to zero, they may start as random numbers!
	printf("Enter numbers to be averaged, hitting enter after each one, and just hit enter to end.\n");
	fgets(line, LONG, stdin);
	if(strlen(line)>1){
		inp = atoi(line);
		low = inp;
		high = inp;
		++i;
		total += inp;
	}
	do{
		fgets(line, LONG, stdin); //stdin is the standard input stream. Could be your keyboard.
		if(strlen(line)>1){
			inp  = atoi(line);	
			i++; // same as i = i + 1
			total += inp; // same as total = total + inp 
			if ( inp < low){
				low = inp;
			}
			if ( inp > high){
				high = inp;
			}
		}
	}while(strlen(line)>1); // if the length is greater than just one character, keep going
	printf("Got a total of %i integers, and %lf is the average.\n", i, (double) total/i);
	if(i > 3){
		printf("%i was the Highest and %i was the Lowest. Ignoring those two,  %lf is the average.\n", high, low, (double) (total - (high + low))/(i-2) );
	}
}
