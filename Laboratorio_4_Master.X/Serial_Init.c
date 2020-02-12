#include <stdint.h>
#include <pic16f887.h>
 #include <stdio.h>
 #include <stdlib.h>
#include "Serial_Init.h"

void initSerial(uint16_t baudrate){ //Inicializacion del USART
    TRISC = 0x80; //Configuracion del puerto c
    
    PIE1bits.RCIE = 0; //Interrupcion del RX
    
    TXSTA=0b00100110; //configuracion del TX
    
    RCSTA=0b10010000; //configuración del RX
    
    BAUDCTLbits.BRG16 = 1; //BaudrateHigh
    
    if(baudrate == 9600){ //casos del baudrate
        SPBRG = 103;
    } else if (baudrate == 10417){
        SPBRG = 95;
    } else if (baudrate == 19200){
        SPBRG = 51;
    } else if (baudrate == 57600){
        SPBRG = 16;
    }
}

void send_int (int msg){ //funcion enviar enteros
    while (TXSTAbits.TRMT == 0){//si no hay datos esperar
    }
    TXREG = msg;//enviar datos
}

