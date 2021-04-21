CC	=	gcc

NAME	=	minishell.a

# CFLAGS	=	-Wall -Wextra -Werror

LIBFT	=	libft

LFLAGS	=	-L ./$(LIBFT) -lft -ltermcap

LIBRARY	=	./libft/libft.a

SRCS	:=	parser/terminal_str.c parser/splitting_str.c

OBJS	:=	$(SRCS:.c=.o)

RM	=	rm	-f

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBRARY)
	ar rcs $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)

clean:
	$(RM)	$(OBJS)

fclean:	clean
	$(RM)	$(NAME)

re:	clean	all

.PHONY:	all	clean	fclean	re