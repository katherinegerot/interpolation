/**
 * Author: Katherine Gerot
 * Date: October 9, 2019
 *
 * Hermite Divided Differences for Table 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char **argv) {
	int n = 5;
	double sum, p = atof(argv[1]);
	
	double x[] = {-2, -1, 0, 1, 2};
	double f[] = {3.230639, -0.730600, -0.633970, 0.586080, 12.03208};
	double fp[] = {-9.97685, -0.440230, 0.144338, 3.812855, 22.60286};
	double z[(2*n)+1];
	double Q[(2*n)+1][(2*n)+1];
	
	for(int i = 0; i < 2*n + 1; i++) {
		z[i] = 0;
		for(int j = 0; j < 2* n + 1; j++) {
			Q[i][j] = 0;
		}
	}
	
	//Hermite Divided Differences
	//initializing
	for(int i = 0; i < n; i++) {
		z[(2*i)+1] = x[i];
		Q[(2*i)][0] = f[i];
		Q[(2*i)+1][1] = fp[i];
		if(i != 0) {
			Q[(2*i)][1] = (Q[(2*i)][0] - Q[(2*i)+1][0]) / (z[(2*i)] - z[(2*i)-1]);
			printf("%lf\n", Q[2*i][1]);
		}
	}
	printf("%g\n", Q[0][0]);
	
	//continuing with approximation
	for(int i = 2; i < ((2*n) + 1); i++) {
		for(int j = 2; j <= i; j++) {
			Q[i][j] = (Q[i][j-1] - Q[i-1][j-1]) / (z[i] - z[i-j]);
			printf("%8.4lf ", Q[i][j]);
		}
		printf("\n");
	}
	
	//Polynomial
	double approx = Q[0][0];
	for(int i = 2; i < 2*n + 1; i++) {
		double product = 1;
		for(int j = 0; j < i - 2; j++) {
			product *= p - x[j - 1];
		}
		approx += product * Q[i][i] * (p - x[n-1]);
	}
	
	printf("x = %g ~= %g\n", p, approx);
	
	return 0;
}