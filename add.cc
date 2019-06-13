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

int a_m_fifo, m_a_fifo;

// rewrite the ctrl-C signal
void ouch(int) {
	close(a_m_fifo);
	close(m_a_fifo);
	unlink(FIFO_A_M);
	printf("\nEnd add process\n");
	exit(0);
}

int main()
{
	signal(SIGINT, ouch);

	if(mkfifo(FIFO_A_M, 0666) == -1) {
		printf("Creat A FIFO_M_A error!\n");
		printf("%s\n",strerror(errno));
		return -1;
	}

	a_m_fifo = open(FIFO_A_M, O_WRONLY);
	m_a_fifo = open(FIFO_M_A, O_RDONLY);

	while(true) {
		int num[2];
		int res;
		read(m_a_fifo, num, sizeof(num));	// read two num from main2add FIFO
		res = num[0] + num[1];
		write(a_m_fifo, &res, sizeof(res));	// write the result to add2main FIFO
	}

	return 0;
}
