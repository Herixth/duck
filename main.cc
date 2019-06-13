#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define FIFO_M_A "./m_a_fifo" // A FIFO send data from main to add
#define FIFO_A_M "./a_m_fifo" // A FIFO send data from add to main

int pid, a_m_fifo, m_a_fifo;

// send signalInt to the add.out process
void ouch(int sig) {
	close(a_m_fifo);
	close(m_a_fifo);
	unlink(FIFO_M_A);
	kill(pid, SIGINT);
	printf("\nEnd main process\n");
	exit(0);
}

int main()
{
	signal(SIGINT, ouch);
	pid = fork();
	// creat a child process
	if(pid == 0) {
		execl("./add.out", "./add.out", NULL);
	}
	else {
		// must doing sleep, otherwise open will be blocked
		sleep(1);
		signal(SIGINT, ouch);
		if(mkfifo(FIFO_M_A, 0666) == -1) {
			printf("Creat A FIFO_M_A error!\n");
			printf("%s\n", strerror(errno));
			return -1;
		}
	
		a_m_fifo = open(FIFO_A_M, O_RDONLY);
		m_a_fifo = open(FIFO_M_A, O_WRONLY);

		while(true) {
			int num[2];
			int res;
			scanf("%d%d",num, num+1);
			write(m_a_fifo, num, sizeof(num));
			read(a_m_fifo, &res, sizeof(res));
			printf("res: %d\n", res);
		}
	}	
	return 0;
}
