#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int run = 1;
	char buf[5000];
	printf("First arg is: %s\n", argv[1]);
	int fd = open(argv[1], O_RDONLY);
	int newFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	printf("%d\n", fd);
	while(run)
	{
		int tmp = read(fd, &buf, 5000);
		if(tmp == 0)
		{
			run = 0;
		}
		write(newFile, &buf, tmp);

	}


	return 0;
}