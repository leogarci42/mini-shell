/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:26:17 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/06 20:57:53 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOMATE_H
# define AUTOMATE_H

# include "tokenizer.h"

/*				check redir utils			*/

t_boolean	ft_check_cmd(t_tokenizer next);
t_boolean	ft_check_appen_target(t_tokenizer next);
t_boolean	ft_check_heredoc_doc(t_tokenizer next);
t_boolean	ft_check_appen(t_tokenizer next);
t_boolean	ft_check_heredoc(t_tokenizer next);
t_boolean	ft_check_redir_out_target(t_tokenizer next);
t_boolean	ft_check_redir_in_target(t_tokenizer next);
t_boolean	ft_check_redir_out(t_tokenizer next);
t_boolean	ft_check_redir_in(t_tokenizer next);
t_boolean	ft_check_args(t_tokenizer next);
t_boolean	ft_check(t_tokenizer curr, t_tokenizer next);

#endif