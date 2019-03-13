#ifndef __IMAGE_HELPER_H__
#define __IMAGE_HELPER_H__

#include "csapp.h"

enum fileType
{
	jpg,
	jpeg,
	png,
	gif
};

void send_image(uint32_t fd, char *buf, size_t len, uint32_t toConnfd);
void recv_image(uint32_t fd, char *buf, size_t len, uint32_t fromConnfd, uint32_t fileSize);
void writeImageFileSize(uint32_t toConnfd, uint32_t fileSize);
void writeImageFileType(uint32_t toConnfd, uint32_t fileSize);
uint32_t readImageFileName(uint32_t fromConnfd);
uint32_t readImageFileType(uint32_t fromConnfd);

#endif /*__IMAGE_HELPER_H__*/