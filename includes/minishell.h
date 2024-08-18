/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:39:56 by ebaillot          #+#    #+#             */
/*   Updated: 2024/08/16 11:27:51 by edouard          ###   ########.fr       */
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
#include <sys/stat.h>
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
	char *append_file;
	struct s_shell *shell;
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
	int tmp_proccess_status;
	int last_exit_status;
	int pipe_fds[2];
	t_env *env_var_list;
} t_shell;

/*
-------------------------------------------------------------
|                       FONCTIONS                           |
-------------------------------------------------------------
*/

/* PARSING */
/* Tokens - Utils */
t_token *ft_create_token(int type, char *value);
void ft_add_token(t_shell *shell, t_token *new_token);
void ft_create_add_token(t_shell *shell, int type, char *value);
void ft_free_cmd_args(char **cmd_args);
int ft_is_special_char(char c);
int ft_skip_whitespace(char *input, int i);
int ft_parse_regular_token(char *input, int i, int *inside_quote, t_shell *shell);
int ft_handle_quotes(t_shell *shell, char *input, int i, int *inside_quote);
t_token_type ft_determine_token_type(char *input, int start, int is_first_token);

// Tokens - Main Functions
void ft_tokenize_input(char *input, t_shell *shell);
int lexer(t_shell *shell);

// Parsing
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
int ft_builtin_export(t_command *cmd, t_env *env_list);
int ft_builtin_pwd(t_command *commands);
int ft_builtin_unset(t_command *cmd, t_env **env_list);
void ft_builtin_exit(t_command *commands, t_shell *shell);

/* Fonctions d'exécution */
int ft_executor(t_shell *shell, char **env);
char **ft_construct_cmd_args(char *cmd_name, char **cmd_args);
char *ft_get_path(t_command *current, t_shell *shell);
void handle_redirections(t_command *current, int prev_fd);
void ft_pipe(t_command *current, t_shell *shell);
void ft_free_array(char **split);
void wait_commands(t_shell *shell);

/* Fonctions utilitaires */
void free_shell(t_shell *shell);
int ft_heredoc_handler(t_command *command, t_shell *shell);
int ft_isspace(char c);
void handle_exit(t_shell *shell);

/*Expander */

char *ft_expander(char *str, t_shell *shell, int inside_single_quote);
void add_char_to_result(char **result, int *j, char c);
int is_var_char(char c);
char *extract_var_name(const char *str, int *i);
#endif // MINISHELL_H