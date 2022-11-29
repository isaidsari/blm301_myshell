CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -O0 -std=c99
NAME = myshell
WRITEC = writef
EXECX = execx

all: build clean run

run: $(NAME)
	clear
	@./$(NAME)

build: $(NAME) $(WRITEC) $(EXECX)

# add DEBUG flag to CFLAGS then run
debug: CFLAGS += -g -D DEBUG
debug: all

# compile object files to executable
$(NAME): $(NAME).o
	$(CC) $(CFLAGS) -o $(NAME) $(NAME).o 

$(WRITEC): $(WRITEC).o
	$(CC) $(CFLAGS) -o $(WRITEC) $(WRITEC).o

$(EXECX): $(EXECX).o
	$(CC) $(CFLAGS) -o $(EXECX) $(EXECX).o

# compile source files to object files
$(NAME).o:
	$(CC) $(CFLAGS) -c $(NAME).c

$(WRITEC).o:
	$(CC) $(CFLAGS) -c $(WRITEC).c

$(EXECX).o:
	$(CC) $(CFLAGS) -c $(EXECX).c


# clean object files
clean:
	rm -f *.o

# clean executable files
fclean: clean
	rm -f $(NAME) $(WRITEC) $(EXECX)
	@clear

.PHONY: clean fclean run
