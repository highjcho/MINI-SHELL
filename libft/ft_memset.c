/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonkim <jonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:34:47 by hyunjcho          #+#    #+#             */
/*   Updated: 2022/06/08 18:37:45 by jonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*s, int	c, size_t	len)
{
	unsigned char	*ptr;

	ptr = s;
	while (len-- > 0)
		*ptr++ = (unsigned char)c;
	return (s);
}