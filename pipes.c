/* ----------------------------------------------------------------
Generic pipe system implementation (which is valid for n processes
and n-1 pipes)
---------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
    // I create pipe
    int fd[2];
    int ret, p10, status;
    pid_t pid;

    for (int i = 1; i < argc; i++)
    {
        // If it is not the last process, I create a pipe
        if (i != (argc-1))
        {
            // STEP 1: create pipe and check
            ret = pipe(fd);
            if (ret < 0)
            {
                perror("pipe: ");
                exit(-1);
            }

            // STEP 2: I do fork and check
            pid = fork();
            if (pid < 0)
            {
                perror("fork: ");
                exit(-1);
            }

            // STEP 3: redirections and STEP 4: cleanup
            if (pid == 0) // Child process
            {
                // If it is not the first process, input redirect
                if (i != 1)
                {
                    // Redirections
                    close(0);
                    dup(p10);
                    // Cleanup
                    close(p10);
                }
                // If not the last process, output redirection
                if (i != (argc-1))
                {
                    // Redirections
                    close(1);
                    dup(fd[1]);
                    // Cleanup
                    close(pd[0]);
                    close(pd[1]);
                }

                execlp(argv[i], argv[i], NULL);
                // If it continues to run, there has been an error
                perror("execlp: ");
                exit(-1);
            }

            else // Parent process
            {
                // If it is not the last process, we save pd[0] in p10
                if (i != (argc-1))
                {
                    // Cleanup
                    close(pd[1]);
                    p10 = pd[0];
                }
                // If it is the last process we save pd[0] in p10
                else
                {
                    close(pd[0]);
                }
            }
        }
    }
    
    // If it is a brackground process, comment the following line
    while (pid != wait(&status));

    return (0);
}
