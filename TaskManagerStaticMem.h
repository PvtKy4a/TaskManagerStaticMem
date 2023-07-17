#ifndef TASK_MANAGER_STATIC_MEM_H
#define TASK_MANAGER_STATIC_MEM_H

#include <stdint.h>

#define TM_TASK_LIST_SIZE 10

typedef enum {
  TM_TASK_CREATED,
  TM_TASK_DELETED,
  TM_TASK_UPDATED,
  TM_INIT_FAILED,
  TM_INIT_SUCCEEDED,
  TM_TASK_LIST_IS_FULL,
  TM_TASK_FUNCTION_IS_EMPTY,
  TM_TASK_NOT_FOUND
} tm_return_status_t;

typedef enum {
  TM_ONE_SHOT_MODE,
  TM_ROLL_MODE
} tm_task_run_mode_t;

tm_return_status_t tm_init_task_manager(void);

void tm_sheduler(void);

void tm_task_manager(void);

tm_return_status_t tm_create_task(void (* task_function)(void *), void * context, tm_task_run_mode_t run_mode, uint32_t delay, uint32_t timeout);

tm_return_status_t tm_delete_task(void (* task_function)(void *));

tm_return_status_t tm_set_delay(void (* task_function)(void *), uint32_t delay);

tm_return_status_t tm_set_timeout(void (* task_function)(void *), uint32_t timeout);

uint8_t get_task_number(void);

#endif
