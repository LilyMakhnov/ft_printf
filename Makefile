LIBFT	= libft

SRCS	=   ft_printf.c parse_flags.c print_str.c print_hexa.c print_deci.c utils.c\



NAME    =	libftprintf.a
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror 

all:		${NAME}

bonus:		$(NAME)

OBJS	=	${SRCS:.c=.o}

.c.o:	
		$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
		$(MAKE) bonus -C $(LIBFT)
		cp libft/libft.a ./$(NAME)
		ar -rcs $(NAME) $(OBJS)

clean:
	        	$(MAKE) clean -C $(LIBFT)
				rm -f ${OBJS} 

fclean:         clean
				$(MAKE) fclean -C $(LIBFT)
	        	rm -f ${NAME}

re:             fclean all

.PHONY:         all clean fclean re
