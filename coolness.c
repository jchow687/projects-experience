#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double coolness(double T, double V);
// declaring the coolness variable //
double coolness(double T, double V){
	return 35.74 + (0.6215 * T) - (35.75 * pow(V, 0.16)) + (0.4275 * T * pow(V, 0.16));
}
// initializing the math function // 

int main(int argc, char *argv[]){ 

	if (argc > 3){
		printf("Usage: ./coolness [temperature] [wind speed]\n");
		return 1;
	}
	// if there are more than two arguments in the cmd line //
	// it will print out this error //
	
	double T = (argc > 1) ? atof(argv[1]) : -10.0; 
	double V = (argc > 2) ? atof(argv[2]) : 5.0;
	// assigns my first argument to T, and my second argument to T//
	
	if (T < -99 || T > 50 || V < 0.5) {
		printf("Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
		return 1;
	}

	double cool_result = coolness(T, V);

	if (argc == 3){
		printf("Temp\tWind\tCoolness\n%.1f\t%.1f\t%.1f\n", T, V, cool_result);
	}
	else if (argc == 2){
		printf("Temp\tWind\tCoolness\n");
		for(int i=5; i <= 15; i+=5){
			double cool_result = coolness(T, V);
			printf("%.1f\t%.1f\t%.1f\n", T, V, cool_result);
			V+=5;
		}
	}
	else if (argc == 1){
		printf("Temp\tWind\tCoolness\n");
		for (int T= -10; T <= 40; T+=10){
			for(int V=5; V <= 15; V+=5){
				cool_result = coolness(T, V);
				printf("%.1f\t%.1f\t%.1f\n", (double)T, (double)V, cool_result);				
			}
			if (T != 40){
				printf("\n");
			}
		}
		
	}
	return 0;	
	
}
