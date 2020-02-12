
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "Serial_Init.h"
#define _XTAL_FREQ 4000000

uint8_t ttl = 0;

void __interrupt() ISR (void){
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
        
    if (PIR1bits.RCIF == 1){//Si hay datos en el puerto se leen y se guardan en una variable
        ttl = RCREG;
    }
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

void main(void) {
    
    TRISB = 0;//Configuración I/O
    TRISC = 0;
    
    PORTB = 0;//Valor inicial de los puertos
    PORTC = 0;
    
    initSerial(9600);//Inicializar serial y baudrate
    
    while (1){
        
        send_int(255);
        send_int(5);
        send_int(4);
        send_int(3);
        send_int(2);
        PORTB = ttl;
        
    }
    
    return;
}
