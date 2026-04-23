#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>

PriorityQueue* create_queue(int initial_capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->capacity = initial_capacity;
    pq->size = 0;
    pq->data = malloc(sizeof(HttpRequest) * initial_capacity);
    return pq;
}

void swap(HttpRequest *a, HttpRequest *b) {
    HttpRequest temp = *a;
    *a = *b;
    *b = temp;
}

void push_request(PriorityQueue *pq, HttpRequest req) {
    // Ölçeklenebilirlik için dinamik kapasite artırımı
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->data = realloc(pq->data, sizeof(HttpRequest) * pq->capacity);
    }

    pq->data[pq->size] = req;
    int i = pq->size;
    pq->size++;

    // Heapify Up: Urgency değeri düşük olan (öncelikli) yukarı çıkar
    while (i != 0 && pq->data[(i - 1) / 2].urgency > pq->data[i].urgency) {
        swap(&pq->data[i], &pq->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HttpRequest pop_request(PriorityQueue *pq) {
    if (pq->size <= 0) return (HttpRequest){-1, -1, "", ""};

    HttpRequest root = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;

    // Heapify Down
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < pq->size && pq->data[left].urgency < pq->data[smallest].urgency)
            smallest = left;
        if (right < pq->size && pq->data[right].urgency < pq->data[smallest].urgency)
            smallest = right;

        if (smallest != i) {
            swap(&pq->data[i], &pq->data[smallest]);
            i = smallest;
        } else break;
    }
    return root;
}

void free_queue(PriorityQueue *pq) {
    free(pq->data);
    free(pq);
}