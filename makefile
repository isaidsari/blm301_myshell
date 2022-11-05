CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -O0 -g
NAME = myshell

all: $(NAME)

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) -o $(NAME) $(NAME).c

clean:
	rm -f $(NAME)

.PHONY: all clean

# https://makefiletutorial.com/
