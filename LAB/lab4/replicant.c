#include "dummy4.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXTAM 1000000 //tamany maxim per a la N.

int main(int argc, char* argv[]){

	int N = atoi(argv[1]);	
	char buffer[N];	//Aqui processarem el "temps".
	
	//Comprovem que sigui correcte el tamany del buffer.
	if(N > 0 && N <= MAXTAM){
		int x; 
		dummy_init(buffer, N);
		//robem el temps i el processem.
		while((x = read(0, &buffer, N)) > 0) 
			dummy_calc(buffer, x);
		dummy_end(); 
	}
	else {
		exit(-1);
	}
	
}

