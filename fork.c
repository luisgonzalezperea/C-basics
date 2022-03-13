int main(int argc, char  *argv[])
{
    int pid;
    pid = fork();

    switch (pid)
    {
        case -1:
            exit(-1);
        case 0:
            printf("Child process\n");
        default:
            sleep (2);
            printf("Parent process\n");
    }
}