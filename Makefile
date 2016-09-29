ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INC_DIR = $(ROOT_DIR)/include
OBJ_DIR = $(ROOT_DIR)/obj
LIB_DIR = $(ROOT_DIR)/lib
TEST_DIR = $(ROOT_DIR)/test

CC = gcc
CC_FLAG = -std=c99 -Wall -Werror -g -I$(INC_DIR) -I$(LIB_DIR)

test.out: $(OBJ_DIR)/main.o  $(OBJ_DIR)/todolist_model.o  $(OBJ_DIR)/todolist_storage.o  \
		$(LIB_DIR)/cJSON.o
	$(CC) $(CC_FLAG) $^ -lm -o $@

$(OBJ_DIR)/main.o: $(TEST_DIR)/main.c  $(INC_DIR)/todolist_model.h  \
	 	$(INC_DIR)/todolist_storage.h
	$(CC) $(CC_FLAG) -c $< -o $@


$(OBJ_DIR)/todolist_model.o: $(SRC_DIR)/todolist_model.c  $(INC_DIR)/todolist_model.h  \
		$(INC_DIR)/todolist_error_code.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/todolist_storage.o: $(SRC_DIR)/todolist_storage.c  $(INC_DIR)/todolist_storage.h  \
		$(INC_DIR)/todolist_error_code.h
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR)/cJSON.o:
	cd $(LIB_DIR) && make CC=$(CC)

clean:
	rm -rf $(OBJ_DIR)/*.o main *.out