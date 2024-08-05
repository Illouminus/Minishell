/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:39:56 by ebaillot          #+#    #+#             */
/*   Updated: 2024/08/02 17:15:27 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

/*
-------------------------------------------------------------
|                       LIBRAIRIE                            |
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
#include <stdbool.h>
#include "../libft/libft.h"

#define MAX_ARGS 100

extern int g_exit_code;

/*
-------------------------------------------------------------
|                       STRUCTURE                            |
-------------------------------------------------------------
*/

// Enum Token Type
typedef enum    e_token_type
  {
	TOKEN_TYPE_CMD, 
	TOKEN_TYPE_ARG, 
	TOKEN_TYPE_REDIR_IN,
	TOKEN_TYPE_REDIR_OUT, 
	TOKEN_TYPE_PIPE, 
    TOKEN_TYPE_EOF,
}	t_token_type;

// Structure d'un token
typedef struct s_token
{
	t_token_type	tok_type;			// Type de token (commande, argument, opérateur de redirection)
	char			*tok_value;			// Valeur du token (texte de la commande ou de l'argument)
	struct s_token *next_tok;			// Pointeur vers le token suivant
	struct s_token *prev_tok;			// Pointeur vers le token précédent
} t_token;


// Structure d'une commande 
typedef struct s_command
{
	char				*cmd_value;			// Nom de la commande
	char				**cmd_args;			// Arguments de la commande
	bool				is_builtin_cmd;		// Indicateur si la commande est une commande intégrée
	t_token				*redir_tokens;		// Liste des redirections associées à la commande || Pas sur de à quoi ça sert ça 
	struct s_command	*next_cmd;			// Pointeur vers la commande suivante
	struct s_command	*prev_cmd;			// Pointeur vers la commande précédente
} t_command;

// Structyre pour env
typedef struct s_env
{
	char				*env_var_name;		// Nom de la variable d'environnement
	char 				*env_value;			// Valeur de la variable d'environnement
	struct s_env		*next_env;			// Pointeur vers la variable d'environnement suivante
} t_env;


typedef struct s_shell
{
	char				*user_input;		// Entrée de l'utilisateur
	t_token				*token_list;		// Liste des tokens générés par le lexer
	t_command			*command_list;		// Liste des commandes générées par le parser
	int					input_fd;			// Descripteur de fichier pour la redirection d'entrée
	int					output_fd;			// Descripteur de fichier pour la redirection de sortie
	pid_t				last_process_id;	// PID du dernier processus exécuté
	int					pipe_fds[2];		// Descripteurs pour les pipes
	int					wait_status;		// Statut de la dernière commande exécutée
	char				*command_path;		// Chemin complet vers l'exécutable de la commande
	char				**env_vars;			// Tableau des variables d'environnement
	char				*heredoc_tempfile;	// Fichier temporaire pour le heredoc
	int					saved_stdin_fd;		// Descripteur de fichier pour sauvegarder stdin
	int					last_exit_status;	// Statut de sortie de la dernière commande exécutée
	t_env				*env_var_list;		// Liste des variables d'environnement
} t_shell;


/*
-------------------------------------------------------------
|                       FONCTIONS                            |
-------------------------------------------------------------
*/


// PARSING
// Tokens
t_token *ft_create_token(int type, char *value);
void ft_add_token(t_shell *shell, t_token *new_token);
//Fonctions pour create et add simultanément un token
void ft_create_add_token(t_shell *shell, int type, char *value); 

// Utils
int ft_skip_whitespace(char *input, int i); 
int ft_handle_quotes(char *input, int i, char *quote_char); 
t_token_type ft_determine_token_type(char *input, int start, int is_first_token); 
void ft_tokenize_input(char *input, t_shell *shell);




char **parse_input(char *input);		// Fonction pour analyser l'entrée utilisateur
int lexer(t_shell *shell);				// Generation des tokens
int parser(t_shell *shell);				// Generation de l'AST


// Exec
void execute_command(t_command *cmd); // Fonction pour exécuter une commande
int executor(t_shell *shell);
// Built-In
void ft_export(t_shell *shell);


int init_shell(t_shell *shell, char **env);

// Env Var
t_env *init_env_vars(char **env);
t_env *init_default_env_vars(void);
t_env *create_env_var_node(char *env_str);
t_env *create_default_env_var_node(char *var_name, char *value);
void add_env_var_to_list(t_env **head, t_env *new_var);
void global_exit_env(t_shell *shell, int status);
void free_env_var_list(t_env *env);


// Display
void ft_print_tokens(t_token *token_list);

// Utils
int ft_isspace(char c); 


// Cleaning
void ft_free_cmd_args(char **cmd_args);
// void ft_free_command_list(t_command *command_list); Pas utilisée pour l'instant 
void   	ft_free_commands_args(char **args); 



// Exit
void handle_exit(t_shell *shell);
void handle_sigint(int sig);
void setup_signal_handlers(void);

#endif // MINISHELL_H