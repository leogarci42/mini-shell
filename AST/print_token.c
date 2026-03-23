/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:40:17 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/05 13:51:11 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokenizer.h"

#define COLOR_RESET   "\033[0m"
#define COLOR_WORD    "\033[1;32m"
#define COLOR_CMD     "\033[1;92m"
#define COLOR_ARG     "\033[1;96m"
#define COLOR_PIPE    "\033[1;34m"
#define COLOR_REDIR   "\033[1;35m"
#define COLOR_LOGIC   "\033[1;36m"
#define COLOR_PARENT  "\033[1;33m"
#define COLOR_QUOTE   "\033[1;31m"
#define COLOR_LABEL   "\033[0;37m"

const char *get_token_name(t_token type)
{
	switch (type)
	{
		case WORD:         return "WORD";
		case PIPE:         return "PIPE";
		case REDIR_IN:     return "REDIR_IN";
		case REDIR_OUT:    return "REDIR_OUT";
		case REDIR_APPEN:  return "REDIR_APPEN";
		case HERE_DOC:     return "HERE_DOC";
		case AND:          return "AND";
		case OR:           return "OR";
		case PARENT_IN:    return "PARENT_IN";
		case PARENT_OUT:   return "PARENT_OUT";
		case SINGLE_QUOTE: return "SINGLE_QUOTE";
		case DOUBLE_QUOTE: return "DOUBLE_QUOTE";
		default:           return "UNKNOWN";
	}
}

const char *get_token_color(t_token type)
{
	switch (type)
	{
		case WORD:         return COLOR_WORD;
		case PIPE:         return COLOR_PIPE;
		case REDIR_IN:
		case REDIR_OUT:
		case REDIR_APPEN:  return COLOR_REDIR;
		case HERE_DOC:     return COLOR_REDIR;
		case AND:
		case OR:           return COLOR_LOGIC;
		case PARENT_IN:
		case PARENT_OUT:   return COLOR_PARENT;
		case SINGLE_QUOTE:
		case DOUBLE_QUOTE: return COLOR_QUOTE;
		default:           return COLOR_RESET;
	}
}

const char *get_role_name(t_role role)
{
	switch (role)
	{
		case NONE: return "NONE";
		case STATE_CMD:  return "STATE_CMD";
		case STATE_ARGS: return "STATE_ARG";
		case STATE_AND:	 return "STATE_AND";
		case STATE_OR:	 return "STATE_OR";
		case STATE_PIPE:	 return "STATE_PIPE";
		case STATE_REDIR_IN:	 return "STATE_REDIR_IN";
		case STATE_REDIR_OUT:	 return "STATE_REDIR_OUT";
		case STATE_REDIR_OUT_TARGET:	 return "STATE_REDIR_OUT_TARGET";
		case STATE_REDIR_IN_TARGET:	 return "STATE_REDIR_IN_TARGET";
        case STATE_APPEN:   return "STATE_APPEN";
        case STATE_APPEN_TARGET:    return "STATE_APPEN_TARGET";
        case STATE_HEREDOC: return "STATE_HEREDOC";
        case STATE_HEREDOC_DOC: return "STATE_HEREDOC_DOC";
        default:   return "UNKNOWN";
	}
}

const char *get_role_color(t_role role)
{
	switch (role)
	{
		case STATE_CMD:  return COLOR_CMD;
		case STATE_ARGS: return COLOR_ARG;
		case STATE_AND:	 return COLOR_LOGIC;
		case STATE_OR:	 return COLOR_LOGIC;
		case STATE_PIPE:	 return COLOR_PIPE;
		case STATE_REDIR_IN:	 return COLOR_REDIR;
		case STATE_REDIR_OUT:	 return COLOR_REDIR;
		case STATE_REDIR_OUT_TARGET:	 return COLOR_REDIR;
		case STATE_REDIR_IN_TARGET:	 return COLOR_REDIR;
        case STATE_APPEN:   return COLOR_REDIR;
        case STATE_APPEN_TARGET:    return COLOR_REDIR;
        case STATE_HEREDOC: return COLOR_REDIR;
        case STATE_HEREDOC_DOC: return COLOR_REDIR;
        case NONE: return COLOR_WORD;
		default:   return COLOR_RESET;
	}
}

void print_token_list(t_tokenizer *head)
{
	printf("\n\033[1m======= Token List =======\033[0m\n\n");
	while (head != NULL) {
		const char *type_name = get_token_name(head->type);
		const char *type_color = get_token_color(head->type);
		const char *role_name = get_role_name(head->role);
		const char *role_color = get_role_color(head->role);
		printf("%sType:%s %s%-13s%s  ", COLOR_LABEL, 
		COLOR_RESET, type_color, type_name, COLOR_RESET);
		printf("%sState:%s %s%-5s%s  ", COLOR_LABEL, 
		COLOR_RESET, role_color, role_name, COLOR_RESET);
		printf("%sValue:%s %s\n", COLOR_LABEL, COLOR_RESET, head->value);
		head = head->next;
	}
	printf("\n\033[1m===========================\033[0m\n\n");
}
