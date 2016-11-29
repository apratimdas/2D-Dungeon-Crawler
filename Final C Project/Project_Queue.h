
#pragma once

#ifndef _PROJECT_QUEUE_H_
#define _PROJECT_QUEUE_H_

#define _CRT_SECURE_NO_WARNINGS_

#include "Project_Monster.h"

typedef struct QueueNode {
	monster *data;
	struct QueueNode *next;
} qnode;

typedef struct Queue {
	qnode *first;
	qnode *last;
} queue;

queue* q_new(void);
void q_insert(queue **myqueue, monster *data);
monster* q_dequeue(queue **myqueue);
int q_delete(queue **myqueue);

#endif // _PROJECT_QUEUE_H_