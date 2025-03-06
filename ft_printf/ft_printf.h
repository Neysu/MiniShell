/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 03:04:09 by elliot            #+#    #+#             */
/*   Updated: 2025/02/18 01:28:55 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft/libft.h"

int		ft_printf(const char *str, ...);
int		ft_ptrlen(unsigned long n);
int		ft_puthex(unsigned int n, char c);
int		ft_putptr(unsigned long long n);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putunbr(unsigned int n);
size_t	ft_strlen(const char *str);
int		ft_putn(int n);
int		ft_intlen(long n);
int		ft_hexlen(unsigned int n);
void	ft_tohex(unsigned int num, char c);
char	*ft_strrev(char *s);
void	ft_toptr(unsigned long long num);

#endif
