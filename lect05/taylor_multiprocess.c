#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define N 4

void sinx_taylor(int a, int terms, double* x, double* result){
	int fd[2*N],pid;
	int child_id;
	char message[100],line[100];

	for(int i=0;i<a;i++){
		pipe(fd+ 2*i);
		child_id = i;
		pid = fork();
		
		if(pid==0){
			break;
		}else{
			close(fd[2*i+1]);
		}
	}

	if(pid == 0){
		int i = child_id;
		close(fd[i*2]);

		double value = x[i];
		double numer = x[i]*x[i]*x[i];
		double denom = 6;
		int sign = -1;

		for(int j=1; j<terms; j++){
			value += (double)sign*numer/denom;
			numer *= x[i]*x[i];
			denom *= (2*(double)j+2)*(2*(double)j+3);
			sign*=-1;
		}
		//result[i] = value;
			
		sprintf(message, "%lf", value);
		int length = strlen(message)+1;
		write(fd[2*i+1], message, length);
		exit(child_id);
	}else{	
		for(int i=0; i<a;i++){
			int status;
			wait(&status);
			int c_id = status >> 8;
			read(fd[2*c_id],line,100);
			result[c_id] = atof(line);
		}
	}
}

int main()
{
	int pid;
	double x[N] = {0, M_PI/6., M_PI/3., 0.134};
	double res[N];

	sinx_taylor(N,3,x,res);
	for(int i=0; i<N;i++){
		printf("sin(%.2f) by Taylor series = %f\n", x[i],res[i]);
	}

	return 0;
}
