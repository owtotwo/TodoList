#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cJSON.h"
#include "todolist_storage.h"
#include "todolist_error_code.h"

error_t todolist_save(const todolist_t* tdl) {
    FILE* fout = fopen(DEFAULT_DATA_ADDRESS, "wt");
    if (!tdl || !fout) return FAILURE;

    cJSON *root, *data, *item;
    
    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "id_count", tdl->id_count);
    cJSON_AddItemToObject(root, "data", data = cJSON_CreateArray());
    item_node_t* p = tdl->item_list->head;
    while (p) {
        cJSON_AddItemToArray(data, item  = cJSON_CreateObject());
        cJSON_AddNumberToObject(item, "id", p->data->id);
        cJSON_AddNumberToObject(item, "state", p->data->state);
        cJSON_AddNumberToObject(item, "timestamp", p->data->timestamp);
        cJSON_AddStringToObject(item, "content", p->data->content);
        p = p->next;
    }

    char* out_buffer = cJSON_Print(root);
    cJSON_Delete(root);

    fprintf(fout, "%s", out_buffer);

    free(out_buffer);
    fclose(fout);

    return SUCCESS;
}

error_t todolist_load(todolist_t* tdl) {
    if (!tdl) return FAILURE;
    FILE* fin = fopen(DEFAULT_DATA_ADDRESS, "rt");
    if (!fin) {
        perror("Loading");
        return FAILURE;
    }

    // get the text lenght
    fseek(fin, 0, SEEK_END);
    int length = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    // store in memory
    char* buffer = (char*)malloc(length * sizeof(char) + 1);
    fread(buffer, sizeof(char), length, fin);
    buffer[length] = '\0';

    // parse as root
    cJSON* root = cJSON_Parse(buffer);

    if (!root) {
        perror("Invalid Json");
        return FAILURE;
    }

    // put the element in a tmp todolist
    todolist_t* tmp = create_todolist();
    assert(tmp);
    
    assert(cJSON_HasObjectItem(root, "data"));
    cJSON* data = cJSON_GetObjectItem(root, "data");
    
    for (int i = cJSON_GetArraySize(data) - 1; i >= 0; i--) {
        cJSON* item = cJSON_GetArrayItem(data, i);
        todolist_add_item(
            tmp,
            cJSON_GetObjectItem(item, "content")->valuestring,
            cJSON_GetObjectItem(item, "id")->valueint,
            cJSON_GetObjectItem(item, "state")->valueint,
            cJSON_GetObjectItem(item, "timestamp")->valueint
        );
    }

    tmp->id_count = cJSON_GetObjectItem(root, "id_count")->valueint;
    cJSON_Delete(root);

    destroy_todolist(&tdl);
    tdl = copy_todolist(tmp);

    return SUCCESS;
}