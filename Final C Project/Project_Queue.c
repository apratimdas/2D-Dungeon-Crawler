
#include "Project_Queue.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * 
 */

// returns head of the queue
queue* q_new(void) {
	queue* tmp = (queue*)malloc(sizeof(queue));

	tmp->first = tmp->last = NULL;

	return tmp;
}

bool q_isEmpty(queue myqueue) {
	return (myqueue.last == NULL);
}

// inserts data ordered by speed
void q_insert(queue **myqueue, monster *data) {
	qnode *newnode = NULL; //
	qnode *tmp = NULL;

	newnode = (qnode*)malloc(sizeof(qnode));

	newnode->data = data;
	newnode->next = NULL;

	if (q_isEmpty(**myqueue)) { // empty queue
		(*myqueue)->last = newnode;
		(*myqueue)->first = (*myqueue)->last;
	}
	else {
		if ((*myqueue)->first->data->speed < data->speed) { // inserts at the start
			//(*myqueue)->last->next = newnode;
			//newnode->next = (*myqueue)->last;
			newnode->next = (*myqueue)->first;
			(*myqueue)->first = newnode;
		}
		else {
			if ((*myqueue)->last->data->speed > data->speed) {
				(*myqueue)->last->next = newnode;
				(*myqueue)->last = newnode;
			}
			else {
				tmp = (*myqueue)->first;

				while ((tmp->next) && (tmp->next)->data->speed >= data->speed) {
					tmp = tmp->next;
				}
				newnode->next = tmp->next;
				tmp->next = newnode;
			}
		}
	}
}

// cicles the queue without dequeuing and enqueuing for turn manipulation
monster* q_cicle_queue(queue **myqueue) {
	if (!q_isEmpty(**myqueue)) { // if not empty queue
		if (!((*myqueue)->first == (*myqueue)->last)) {
			(*myqueue)->last->next = (*myqueue)->first;
			(*myqueue)->first = (*myqueue)->first->next;
			(*myqueue)->last = (*myqueue)->last->next;
			(*myqueue)->last->next = NULL;
		}
	}
}

// adds to the end of the queue
void q_enqueue(queue **myqueue, monster *data) {
	qnode *newnode = NULL; //
	qnode *tmp = NULL;

	newnode = (qnode*)malloc(sizeof(qnode));

	newnode->data = data;
	newnode->next = NULL;

	if (q_isEmpty(**myqueue)) { // empty queue
		(*myqueue)->last = newnode;
		(*myqueue)->first = (*myqueue)->last;
	}
	else {
		(*myqueue)->last->next = newnode;
		(*myqueue)->last = newnode;
	}
}

// returns the first node (remember to free outside the function)
qnode* q_dequeue(queue **myqueue) {
	qnode* tmpnode = NULL;

	if (q_isEmpty(**myqueue)) {
		printf("Queue is Empty\n");
	}
	else {
		tmpnode = (*myqueue)->first;

		if ((*myqueue)->first == (*myqueue)->last) {
			(*myqueue)->first = (*myqueue)->last = NULL;
		}
		else {
			(*myqueue)->first = (*myqueue)->first->next;

			/*if ((*myqueue)->first == NULL) {
				(*myqueue)->first = (*myqueue)->last;
			}*/
		}
	}

	return tmpnode;
}

// frees whole queue
int q_delete(queue **myqueue) {
	qnode *tmp = NULL;

	if (!(*myqueue) || q_isEmpty(**myqueue)) {
		// empty list;
		return 1;
	}
	
	while ((*myqueue)->first != NULL) {
		tmp = (*myqueue)->first;
		(*myqueue)->first = (*myqueue)->first->next;
		free(tmp);
		tmp = NULL;
	}

	(*myqueue)->first = (*myqueue)->last = NULL;
	free(*myqueue);
	*myqueue = NULL;

	return 0;
}
