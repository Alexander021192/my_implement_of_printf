#include "parser.h"

int		ft_strlen(char *str)
{
	int len;

	len = 0;
	if(str)
		while (str[len])
			len++;
	else
		len = 6;
	return(len);
}

int		get_char(va_list va_point)
{
	char	ch;
	int res;

	ch = va_arg(va_point, int );
	
	res = parser_struct.width;
	while (parser_struct.flag != '-' && parser_struct.width-- > 1)
		write(1, &" ", 1);
	write(1, &ch, 1);
	while (parser_struct.flag == '-' && parser_struct.width-- > 1)
		write(1, &" ", 1);
	return ((res > 1) ? res : 1);
}

int		get_string(va_list va_point)
{
	char	*str;
	int		len_str;
	int		num_space;
	//int		res;

	str = va_arg(va_point, char *);
	str = (str) ? str : "(null)";
	len_str = ft_strlen(str);
	//res = (len_str == 0) ? 6 : len_str;
	if (parser_struct.precise < len_str && parser_struct.precise > -1)
	{
		num_space = parser_struct.width - parser_struct.precise;
		len_str = parser_struct.precise;
	}
	else
		num_space = parser_struct.width - len_str;

	//printf("%d is width , %d is presize , %d is num_space, %d its len, %s its str\n", parser_struct.width, parser_struct.precise, num_space, len_str, str);

	while (parser_struct.flag != '-' && num_space-- > 0)
		write(1, &" ", 1);
	// if (strcmp(str, "(null)") == 0 && parser_struct.precise < 5 && parser_struct.precise > -1) //if for linux
	// {
	// 	len_str = (parser_struct.width < len_str) ? parser_struct.width : len_str;
	// 	write(1, "    ", len_str);
	// }	
	if (str)
		write(1, str, len_str);
	// else if (str == 0 && parser_struct.precise == -1)
	// 	write(1, "(null)", 6);
	while (parser_struct.flag == '-' && num_space-- > 0)
		write(1, &" ", 1);
	return ((len_str > parser_struct.width) ? len_str : parser_struct.width);
}