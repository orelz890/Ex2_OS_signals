#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>


int sock;

void sig_handler(int signum)
{
	int i=5;
	int j=0;
	int k;
    int *p = NULL;
    char buf[10];
    int *iptr;
    char *cptr;
    FILE * f;
	switch (signum) {
		case SIGCHLD:
			printf("I am in SIGCHLD\n");
			fflush(stdout);
			raise(SIGUSR1);
		case SIGUSR1: 
			printf("I am in SIGUSR1\n");
			fflush(stdout);
			k=i/j;
		case SIGFPE:
			printf("I am in SIGFPE\n");
			fflush(stdout);
            *p = 25;
        case SIGSEGV:
            printf("I am in SIGSEGV\n");
            fflush(stdout);
            abort();
        case SIGABRT:
            printf("I am in SIGABRT\n");
            fflush(stdout);
            char s[] = "123";
            s[0] = 3;
        case SIGTERM:
            printf("I am in SIGTERM\n");
            fflush(stdout);
            alarm(0);
        case SIGALRM:
            printf("I am in SIGALRM\n");
            fflush(stdout);
            send(sock, buf,sizeof(buf), 0);
        case SIGPIPE:
        // taken from: https://en.wikipedia.org/wiki/Bus_error
            printf("I am in SIGPIPE\n");
            fflush(stdout);
            cptr = malloc(sizeof(int)+1);
            iptr = (int*) ++cptr;
            *iptr = 42;
        case SIGBUS:
            printf("I am in SIGBUS\n");
            fflush(stdout);
            asm("int3");
        case SIGTRAP:
            printf("I am in SIGTRAP\n");
            fflush(stdout);
            kill(getgid(), SIGPOLL);
        case SIGPOLL:
            printf("I am in SIGPOLL\n");
            fflush(stdout);
            raise(SIGILL);
        case SIGILL:
            printf("I am in SIGILL\n");
            fflush(stdout);
            exit(1);
    }
}

void sig_handler2(int signum)
{
	printf("I am in sighandler2222\n");
	fflush(stdout);
	exit(1);
}

int main()
{
    int sigs[] = {SIGCHLD, SIGUSR1, SIGFPE,SIGSEGV, SIGABRT, SIGTERM, SIGALRM, SIGPIPE, SIGBUS, SIGTRAP,SIGPOLL, SIGILL};
    sock = socket(AF_INET,SOCK_STREAM, 0);
	int status;
    for (int i = 0; i < sizeof(sigs)/sizeof(int); i++){
        signal(sigs[i], sig_handler);
    }
	if (!(fork())) {
		exit(1);
	}
	wait(&status);

}