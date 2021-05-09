CC	=	gcc

NAME	=	minishell.a

# CFLAGS	=	-Wall -Wextra -Werror

LFLAGS	=	-ltermcap

LIBFT	=	./libft/libft.a

SRCS_DIR =	./parser/

FILES	=	terminal_str.c, splitting_str.c, lexers.c


# SRCS	=	$(addprefix $(SRCS_DIR), $(FILES))
SRCS	:=	parser/terminal_str.c parser/actions.c parser/splitting_str.c parser/lexers.c parser/utils/check_words.c \
			parser/utils/analysis_spec_symb.c

SRCS	+= 	${wildcard execution/builtins/*.c} ${wildcard execution/work_it/*.c}

# OBJS   :=    $(SRCS:%.c=$(OBJS)/%.o)
OBJS	:=	$(SRCS:.c=.o)

RM	=	rm	-f

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)
	gcc -fsanitize=address -g main_fbrightw.c -ltermcap libft/libft.a $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

.c.o:
	$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)

clean:
	$(RM)	$(OBJS)

fclean:	clean
	$(RM)	$(NAME)

re:	fclean	all

.PHONY:	all	clean	fclean	re
