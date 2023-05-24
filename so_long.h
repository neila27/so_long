/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/05/24 16:38:56 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG.H
# define SO_LONG.H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <mlx.h>
# include "libft.h"

typedef struct s_list_data {
	void    *mlx_ptr;
    void    *mlx_wind;
    char    *map;
    int     nbr_player;
    int     exit;
    int     coin;
    int     nbr_rows;
    int     columns;

}			t_list_data;

#endif
