#include "parser.h"

int dec2hex(uintptr_t dec_point)
{
	char* base_hex;

	if(parser_struct.type == 'X')
		base_hex = "0123456789ABCDEF";
	else
		base_hex = "0123456789abcdef";
	if(dec_point < 16) 
		write(1, &base_hex[dec_point%16], 1);
	else
	{
		dec2hex(dec_point/16);
		write(1, &base_hex[dec_point%16], 1);
	}
	return (0);
}

int get_point(va_list va_point)
{
	uintptr_t	p_num;
	int			len_point;
	int			num_space;
	
	p_num  = (uintptr_t)va_arg(va_point, void *);
	len_point = ft_len_nmbr(p_num) + 2; //for linux + 2 * (p_num == 0)
	if (p_num == 0 && parser_struct.precise == 0)
		len_point--;
	num_space = parser_struct.width - len_point;
	while (parser_struct.flag != '-' && num_space-- > 0)
		write(1, " ",1);
	write(1, "0x", 2);
	if (parser_struct.precise > 0 || parser_struct.precise == -1)
		dec2hex(p_num);
 	// else // for linux null pointer 
	// 	write(1, "(nil)", 5);
	while (parser_struct.flag == '-' && num_space-- > 0)
		write(1, " ",1);
	//printf("\n%d len\n", len_point);
	return ((len_point > parser_struct.width) ? len_point: parser_struct.width);
}