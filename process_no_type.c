#include "parser.h"

int	get_no_type()
{
	int					num_zero_space;
	int					res;

	res = 0;
	num_zero_space = parser_struct.width - 1;
	while (parser_struct.flag != '-' && num_zero_space-- > 0 && ++res)
		write(1, &" 0"[(parser_struct.flag == '0')],1);
	if (parser_struct.type)
		write(1, &parser_struct.type, 1);
	// else
	// 	parser_struct.step = 0;
	while (parser_struct.flag == '-' && num_zero_space-- > 0 && ++res)
		write(1, &" ",1);
	//printf("%d width\n", parser_struct.width);
	return (res + 1 * (parser_struct.type != 0));
}