#include <stdio.h>			
#include <sys/types.h>	
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buffer[BUFFER_SIZE]; // Buffer
	int fd1; // File descriptor
	int nb_read, nb_write;

	if(argc < 2)
	{
		printf("Not enough arguments\n");
		return (-1);
	}

	// Open the file
	fd1 = open(argv[1], O_RDONLY); 
	
	if (fd1 < 0) 
	{
		perror("open:");
		return (-1);
	}

	while ( (nb_read = read(fd1, buffer, BUFFER_SIZE)) > 0)
	{
		do
		{
			nb_write = write(STDOUT_FILENO, buffer, nb_read);
			if (nb_write < 0)
			{
				if (close(fd1) < 0)
				{
					perror("close:");
					return (-1);
				}
				perror("write:");
				return (-1);
			}
			nb_read -= nb_write;

		} while (nb_read > 0);
	}
	
	if (nb_read < 0)
	{
		perror("read:");
		if (close(fd1) < 0)
		{
			perror("close:");
		}
		return (-1);
	}

	close(fd1);
	return (0);
}
