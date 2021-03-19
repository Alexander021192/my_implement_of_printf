/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocalamar <ocalamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:14:34 by ocalamar          #+#    #+#             */
/*   Updated: 2021/01/19 12:16:05 by ocalamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		ft_isdigit(char ch)
{
	if (ch && ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int		ft_findtype(char type)
{
	char *all_type;

	all_type = "fcspdiuxX%";
	while (*all_type)
	{
		if (type == *all_type)
			return (1);
		all_type++;
	}
	return (0);
}

int		ft_set_default_parser_struct(void)
{
	parser_struct.flag = 0;
	parser_struct.type = 0;
	parser_struct.width = 0;
	parser_struct.precise = -1;
	parser_struct.step = 0;
	return (0);
}

int		parser_format(char *p_format, va_list va_point)
{
	int step;
	
	step = 0;
	ft_set_default_parser_struct();

	// printf("\n%c its forpmatstep\n", p_format[step]);
	// printf("\n%c its *forpmat\n", *p_format);

	while(p_format[step] == '0' || p_format[step] == '-')
	{
		if (!parser_struct.flag)
			parser_struct.flag = p_format[step];
		else if (parser_struct.flag == '0' && p_format[step] == '-')
			parser_struct.flag = p_format[step];
		step++;
	}
	if(ft_isdigit(p_format[step]) || p_format[step] == '*') // функция isdigit
	{
		if (p_format[step] == '*')
		{
			parser_struct.width = va_arg(va_point, int);
			if (parser_struct.width < 0)
			{
				parser_struct.width *= -1;
				parser_struct.flag = '-';
			}
			step++;
		}
		while(ft_isdigit(p_format[step]))
			parser_struct.width = parser_struct.width * 10 + (p_format[step++] - '0');
	}
	if (p_format[step] == '.')
	{
		parser_struct.precise = 0;
		if (p_format[++step] == '*')
		{
			parser_struct.precise = va_arg(va_point, int);
			// else if (parser_struct.precise < 0)
			// 	parser_struct.precise = -1;
			step++;
		}
		while(ft_isdigit(p_format[step]))
			parser_struct.precise = parser_struct.precise * 10 + (p_format[step++] - '0');
		if(parser_struct.precise >= 0 && parser_struct.flag == '0') 
			parser_struct.flag = 0;
	}
	if(ft_findtype(p_format[step]))
		parser_struct.type = p_format[step++];
	parser_struct.step = step;
	// printf("\n|%d width| |%c type| |%c flag| |%d step|\n", parser_struct.width, parser_struct.type, parser_struct.flag, parser_struct.step);
	return (0);
}
