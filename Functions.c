#include "main.h"

/*********************PRINT CHARACTER ********************/
/**
  * Description - Function to print out a character
  * print_char - Starting point
  * @types: A ‘va_list’ variable that represents the variable arguments
  * @buffer: Character array that serves as a buffer
  * @flags:  Calculates active flags for the function
  * @width: Width specifier for the function
  * @precision: Integer representing the precision
  * @size: Size specifier for the function
  * count: total number of characters printed
  * Return: The count of characters printed
  */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************** PRINT A STRING *****************/
/**
  * Description - This prints out a string
  * print_string - Starting point
  * @types: List a of arguments
  * @buffer:Character array that serves as a buffer
  * @flags:  Calculates active flags
  * @width: get width of the char
  * @precision: Precision specifier
  * @size: Size specifier for the function
  * Return: the count of characters printed
  */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/************** PRINTS A PERCENT SIGN ***************/
/**
  * Description - This prints out the perceent sign
  * print_percent – starting point
  * @types: A ‘va_list’ variable that represents the variable arguments
  * @buffer: Character array that serves as a buffer
  * @flags:  Calculates active flags for the function
  * @width: Width specifier for the function
  * @precision: Integer representing the precision specifier
  * @size: Size specifier for the function
  * Return: The count of characters to be printed
  */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/******************* PRINTS AN INTEGER *******************/
/**
  * Description - Afunction that prints out an integer
  * print_int – Starting point
  * @types: A ‘va_list’ variable that represents the variable arguments
  * @buffer: Character array that serves as a buffer
  * @flags:  Calculates active flags for the function
  * @width: Width specifier for the function
  * @precision: Integer representing the precision specifier
  * @size: Size specifier for the function
  * Return: The count of characters to be printed
  */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/****************** PRINTS A BINARY *********************/
/**
  * Description - Function prints out a binary
  * print_binary - Starting point
  * @types: A ‘va_list’ variable that represents the variable arguments
  * @buffer: Character array that serves as a buffer
  * @flags:  Calculates active flags for the function
  * @width: Width specifier for the function
  * @precision: Integer representing the precision specifier
  * @size: Size specifier for the function
  * Return: The count of characters to be printed
  */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
