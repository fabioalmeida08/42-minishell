/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:41:14 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/15 14:41:46 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_ast(t_ast *node, int depth)
{
    if (!node)
        return;

    // indentação
    for (int i = 0; i < depth; i++)
        printf("  ");

    // tipo do nó
    if (node->type == CMD_NODE)
    {
        printf("CMD_NODE: ");
        for (int i = 0; node->args[i]; i++)
            printf("%s ", node->args[i]);
        printf("\n");

        if (node->in)
            printf("%*sIN REDIR: %s\n", depth * 2 + 2, "", node->in->file);
        if (node->out)
            printf("%*sOUT REDIR: %s\n", depth * 2 + 2, "", node->out->file);
    }
    else if (node->type == PIPE_NODE)
    {
        printf("PIPE_NODE\n");
    }

    // recursão
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}
