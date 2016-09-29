#include <stdio.h>
#include <time.h>

#include "todolist_model.h"
#include "todolist_storage.h"

int main() {
    todolist_t* tdl = create_todolist();
    todolist_add_item(tdl, "The First", 1, UNFINISHED, time(NULL));
    todolist_add_item(tdl, "The Second", 2, UNFINISHED, time(NULL));
    todolist_add_item(tdl, "The Third", 3, UNFINISHED, time(NULL));
    todolist_finish_item(tdl, 2, time(NULL));
    todolist_save(tdl);
    destroy_todolist(&tdl);
    return 0;
}