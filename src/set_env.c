/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:13:12 by bolegari          #+#    #+#             */
/*   Updated: 2025/11/24 20:26:00 by bolegari         ###   ########.fr       */
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
	{
		shell_vars->env_list = new_node;
	}
	else
	{
		temp = shell_vars->env_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (1);
}

static void print_env_list(t_env *env_list)
{
	t_env	*temp = env_list;
	while (temp != NULL)
	{
		printf("key: %s | value: %s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void get_key_env_list(t_env *env_list, char *str)
{
    t_env	*temp = env_list;
	t_env	*found;

    while (temp != NULL)
	{
		if (ft_strcmp(temp->key, str))
		{
			found = temp;
			printf("FOUND key: %s | value: %s\n", found->key, found->value);
		}
		temp = temp->next;
	}
}

void	init_env(char **envp, t_shell *shell_vars)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	shell_vars->envp = envp;
	shell_vars->env_list = NULL;
	while (envp[i])
	{	
		key_value_breaker(envp, i, &key, &value);
		if (!(set_env_list(&key, &value, shell_vars)))
			break;
		i++;
	}
	print_env_list(shell_vars->env_list);
	get_key_env_list(shell_vars->env_list, "PATH");
}
