# OBJS specifies which files to compile as part of the project
OBJS = server.c thpool.c server_handler.c client_handler.c

# CC specidies which compiler we're using
CC = gcc

# COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -pthread -Wall -g

# OBJ_NAME specifies the name of executable
OBJ_NAME = server

all : $(OBJS) 
	$(CC) $(COMPILER_FLAGS) $(OBJS) -o $(OBJ_NAME)
