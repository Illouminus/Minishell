/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:59:33 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:04:07 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar_fd(n % 10 + '0', fd);
}

/* int main()
{
	printf("Testing ft_putnbr_fd:\n");

	printf("Number: 42\nOutput: \n ");
	ft_putnbr_fd(42, 1);
	printf("\n");

	printf("Number: -42\nOutput: \n");
	ft_putnbr_fd(-42, 1);
	printf("\n");

	printf("Number: 2147483647 (INT_MAX)\nOutput: \n");
	ft_putnbr_fd(2147483647, 1);
	printf("\n");

	printf("Number: -2147483648 (INT_MIN)\nOutput:\n");
	ft_putnbr_fd(-2147483648, 1);
	printf("\n");

	return (0);
} */