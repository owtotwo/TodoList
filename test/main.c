#include <stdio.h>
#include <time.h>

#include "todolist_model.h"
#include "todolist_storage.h"

int main() {
    todolist_t* tdl = create_todolist();
    todolist_load(tdl);
    todolist_save(tdl);
    destroy_todolist(&tdl);
    return 0;
}