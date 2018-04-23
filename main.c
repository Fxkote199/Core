//
//  main.c
//  pr_corewar
//
//  Created by Kostiantyn MYKHAILENKO on 4/18/18.
//  Copyright © 2018 Kostiantyn MYKHAILENKO. All rights reserved.
//
/*
    ПРИНИМАЮ И ЧЕКАЮ ФАЙЛ
 */
#include "vm_header.h"

void	ft_init_map(t_map *map, t_reg *reg)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (i < 3)
	{
		map->arg[i] = 0;
		CODE_CODAGE[i++] = 0;
	}
	while (c < 16)
	{
		i = 0;
		while (i < 4)
			reg->rg[c][i++] = 0;
		c++;
	}
	reg->big_end = 0;
	LINE = NULL;
	MAPA = NULL;
	CODE_OF_BOT = NULL;
	map->fake = 0;
	map->cnt_bot = 0;
	STEP = 1;
	map->label = NULL;
	MAGIC_NB = 0;
	COMMENT = 0;
	BOT_NAME = 0;
	map->val = 0;
	map->codage = 0;
	map->pc = 0;
}

void	ft_realloc_uint(t_map *map, unsigned char ch)
{
	uint8_t *tmp;
	int		i;

	i = 0;
	if (!map->cnt_bot)
	{
		CODE_OF_BOT = (uint8_t*)malloc(sizeof(uint8_t) * 1);
		CODE_OF_BOT[map->cnt_bot] = ch;
	}
	else
	{
		tmp = (uint8_t*)malloc(sizeof(uint8_t) * map->cnt_bot);
		while (i < map->cnt_bot)
		{
			tmp[i] = CODE_OF_BOT[i];
			i++;
		}
		i = 0;
		free(CODE_OF_BOT);
		CODE_OF_BOT = (uint8_t*)malloc(sizeof(uint8_t) * (map->cnt_bot + 1));
		while (i < map->cnt_bot)
		{
			CODE_OF_BOT[i] = tmp[i];
			i++;
		}
		CODE_OF_BOT[i] = ch;
		free(tmp);
	}
}

void	ft_check_bot(t_map *map, int fd)
{
	int i;
	int c;
	unsigned char ch;
	unsigned char buff[TOTAL_SIZE];

	i = 0;
	c = 0;
	if (read(fd, buff, TOTAL_SIZE) < 0)
		exit(1);
	while (i < TOTAL_SIZE)
	{
		map->val += ft_atoi(ft_itoa_base(buff[i], 10));
		(i < 3) ? (map->val = map->val << 8) : 0;
		if (i == 3)
		{
			if (map->val != COREWAR_EXEC_MAGIC)
				exit(1);
			map->val = 0;
		}
		(i > 3 && i < PROG_NAME_LENGTH && map->val) ? (BOT_NAME = 1) : 0;
		(i == PROG_NAME_LENGTH - 1) ? (map->val = 0) : 0;
		(i >= PROG_NAME_LENGTH && i < TOTAL_SIZE && map->val) ? (COMMENT = 1) : 0;
		i++;
	}
	while (read(fd, &ch, 1))
	{
		if (ch != 0)
			c = 1;
		(c) ? ft_realloc_uint(map, ch) : 0;
		map->cnt_bot += (c) ? 1 : 0;
	}
	if (!BOT_NAME || !COMMENT)
		exit(1);
}

int main()
{
    int fd;
	int i;

	i = 0;
	t_map *map;
	t_reg *reg;
	fd = open("/Users/kmykhail/Desktop/Corewar/vm_champs/bots/zork.cor", O_RDONLY);
	map = (t_map*)malloc(sizeof(t_map));
	reg = (t_reg*)malloc(sizeof(t_reg));
	ft_init_map(map, reg);
	ft_check_bot(map, fd);
	//каретка у Олега
	ft_table_label(map, reg);
}
