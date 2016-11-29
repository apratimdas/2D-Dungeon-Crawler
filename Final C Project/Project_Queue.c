
#include "Project_Queue.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 
 */

queue* q_new(void) {
	return ( (queue*)malloc(sizeof(queue)) );
}

void q_insert(queue **myqueue, monster *data) {
	qnode *newnode = NULL; //
	qnode *tmp = NULL;

	newnode = (qnode*)malloc(sizeof(qnode));

	newnode->data = data;
	newnode->next = NULL;

	if ((*myqueue)->last == NULL) { // empty queue
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

int q_delete(queue **myqueue) {
	qnode *tmp = NULL;

	if ((*myqueue)->first == NULL && (*myqueue)->first == (*myqueue)->last) {
		// empty list;
		return 1;
	}
	
	while ((*myqueue)->first != NULL) {
		tmp = (*myqueue)->first;
		(*myqueue)->first = (*myqueue)->first->next;
		free(tmp);
	}

	(*myqueue)->first = (*myqueue)->last = NULL;
	free(*myqueue);
	*myqueue = NULL;

	return 0;
}
