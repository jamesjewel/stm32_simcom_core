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
 * @defgroup	GSM_USER_FUNCTIONS
 * @brief		Functions to be implemented by the user
 * @{
 **/
/**
 * @brief	send a byte on uart
 * 			only declaration--to be defined by the user in the application
 * @param	byte
 * @retval	0/1 for failure/success
 */
uint8_t gsm_uart_txbyte(uint8_t byte);
uint8_t gsm_uart_rxbyte(uint8_t* pbyte);
uint8_t gsm_uart_rx_callback(uint8_t byte);
void gsm_delay(uint16_t t);
uint8_t gsm_pwrkey(uint8_t set_reset);
uint8_t gsm_rst(uint8_t set_reset);
uint8_t gsm_debug_print(char* str);
/**
  * @}
  */
/**
 * @brief	print string to any debug output
 * 			only declaration--to be defined by the user in the application
 * @param	string to be printed
 */

/**
 * @defgroup	GSM_LIB_FUNCTIONS
 * @brief		Library functions for the application
 * @{
 **/
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
  * @}
  */
void gsm_test(); /* TODO DELETE */
#endif /* CORE_INC_GSM_H_ */
