#include "q.h"
//#include <unistd.h>
//#include <stdlib.h>
//#include <stdio.h>

int qSize = 5;

queue *queueInit (int size)
{
	queue *q;
//inistialize the equeue//
	q = (queue *)malloc (sizeof (queue));
	if (q == NULL) return (NULL);

	QUEUESIZE(q) = size;
	q->empty = 1;
	q->full = 0;
	q->head = 0;
	q->tail = 0;
	q->buf = (int *)calloc(QUEUESIZE(q), sizeof(int));
	q->mut = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t));
	pthread_mutex_init (q->mut, NULL);
	q->notFull = (pthread_cond_t *) malloc (sizeof (pthread_cond_t));
	pthread_cond_init (q->notFull, NULL);
	q->notEmpty = (pthread_cond_t *) malloc (sizeof (pthread_cond_t));
	pthread_cond_init (q->notEmpty, NULL);

	return (q);
}
//Tail is 0 on queue initialization//
void queueDelete (queue *q)
{
	pthread_mutex_destroy (q->mut);
	free (q->mut);	
	pthread_cond_destroy (q->notFull);
	free (q->notFull);
	pthread_cond_destroy (q->notEmpty);
	free (q->notEmpty);
	free (q);
}

void queueEnq (queue *q, int in)
{
	q->buf[q->tail] = in;
	q->tail = (q->tail+1)%QUEUESIZE(q);
	if (q->tail == q->head)
	{
		q->full = 1;
		printf("Q Full\n");
	}
	q->empty = 0;

	return;
}

void queueDeq (queue *q, int *out)
{
	*out = q->buf[q->head];

	q->head = (q->head+1)%QUEUESIZE(q);
	if (q->head == q->tail)
	{
		q->empty = 1;
		printf("Q Empty\n");
	}
	q->full = 0;

	return;
}
