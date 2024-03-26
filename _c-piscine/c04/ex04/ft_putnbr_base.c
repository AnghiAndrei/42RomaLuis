/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:21:25 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/08 20:21:55 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include<unistd.h>

// int controllo(char *base);
// int ft_strlen(char *base);

// void ft_putnbr_base(int nbr, char *base)
// {
//     if(controllo(base))
//     {
//         return (1);
//     }
//     return (0);
// }

// int controllo(char *base)
// {
//     int i;
//     int j;

//     while(i<ft_strlen(base))
//     {
//         while(i<ft_strlen(base))
//         {
//             i++;
//         }
//         j++;
//     }
// }

// void decimalToBase(int num, int base) {
//     char *symbols;
//     int result[32];
//     int index = 0;

//     symbols = "0123456789ABCDEF";
//     while (num > 0) {
//         result[index] = num % base;
//         num /= base;
//         index++;
//     }
//     for (int i = index - 1; i >= 0; i--) {
//         if (base == 16) {
//             printf("%c", symbols[result[i]]);
//         } else {
//             printf("%d", result[i]);
//         }
//     }
// }

// int ft_strlen(char *base)
// {
//     while(*base=='\0')
//         base++
//     return (base);
// }

// int main(){

// }
