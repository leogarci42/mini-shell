/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:42:56 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/21 20:42:58 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

int		ft_strlen1(char *str);
char	*get_a_line(int fd, char *str);
char	*get_next_line(int fd);
char	*ft_uptstrjoin(char *s1, char const *s2);
int		checkline(char *str);

#endif
