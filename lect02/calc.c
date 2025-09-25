#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[]){
int num1 = atoi(argv[1]);
int num2 = atoi(argv[3]);

if(strcmp(argv[2], "+")==0){
	printf("%d\n", num1+num2);
}else if(strcmp(argv[2],"-")==0){
	printf("%d\n", num1-num2);
}else if(strcmp(argv[2],"x")==0){
	printf("%d\n", num1*num2);
}else if(strcmp(argv[2],"/")==0){
	printf("%d\n", num1/num2);
}

return 0;
}
