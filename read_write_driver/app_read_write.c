#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char **argv)
{
	int fd;
	char c;
	if(argc < 2)
	{
		printf("Enter file to open as argument!\n");
		return 0;
	}
	fd = open(argv[1], O_RDWR);

	if(fd < 0)
	{
		perror("open");
		return fd ;
	}
	while(read(fd, &c, 1))
	{
		putchar(c);
	}

	close(fd);
}
