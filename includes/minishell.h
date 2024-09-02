/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:39:56 by ebaillot          #+#    #+#             */
/*   Updated: 2024/08/30 13:41:34 by ebaillot         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
-------------------------------------------------------------
|                       BIBLIOTHÈQUES                       |
-------------------------------------------------------------
*/

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_ARGS 100

extern int				g_exit_code;

/*
-------------------------------------------------------------
|                       STRUCTURES                          |
-------------------------------------------------------------
*/

// Enumération des types de tokens
typedef enum e_token_type
{
	TOKEN_TYPE_CMD,
	TOKEN_TYPE_ARG,
	TOKEN_TYPE_REDIR_IN,
	TOKEN_TYPE_REDIR_OUT,
	TOKEN_TYPE_REDIR_APPEND,
	TOKEN_TYPE_HEREDOC,
	TOKEN_TYPE_PIPE,
	TOKEN_TYPE_EOF,
}						t_token_type;

// Enumération des types de redirections
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
}						t_redir_type;

// Structure pour l'expander
typedef struct s_expand_state
{
    char    **result;
    int     *j;
    int     *len;
}   t_expand_state;


// Structure d'un token
typedef struct s_token
{
	t_token_type		tok_type;
	char				*tok_value;
	struct s_token		*next_tok;
	struct s_token		*prev_tok;
}						t_token;

// Structure d'une redirection
typedef struct s_redir
{
	char				*filename;
	t_redir_type		redirection_type;
	struct s_redir		*next;
	struct s_redir		*prev;
}						t_redir;

// Structure d'une commande
typedef struct s_command {
	char *cmd_value;
	char **cmd_args;
	bool is_builtin_cmd;
	t_token *redir_tokens;
	struct s_command *next_cmd;
	struct s_command *prev_cmd;
	t_redir *redirections;
	t_redir *last_redirection;
	int redir_count;
	struct s_shell *shell;
} t_command;


// Structure pour les variables d'environnement
typedef struct s_env
{
	char				*env_var_name;
	char				*env_value;
	struct s_env		*next_env;
}						t_env;

// Structure principale du shell
typedef struct s_shell
{
	char				*user_input;
	t_token				*token_list;
	t_command			*command_list;
	pid_t				last_process_id;
	int					wait_status;
	char				**env_vars;
	int					tmp_proccess_status;
	int					last_exit_status;
	int					pipe_fds[2];
	t_env				*env_var_list;
}						t_shell;

/*
-------------------------------------------------------------
|                       FONCTIONS                           |
-------------------------------------------------------------
*/

/* ========================================================= */
/*                         TOKENS                            */
/* ========================================================= */

/* Tokens - Fonctions Utilitaires */
t_token					*ft_create_token(int type, char *value);
void					ft_add_token(t_shell *shell, t_token *new_token);
void					ft_create_add_token(t_shell *shell, int type,
							char *value);
void					ft_free_cmd_args(char **cmd_args);
int						ft_is_special_char(char c);
int						ft_skip_whitespace(char *input, int i);
int						ft_parse_regular_token(char *input, int i,
							int *inside_quote, t_shell *shell);
int						ft_handle_quotes(t_shell *shell, char *input, int i,
							int *inside_quote);
t_token_type			ft_determine_token_type(char *input, int start,
							int is_first_token);

/* Tokens - Fonctions Principales */
void					ft_tokenize_input(char *input, t_shell *shell);
int						lexer(t_shell *shell);

/* ========================================================= */
/*                         PARSING                           */
/* ========================================================= */

/* Parsing - Fonctions Utilitaires */
char					*ft_clean_token_value(const char *token,
							int *inside_single_quote);
t_command				*ft_new_command_init(t_command *command, int nb_of_args,
							char *cmd_value_clean, t_shell *shell);
int						ft_determine_nb_args(t_token *token_list);
int						ft_cmd_is_built_in(char *value);
void					add_redirection(t_command *cmd, int type,
							char *filename);

/* Parsing - Fonctions Principales */
int						ft_cmd_is_built_in(char *value);
int						ft_determine_nb_args(t_token *token_list);

void					ft_parser_handle_redirection(t_token **current_token,
							t_shell *shell, t_command *last_command,
							int *inside_single_quote);
void					ft_parser_handle_command(t_token *current_token,
							char *cmd_value_clean, t_shell *shell,
							t_command **last_command);
int						ft_parser_handle_empty_command(char *cmd_value_clean,
							t_token **current_token);
char					*ft_handle_token_expansion(t_token *current_token,
							t_shell *shell, int *inside_single_quote);
int						parser(t_shell *shell);

/* ========================================================= */
/*                        EXECUTION                          */
/* ========================================================= */

/* Initialisation du Shell */
int						init_shell(t_shell *shell, char **env);

/* Exécution des Commandes */
int						ft_executor(t_shell *shell, char **env);
char					**ft_construct_cmd_args(char *cmd_name,
							char **cmd_args);
char					*ft_get_path(t_command *current, t_shell *shell);
void					handle_redirections(t_command *current, int prev_fd);
void					ft_pipe(t_command *current, t_shell *shell);
void					wait_commands(t_shell *shell);
void					ft_free_array(char **array);
void					handle_error(const char *cmd, const char *error_message,
							int exit_code, t_shell *shell);
void					handle_error_non_critical(const char *cmd,
							const char *error_message, int exit_code,
							t_shell *shell);
void					handle_redirection_error(const char *filepath,
							const char *error_message, int exit_code,
							t_shell *shell, int fd);
int						check_and_open_file(const char *filepath, int flags,
							mode_t mode, t_shell *shell);
/* Fonctions Intégrées (Built-Ins) */
int						ft_builtin_cd(t_command *cmd, t_shell *shell);
int						ft_builtin_echo(t_command *cmd);
int						ft_builtin_env(t_env *env);
int						ft_builtin_export(t_command *cmd, t_env **env_list);
int						ft_builtin_pwd(t_command *commands);
int						ft_builtin_unset(t_command *cmd, t_env **env_list);
void					ft_builtin_exit(t_command *commands, t_shell *shell);
void					ft_print_env_list(t_env *env_list);

/* ========================================================= */
/*                VARIABLES D'ENVIRONNEMENT                  */
/* ========================================================= */

t_env					*init_env_vars(char **env);
t_env					*init_default_env_vars(void);
t_env					*create_env_var_node(char *env_str);
t_env					*create_default_env_var_node(char *var_name,
							char *value);
t_env					*ft_get_env_var_by_name(t_env *head, const char *name);
char					*ft_getenv(t_env *env_list, const char *name);
void					ft_setenv(t_env **env_list, const char *name,
							const char *value);
void					add_env_var_to_list(t_env **head, t_env *new_var);
void					global_exit(t_shell *shell);
void					free_env_var_list(t_env *env);

/* ========================================================= */
/*                  GESTION DES SIGNAUX                      */
/* ========================================================= */

void					handle_sigint(int sig);
void					handle_sigpipe(int sig);
void					setup_signal_handlers(void);

/* ========================================================= */
/*                    FONCTIONS UTILITAIRES                  */
/* ========================================================= */

void					free_shell(t_shell *shell);
char					*ft_heredoc_handler(char *marker);
int						ft_isspace(char c);
void					handle_exit(t_shell *shell);

/* ========================================================= */
/*                          EXPANDER                         */
/* ========================================================= */

char					*ft_expander(char *str, t_shell *shell,
							int inside_single_quote);
void					add_char_to_result(char **result, int *j, char c);
int						is_var_char(char c);
char					*extract_var_name(const char *str, int *i);
void					add_redirection(t_command *cmd, int type,
							char *filename);

#endif // MINISHELL_H