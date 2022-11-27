#include <stdio.h>
//#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
//#include <signal.h>
#include "dummy4.h"

#define SERVNAME "SIOP-server"
#define SERVADDR "147.83.159.200"
#define SERVPORT 9999
#define CTRLPORT 9900
#define TEAMNAME "ixent.cornella"
#define ENIGMA3 "07F4"
#define SILVERKEY "ab406"
#define GOLDKEY "" // use only for SIOP Challenge : insert GOLDKEY between ""
//0xdc146

int main(int argc, char* argv[]){
	
	//Comprovem que el nombre d'arguments introduits siguin correctes.
    if(argc != 3){
        printf("ERROR: Has d'introduir exactament DOS numeros: M i N.\n");
		exit(-1);
    }
	
	int M = atoi(argv[1]);  //M i N, representen els arguments introduits.
	int N = atoi(argv[2]);

	if(M <= 0 || N <= 0){
		//Mirem que siguin vàlids.
		printf("ERROR: Si us plau, introdueix unicament numeros, M i N (mes grans que 0).\n");
		exit(-1);
	}
	
	//on acumularem els codis d'exit dels replicants	
	int acum = 0;

	int ctrlfd = ctrlconnect(SERVADDR, CTRLPORT, ENIGMA3, TEAMNAME, SILVERKEY, GOLDKEY); //retorna el file descriptor del canal de control i verifica l'enigma i la clau
	int fd = connecta(SERVADDR, SERVPORT); //retorna el file descriptor del canal de dades

	//creem M replicants.
	for(int i = 0; i < M; ++i){
		
		int id = fork();
		if(id == 0){
			//redirigim els canals del replicant.
			dup2(fd, 0);
			close(fd);
			close(ctrlfd);
			// executem per cada replicant el codi per atacar el banc
			execl("./replicant", "./replicant", argv[2], NULL);
					
		}   
	}
	
	//esperem els replicants...
	int st;
	while(waitpid(-1, &st, 0) > 0){
		if (WIFEXITED(st)) {
			int es = WEXITSTATUS(st);
			//printf("Exit status was %d\n", es);
			acum += es;
		}
		else{
			printf("ERROR: 'N' unitats de temps son massa grans per poder-les robar-les. Redueix N.\n");
			while(wait(NULL) > 0); //ABORTEM MISSIO
		}
	}

	//Enviem acum al capitol, i rebem la seva resposta en funcio de si acum esta be o no.
	/*******sending acum to capitol *******************/
	char buf[10];
	int nbytes = sprintf (buf, "%d", acum);
	write(ctrlfd,buf,nbytes);

	/*******reading answer from Capitol **************/
	char buffy[128];
	int len = read(ctrlfd,buffy,128);
	buffy[len] = '\0';
	printf("MISSION: %s\n",buffy);		      
						
		
	
}
