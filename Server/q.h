#ifndef __Q_H__
#define __Q_H__

#include "csapp.h"

#define QUEUESIZE(a) (a->qSize)

typedef struct {
	int qSize;
	int *buf;
	long head, tail;
	int full, empty;
	pthread_mutex_t *mut;
	pthread_cond_t *notFull, *notEmpty;
} queue;

queue *queueInit (int);
void queueDelete (queue *q);
void queueEnq (queue *q, int in);
void queueDeq (queue *q, int *out);

#endif //__Q_H__
