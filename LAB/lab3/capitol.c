#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char* argv[]){
	
	kill(getppid(), SIGUSR1);
	
	char c;
	while (read(0, &c, 1) > 0) write(1, &c, 1);
	exit(0);
}