#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "priority_levels.h"

typedef struct {
    HttpRequest *data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* create_queue(int initial_capacity);
void push_request(PriorityQueue *pq, HttpRequest req);
HttpRequest pop_request(PriorityQueue *pq);
void free_queue(PriorityQueue *pq);

#endif