/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memmove.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jbastard <jbastard@student.42.fr>		  #+#  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024-10-21 12:13:01 by jbastard		  #+#	#+#			 */
/*   Updated: 2024-10-21 12:13:01 by jbastard		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */
#include "../../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	}
	if (dest <= src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
