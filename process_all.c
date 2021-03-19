#include "parser.h"

int		process_all(char type, va_list va_point)
{
	int res;

	res = 0;
	if(type == 'p')
		res = get_point(va_point);
	else if(type == 'c')
		res = get_char(va_point);
	else if(type == 's')
		res = get_string(va_point);
	else if(type == 'd' || type == 'i' || type == 'u' 
	|| type == 'x' || type == 'X')
		res = get_num(va_point);
	else
		res = get_no_type();
	return (res);
}