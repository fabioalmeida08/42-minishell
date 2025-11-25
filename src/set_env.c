/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:13:12 by bolegari          #+#    #+#             */
/*   Updated: 2025/11/25 10:55:32 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	key_value_breaker(char **envp, int i, char **key, char **value)
{
	char	*eq;

	eq = strchr(envp[i], '=');
	if (eq)
	{
		*key = ft_substr(envp[i], 0, eq - envp[i]);
		*value = ft_substr(envp[i], (eq - envp[i]) + 1, ft_strlen(eq + 1));
	}
	else
	{
		*key = ft_strdup(envp[i]);
		*value = NULL;
	}
}

static int	set_env_list(char **key, char **value, t_shell *shell_vars)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->key = *key;
	new_node->value = *value;
	new_node->next = NULL;
	if (shell_vars->env_list == NULL)
		shell_vars->env_list = new_node;
	else
	{
		temp = shell_vars->env_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (1);
}

t_env	*get_key_env_list(t_env *env_list, char *str)
{
	t_env	*temp;
	t_env	*found;

	temp = env_list;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, str))
		{
			found = temp;
			return (found);
		}
		temp = temp->next;
	}
	return (NULL);
}

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list != NULL)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	init_env(char **envp, t_shell *shell_vars)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*test;

	i = 0;
	shell_vars->envp = envp;
	shell_vars->env_list = NULL;
	while (envp[i])
	{	
		key_value_breaker(envp, i, &key, &value);
		if (!(set_env_list(&key, &value, shell_vars)))
		{
			free(key);
			free(value);
			break ;
		}
		i++;
	}
	test = get_key_env_list(shell_vars->env_list, "PATH");
	printf("TEST key %s | value %s\n", test->key, test->value);
	free_env_list(shell_vars->env_list);
}
