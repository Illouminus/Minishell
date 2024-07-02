/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:39:56 by ebaillot          #+#    #+#             */
/*   Updated: 2024/07/02 14:37:18 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_ARGS 100

typedef struct s_token
{
	int tok_type;				  // Type de token (commande, argument, opérateur de redirection)
	char *tok_value;			  // Valeur du token (texte de la commande ou de l'argument)
	int quote_status;			  // Statut des guillemets (simple, double ou aucun)
	struct s_token *next_tok; // Pointeur vers le token suivant
	struct s_token *prev_tok; // Pointeur vers le token précédent
} t_token;

typedef struct s_command
{
	char **cmd_args;				 // Nom de la commande et ses arguments
	bool is_builtin_cmd;			 // Indicateur si la commande est une commande intégrée
	t_token *redir_tokens;		 // Liste des redirections associées à la commande
	struct s_command *next_cmd; // Pointeur vers la commande suivante
	struct s_command *prev_cmd; // Pointeur vers la commande précédente
} t_command;

typedef struct s_env
{
	char *env_var_name;		// Nom de la variable d'environnement
	char *env_value;			// Valeur de la variable d'environnement
	struct s_env *next_env; // Pointeur vers la variable d'environnement suivante
} t_env;

typedef struct s_shell
{
	char *user_input;			 // Entrée de l'utilisateur
	t_token *token_list;		 // Liste des tokens générés par le lexer
	t_command *command_list; // Liste des commandes générées par le parser
	int input_fd;				 // Descripteur de fichier pour la redirection d'entrée
	int output_fd;				 // Descripteur de fichier pour la redirection de sortie
	pid_t last_process_id;	 // PID du dernier processus exécuté
	int pipe_fds[2];			 // Descripteurs pour les pipes
	int wait_status;			 // Statut de la dernière commande exécutée
	char *command_path;		 // Chemin complet vers l'exécutable de la commande
	char **env_vars;			 // Tableau des variables d'environnement
	char *heredoc_tempfile;	 // Fichier temporaire pour le heredoc
	int saved_stdin_fd;		 // Descripteur de fichier pour sauvegarder stdin
	int last_exit_status;	 // Statut de sortie de la dernière commande exécutée
	t_env *env_var_list;		 // Liste des variables d'environnement
} t_shell;

char **parse_input(char *input);		  // Fonction pour analyser l'entrée utilisateur
void execute_command(t_command *cmd); // Fonction pour exécuter une commande

int init_shell(t_shell *shell, char **env);

// fonction for env var

t_env *init_env_vars(char **env);
t_env *create_env_var_node(char *env_str);
t_env *create_default_env_var_node(char *var_name, char *value);
t_env *init_default_env_vars(void);
void add_env_var_to_list(t_env **head, t_env *new_var);
t_env *create_default_env_var_node(char *var_name, char *value);
void free_env_var_list(t_env *head);
#endif // MINISHELL_H