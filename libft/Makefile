# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 13:08:47 by fbrightw          #+#    #+#              #
#    Updated: 2020/11/13 14:00:28 by fbrightw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

CC	=	gcc 
	
NAME	=	libft.a
	
CFLAGS	=	-Wall -Wextra -Werror

SRCS	:=	$(wildcard ft_*.c) 

SRCS_B	:=	$(wildcard ft_lst*.c)

SRCS	:=	$(filter-out $(SRCS_B),$(SRCS))

OBJS	:=	$(SRCS:.c=.o)

OBJS_B	:=	$(SRCS_B:.c=.o)

RM	=	rm	-f

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus:	$(NAME) $(OBJS_B)
	ar rcs $(NAME) $(OBJS_B) 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean: 
	$(RM)	$(OBJS)	$(OBJS_B)

fclean:	clean 
	$(RM)	$(NAME)

re:	clean	all

.PHONY:	all	clean	fclean	re	bonus
