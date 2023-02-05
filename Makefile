NAME	=	philo

SRCS	=	./src/philo.c		./src/inits.c		./src/philo_actions.c\
			./utils/errors.c	./utils/ft_atoi.c	./utils/setting.c\
			./utils/utils.c

HEAD	=	./inc/philo.h

OBJS	=	$(SRCS:%.c=%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread
RM		=	rm -f
FALL	=	fclean all

GREEN	=	\033[0;32m
RED		=	\033[0;31m
WHITE	=	\033[0m


all	:	$(NAME)

$(NAME)	:	$(OBJS) $(HEAD)
	@echo "$(WHITE)     ----COMPILING----$(WHITE)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)	----DONE----		$(WHITE)"

%.o		:	%.c $(HEAD)
	
	@$(CC) $(CFLAGS) -c $< -o $@

clean	:
	@$(RM) $(OBJS)
	@echo "$(RED)----CLEANING OBJECT FILES----$(WHITE)"
	@echo "$(GREEN)	----DONE----		$(WHITE)"

fclean	:	clean
	@echo "$(RED)    ----REMOVING EXEC----$(WHITE)"
	@$(RM) $(NAME)
	@echo "$(GREEN)	----DONE----		$(WHITE)"

re		:	$(FALL)
	@echo "$(RED)----RECOMPILING EVERYTHING----$(WHITE)"
	@echo "$(GREEN)	----DONE----		$(WHITE)"

.PHONY	:	all clean fclean re