/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:39:56 by ebaillot          #+#    #+#             */
/*   Updated: 2024/08/09 16:17:03 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

/*
-------------------------------------------------------------
|                       BIBLIOTHÈQUES                       |
-------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdbool.h>
#include "../libft/libft.h"

#define MAX_ARGS 100

extern int g_exit_code;

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
	TOKEN_TYPE_PIPE,
	TOKEN_TYPE_EOF,
} t_token_type;

// Structure d'un token
typedef struct s_token
{
	t_token_type tok_type;
	char *tok_value;
	struct s_token *next_tok;
	struct s_token *prev_tok;
} t_token;

// Structure d'une commande
typedef struct s_command
{
	char *cmd_value;
	char **cmd_args;
	bool is_builtin_cmd;
	t_token *redir_tokens;
	struct s_command *next_cmd;
	struct s_command *prev_cmd;
	char *heredoc_marker;
	char *input_file;
	char *output_file;
	int pipe_fds[2];
} t_command;

// Structure pour les variables d'environnement
typedef struct s_env
{
	char *env_var_name;
	char *env_value;
	struct s_env *next_env;
} t_env;

// Structure principale du shell
typedef struct s_shell
{
	char *user_input;
	t_token *token_list;
	t_command *command_list;
	pid_t last_process_id;
	int wait_status;
	char *command_path;
	char **env_vars;
	char *heredoc_tempfile;
	int saved_stdin_fd;
	int last_exit_status;
	t_env *env_var_list;
} t_shell;

/*
-------------------------------------------------------------
|                       FONCTIONS                           |
-------------------------------------------------------------
*/

/* Parsing */
t_token *ft_create_token(int type, char *value);
void ft_add_token(t_shell *shell, t_token *new_token);
void ft_create_add_token(t_shell *shell, int type, char *value);
void ft_free_cmd_args(char **cmd_args);

/* Utils */
int ft_skip_whitespace(char *input, int i);
int ft_handle_quotes(char *input, int i);
t_token_type ft_determine_token_type(char *input, int start, int is_first_token); // TODO check if it's needed
void ft_tokenize_input(char *input, t_shell *shell);
int lexer(t_shell *shell);
int parser(t_shell *shell);

/* Execution */
int init_shell(t_shell *shell, char **env);

/* Variables d'environnement */
t_env *init_env_vars(char **env);
t_env *init_default_env_vars(void);
t_env *create_env_var_node(char *env_str);
t_env *create_default_env_var_node(char *var_name, char *value);
t_env *ft_get_env_var_by_name(t_env *head, const char *name);
char *ft_getenv(t_env *env_list, const char *name);
void ft_setenv(t_env **env_list, const char *name, const char *value);
void add_env_var_to_list(t_env **head, t_env *new_var);
void global_exit_env(t_shell *shell, int status);
void free_env_var_list(t_env *env);

/* Gestion des signaux */
void handle_sigint(int sig);
void setup_signal_handlers(void);
void print_error(char *cmd, char *error_message);

/* Fonctions intégrées (Built-In) */
int ft_builtin_cd(t_command *cmd, t_shell *shell);
int ft_builtin_echo(t_command *cmd);
int ft_builtin_env(t_env *env);
int ft_builtin_exit(void);
int ft_builtin_export(t_command *cmd, t_env *env_list);
int ft_builtin_pwd(t_command *commands);
int ft_builtin_unset(t_command *cmd, t_env **env_list);

/* Fonctions d'exécution */
int ft_executor(t_shell *shell, char **env);
char **ft_construct_cmd_args(char *cmd_name, char **cmd_args);
char *ft_get_path(t_command *current, t_shell *shell);
void handle_redirections(t_command *current, int prev_fd);
void ft_pipe(t_command *current, t_shell *shell);
void ft_free_array(char **split);

/* Fonctions utilitaires */
void free_shell(t_shell *shell);
int ft_heredoc_handler(t_command *command, t_shell *shell);
int ft_isspace(char c);
void handle_exit(t_shell *shell);
char *ft_expander(char *str, t_shell *shell);

#endif // MINISHELL_H