/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:44:58 by aamhal            #+#    #+#             */
/*   Updated: 2023/06/05 09:12:50 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_left(char	*data)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (!data[i])
		return (free(data), NULL);
	tmp = malloc((ft_strlen(data) - i) * sizeof(char));
	if (!tmp)
		return (free(data), NULL);
	while (data[i])
	{
		tmp[j] = data[i + 1];
		i++;
		j++;
	}
	free(data);
	return (tmp);
}

static char	*ft_return(char *data)
{
	char	*tmp;
	int		i;

	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	tmp = malloc((i + 2) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[i + 1] = '\0';
	while (i > -1)
	{
		tmp[i] = data[i];
		i--;
	}
	return (tmp);
}

static char	*ft_readfile(int fd, char *data)
{
	char	*buffer;
	int		nb;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	nb = 1;
	while (nb && ft_strchr(data, '\n'))
	{
		nb = read(fd, buffer, BUFFER_SIZE);
		if (nb == 0 && *data)
			break ;
		if (nb <= 0)
			return (free(buffer), free(data), NULL);
		buffer[nb] = '\0';
		data = ft_strjoin(data, buffer);
		if (!data)
			return (free(buffer), free(data), NULL);
	}
	free(buffer);
	return (data);
}

char	*get_next_line(int fd)
{
	static char	*data;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!data)
		data = ft_strdup("");
	data = ft_readfile(fd, data);
	if (!data)
		return (NULL);
	str = ft_return(data);
	data = ft_left(data);
	return (str);
}
