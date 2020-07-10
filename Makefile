##
## EPITECH PROJECT, 2020
## PSU_2019_malloc
## File description:
## Makefile
##


CC		=	gcc

CFLAGS	=	-Wall -Wextra
CFLAGS 	=	-fPIC

RM		=	rm -f

SRCS	=	malloc.c \

OBJS	=	$(SRCS:.c=.o)

NAME	=	libmy_malloc.so

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) -fPIC -shared $(OBJS) -o $(NAME)

clean:
		$(RM) $(NAME) $(OBJS)
fclean:	clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re