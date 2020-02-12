/* 
 * File:   Serial_Init.h
 * Author: jorge
 *
 * Created on 8 de febrero de 2020, 02:18 PM
 */

#ifndef SERIAL_INIT_H
#define	SERIAL_INIT_H

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000

void initSerial (uint16_t baudrate);//Prototipos
void send_int (int msg);

#endif	/* SERIAL_INIT_H */

