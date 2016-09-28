#include <stdlib.h>
#include <string.h>

#include "todolist_model.h"

/* Methods for Class Item */
item_t* create_item(const char* content, id_t id,
                 item_state_t state, time_t timestamp) {
    item_t* new_item = (item_t*)malloc(sizeof(item_t));
    if (!new_item) return NULL; // create failed

    new_item->content = (char*)malloc((strlen(content) + 1) * sizeof(char));
    strcpy(new_item->content, content);
    new_item->id = id;
    new_item->state = state;
    new_item->timestamp = timestamp;

    return new_item;
}

void destroy_item(item_t** item) {
    if (!item) return;

    free((*item)->content);
    (*item)->content = NULL;
    free(*item);
    *item = NULL;
}

item_t* copy_item(const item_t* item) {
    item_t* new_item = (item_t*)malloc(sizeof(item_t));
    if (!item || !new_item) return NULL; // copy failed
    
    new_item->content = (char*)malloc((strlen(item->content) + 1) * sizeof(char));
    strcpy(new_item->content, item->content);
    new_item->id = item->id;
    new_item->state = item->state;
    new_item->timestamp = item->timestamp;

    return new_item;
}

/* Methods for Class Item List */
item_list_t* create_item_list() {
    item_list_t* new_item_list = (item_list_t*)malloc(sizeof(item_list_t));
    if (!new_item_list) return NULL; // create failed

    new_item_list->head = NULL;
    new_item_list->tail = NULL;

    return new_item_list;
}

void destroy_item_list(item_list_t** item_list) {
    if (!item_list) return;

    item_node_t* p = (*item_list)->head;
    while (p) {
        item_node_t* tmp = p;
        p = p->next;
        destroy_item(&(tmp->data));
        free(tmp);
        tmp = NULL;
    }

    free(*item_list);
    *item_list = NULL;
}

item_list_t* copy_item_list(const item_list_t* item_list) {
    new_item_list = create_item_list();
    if (!new_item_list) return NULL;

    item_node_t* p = (*item_list)->tail;
    while (p) {
        item_list_add(&new_item_list, p->data);
        p = p->prev;
    }
    
    return new_item_list;
}

error_t item_list_add(item_list_t* item_list, const item_t* item) {
    if (!item_list || !item) return FAILURE;

    item_t* new_item = copy_item(item);
    if (!new_item) return FAILURE;
    item_node_t* new_node = (item_node_t*)malloc(sizeof(item_node_t));
    if (!new_node) {
        destroy_item(&new_item);
        return FAILURE;
    }

    item_node_t* p = item_list->head;
    p->prev = new_node;
    new_node->next = p;
    new_node->prev = NULL;
    item_list->head = new_node;
    
    return SUCCESS;
}

/* Methods for Class Todolist */

todolist_t* create_todolist() {
    todolist_t* new_tdl = (todolist*)malloc(sizeof(todolist_t));
    if (!new_tdl) return NULL;

    new_tdl->id = 0;
    new_tdl->item_list = create_item_list();

    return new_tdl;
}

void destroy_todolist(todolist_t** tdl) {
    if (!tdl) return;

    destroy_item_list(&tdl->item_list);

    free(*tdl);
    *tdl = NULL;
}

todolist_t* copy_todolist(const todolist_t* tdl) {
    todolist_t* new_tdl = create_todolist();
    if (!new_tdl) return NULL;

    new_tdl->id = tdl->id;
    destroy_item_list(&new_tdl->item_list);
    new_tdl->item_list = copy_item_list(tdl->item_list);

    return new_tdl;
}

error_t todolist_add_item(todolist_t* tdl, const char* content, id_t id,
                          item_state_t state, time_t timestamp) {
    ;
}
error_t todolist_finish_item(todolist_t* tdl, id_t id, time_t timestamp);
error_t todolist_find_item(const todolist_t* tdl, item_list_t** return_list,
                           filter_t filter, ...);