/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:15:23 by edouard           #+#    #+#             */
/*   Updated: 2024/08/30 14:19:14 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free redirection list and handle potential errors safely
static void free_redirections(t_redir **redir)
{
    t_redir *temp;

    while (*redir)
    {
        temp = *redir;
        *redir = (*redir)->next;

        // Unlink and free filename only if it exists and matches the heredoc name
        if (temp->filename && ft_strcmp(temp->filename, "minishell_heredoc") == 0)
        {
            unlink(temp->filename);
        }

        // Free the filename and set pointer to NULL for safety
        if (temp->filename)
        {
            free(temp->filename);
            temp->filename = NULL;
        }

        // Free the redirection node and set pointer to NULL for safety
        free(temp);
        temp = NULL;
    }

    // Ensure the redirection list pointer is NULL after freeing
    *redir = NULL;
}

// Free command arguments
static void free_command_args(char **cmd_args)
{
    if (cmd_args)
    {	
        char **args = cmd_args;
        while (*args)
        {
			if(*args)
            	free(*args);  // Free each argument
            *args = NULL; // Set to NULL for safety
            args++;
        }
        free(cmd_args);  // Free the array of pointers
        cmd_args = NULL; // Set pointer to NULL for safety
    }
	return ;
}

// Free command list and handle potential errors safely
static void free_commands(t_command **command_list)
{
    t_command *cmd_temp;

    while (*command_list)
    {
        cmd_temp = *command_list;
        *command_list = (*command_list)->next_cmd;

        // Free command value if it exists
        if (cmd_temp->cmd_value)
        {
            free(cmd_temp->cmd_value);
            cmd_temp->cmd_value = NULL;
        }

        // Free command arguments
		if(cmd_temp->cmd_args)
		{
		free_command_args(cmd_temp->cmd_args);
		}
        	

        // Free redirections if they exist
        if (cmd_temp->redirections)
        {
            free_redirections(&cmd_temp->redirections);
        }

        // Free the command node and set pointer to NULL for safety
        free(cmd_temp);
        cmd_temp = NULL;
    }

    // Ensure the command list pointer is NULL after freeing
    *command_list = NULL;
}

// Free token list and handle potential errors safely
static void free_tokens(t_token **token_list)
{
    t_token *tok_temp;

    while (*token_list)
    {
        tok_temp = *token_list;
        *token_list = (*token_list)->next_tok;

        // Free token value if it exists
        if (tok_temp->tok_value)
        {
            free(tok_temp->tok_value);
            tok_temp->tok_value = NULL;
        }

        // Free the token node and set pointer to NULL for safety
        free(tok_temp);
        tok_temp = NULL;
    }

    // Ensure the token list pointer is NULL after freeing
    *token_list = NULL;
}

// Free the entire shell structure
void free_shell(t_shell *shell)
{
    if (!shell)
        return;

    // Free command list if it exists
    if (shell->command_list)
    {
        free_commands(&shell->command_list);
    }

    // Free token list if it exists
    if (shell->token_list)
    {
        free_tokens(&shell->token_list);
    }

    // Additional shell-specific memory cleanup can be added here
    // e.g., freeing environment variables, history, etc.
}
