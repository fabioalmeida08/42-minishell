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

static void	key_value_breaker(char *envp, char **key, char **value)
{
	char	*eq;

	eq = strchr(envp, '=');
	if (eq)
	{
		*eq = 0;
		*key = ft_strdup(envp);
		*value = ft_strdup(eq + 1);
		*eq = '=';
	}
	else
	{
		*key = ft_strdup(envp);
		*value = NULL;
	}
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	if (!new_node->key || (value && !new_node->value))
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

int	append_env_list(t_env **head, t_env *new_node)
{
	t_env	*temp;

	if (!new_node)
		return (0);
	if (*head == NULL)
	{
		*head = new_node;
		return (1);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return (1);
}

void	free_env_list(t_env *head)
{
	t_env *temp;

	while(head)
	{
		temp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = temp;
	}
}

t_env	*get_env_node(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*node;

	node = get_env_node(env_list, key);
	if (node)
		return (node->value);
	else
		return (NULL);
}

int	add_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (!new_node)
		return (0);
	return append_env_list(env_list, new_node);
}

int	update_env_var(t_env *env_list, char *key, char *value)
{
	t_env	*node;

	node = get_env_node(env_list, key);
	if (!node)
		return (0);
	free(node->value);
	node->value = ft_strdup(value);
	return (node->value != NULL);
}

int	remove_env_var(t_env **env_list, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env_list;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, key))
		{
			if (prev)
				prev->next = temp->next;
			else
				*env_list = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

void	init_env(char **envp, t_shell *shell_vars)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*node;
	t_env	*temp;
	t_env	*test;

	i = 0;
	shell_vars->envp = envp;
	shell_vars->env_list = NULL;
	while (envp[i])
	{	
		key_value_breaker(envp[i], &key, &value);
		node = create_env_node(key, value);
		free(key);
		free(value);
		if (!append_env_list(&shell_vars->env_list, node))
		{
			free_env_list(shell_vars->env_list);
			return ;
		}
		i++;
	}
	test = get_env_node(shell_vars->env_list, "NAME");
	printf("KEY %s | VALUE %s\n", test->key, test->value);
	printf("%s\n", get_env_value(shell_vars->env_list, "NAME"));
	free_env_list(shell_vars->env_list);
}
