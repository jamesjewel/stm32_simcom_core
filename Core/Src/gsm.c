/*
 * gsm.c
 *
 *  Created on: Sep 14, 2024
 *      Author: Jewel James
 */

#include "gsm.h"
#include <stdio.h> /* for sprintf */
#include <stdarg.h> /* for variadic printf func */
#include <string.h> /* for str funcs */

#define GSM_TX_SIZE		100
#define GSM_RX_SIZE		100

uint8_t gsm_active;
uint16_t rx_index;
uint8_t gsm_rx_buff[GSM_RX_SIZE];

/* util functions */
void _gsm_uart_sendstr(char* str);
void _gsm_uart_rxbuffclr();
void _gsm_uart_txbuffclr();
void _gsm_debug_printf(const char* str,  ...);

uint8_t gsm_init() {
	/* turn on */
	gsm_setpower(1);
	for(size_t i = 0; i < 5; i++) { /* retry 5 times */
		if(gsm_sendcmd("ATEO", "OK", 5000)) {
			gsm_debug_print("Modem powered up.");
			gsm_active = 1;
			break;
		}
		else {
			gsm_active = 0;
			gsm_delay(2000); /* wait for 2s before retry */
		}
	}
	if(gsm_active == 0)
		gsm_debug_print("Modem not powering up.");
	/* start rx */
	// gsm_uart_recvbyte();
	return gsm_active;
}

uint8_t gsm_uart_rx_callback(uint8_t byte) {
	gsm_rx_buff[rx_index++] = byte;
	if(rx_index < GSM_RX_SIZE)
		rx_index++;
	else {
		/* TODO clear rx buff? */
	}
	return 1; /* TODO fix this */
}

uint8_t gsm_sendcmd(char* cmd, char* resp, uint16_t timeout) {
	char str[20] = "";
	/* append /r/n */
	strcat(str, cmd);
	strcat(str, "/r/n");
	_gsm_uart_sendstr(cmd);
	return 1; /* TODO fix this */
}

/***************************/
/** util func definitions **/
 /* calculate string length
  * => no of bytes
  * call uart_sendbyte in a loop from 0 to strlen
  */
void _gsm_uart_sendstr(char* str) {
	char* p = str;
	while(*p != '\0') {
		gsm_uart_sendbyte(*p);
		p++;
	}
}

/**
 * special printf
 * code by GeeksForGeeks: https://www.geeksforgeeks.org/how-to-write-your-own-printf-in-c/
 */
void _gsm_debug_printf(const char* str,  ...) {
	// initializing list pointer
	char pstr[100] = "", temp[50] = "";
	va_list ptr;
	va_start(ptr, str);

	// char array to store token
	char token[20];
	// index of where to store the characters of str in
	// token
	int k = 0;

	// parsing the formatted string
	for (int i = 0; str[i] != '\0'; i++) {
		token[k++] = str[i];

		if (str[i + 1] == '%' || str[i + 1] == '\0') {
			token[k] = '\0';
			k = 0;
			if (token[0] != '%') {
				sprintf(temp, "%s", token); // printing the whole token if
				strcat(pstr, temp);
				// it is not a format specifier
			}
			else {
				int j = 1;
				char ch1 = 0;

				// this loop is required when printing
				// formatted value like 0.2f, when ch1='f'
				// loop ends
				while ((ch1 = token[j++]) < 58) {
				}
				// for integers
				if (ch1 == 'i' || ch1 == 'd' || ch1 == 'u'
						|| ch1 == 'h') {
					sprintf(temp, token, va_arg(ptr, int));
					strcat(pstr, temp);
				}
				// for characters
				else if (ch1 == 'c') {
					sprintf(temp, token, va_arg(ptr, int));
					strcat(pstr, temp);
				}
				// for float values
				else if (ch1 == 'f') {
					sprintf(temp, token, va_arg(ptr, double));
					strcat(pstr, temp);
				}
				else if (ch1 == 'l') {
					char ch2 = token[2];

					// for long int
					if (ch2 == 'u' || ch2 == 'd'
							|| ch2 == 'i') {
						sprintf(temp, token, va_arg(ptr, long));
						strcat(pstr, temp);
					}

					// for double
					else if (ch2 == 'f') {
						sprintf(temp, token, va_arg(ptr, double));
						strcat(pstr, temp);
					}
				}
				else if (ch1 == 'L') {
					char ch2 = token[2];

					// for long long int
					if (ch2 == 'u' || ch2 == 'd'
							|| ch2 == 'i') {
						sprintf(temp, token, va_arg(ptr, long long));
						strcat(pstr, temp);
					}

					// for long double
					else if (ch2 == 'f') {
						sprintf(temp, token, va_arg(ptr, long double));
						strcat(pstr, temp);
					}
				}

				// for strings
				else if (ch1 == 's') {
					sprintf(temp, token, va_arg(ptr, char*));
					strcat(pstr, temp);
				}

				// print the whole token
				// if no case is matched
				else {
					sprintf(temp, "%s", token);
					strcat(pstr, temp);
				}
			}
		}
	}

	// ending traversal
	va_end(ptr);
	gsm_debug_print(pstr);
	return;
}
