/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:57:35 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/14 16:45:43 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define INITIAL_SIZE 128

static char	*append_char_to_line(char *line, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(line, buf);
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (tmp);
}

char	*ft_readline(void)
{
	char	buf;
	char	*line;
	ssize_t	bytes;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	bytes = read(0, &buf, 1);
	while (bytes > 0)
	{
		if (buf == '\n')
			break ;
		line = append_char_to_line(line, buf);
		if (!line)
			return (NULL);
		bytes = read(0, &buf, 1);
	}
	if ((bytes <= 0 && *line == '\0') || !line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static t_boolean	read_and_write_heredoc_lines(int fd, char *delimiter,
	char **envp, int *backup)
{
	char	*str;

	while (1)
	{
		write(1, "> ", 2);
		str = ft_readline();
		if (g_status == STATUS_SIGINT_HEREDOC || !str)
		{
			free(str);
			if (g_status != STATUS_SIGINT_HEREDOC)
				return (printf(ST, delimiter), TRUE);
			return (FALSE);
		}
		if (ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(str) == ft_strlen(delimiter))
		{
			free(str);
			break ;
		}
		str = ft_expander(str, envp, backup);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	return (TRUE);
}

t_boolean	ft_heredoc(char *delimiter, int *backup, char **envp, char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0644);
	if (fd <= 0)
		return (FALSE);
	g_status = STATUS_OK;
	setup_heredoc_signals();
	if (read_and_write_heredoc_lines(fd, delimiter, envp, backup))
	{
		close(fd);
		if (g_status == STATUS_SIGINT_HEREDOC)
			backup[EXIT_STATUS] = 130;
		g_status = STATUS_OK;
		return (TRUE);
	}
	if (close(fd) < 0)
		return (FALSE);
	return (TRUE);
}
