/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_outils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:35:44 by ebaillot          #+#    #+#             */
/*   Updated: 2024/09/22 11:28:40 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define PATH_MAX_SIZE 1000

int handle_cd_error(t_error_info error_info, t_shell *shell, char *s1, char *s2)
{
	handle_error_non_critical(error_info.filepath, error_info.error_message,
									  error_info.exit_code, shell);
	free(s1);
	free(s2);
	return (1);
}

void free_segments(char **segments)
{
	int i;

	i = 0;
	if (segments)
	{
		while (segments[i])
		{
			free(segments[i]);
			i++;
		}
		free(segments);
	}
}

char **split_path_segments(const char *path)
{
	char **segments;

	segments = ft_split(path, '/');
	return (segments);
}

char *combine_paths(const char *current_path, const char *path)
{
	char *combined;
	char *temp;

	combined = ft_strjoin(current_path, "/");
	if (!combined)
		return (NULL);
	temp = ft_strjoin(combined, path);
	free(combined);
	if (!temp)
		return (NULL);
	return (temp);
}

void process_segment(const char *segment, char **stack, int *top)
{
	if (ft_strcmp(segment, ".") == 0)
	{
	}
	else if (ft_strcmp(segment, "..") == 0)
	{
		if (*top >= 0)
			(*top)--;
	}
	else
	{
		(*top)++;
		stack[*top] = (char *)segment;
	}
}

char **duplicate_stack(char **stack, int top)
{
	char **resolved;
	int j;

	resolved = (char **)malloc((top + 2) * sizeof(char *));
	if (!resolved)
		return (NULL);
	j = 0;
	while (j <= top)
	{
		resolved[j] = ft_strdup(stack[j]);
		if (!resolved[j])
		{
			while (j > 0)
				free(resolved[--j]);
			free(resolved);
			return (NULL);
		}
		j++;
	}
	resolved[j] = NULL;
	return (resolved);
}
// Функция для обработки всех сегментов
char **resolve_segments(char **segments, int *new_count)
{
	char *stack[PATH_MAX_SIZE];
	int top;
	int i;
	char **resolved_segments;

	top = -1;
	i = 0;
	while (segments[i])
	{
		process_segment(segments[i], stack, &top);
		i++;
	}
	resolved_segments = duplicate_stack(stack, top);
	if (!resolved_segments)
		return (NULL);
	*new_count = top + 1;
	return (resolved_segments);
}

char *build_normalized_path(char **segments)
{
	char *normalized;
	int i;

	normalized = (char *)malloc(PATH_MAX_SIZE);
	if (!normalized)
		return (NULL);
	normalized[0] = '\0';
	if (!segments[0])
	{
		ft_strncpy(normalized, "/", PATH_MAX_SIZE);
		return (normalized);
	}
	i = 0;
	while (segments[i])
	{
		ft_strlcat(normalized, "/", PATH_MAX_SIZE);
		ft_strlcat(normalized, segments[i], PATH_MAX_SIZE);
		i++;
	}
	if (ft_strlen(normalized) > 1 && normalized[ft_strlen(normalized) - 1] == '/')
		normalized[ft_strlen(normalized) - 1] = '\0';
	return (normalized);
}

char *normalize_path(const char *current_path, const char *path)
{
	char **segments;
	char **resolved_segments;
	char *normalized;
	char *combined_path;
	int new_count;

	new_count = 0;
	if (path[0] == '/')
		segments = split_path_segments(path);
	else
	{
		combined_path = combine_paths(current_path, path);
		if (!combined_path)
			return (NULL);
		segments = split_path_segments(combined_path);
		free(combined_path);
	}
	resolved_segments = resolve_segments(segments, &new_count);
	free_segments(segments);
	if (!resolved_segments)
		return (NULL);
	normalized = build_normalized_path(resolved_segments);
	free_segments(resolved_segments);
	return (normalized);
}

void ft_update_pwd(t_shell *shell, const char *path)
{
	char *old_dir = ft_getenv(shell->env_var_list, "PWD");
	if (!old_dir)
	{
		handle_error_non_critical("cd", "PWD not set", 1, shell);
		return;
	}

	char *new_pwd = normalize_path(old_dir, path);
	if (!new_pwd)
	{
		handle_error_non_critical("cd", "Failed to normalize path", 1, shell);
		free(old_dir);
		return;
	}

	ft_setenv(&shell->env_var_list, "OLDPWD", old_dir);
	ft_setenv(&shell->env_var_list, "PWD", new_pwd);

	free(old_dir);
	free(new_pwd);
}

int ft_fd_minus(t_shell *shell, int option)
{
	(void)option;
	char *oldpwd;
	char *pwd;

	pwd = ft_getenv(shell->env_var_list, "PWD");
	oldpwd = ft_getenv(shell->env_var_list, "OLDPWD");

	if (!oldpwd)
		return handle_cd_error((t_error_info){"cd", "OLDPWD not set", 1}, shell, oldpwd, pwd);
	if (!pwd)
		return handle_cd_error((t_error_info){"cd", "PWD not set", 1}, shell, oldpwd, pwd);
	if (chdir(oldpwd) == -1)
		return handle_cd_error((t_error_info){"cd", ft_strdup(strerror(errno)), 1}, shell, oldpwd, pwd);

	ft_setenv(&shell->env_var_list, "OLDPWD", pwd);
	ft_setenv(&shell->env_var_list, "PWD", oldpwd);

	free(oldpwd);
	free(pwd);

	return 0;
}
