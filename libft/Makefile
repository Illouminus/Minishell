NAME = libft.a
CC  = gcc
RM  = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDES = includes

SRCS = $(wildcard *.c)

BONUS =	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)
LIBC = ar rc
LIBR = ranlib

all: $(NAME)

so:
	@$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(BONUS)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(BONUS_OBJS)
	
$(NAME): $(OBJS)
	@$(LIBC) $(NAME) $(OBJS) 
	$(LIBR) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

bonus: $(OBJS) $(BONUS_OBJS)
	$(LIBC) $(NAME) $(OBJS) $(BONUS_OBJS)
	$(LIBR) $(NAME)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS) 

fclean: clean
	@echo "Cleaning libft.a"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
