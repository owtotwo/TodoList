#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "todolist_service.h"
#include "todolist_model.h"
#include "todolist_storage.h"

int main() {
    todolist_t* tdl = create_todolist();
    todolist_load(tdl);
    service_add_item(tdl, "hey man");
    service_add_item(tdl, "hello man");
    service_add_item(tdl, "sorry man");
    service_add_item(tdl, "hello world");
    service_finish_item(tdl, 8);
    item_t* item = create_empty_item();
    service_find_item_by_id(tdl, 2, &item);
    printf("content: %s\n", item->content);
    destroy_item(&item);
    item_list_t* item_list = create_item_list();
    int count = service_get_n_items_by_state(tdl, &item_list, 6, 0);
    const item_node_t* p = item_list->head;
    for (int i = 0; i < count && p; i++, p = item_node_next(p)) {
        assert(p->data);
        printf("[%d] %s\n", p->data->id, p->data->content);
    }
    destroy_item_list(&item_list);
    todolist_save(tdl);
    destroy_todolist(&tdl);
    return 0;
}