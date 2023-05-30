#include "main.h"

/****************** PRINTS AN UNSIGNED NUMBER ****************/
/**
  * Description - This prints out an unsigned number
  * print_unsigned - Starting point
  * @types: A ‘va_list’ variable that represents the variable arguments
  * @buffer: Character array that serves as a buffer
  * @flags:  Calculates active flags for the function
  * @width: Width specifier for the function
  * @precision: Integer representing the precision specification
  * @size: Size specifier for the function
  * Return: The count of characters to be printed
  */

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/******** PRINTS AN UNSIGNED NUMBER IN OCTAL  ********/
/**
  * Description - Prints out an unsigned number in octal form
  * print_octal - Starting point
  * @types: A ‘va_list’ variable that represents the variable arguments
  * @buffer: Character array that serves as a buffer to handle the printing
  * @flags:  Calculates active flags for the function
  * @width: Width specifier for the function
  * @precision: Integer representing the precision specifier
  * @size: Size specifier for the function
  * Return: The count of characters to be printed
  */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/********** PRINT UNSIGNED NUMBER IN HEXADECIMAL **********/
/**
  * Description - Prints unsigned nums in hexadecimal form
  * print_hexadecimal - starting point
  * @types: A ‘va_list’ variable that represents the variable arguments
  * @buffer: Character array that serves as a buffer
  * @flags:  Calculates active flags for the function
  * @width: Width specifier for the function
  * @precision: Integer representing the precision specification
  * @size: Size specifier for the function
  * Return: The count of characters to be printed
  */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/********** PRINTS UNSIGNED NUMBER IN UPPER HEXADECIMAL ***********/
/**
  * Description - Prints an unsigned number in upper hexadecimal form
  * print_hexa_upper - Starting point
  * @types: A ‘va_list’ variable that represents the variable arguments
  * @buffer: Character array that serves as a buffer
  * @flags:  Calculates active flags for the function
  * @width: Width specifier for the function
  * @precision: Integer representing the precision specification
  * @size: Size specifier for the function
  * Return: The count of characters to be printed
  */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/*********** PRINTS HEXX NUM IN LOWER OR UPPER **********/
/**
  * Description - Prints a hexadecimal num in lower or upper forms
  * print_hexa - Starting point
  * @types: A ‘va_list’ variable that represents the variable arguments
  * @buffer: Character array that serves as a buffer
  * @flags:  Calculates active flags for the function
  * @width: Width specifier for the function
  * @precision: Integer representing the precision
  * @size: Size specifier for the function
  * @map_to: Array of values to map the number to
  * @flag_ch: Calculates active flags
  * @size: Size specification
  * Return: The count of characters to be printed
  */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
