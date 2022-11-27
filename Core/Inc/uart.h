/*
 * uart.h
 *
 *  Created on: Nov 20, 2022
 *      Author: tan
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "software_timer.h"
#include<stdio.h>

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

#define MAX_BUFFER_SIZE 10
#define IDLE 0

#define CMD_READY 5
#define	CMD_WAIT 6

#define START_CMD 1
#define END_CMD  2

#define FLAG_R 10
#define FLAG_S 11
#define FLAG_T 12
#define FLAG_O 13
#define FLAG_K 14

#define ERR_CMD_BUF 7

#define SEND 3
#define STOP_SEND 4

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

extern uint8_t action_flag;

extern uint8_t cmd_buffer[MAX_BUFFER_SIZE];
extern uint8_t cmd_length;
extern uint8_t cmd_Action;
extern uint8_t cmd_flag;
extern uint8_t cmd_start_flag;
extern uint8_t pkgsent_flag;
extern uint32_t toSend;
extern char* str;

void raiseCmdStartFlag(uint8_t value);
uint8_t getCmdStartFlag();

void raiseAction(int action);
uint8_t getAction();
void resetCmdBuf();

void command_parser_fsm();
void uart_communiation_fsm();

#endif /* INC_UART_H_ */
