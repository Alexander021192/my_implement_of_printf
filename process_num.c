#include "parser.h"

int		ft_len_nmbr(uintptr_t num)
{
	int len;
	uintptr_t base;

	len = 1;
	if (parser_struct.type == 'x' || parser_struct.type == 'X' ||
	parser_struct.type == 'p')
		base = 16;
	else
		base = 10;
	while (num >= base)
	{
		num /= base;
		len++;
	}
	return (len);
}

int		ft_put_nmbr(unsigned int num, int len_num)
{
	char num_ch;
	
	if(len_num-- < 2)
	{
		num_ch = num + '0';
		write(1, &num_ch, 1);
	}
	else
	{
		ft_put_nmbr(num / 10, len_num);
		num_ch = (num % 10) + '0';
		write(1, &num_ch, 1);
	}
	return (0);
}

int		get_num(va_list va_point)
{
	char				minus;
	unsigned int		num;
	int					len_num;
	int					num_zero_space;
	int					res;

	minus = 0;
	res = 0;
	num = va_arg(va_point, unsigned int);
	
	// if(parser_struct.precise != -1 && parser_struct.flag == '0') // может убрать это условие? оно не работет с флагами для принтф
	// 	parser_struct.flag = 0;

	
	if (num > MAX_INT && (parser_struct.type == 'd' || parser_struct.type == 'i')) //проверка на отрицательный инт
	{
		num = (unsigned int)(MAX_UN_INT - num + 1);
		minus = '-';
		parser_struct.width--;
	}
	len_num = ft_len_nmbr(num);
	
	if (parser_struct.precise > len_num)
		num_zero_space = parser_struct.width - parser_struct.precise;
	else
		num_zero_space = parser_struct.width - len_num;

	if (num == 0 && parser_struct.precise == 0)
	{
		while(num_zero_space-- >= 0 && ++res)
			write(1, &" ", 1);
		return (res);
	}
	
	if (parser_struct.flag == '0' && minus && ++res)
	{
		write(1, &minus, 1);
		minus = '+';
	}
	while (parser_struct.flag != '-' && num_zero_space-- > 0 && ++res)
		write(1, &" 0"[(parser_struct.flag == '0')],1);
	if (minus == '-' && ++res)
		write (1, &minus, 1);
	while ((parser_struct.precise-- - len_num) > 0 && ++res)
		write(1,&"0",1);
	if(parser_struct.type == 'x' || parser_struct.type == 'X')
		dec2hex(num);
	else
		ft_put_nmbr(num, len_num);
	while (parser_struct.flag == '-' && num_zero_space-- > 0 && ++res)
		write(1, &" ",1);
	//printf("%d width\n", parser_struct.width);
	return (res + len_num);
}