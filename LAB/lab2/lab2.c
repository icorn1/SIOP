
#include <stdio.h>
#include <stdlib.h>
#include "dummy2.h"


#define TEAMNAME "ixent.cornella"
#define ENIGMA1 "FFEE"
//BRONCEKEY: 7a6c6  [Keep save this key]


short enters(float a, float b){     //Fem un short ja que el resultat que retorna la funcio sera 0, 1, en funcio de si a i b son enters.
	
    short result;
    int _a = a/1;       //Divdim els numeros per 1 per veure si son enters o no, si no ho fossin, llavors el resultat es l'arrodoniment del 
    int _b = b/1;       //float al enter mes proper.

    if(_a != a && _b != b){
        // si els dos son iguals a l'operacio " x/1 ", no son enters
        result = 0;
    }
    else if (_a == a && _b != b){
        result = 0;
    }
    else if (_a != a && _b == b){
        result = 0;
    }
    else if(a > 0 && b > 0){
    	result = 1;
    }
    else{
    	result = 0;
    }
    
    return result;
}

int main(int argc, char* argv[]){
	

    if(argc != 3){
        printf("ERROR: Has d'introduir exactament DOS numeros: M i N.\n");
    }
    else{
	
	float num1 = atof(argv[1]);
	float num2 = atof(argv[2]);

        if(num1 <= 0 || num2 <= 0){
            printf("ERROR: Si us plau, introdueix unicament numeros, M i N (mes grans que 0).\n");
        }
        else{
	     	
            short valid = enters(num1, num2);
            
            if(valid){

                int M = num1;
                int N = num2;
                
                char buffer[256];
		
		int fd = dummy_open(); // obrim dummy.
		int acum = 0;
		
		char error = 0;
		if(sizeof(buffer) < N) {
                	printf("ERROR: 'N' unitats de temps son massa grans per poder-les robar-les. Redueix N.\n");
                	error = 1;
             

                }
		
		close(0);
		dup(fd);
		close(fd);
		
		if(!error){
			for(int i = 0; i < M; i++){
				
		            int id = fork();
		 
		            if(id == 0){

		                // comprovacions inicials //array 2000-> bloc < 2000 
		                
		                dummy_init(buffer, N);
		                int x; 
		                do{
		                	x = read(0, buffer, N);
		                	dummy_comp(buffer, x);
		                } while (x > 0);
		                 //bytesllegits = read
		        
		                dummy_exit();
		                
		            }
		        
		            
		       }
		       int st;
		       while(waitpid(-1, &st, 0) > 0){
		       	if ( WIFEXITED(st)) {
				int es = WEXITSTATUS(st);
				//printf("Exit status was %d\n", es);
				acum += es;
			
				}
			

		       	else printf("ERROR: NO s'ha pogut robar temps correctament. Missio fallida.\n");
		       }
		       
		       
		       dummy_test(acum, ENIGMA1, TEAMNAME); 
		       dummy_exit();
                
             	   }
             }
		
		else{
            
            		printf("ERROR: Introdueix NOMES nombres enters mes grans que 0.\n");
            	
            		exit(-1);
            	}	
        }
     }
}