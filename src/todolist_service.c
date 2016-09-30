#include "todolist_service.h"
#include "todolist_model.h"
#include "todolist_error_code.h"

#include <time.h>
#include <assert.h>

static int filter_by_id(const item_t* item, va_list ap);
static int filter_by_state(const item_t* item, va_list ap);

error_t service_add_item(todolist_t* tdl, const char* content) {
    if (!tdl) return FAILURE;
    return todolist_add_item(tdl, content, todolist_get_a_new_id(tdl), UNFINISHED,
                      time(NULL));
}

error_t service_finish_item(todolist_t* tdl, id_t item_id) {
    if (!tdl) return FAILURE;
    return todolist_finish_item(tdl, item_id, time(NULL));
}

error_t service_find_item_by_id(const todolist_t* tdl, id_t item_id,
                                item_t** item) {
    item_list_t* return_list = create_item_list();
    if (todolist_find_item(tdl, &return_list, filter_by_id, item_id) == FAILURE)
        return FAILURE;
    assert(return_list->head && return_list->head == return_list->tail);
    *item = copy_item(return_list->head->data);
    destroy_item_list(&return_list);
    return SUCCESS;
}
error_t service_find_item_by_keyword(const todolist_t* tdl, const char* item_keyword,
                                     item_t** item){
    // TODO();
    return FAILURE;
}

int service_get_n_items_by_state(const todolist_t* tdl, item_list_t** item_list,
                                     int line_count, int done_needed) {
    item_state_t state = done_needed ? FINISHED : UNFINISHED;

    item_list_t* tmp = create_item_list();
    todolist_find_item(tdl, &tmp, filter_by_state, state);

    const item_node_t* p = tmp->head;
    int count = 0;
    for (; count < line_count && p ; count++, p = item_node_next(p))
        item_list_add((*item_list), p->data);
    
    destroy_item_list(&tmp);
    return count;
}

static int filter_by_id(const item_t* item, va_list ap) {
    assert(item);
    int id = va_arg(ap, int);
    return item->id == id;
}

static int filter_by_state(const item_t* item, va_list ap) {
    assert(item);
    item_state_t state = va_arg(ap, item_state_t);
    return item->state == state;
}
