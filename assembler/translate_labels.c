/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_labels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:15:08 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/02 22:16:22 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	findlabel(t_list **lst, t_list *labels)
{
	char label[ft_strlen(TOKEN) - ((TTYPE == DIRECT_LABEL) ? 2 : 1)];

	ft_strcpy(label, TOKEN + ((TTYPE == DIRECT_LABEL) ? 2 : 1));
	while (labels)
	{
		if (ft_strequ(label, ((t_label *)(labels->data))->name))
		{
			free(TOKEN);
			TOKEN = ft_itoa(((t_label *)(labels->data))->pos - TOK->pos[2]);
			return ;
		}
		labels = labels->next;
	}
	c_error(lst, LBL);
}

static void	addlabel(t_list **labels, char *token, int pos)
{
	t_label *label;

	if (!(label = (t_label *)malloc(sizeof(t_label))))
		exit(1);
	label->name = ft_strndup(token, (ft_strlen(token) - 1));
	label->pos = pos;
	ld_push_back(labels, label);
}

static void	lbcondel(t_list **labels)
{
	t_label	*label;

	if (labels && *labels && (label = (t_label *)((*labels)->data)))
	{
		ft_memdel((void **)&label->name);
		ft_memdel((void **)&(*labels)->data);
	}
}

void		translate_labels(t_list **lst)
{
	t_list	*head;
	t_list	*labels;

	head = *lst;
	labels = NULL;
	while (*lst)
	{
		if (TTYPE == LABEL)
			addlabel(&labels, TOK->token, TOK->pos[2]);
		*lst = (*lst)->next;
	}
	*lst = head;
	while (*lst)
	{
		if (TTYPE == DIRECT_LABEL || TTYPE == INDIRECT_LABEL)
			findlabel(lst, labels);
		*lst = (*lst)->next;
	}
	*lst = head;
	l_delall(&labels, lbcondel);
}
