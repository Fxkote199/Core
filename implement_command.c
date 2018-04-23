//
//  implement_command.c
//  pr_corewar
//
//  Created by Kostiantyn MYKHAILENKO on 4/21/18.
//  Copyright © 2018 Kostiantyn MYKHAILENKO. All rights reserved.
//

#include "vm_header.h"

void	ft_what_type_args(t_map *map, t_reg *reg, uint8_t command)
{
	int i;
	int cnt;
	int len;
	char *bin;

	i = 0;
	cnt = 0;
	bin = ft_itoa_base(map->codage, 2);
	len = ft_strlen(bin);
	if (len != 8)
	{
		cnt = 8 - len;
		while (cnt > 0)
		{
			bin = ft_strjoin("0", bin);//LEAK
			cnt--;
		}
	}
	while (i < len)
	{
		(cnt > 3) ? exit(printf("wrong codage\n")) : 0;
		if (bin[i] == '1')
			cnt++;
		i++;
	}
	i = 0;
	while (i < len)
	{
		(bin[i] == '0' && bin[i + 1] == '1' && i + 1 < ft_strlen(bin) && !CODE_CODAGE[0]) ? (CODE_CODAGE[0] = 1) : 0;
		if (bin[i] == '1' && bin[i + 1] == '0' && i + 1 < ft_strlen(bin) && !CODE_CODAGE[1])
			CODE_CODAGE[1] = (map->label[command][3] == 4) ? 4 : 2;
		if (bin[i] == '1' && bin[i + 1] == '1' && i + 1 < ft_strlen(bin) && !CODE_CODAGE[2])
			CODE_CODAGE[2] = 2;
		i += 2;
	}
	ft_strdel(&bin);
}

void	ft_convert_endian(t_map *map, t_reg *reg, uint8_t command)
{
	/*int val;
    int val_1;
    int a;
    int i;

    i = 0;
    a = 0;
    uint8_t arr[2];

	val = 0;
    val_1 = 0;
	printf("%x %x\n", CODE_OF_BOT[map->pc + 2], CODE_OF_BOT[map->pc + 3]);
    arr[0] = CODE_OF_BOT[map->pc + 2];
    arr[1] = CODE_OF_BOT[map->pc + 3];
    uint16_t res = *(uint16_t*)arr;
    printf("%d %x\n", res, res);
    a = 0;
    a = a | arr[0];
    a = a << 8;
    a = a | arr[1];
    int b = 0x1;
    val = REVERSE_2_BYTES(a);
    val_1 = REVERSE_2_BYTES(b);
    printf("%d %x\n", val, val);
    printf("%d %x\n", val_1, val_1);*/
    
}

void	ft_implement_command(t_map *map, t_reg *reg, uint8_t command)
{
	ft_what_type_args(map, reg, command);
	if (command == 2)//ld
		ft_convert_endian(map, reg, command);
	exit(1);
}
