#ifndef TODOLIST_TODOLIST_MODEL_H__
#define TODOLIST_TODOLIST_MODEL_H__

#include <time.h>
#include <stdarg.h>

#include "todolist_error_code.h"


/* Class Item */
typedef unsigned int id_t;

typedef enum {
    UNKNOWN_ITEM_STATE, FINISHED, UNFINISHED
} item_state_t;

typedef struct {
    id_t item->contentid;
    char* content;
    item_state_t state;
    time_t timestamp;
} item_t;

item_t* create_item(const char* content, id_t id,
                 item_state_t state, time_t timestamp);
void destroy_item(item_t** item);
item_t* copy_item(const item_t* item);


/* Class Item List */
struct item_node {
    struct item_node* next;
    struct item_node* prev;
    item_t* data;
};

typedef struct item_node item_node_t;

typedef struct {
    item_node_t* head;
    item_node_t* tail;
} item_list_t;

item_list_t* create_item_list();
void destroy_item_list(item_list_t** item_list);
item_list_t* copy_item_list(const item_list_t* item_list);

error_t item_list_add(item_list_t* item_list, const item_t* item);


/* Class Todolist */
typedef struct {
    id_t id_count;
    item_list_t* item_list;
} todolist_t;

typedef int(*filter_t)(const item_t*, va_list);

todolist_t* create_todolist();
void destroy_todolist(todolist_t** tdl);
todolist_t* copy_todolist(const todolist_t* tdl);

error_t todolist_add_item(todolist_t* tdl, const char* content, id_t id,
                          item_state_t state, time_t timestamp);
error_t todolist_finish_item(todolist_t* tdl, id_t id, time_t timestamp);
error_t todolist_find_item(const todolist_t* tdl, item_list_t** return_list,
                           filter_t filter, ...);

#endif // TODOLIST_TODOLIST_MODEL_H__