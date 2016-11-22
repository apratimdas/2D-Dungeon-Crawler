
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

void qinsert(queue **myqueue, monster **data);
int qdelete(queue **myqueue);

#endif // _PROJECT_QUEUE_H_