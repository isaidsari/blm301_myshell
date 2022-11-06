CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -O0 -g3 -std=c99
NAME = myshell
WRITEC = writef
EXECX = execx

all: build clean run

run: $(NAME)
	clear
	@./$(NAME)

build: $(NAME) $(WRITEC) $(EXECX)


$(NAME): $(NAME).o 
	$(CC) $(CFLAGS) -o $(NAME) $(NAME).o 

$(WRITEC): $(WRITEC).o
	$(CC) $(CFLAGS) -o $(WRITEC) $(WRITEC).o

$(EXECX): $(EXECX).o
	$(CC) $(CFLAGS) -o $(EXECX) $(EXECX).o


$(NAME).o:
	$(CC) $(CFLAGS) -c $(NAME).c

$(WRITEC).o:
	$(CC) $(CFLAGS) -c $(WRITEC).c

$(EXECX).o:
	$(CC) $(CFLAGS) -c $(EXECX).c


clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) $(WRITEC) $(EXECX)

.PHONY: clean fclean run

# https://makefiletutorial.com/
