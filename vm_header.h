//
//  vm_header.h
//  pr_corewar
//
//  Created by Kostiantyn MYKHAILENKO on 4/20/18.
//  Copyright © 2018 Kostiantyn MYKHAILENKO. All rights reserved.
//

#ifndef vm_header_h
#define vm_header_h
#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "op.h"
#define LINE map->line
#define MAPA map->mapa
#define TOTAL_SIZE (2176)
#define MAGIC_NB map->magic_nb
#define BOT_NAME map->bot_name
#define COMMENT map->comment
#define CODE_OF_BOT map->code_of_bot
#define STEP map->steper
#define CODE_CODAGE map->code_codage
#define REVERSE_2_BYTES(x) ((((x) & 0xFF) << 8) | (((x) & 0xFF00) >> 8))
#define REVERSE_4_BYTES(x) ((((x) & 0xFF) << 24) | ((((x) & 0xFF00) << 8)) | ((((x) & 0xFF0000) >> 8)) | (((x) & 0xFF000000) >> 24))

typedef struct  s_map
{
	int		pc; // каретка
	int		fake;
	char	*line;
	char	*mapa;
	uint8_t *code_of_bot;
	int		val;
	int		magic_nb;
	int		bot_name;
	int		comment;
	int		cnt_bot;
	int		**label;
	int		steper;
	int		codage;
	int		code_codage[3];//храняться аргументы [0] - байт T_REG, [1] - байты(2, 4) T_DIR, [2] - байт T_IND
	uint8_t arg[3];
}				t_map;

typedef struct	s_reg
{
	uint8_t rg[16][4];
	uint32_t	big_end;
	
}				t_reg;

void	ft_table_label(t_map *map, t_reg *reg);
void	ft_implement_command(t_map *map, t_reg *reg, uint8_t proc);
#endif /* vm_header_h */
