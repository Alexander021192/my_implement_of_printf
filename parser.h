#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <stdio.h>
#include <unistd.h>

#include <stdarg.h>
#include <stdint.h>

#define MAX_UN_INT 4294967295
#define MAX_INT 2147483647

typedef struct parser
{
	char	flag;
    int		width;
    int		precise;
    char	type;
    int		step;

}			parser_f;

parser_f	parser_struct;

int			parser_format(char *p_format, va_list va_point);

int			process_all(char type, va_list va_point);
int			get_string(va_list va_point);
int			get_char(va_list va_point);
int			get_point(va_list va_point);
int			get_num(va_list va_point);

int			dec2hex(uintptr_t dec_point);
int			ft_len_nmbr(uintptr_t p_num);

int			get_no_type();