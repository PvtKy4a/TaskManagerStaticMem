#include "QueueStaticMem.h"
#include <stdlib.h>

Queue_t * q_create_queue(uint16_t capacity) {
  Queue_t * new_queue = (Queue_t *)malloc(sizeof(*new_queue));
  if (new_queue == NULL) {
    return NULL;
  }
  new_queue->data_queue = (QueueNode_t *)malloc(capacity * sizeof(*new_queue->data_queue));
  if (new_queue->data_queue == NULL) {
    free(new_queue);
    return NULL;
  }
  new_queue->head = NULL;
  new_queue->tail = NULL;
  new_queue->free_place = 0;
  new_queue->capacity = capacity;
  new_queue->size = 0;
  return new_queue;
}

q_return_status_t q_push(Queue_t * queue, void * data) {
  if (queue == NULL) {
    return Q_QUEUE_LOST;
  }
  if (queue->size == queue->capacity) {
    return Q_QUEUE_IS_FULL;
  }
  QueueNode_t new_node;
  new_node.data = data;
  new_node.next = NULL;
  queue->data_queue[queue->free_place] = new_node;
  if (queue->size == 0) {
    queue->tail = &queue->data_queue[queue->free_place];
    queue->head = queue->tail;
  } else {
    queue->tail->next = &queue->data_queue[queue->free_place];
    queue->tail = &queue->data_queue[queue->free_place];
  }
  ++queue->size;
  ++queue->free_place;
  if (queue->free_place == queue->capacity) {
    queue->free_place = 0;
  }
  return Q_DATA_PUSHED;
}

void * q_pop(Queue_t * queue) {
  if (queue == NULL) {
    return NULL;
  }
  if (queue->size == 0) {
    return NULL;
  }
  void * data = NULL;
  data = queue->head->data;
  queue->head = queue->head->next;
  --queue->size;
  return data;
}

void * q_get(Queue_t * queue) {
  if (queue == NULL) {
    return NULL;
  }
  void * data = NULL;
  if (queue->head == NULL) {
    return NULL;
  }
  data = queue->head->data;
  return data;
}

q_return_status_t q_delete(Queue_t * queue) {
  if (queue == NULL) {
    return Q_QUEUE_LOST;
  }
  void * data = NULL;
  if (queue->head == NULL) {
    return Q_QUEUE_IS_EMPTY;
  }
  data = q_pop(queue);
  return Q_DATA_DELETED;
}

int16_t q_get_size(Queue_t * queue) {
  if (queue == NULL) {
    return -1;
  }
  return queue->size;
}

int8_t q_is_empty(Queue_t * queue) {
  if (queue == NULL) {
    return -1;
  }
  if (queue->size == 0) {
    return 1;
  }
  return 0;
}
