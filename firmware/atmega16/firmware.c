/*********************************************** 
 *	File: atmega-firmware.c
 *
 *	Popis: Firmware pro ATmega 16 & 128
 *
 *	Softwarovy timer pro Atmega16 na ovladani serva.
 *	Krystal:			6.000 MHz
 *	Delka ramce pulzu:	20ms = 14999 ticku timeru
 *	Delka pulzu:		666 - 2333us
 *
 **********************************************/	
#include <avr/io.h>
#include <avr/interrupt.h>

#define FRAME_LENGTH 14999	
#define PULSE_LENGTH_MAX 1750
#define PULSE_LENGTH_MIN 500
#define NO_OF_SERVOS 6

volatile unsigned char timerCompare = 0;// indikator toho, ze nastalo compare mezi OCR1A a TCNT1
volatile unsigned char timerPhase = 0;	// ukazuje ve ktere fazi jsme
volatile unsigned char idAccepted = 0;	// zda uz bylo prijato cislo serva, se kterym se ma pohnout
volatile unsigned char servoId = 0;
unsigned int servoStates[NO_OF_SERVOS] = {1125,1125,1125,1125,1125,1125};	// 500-1750 ticku
unsigned char i = 0;

void main(void)  {

	DDRB = 0xFF;
    PORTB = 0x00;

    UBRRH=0x00;  
	UBRRL=0x26;						//Baud rate 9600 
	UCSRA=0b00000000;				//Flagovy registr USARTu. Vsechno vynulujeme.  
	UCSRB=0b00010000;				//Zapneme interrupt pri obdrzeni dat, povolime prijimac
	UCSRC=0b10000110;				//Asynchronni operace, parita zakazana, 1 stop-bit, character size 8bitu
	
	OCR1A = FRAME_LENGTH-PULSE_LENGTH_MAX;					//Nastaveni casu, kdy bude signal v 0. OCR1A se bude casem menit potom
	
	/*
	 *  Nastavime timer: chovani OC1A a OC1B portu na normalni fungovani, force output compare vypnuto, waweform
	 *	generace  WGM11 a WGM00 oboji na 0 (priprava na CTC mod)
	 */
	TCCR1A = 0b00000000;		
							
    /*
	 *	Donastaveni timeru. Vstupni interrupty neresime, Waweform generace WGM 13 a 12 nastaveno na 01,
	 *	prescaler 8, nastaveni 010
	 */								
	TCCR1B = 0b00001010;								 
	TIMSK = 0b00010000;										// Nastavit output compare interrupt flag na OCR1A
	SREG |= 0b10000000;										// povoleni globalnich interruptu
	
	while( 1 ) {
		          
		 //pokud nastalo porovnani		  
		if ( timerCompare ) {
			//kdyz jsme v druhe fazi
			if (timerPhase) {     
					PORTB = 0x00;							//srazime vystup do 0                
					OCR1A = FRAME_LENGTH-PULSE_LENGTH_MAX;	//a nastavime casovac na prvni fazi
					timerPhase = 0;							//nastavime indikator prvni faze	
			} else {										//kdyz jsme v 1 fazi
					OCR1A = PULSE_LENGTH_MAX;				//nastavime casovac na 2 fazi
					timerPhase = 1;							//nastavime indikator druhe faze
			}
			timerCompare = 0;								//obsluha provedena
		}
		
        if ( timerPhase ) {									//kdyz jsme v druhe fazi
             PORTB =((TCNT1 >= (PULSE_LENGTH_MAX-servoStates[0]))) 		|
					((TCNT1 >= (PULSE_LENGTH_MAX-servoStates[1])) << 1)	|
					((TCNT1 >= (PULSE_LENGTH_MAX-servoStates[2])) << 2)	|
					((TCNT1 >= (PULSE_LENGTH_MAX-servoStates[3])) << 3)	|
					((TCNT1 >= (PULSE_LENGTH_MAX-servoStates[4])) << 4)	|
					((TCNT1 >= (PULSE_LENGTH_MAX-servoStates[5])) << 5);
		}
		//pokud mame nejaka data
        if ( UCSRA & 0b10000000 ) {       
			//pokud jsme uz prijali id serva
            if ( idAccepted ) {     
					SREG = 0b00000000;
					servoStates[servoId] = (UDR-5)*5+500;	//ulozime novy stav
					SREG |= 0b10000000;  
                
					idAccepted = 0;					//vynulujeme priznak prijateho id
            } else {								//pokud jsme id neprijali
                servoId = UDR;      				//ulozime id serva
				
				if ( servoId < NO_OF_SERVOS && servoId >= 0 ) {
					idAccepted = 1;   
				} else {
					idAccepted = 0;
                }
			}
		}	
	}
}

ISR(TIMER1_COMPA_vect) {
	timerCompare = 1;
}