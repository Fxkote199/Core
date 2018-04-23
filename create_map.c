//
//  create_map.c
//  pr_corewar
//
//  Created by Kostiantyn MYKHAILENKO on 4/21/18.
//  Copyright © 2018 Kostiantyn MYKHAILENKO. All rights reserved.
//

#include "vm_header.h"

int		ft_set_value(int i, int c)
{
	int val;

	val = 0;
	if (!c)
		val = 0;
	else if (c == 1)
		val = (!i || i == 8 || i == 11 || i == 14) ? 0 : 1;
	else if (c == 2)
	{
		(i == 0 || i == 3 || i == 4 || i == 12) ? (val = 10) : 0;
		(i == 1 || i ==2) ? (val = 5) : 0;
		(i >= 5 && i <= 7) ? (val = 6) : 0;
		(i == 8) ? (val = 20) : 0;
		(i == 9 || i == 10) ? (val = 25) : 0;
		(i == 11) ? (val = 800) : 0;
		(i == 13) ? (val = 50) : 0;
		(i == 14) ? (val = 1000) : 0;
		(i == 15) ? (val = 2) : 0;
	}
	else if (c == 3)
		val = (c == 3 && ((i >= 0 && i < 8) || i == 12 || i == 15)) ? 4 : 2;
	return (val);
}

int     ft_step_pc(t_map *map, int num)
{
	int     step;
	
	step = 0;
	if (map->arg[0])
	{
		if (map->arg[0] == 1)
			step += 1;
		if (map->arg[0] == 2)
			step += map->label[num][3];
		if (map->arg[0] == 3)
			step += 2;
	}
	if (map->arg[1])
	{
		if (map->arg[1] == 1)
			step += 1;
		if (map->arg[1] == 2)
			step += map->label[num][3];
		if (map->arg[1] == 3)
			step += 2;
	}
	if (map->arg[2])
	{
		if (map->arg[2] == 1)
			step += 1;
		if (map->arg[2] == 2)
			step += map->label[num][3];
	}
	map->arg[0] = 0;
	map->arg[1] = 0;
	map->arg[2] = 0;
	return (step);
}

void    ft_check_codage(t_map *map, uint8_t num)
{
	int     i;

	i = 1;
	map->codage = num;
	while (1)
	{
		if ((i == 1 || i == 2))
		{
			map->arg[0] = map->arg[0] << 1;
			map->arg[0] += (num >= 128) ? 1 : 0;
		}
		if (i == 3 || i == 4)
		{
			map->arg[1] = map->arg[1] << 1;
			map->arg[1] += (num >= 128) ? 1 : 0;
		}
		if (i == 5 || i == 6)
		{
			map->arg[2] = map->arg[2] << 1;
			map->arg[2] += (num >= 128) ? 1 :0;
		}
		if (num == 0)
			break ;
		num = num << 1;
		i++;
	}
}

void	ft_walk_on_array(t_map *map, t_reg *reg)
{

	map->pc = 0;
	while (map->pc < 100)
	{
		STEP = 1;
		if (CODE_OF_BOT[map->pc] >= 16) //ВЫХОД
			exit(1);
		if (CODE_OF_BOT[map->pc] != 1 &&  CODE_OF_BOT[map->pc] != 8 && \
		CODE_OF_BOT[map->pc] != 12 && CODE_OF_BOT[map->pc] != 15 && CODE_OF_BOT[map->pc] != 16)
		{
			if (map->pc + 1 < map->cnt_bot)
				ft_check_codage(map, CODE_OF_BOT[map->pc + 1]);
			else
				exit(1);
			ft_implement_command(map, reg, CODE_OF_BOT[map->pc]);
			STEP += ft_step_pc(map, CODE_OF_BOT[map->pc]);
			map->pc += STEP;//step carrete
		}
		else
		{
			//НУЖНО НАПИСАТЬ ИСКЛЮЧЕНИЯ ДЛЯ ТАКИХ КОМАНД КАК FORK........
		}
		map->pc++;
	}
}

void	ft_table_label(t_map *map, t_reg *reg)
{
	int  i;
	int c;

	i = 0;
	map->label = (int**)malloc(sizeof(int*) * 17);
	while (i < 16)
	{
		c = 0;
		map->label[i] = (int*)malloc(sizeof(int) * 5);
		while (c < 4)
		{
			map->label[i][c] = ft_set_value(i, c);
			c++;
		}
		i++;
	}
	ft_walk_on_array(map, reg);
}
