NAME = minishell
CC = cc -g
RM = rm -f
CFLAGS =  -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

SRC_DIR = src
OBJ_DIR = obj

# Указание всех исходных файлов вручную
SRCS = 	main.c \
		$(SRC_DIR)/env/env.c \
		$(SRC_DIR)/env/outils.c \
		$(SRC_DIR)/executor/builtins/builtin_cd.c \
		$(SRC_DIR)/executor/builtins/cd_outils.c \
		$(SRC_DIR)/executor/builtins/builtin_echo.c \
		$(SRC_DIR)/executor/builtins/builtin_env.c \
		$(SRC_DIR)/executor/builtins/builtin_exit.c \
		$(SRC_DIR)/executor/builtins/builtin_export.c \
		$(SRC_DIR)/executor/builtins/builtin_pwd.c \
		$(SRC_DIR)/executor/builtins/builtin_unset.c \
		$(SRC_DIR)/executor/heredoc/heredoc.c \
		$(SRC_DIR)/executor/redirection/redirection.c \
		$(SRC_DIR)/executor/redirection/redirection_outils.c \
		$(SRC_DIR)/executor/executor_outils.c \
		$(SRC_DIR)/executor/executor_outils_2.c \
		$(SRC_DIR)/executor/executor.c \
		$(SRC_DIR)/executor/env_converter.c \
		$(SRC_DIR)/executor/ft_pipe.c \
		$(SRC_DIR)/executor/outils.c \
		$(SRC_DIR)/init/init_outils.c \
		$(SRC_DIR)/lexer/lexer.c \
		$(SRC_DIR)/lexer/ft_token_create_utils.c \
		$(SRC_DIR)/lexer/ft_tokenise_utils.c \
		$(SRC_DIR)/outils/free_exit.c \
		$(SRC_DIR)/outils/signals.c \
		$(SRC_DIR)/outils/ft_isspace.c \
		$(SRC_DIR)/parser/parser.c \
		$(SRC_DIR)/parser/parser_outils.c \
		$(SRC_DIR)/parser/outils.c \
		$(SRC_DIR)/parser/parser_handle.c \
		$(SRC_DIR)/parser/parser_handle_redir.c \
		$(SRC_DIR)/parser/expander/expander.c \
		$(SRC_DIR)/parser/expander/outils.c \

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
INC = -Iincludes -Ilibft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Building project $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Full cleanup done."

re: fclean all

.PHONY: all clean fclean re