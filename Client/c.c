#include "csapp.h"
//#include <unistd.h>
#include "image_helper.h"

int main(int argc, char **argv)
{
	int clientfd;
	char *host, buf[MAXLINE];
	uint32_t reti = 0;

	if (argc < 5)
	{
		fprintf(stderr, "usage: %s <host> <port> <i/p_image_name.jpg> <o/p_image_name.jpg>\n", argv[0]);
		exit(0);
	}

	host = argv[1];
	clientfd = Open_clientfd(host, argv[2]);

//	char *ft = calloc(10, sizeof(char));
	enum fileType ipImageFileType;
	if(strstr(argv[3], ".jpg"))	//strstr is search substring in third argument//
		ipImageFileType = jpg;
	else if(strstr(argv[3], ".jpeg"))
		ipImageFileType = jpeg;
	else if(strstr(argv[3], ".png"))
		ipImageFileType = png;
	else
		ipImageFileType = gif;

	//open input image file
	uint32_t fd = open(argv[3], O_RDONLY, 0666);
	if(fd<0)
	{
		printf("%s:%d:", __func__, __LINE__);
		perror("Error in creating input file:");
		exit(fd);
	}

	/*Calculate input file size in bytes*/
	uint32_t fileSize = Lseek(fd, 0, SEEK_END);
	Lseek(fd, 0, SEEK_SET);

	/*Send file size*/
	writeImageFileSize(clientfd, fileSize);

	/*Send file type*/
	writeImageFileType(clientfd, ipImageFileType);

	int n = 0;

	/*Send file to server*/
	sleep(1);
	printf("Sending the image file to the server\n");
	send_image(fd, buf, 256, clientfd);
	Close(fd);

	/*Create an output file*/
	int fd2 = open(argv[4], O_WRONLY | O_CREAT , 0666);	//Read Write permissions....read write execute...first 6 is for root....then user...then execute//
	if(fd2 < 0)
	{
		printf("%s:%d:", __func__, __LINE__);
		perror("Error in creating output file:");
		exit(fd2);
	}
	memset(buf, 0, MAXLINE);

	/*Read the result of the conversion*/
	int result = 0;
	read(clientfd, &result, sizeof(result));
	if(result)
	{
		printf("BW image conversion failed at the server side. Closing the client.\n");
		return result;
	}

	/*Read the BW image file size*/
	fileSize = readImageFileSize(clientfd);

	/*Receive an image from Sever - B/W image*/
	recv_image(fd2, buf, 256, clientfd, fileSize);
	Close(fd2);
	Close(clientfd);

//Input given to execl to display the B/W image//
	if(Fork()==0)
	{
		char cgiargs[MAXLINE] = {0};

		sprintf(cgiargs, "%s#%s", argv[3], argv[4]);
		execl("cIPA/sample", "sample", cgiargs, NULL);
	}

	printf("Done.\n");
	exit(0);
}
