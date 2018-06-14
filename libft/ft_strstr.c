/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 10:07:27 by vmazurok          #+#    #+#             */
/*   Updated: 2017/09/26 10:09:06 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	int l1;
	int l2;

	l1 = 0;
	if (to_find[0] == 0)
		return ((char *)str);
	while (str[l1] != '\0')
	{
		l2 = 0;
		while (str[l1] == to_find[l2])
		{
			if (to_find[l2 + 1] == '\0')
			{
				return (&(*(char *)(str + l1 - l2)));
			}
			l1++;
			l2++;
		}
		l1 = l1 - l2;
		l1++;
	}
	return (0);
}
