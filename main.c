#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void sighandler(int sig){
  if (sig == SIGUSR1){
    printf("Parent pid: %d\n", getppid());
		sleep(1);
	}

  else if (sig == SIGINT){
		int file = open("file.txt", O_WRONLY | O_CREAT , 0666);

		if (file < 0) {
			printf("Error num: %d in open, %s\n", errno, strerror(errno));
			exit(1);
    }

		write(file, "Program exited due to SIGINT", 28);
		close(file);
		exit(0);
	}
}

int main(){
	signal(SIGUSR1, sighandler);
	signal(SIGINT, sighandler);

	while(1){
		printf("PID of this process: %d\n", getpid());
		sleep(1);
	}

	return 0;
}
