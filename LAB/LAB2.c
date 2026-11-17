#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handleSignal(int sig)
{
    printf("\nCtrl+C pressed!\n");
    printf("SIGINT signal received and handled.\n");
}

int main()
{
    pid_t pid;
    int status;

    /* Event Handling - Signal */
    signal(SIGINT, handleSignal);

    printf("Parent Process Started\n");
    printf("Parent PID = %d\n", getpid());

    /* Creation - Fork */
    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }

    /* Child Process */
    if (pid == 0)
    {
        printf("\nChild Process Created\n");
        printf("Child PID = %d\n", getpid());

        /* Program Execution - Execlp */
        printf("Executing ls using execlp...\n");

        execlp("ls", "ls", "-l", NULL);

        /* Executes only if execlp fails */
        perror("execlp failed");

        /* Child Termination */
        _exit(1);
    }

    /* Parent Process */
    else
    {
        printf("\nParent is waiting for child...\n");

        /* Child Process Handling - wait */
        wait(&status);

        if (WIFEXITED(status))
        {
            printf("\nChild terminated normally.\n");
            printf("Child exit status = %d\n", WEXITSTATUS(status));
        }

        printf("\nPress Ctrl+C to test signal handling.\n");
        sleep(10);

        printf("\nParent Process Terminated.\n");
    }

    return 0;
}