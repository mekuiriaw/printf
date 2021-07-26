#include "holberton.h"
#include <stdlib.h>

/**
 * print_space - prints a space
 *
 * Return: always 1 (number of chars printed)
 */
int print_space(void)
{
	_putchar(' ');
	return (1);
}

/**
 * increment_index - increments the index of format depending on char c
 * @c: char to determine index increment
 * @j: number of indices that c is away from the current index
 *
 * Return: (j + 1) if c is a percent sign or j
 */
unsigned int increment_index(char c, unsigned int j)
{
	if (c == '%')
		return (j + 1);
	return (j);
}

/**
 * check_for_specifiers - checks if there is a valid format specifier
 * @format: possible format specifier
 *
 * Return: pointer to valid function or NULL
 */
static int (*check_for_specifiers(const char *format))(va_list)
{
	unsigned int i;
	print_t p[] = {
		{"c", print_c},
		{"s", print_s},
		{"i", print_i},
		{"d", print_d},
		{"u", print_u},
		{"b", print_b},
		{"o", print_o},
		{"x", print_x},
		{"X", print_X},
		{"p", print_p},
		{"S", print_S},
		{"r", print_r},
		{"R", print_R},
		{NULL, NULL}
	};

	for (i = 0; p[i].t != NULL; i++)
	{
		if (*(p[i].t) == *format)
		{
			break;
		}
	}
	return (p[i].f);

}

/**
 * _printf - prints anything
 * @format: list of argument types passed to the function
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	unsigned int i = 0, j, count = 0;
	va_list valist;
	int (*f)(va_list);

	va_start(valist, format);
	while (format && format[i])
	{
		for (; format[i] != '%' && format[i]; i++)
		{
			_putchar(format[i]);
			count++;
		}
		if (!format[i])
			return (count);
		f = check_for_specifiers(&format[i + 1]);
		if (f != NULL)
		{
			count += f(valist);
			i += 2;
			continue;
		}
		for (j = 1; format[i + j] == ' '; j++)
			;
		if (!format[i + j])
			return (-1);
		if (format[i + j] == 's')
		{
			count += print_s(valist);
			i += j + 1;
			continue;
		}
		_putchar(format[i]);
		count++;
		if (j > 1 && format[i + j] != '%')
			count += print_space();
		i += increment_index(format[i + j], j);
	}
	va_end(valist);
	return (count);
}
