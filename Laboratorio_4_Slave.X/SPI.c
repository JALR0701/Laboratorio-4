
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

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI_Init.h"
#include "ADC_Init.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

uint8_t ready = 0, adc1 = 0, adc2 = 0, state = 0;

void __interrupt() isr(void){
   if(SSPIF == 1){
        state = spiRead();
        PORTB = state;
        if (state == 1){
            spiWrite(adc1);
        }
        if (state == 2){
            spiWrite(adc2);
        }
        SSPIF = 0;
    }
   if(ADCON0bits.GO_DONE == 0){//Si se realizo una conversion levantamos la bandera (se ejecua en el loop)
        ready = 1;
        PIR1bits.ADIF = 0;
    }
}

void main(void) {
    
    ANSEL = 0b00000011;
    ANSELH = 0;
    
    TRISA = 0b00100011;
    TRISB = 0;
    TRISD = 0;
    
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

    while(1){
       initADC(0); //Inicializamos el primer canal del ADC
        if(ready){  //Guardamos el valor de la conversion
            adc1 = ADRESH;
            ready = 0;
            ADCON0bits.GO_DONE = 1;
        }
       initADC(1); //Inicializamos el primer canal del ADC
        if(ready){  //Guardamos el valor de la conversion
            adc2 = ADRESH;
            ready = 0;
            ADCON0bits.GO_DONE = 1;
        }
    }
    return;
}
