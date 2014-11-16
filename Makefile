CC = g++
CFLAGS = -g -O2
CFLAGS_EXTRA = -lpthread
BIN_FILE = xpop3
OBJ_FILES = module_mail.o module_user.o xpop3.o
SRC_FILES = module_mail.cpp module_user.cpp xpop3.cpp

all: $(BIN_FILE)
$(BIN_FILE): $(OBJ_FILES) xpop3.cpp
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(BIN_FILE) $(CFLAGS_EXTRA)
$(OBJ_FILES):
	$(CC) $(CFLAGS) -c $(SRC_FILES)

clean:
	rm $(OBJ_FILES) $(BIN_FILE)
