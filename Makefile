CC	=	gcc

NAME	=	minishell.a

# CFLAGS	=	-Wall -Wextra -Werror

LFLAGS	=	-ltermcap

LIBFT	=	./libft/libft.a

SRCS	:=	parser/terminal_str.c parser/splitting_str.c utils/lists.c

OBJS	:=	$(SRCS:.c=.o)

RM	=	rm	-f

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

$(LIBFT):
	$(MAKE) -C ./libft

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

test:
	gcc main_fbrightw.c -ltermcap libft/libft.a $(NAME)
clean:
	$(RM)	$(OBJS)

fclean:	clean
	$(RM)	$(NAME)

re:	clean	all

.PHONY:	all	clean	fclean	re