#include <stdio.h>

unsigned int get_rtc_tick(void)
{
	return 0;
}

int get_rtc_tick_per_second(void)
{
	return 0;
}

void uart_init(int uart, int speed)
{
}

int uart_read_byte_b(int uart)
{
	return 0;
}

int uart_read_byte(int uart)
{
	return 0;
}

void uart_write_byte_b(int uart, int ch)
{
	fputc(ch, stdout);
}

int uart_write_byte(int uart, int ch)
{
	return fputc(ch, stdout);
}

void uart_write_b(int uart, char *buf, int len)
{
}

void uart_write_string_b(int uart, char *buf)
{
}

void Uart_Printf(char *fmt, ...)
{
}

void uart_write_char_b(int uart, int ch)
{
}

int is_uart_handler_enabled(int uart)
{
	return 0;
}

void enable_uart_handler(int uart)
{
}

void disable_uart_handler(int uart )
{
}

char * get_uart_buffer_pointer(int uart)
{
	return 0;
}

int get_uart_buffer_size(int uart)
{
	return 0;
}

void set_uart_buffer(int uart, char *buf, int sz)
{
}

int get_uart_pos(int uart)
{
	return 0;
}
void set_uart_buffer_ex(int no, int slot, char * buf, int size)
{
}

void set_uart_receiver(int no, void *receiver)
{
}

void select_uart_slot(int no, int slot, int reset)
{
}

int get_uart_handler_flag(int no)
{
	return 0;
}

void set_uart_handler_flag(int no, int flag_value)
{
}

char * get_uart_buffer_pointer_ex(int no, int slot)
{
	return 0;
}

void clear_uart_receiver(int no)
{
}

void toggle_uart_buffer_slot(int no, int reset)
{
}

char * get_prev_uart_buffer_pointer(int no)
{
	return 0;
}

void user_save_uart_character(int uart, char ch)
{
}

int is_uart_handler_buffer_full(int no)
{
	return 0;
}

void clear_uart_buffer_full_flag(int no)
{
}

void reset_uart_buffer(int no)
{
}


