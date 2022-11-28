/*
 * uart.c
 *
 *  Created on: Nov 20, 2022
 *      Author: tan
 */

#include "uart.h"
ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;

uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer;

uint8_t temp = 0;
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t cmd_buffer[MAX_BUFFER_SIZE];
uint8_t cmd_length = 0;
uint8_t pkgsent_flag = 0;
uint8_t send_cmd;
uint32_t toSend = 0;
uint8_t cmd_Action = 0;
uint8_t cmd_flag = IDLE;
uint8_t cmd_start_flag = 0;

void raiseCmdStartFlag(uint8_t value){
	cmd_start_flag = value;
}

uint8_t getCmdStartFlag(){
	return cmd_start_flag;
}

void raiseAction(int action){
	cmd_Action = action;
}
uint8_t getAction(){
	return cmd_Action;
}

void resetCmdBuf(){
	for(int i=0; i<MAX_BUFFER_SIZE; i++){
		cmd_buffer[i] = 0;
	}
	cmd_length=0;
}
uint8_t prev_data = 0;
uint8_t action_flag = 0;
uint8_t str[MAX_BUFFER_SIZE];

void command_parser_fsm(){
	switch(cmd_flag){
	case IDLE:
		if(buffer[index_buffer-1] == '!'){
			cmd_flag=START_CMD;
		}
		break;
	case START_CMD:
		if(buffer[index_buffer-1] == 'R'){
			cmd_flag=FLAG_R;
		}
		else if(buffer[index_buffer-1] == 'O'){
			cmd_flag=FLAG_O;
		}
		else cmd_flag = IDLE;
		break;
	case FLAG_R:
		if(buffer[index_buffer-1] == 'S'){
			cmd_flag=FLAG_S;
		}
		else cmd_flag = IDLE;
		break;
	case FLAG_O:
		if(buffer[index_buffer-1] == 'K'){
			cmd_flag=FLAG_K;
		}
		else cmd_flag = IDLE;
		break;
	case FLAG_S:
		if(buffer[index_buffer-1] == 'T'){
			cmd_flag=FLAG_T;
		}
		else cmd_flag = IDLE;
		break;
	case FLAG_T:
		if(buffer[index_buffer-1] == '#'){
			action_flag = SEND;
			cmd_flag = IDLE;
		}
		else cmd_flag = IDLE;
		break;
	case FLAG_K:
		if(buffer[index_buffer-1] == '#'){
			action_flag = STOP_SEND;
			cmd_flag = IDLE;
		}
		else cmd_flag = IDLE;
		break;
	}
}

void uart_communiation_fsm(){
	  if(action_flag==SEND){
		  if(pkgsent_flag == 0){
			  pkgsent_flag = 1;
			  toSend = HAL_ADC_GetValue(&hadc1);
		  }
		  if(isTimerFlagRaised(1)==1){
			  HAL_UART_Transmit(&huart2, &(str[0]), sprintf( &(str[0]), "!ADC=%ld#\r\n", toSend), 100);
			  setTimer1(3000/10);
		  }
	  }
	  else if(action_flag==STOP_SEND){
		  pkgsent_flag = 0;
	  }
}
