/*
 * gsm.h
 *
 *  Created on: Sep 14, 2024
 *      Author: Jewel James
 */

#ifndef CORE_INC_GSM_H_
#define CORE_INC_GSM_H_
#include "main.h"

/**
 * @brief	send a byte on uart
 * 			only declaration--to be defined by the user in the application
 * @param	byte
 * @retval	0/1 for failure/success
 */
uint8_t gsm_uart_sendbyte(uint8_t byte);
uint8_t gsm_uart_rx_callback(uint8_t byte);
void gsm_delay(uint16_t t);
uint8_t gsm_pwrkey(uint8_t set_reset);
uint8_t gsm_rst(uint8_t set_reset);
/**
 * @brief	print string to any debug output
 * 			only declaration--to be defined by the user in the application
 * @param	string to be printed
 */
uint8_t gsm_debug_print(char* str);

uint8_t gsm_init();
uint8_t gsm_setpower(uint8_t on_off);
/**
 * @brief 	send an AT command, capture the resp,
 * 			check the desired response was received
 * @param	FULL command, as a string
 * @retval	0/1 based on whether the respnse was okay
 */
uint8_t gsm_sendcmd(char* cmd, char* resp, uint16_t timeout);

/* Applicaion functions */
uint8_t gsm_getnets();
uint8_t gsm_getownnumber();

/**
 * 1. read signal strength
 * 2. upload data with a buffer contraining payload, return status
 * 3.
 */
#endif /* CORE_INC_GSM_H_ */
