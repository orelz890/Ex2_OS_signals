#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int signals_list[] = {SIGCHLD,SIGUSR1,SIGFPE,SIGSEGV,SIGHUP, SIGINT,SIGQUIT,SIGILL,SIGTRAP,SIGABRT,SIGUSR2};
int sleep_time = 0;
int zero = 0;
int not_zero = 10;
int result;
int status;

// struct sigaction sa2;
// struct sigaction sa3;
// struct sigaction sa4;
// struct sigaction sa5;
// struct sigaction sa6;

void sig_handler(int signum);

int current_case = 0;

void print_signal_message(int signum){
	// sleep(1);
	switch (signum){
	case SIGCHLD:
	    write(STDOUT_FILENO, "I am in signal_SIGCHLD\n",23);
		break;
	case SIGUSR1:
	    write(STDOUT_FILENO, "I am in signal_SIGUSR1\n",23);
		break;
	case SIGFPE:
		write(STDOUT_FILENO,"I am in signal_SIGFPE\n",23);
		break;
	case SIGSEGV:
	    write(STDOUT_FILENO,"I am in signal_SIGSEGV\n",23);
		break;
	case SIGHUP:
	    write(STDOUT_FILENO,"I am in signal_SIGHUP\n",23);
		break;
	case SIGINT:
	    write(STDOUT_FILENO,"I am in signal_SIGINT\n",23);
		break;
	default:
		break;
	}
}

int next_signal(){
    current_case += 1;
    current_case %= 5;
    return current_case;
}

void sig_handler(int signum){

    print_signal_message(signum);
    signal(signum,sig_handler);
    sleep_time = sleep(1);
    int sig = next_signal();
    int *p = NULL;
    switch (sig){
        case 0:
            kill(getpid(),signum);
            break;
        case 1:
            raise(SIGINT);
            break;
        case 2:
            // result = not_zero/zero;
            raise(SIGFPE);
            break;
        case 3:
            kill(getpid(), signum);
            break;
        case 4:
            // *p = 25;
            raise(SIGSEGV);
            break;
        default:
            kill(getpid(),signum);
            break;
    }
    printf("Still waiting!\n");
    fflush(stdout);
    // pause();
    // signal(signum, SIG_DFL);
    // kill(getpid(),signum);

}


int main(){
    
    signal (SIGCHLD, sig_handler);
    signal (SIGUSR1, sig_handler);
    signal (SIGFPE, sig_handler);
    signal (SIGSEGV, sig_handler);
    signal (SIGHUP, sig_handler);
    signal (SIGINT, sig_handler);
    if (!(fork())) {
        exit(1);
    }
    wait(&status);
    // raise(SIGCHLD);
    // while (1){
    //     printf("hesdvv\n");
    //     sleep(1);
    // }

}
