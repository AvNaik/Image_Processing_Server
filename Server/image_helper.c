#include "image_helper.h"

void send_image(uint32_t fd, char *buf, size_t len, uint32_t toConnfd)
{
	uint32_t status = 0;
	uint32_t fileSize = Lseek(fd, 0, SEEK_END);
	Lseek(fd, 0, SEEK_SET);
	do
	{
		fileSize -= status;
		Write(toConnfd, buf, status);
		usleep(500);
		//printf("remaining: %d\n", fileSize);
	}while(((status = Read(fd, buf, len)) > 0) && fileSize);
}

void recv_image(uint32_t fd, char *buf, size_t len, uint32_t fromConnfd, uint32_t fileSize)
{
	uint32_t n = 0;
	do
	{
		n = Read(fromConnfd, buf, 256);
		Write(fd, buf, n);
		fileSize -= n;
		//printf("remaining: %d\n", fileSize);
	}while((n > 0) && fileSize);
}

uint32_t readImageFileSize(uint32_t fromConnfd)
{
	uint32_t fileSize;
	uint32_t ret = Read(fromConnfd, &fileSize, sizeof(fileSize));
	//printf("fileSize red is %d (%d bytes) \n", fileSize, ret);
	return fileSize;
}

uint32_t readImageFileType(uint32_t fromConnfd)
{
	uint32_t fileType;
	uint32_t ret = Read(fromConnfd, &fileType, sizeof(fileType));
	//printf("fileType red is %d (%d bytes) \n", fileType, ret);
	return fileType;
}

void writeImageFileSize(uint32_t toConnfd, uint32_t fileSize)
{
	uint32_t ret = Write(toConnfd, &fileSize, sizeof(fileSize));
	//printf("fileSize written is %d (%d bytes)\n", fileSize, ret);
}

void writeImageFileType(uint32_t toConnfd, uint32_t fileType)
{
	uint32_t ret = Write(toConnfd, &fileType, sizeof(fileType));
	//printf("fileType written is %d (%d bytes)\n", fileType, ret);
}