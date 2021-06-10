#.SILENT:

CC	=	gcc

NAME	=	minishell

LMIN	=	minishell.a

# CFLAGS	=	-Wall -Wextra -Werror

LFLAGS	=	-ltermcap

LIBFT	=	./libft/libft.a

SRCS_DIR =	./parser/

FILES	=	terminal_str.c, splitting_str.c, lexers.c

SRCS	= parser/terminal_str.c parser/actions.c parser/splitting_str.c parser/from_parser_to_execute.c parser/spec_symbols.c \
			parser/utils/analysis_spec_symb.c parser/utils/additional_for_termcaps.c parser/utils/finding_pipes.c \
			parser/utils/skipping_redirs.c parser/utils/env_status_work.c parser/utils/free_memory.c parser/utils/memory_alloc.c \
			parser/utils/utils_for_spec_smbls.c parser/utils/bin_file.c


SRCS	+=  execution/pipes_redirs/other_command.c \
			parser/utils/types_of_redirs.c execution/pipes_redirs/redirects.c execution/pipes_redirs/handle_pipes.c \
			execution/handle_signals.c execution/pipes_redirs/processes_in_pipe.c execution/pipes_redirs/utils.c \
			execution/free_everything.c execution/checking.c

SRCS	+= ${wildcard execution/builtins/*.c}

OBJS	:=	$(SRCS:.c=.o)

RM	=	rm	-f

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(LMIN) $(OBJS)
	#gcc -g main_fbrightw.c -ltermcap libft/libft.a $(LMIN) -o $(NAME)
	gcc -g -fsanitize=address main_fbrightw.c -ltermcap libft/libft.a $(LMIN) -o $(NAME)

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
