/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:08:27 by jsala-ba          #+#    #+#             */
/*   Updated: 2023/09/19 09:26:47 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_alloc(int len, char **ind_ptrs, int cnt)
{
	int		n;
	char	*ptr;

	ptr = malloc(len);
	if (!ptr)
	{
		n = 0;
		while (n < cnt)
		{
			free(ind_ptrs[n]);
			n++;
		}
		free(ind_ptrs);
		return (NULL);
	}
	ind_ptrs[cnt] = ptr;
	return (ptr);
}

static int	ft_strlen_sep(const char *str, char sep)
{
	int	n;

	n = 0;
	while (str[n] && str[n] != sep)
		n++;
	return (n);
}

static int	ft_cpystr(const char *src, char sep, char **ptrs)
{
	int		n;
	int		cnt;
	int		len;
	char	*ptr;

	cnt = 0;
	n = 0;
	while (src[n])
	{
		while ((src[n] == sep) && src[n])
			n++;
		if (!src[n])
			break ;
		len = ft_strlen_sep(src + n, sep);
		ptr = ft_alloc(len + 1, ptrs, cnt);
		if (!ptr)
			return (0);
		cnt++;
		while ((src[n] != sep) && src[n])
			*ptr++ = src[n++];
		*ptr = '\0';
	}
	ptrs[cnt] = 0;
	return (1);
}

static int	ft_strcnt(const char *src, char sep)
{
	int	n;
	int	cnt;

	cnt = 0;
	n = 0;
	while (src[n])
	{
		while ((src[n] == sep) && src[n])
			n++;
		if (!src[n])
			break ;
		cnt++;
		while ((src[n] != sep) && src[n])
			n++;
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**ind_ptr;
	int		ind_size;
	int		cnt;

	if (!s)
		return (NULL);
	cnt = ft_strcnt(s, c);
	ind_size = sizeof(char *) * (cnt + 1);
	ind_ptr = malloc(ind_size);
	if (!ind_ptr)
		return (NULL);
	if (!ft_cpystr(s, c, ind_ptr))
		return (NULL);
	return (ind_ptr);
}
