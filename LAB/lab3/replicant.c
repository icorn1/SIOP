#include "dummy3.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXTAM 1000000

int main(int argc, char* argv[]){

	int N = atoi(argv[1]);	
	char buffer[MAXTAM];
	
	if(N > 0 && N <= MAXTAM){
		int x; 
		dummy_init(buffer, N);
		while((x = read(0, &buffer, N)) > 0) 
			dummy_calc(buffer, x);
		dummy_end(); 
	}
	else {
		printf("ERROR: 'N' unitats de temps son massa grans per poder-les robar-les. Redueix N.\n");
		exit(-1);
	}
	
}

