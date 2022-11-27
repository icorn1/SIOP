#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short enters(float a, float b){     //Fem un short ja que el resultat que retorna la funcio sera 0, 1, en funcio de si a i b son enters.
	
    short result;
    int _a = a/1;       //Divdim els numeros per 1 per veure si son enters o no, si no ho fossin, llavors el resultat es l'arrodoniment del 
    int _b = b/1;       //float al enter mes proper.

    if(_a != a && _b != b){
        //printf ("Els numeros %f i %f no son enters.", a, b);          // si els dos son iguals a l'operacio " x/1 ", no son enters
        result = 0;
    }
    else if (_a == a && _b != b){
       // printf ("El numero %d es enter, mentre que el numero %f no es enter.", _a, b);
        result = 0;
    }
    else if (_a != a && _b == b){
        //printf ("El numero %f no es enter, mentre que el numero %d es enter.", a, _b);
        result = 0;
    }
    else if(a > 0 && b > 0){
    	printf ("Els dos numeros %d i %d son enters mes grans que 0.\n", _a, _b);
    	result = 1;
    }
    else{
    	result = 0;
    }
    
    return result;
}

int main(int argc, char *argv[]){

    float num1, num2;       //Variables que introduira el usuari 

    char resposta[10];      //Resposta del usuari si vol seguir el programa

    if(argc != 3){
        printf("ERROR: Has d'introduir exactament DOS numeros, el programa et dira si son enters o no.\n");
    }
    else{

        num1 = atof(argv[1]);
        num2 = atof(argv[2]);

        if(num1 <= 0 || num2 <= 0){
            printf("ERROR: Si us plau, introdueix unicament numeros (mes grans que 0)\n");
        }
        else{
	     
            short valid = enters(num1, num2);
            
            if(valid){

                int valor;
            	
            	for(int i = 0; i < num1; i++){
                    int id = fork();
                    if(id == 0){

                        valor = num2;
                        printf("El meu valor es %d.\n", valor);
                        exit(0);

                    }
                }
            	
            }
            else{
            
            	printf("ERROR: Introdueix NOMES nombres enters mes grans que 0.\n");
            	
            	exit(-1);
            }
        
        }

    }
        
}

/* 
   Una mutació equivaldria a la comanda "execlp", cada fill tindria
   la capacitat de canviar els parametres de la comanda execlp, i per tant,
   canviar el seu codi, dit d'una altra manera, mutar.
*/