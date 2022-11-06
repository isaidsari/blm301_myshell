CC = clang
CFLAGS = -Wall -Wextra #-Werror -pedantic -O0 -g
NAME = myshell
WRITEC = writef
EXECX = execx

all: $(NAME) $(WRITEC) $(EXECX) clean run

run: $(NAME)
	clear
	./$(NAME)

#

$(NAME): $(NAME).o 
	$(CC) $(CFLAGS) -o $(NAME) $(NAME).o 

$(WRITEC): $(WRITEC).o
	$(CC) $(CFLAGS) -o $(WRITEC) $(WRITEC).o

$(EXECX): $(EXECX).o
	$(CC) $(CFLAGS) -o $(EXECX) $(EXECX).o

#

$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c $(NAME).c

$(WRITEC).o: $(WRITEC).c
	$(CC) $(CFLAGS) -c $(WRITEC).c

$(EXECX).o: $(EXECX).c
	$(CC) $(CFLAGS) -c $(EXECX).c

#

$(NAME).c:
	$(CC) $(CFLAGS) -o $(NAME) $(NAME).c

$(WRITEC).c:
	$(CC) $(CFLAGS) -o $(WRITEC) $(WRITEC).c

$(EXECX).c:
	$(CC) $(CFLAGS) -o $(EXECX) $(EXECX).c

#

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) $(WRITEC) $(EXECX)

.PHONY: clean fclean

# https://makefiletutorial.com/
