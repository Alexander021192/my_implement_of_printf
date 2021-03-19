#include "parser.h"

//исправить все имена функций на ft_

int		ft_printf(char* format, ...)
{
	va_list va_point;         // указатель на необязательный параметр
	va_start(va_point, format);   // устанавливаем указатель
	char *p_format = format;
	int res;

	res = 0;
	while (*p_format)
	{
		if(*p_format != '%') //|| (*p_format == '%' && *(++p_format) == '%')
		{
			write(1, p_format++, 1);
			res++;
		}
		else if(*(p_format) == '%')
		{
			if(*(++p_format))
				parser_format(p_format, va_point);
			res += process_all(parser_struct.type, va_point); //как то может изменить имя функции
			p_format = p_format + parser_struct.step;
		}
	}
	va_end(va_point);
	return (res);
}

// int main()
// {
// 	int res1, res2 = 0;
// 	res1 = printf("%2.9p", 1234);
// 	printf("\nresult %d \n", res1);
// 	res2 = ft_printf("%2.9p", 1234);
// 	printf("\nresult %d \n", res2);

// 	res1 = printf("%.5p", 0);
// 	printf("\nresult %d \n", res1);
// 	res2 = ft_printf("%.5p", 0);
// 	printf("\nresult %d \n", res2);

// }

