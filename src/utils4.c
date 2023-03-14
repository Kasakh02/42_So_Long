/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:06 by hcorrea-          #+#    #+#             */
/*   Updated: 2023/03/11 09:47:46 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	rand_nbr_enemy(t_data *data, int i)
{
	int	nbr;

	nbr = rand() % 4;
	if (nbr == 0 && !is_wall_enemy(data, -1, 0, i))
		upgrade_pos_render_map_enemy(data, -50, 0, i);
	else if (nbr == 1 && !is_wall_enemy(data, 1, 0, i))
		upgrade_pos_render_map_enemy(data, 50, 0, i);
	else if (nbr == 2 && !is_wall_enemy(data, 0, 1, i))
		upgrade_pos_render_map_enemy(data, 0, 50, i);
	else if (!is_wall_enemy(data, 0, -1, i))
		upgrade_pos_render_map_enemy(data, 0, -50, i);
}

void	draw_render(t_data *data, int i, int j)
{
	if (data->map->lines[j][i] == '1')
		draw_square(i * 50, j * 50, RED_PIXEL, data);
	else
		draw_square(i * 50, j * 50, BLACK_PIXEL, data);
	if (data->map->lines[j][i] == 'P' && data->pacman->flag != 1)
		render_pacman(data, i, j);
	if (data->map->lines[j][i] == 'E' && data->exit->flag != 1)
		render_exit(data, i, j);
}

void	set_enemies_state(t_data *data, int i)
{
	while (++i < nbr_enemies(data))
	{
		if (data->pacman->curr_pos.x == data->enemy[i]->curr_pos.x
			&& data->pacman->curr_pos.y == data->enemy[i]->curr_pos.y
			&& data->enemy[i]->print)
		{
			if (data->enemy[i]->state == 0)
			{
				data->nbr_enemies_killed++;
				data->enemy[i]->print = 0;
			}
			else
				die(data);
		}
	}
}

void	nbr_enemies_consumables(t_data *data, int i, int j)
{
	struct timeval	now;

	set_enemies_state(data, i);
	while (++j < nbr_consumables(data))
	{
		if (data->pacman->curr_pos.x == data->consumable[j]->curr_pos.x
			&& data->pacman->curr_pos.y == data->consumable[j]->curr_pos.y
			&& data->consumable[j]->print)
		{
			if (data->pacman->nbr_consumables <= nbr_consumables(data))
				data->pacman->nbr_consumables++;
			data->consumable[j]->print = 0;
			gettimeofday(&now, NULL);
			set_enemies_vulnerable(data, 0);
			data->pacman->last_vulnerable = now;
		}
	}
}

int	verify_height(t_data *data, int map_height, int map_width, int i)
{
	while (i < map_height)
	{
		if (data->map->lines[i][0] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map_height)
	{
		if (data->map->lines[i][map_width - 1] == '\0')
		{
			if (data->map->lines[i][map_width - 2] == '\n')
			{
				if (data->map->lines[i][map_width - 3] != '1')
					return (0);
			}
			else if (data->map->lines[i][map_width - 2] != '1')
				return (0);
		}
		else if (data->map->lines[i][map_width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
