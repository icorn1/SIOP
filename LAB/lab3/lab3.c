#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "dummy3.h"

#define TEAMNAME "ixent.cornella"
#define ENIGMA2 "SIGSTOP"
#define BRONCEKEY "7a6c6"
//#define SILVERKEY "ab406"


int main(int argc, char* argv[]){
	

    if(argc != 3){
        printf("ERROR: Has d'introduir exactament DOS numeros: M i N.\n");
    }
    else{
	
	int M = atoi(argv[1]);
	int N = atoi(argv[2]);

        if(M <= 0 || N <= 0){
            printf("ERROR: Si us plau, introdueix unicament numeros, M i N (mes grans que 0).\n");
        }
        else{
            
      
    	signal(SIGUSR1, ready); 
	int acum = 0;
	
	int p[2];
	pipe(p);
	
	int fd = open("dummy.dat", O_RDONLY);
	dummy_checkfile(fd);
	
	int capitol = fork();
	if(capitol == 0){
	//redireccionar canal 0 i 1.
		dup2(fd, 0);
		dup2(p[1], 1);
		close(fd);
		close(p[0]);
		close(p[1]);
		
		execl("./capitol", "./capitol", NULL);
	}
	pause();
	close(fd); //no ens fa falta
	close(p[1]);
	
	
		for(int i = 0; i < M; i++){
			
	            int id = fork();
	            if(id == 0){
			dup2(p[0], 0);
			close(p[0]);
	                // execl
	             	execl("./replicant", "./replicant", argv[2], NULL);
	                  
	            }   
	            	
	 
	       }
	       int st;
     		while(waitpid(-1, &st, 0) > 0){
		if (WIFEXITED(st)) {
				int es = WEXITSTATUS(st);
				printf("Exit status was %d\n", es);
				acum += es;

			}
	       
	       }
	  
	       close(p[0]);
	       if(dummy_testing(acum, ENIGMA2, TEAMNAME, BRONCEKEY) == 0) exit(0);
	       else {
	       	printf("ERROR: NO s'ha pogut robar temps correctament. Missio fallida.\n");
	       	exit(-1);
	       }		      
             	   	
        }
     }
}