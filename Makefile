ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/obj
LIB_DIR = $(ROOT_DIR)/lib

CC = gcc
CC_FLAG = -std=c99 -Wall -Werror -g -I$(INC_DIR) -I$(LIB_DIR)

$(OBJ_DIR)/todolist_model.o: $(SRC_DIR)/todolist_model.c  $(INC_DIR)/todolist_model.h  \
		$(INC_DIR)/todolist_error_code.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/todolist_storage.o: $(SRC_DIR)/todolist_storage.c $(INC_DIR)/todolist_storage.h  \
		$(INC_DIR)/todolist_error_code.h
	$(CC) $(CC_FLAG) -c $< -o $@
	
clean:
	rm -rf $(OBJ_DIR)/*.o main