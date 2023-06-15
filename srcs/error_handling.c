/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:05:38 by gmattei           #+#    #+#             */
/*   Updated: 2023/06/15 17:05:40 by gmattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int err(int error)
{
    if(error == 1)
        printf("Error: negative digits not allowed\n");
    else if(error == 2)
        printf("Error: invalid argument\n");
    else if(error == 3)
        printf("Error: memory allocation\n");
    else if(error == 4)
        printf("Error: invalid number of arguments\n");
    else if(error == 5)
        printf("Error: invalid thread creation\n");
    return(-1);
}
