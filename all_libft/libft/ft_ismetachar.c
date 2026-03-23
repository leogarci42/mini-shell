/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismetachar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 04:04:26 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 15:19:53 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ismetachar(char c)
{
	int		i;
	char	meta_chars[3];

	meta_chars[0] = '|';
	meta_chars[1] = '<';
	meta_chars[2] = '>';
	i = 0;
	while (meta_chars[i] != '\0')
	{
		if (meta_chars[i] == c)
			return (1);
		i++;
	}
	return (0);
}
