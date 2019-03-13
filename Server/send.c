#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	uint32_t fd = open(argv[1], O_RDONLY);
	if(fd<0)
	{
		perror("Error in opening the input file");
		return fd;
	}

	uint32_t ret = 0;
	uint32_t fileSize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

	char *image = calloc(fileSize, sizeof(char));
	if(image == NULL)
		perror("Error allocating a buffer for image:");

	ret = read(fd, image, fileSize);
	if(ret < 0)
		perror("Error reading the input file:");

	/*Create a new file and dump earlier file into new file.*/
	uint32_t fd2 = open("output.jpg", O_WRONLY | O_CREAT , 0666);
	if(fd2 < 0)
		perror("Error in opening output file:");

	ret = write(fd2, image, fileSize);
	if(ret < 0)
		perror("Error writting into the output file:");
	close(fd2);
	close(fd);

	return 0;
}
