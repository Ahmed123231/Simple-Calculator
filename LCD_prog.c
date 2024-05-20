/*
 * LCD_prog.c
 *
 * Created: 5/11/2024 11:49:09 PM
 *  Author: ahmed
 */ 

#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "DIO_interface.h"



#define   F_CPU 16000000UL
#include  <util/delay.h>




/************* Function so send the lower nibble of Data ****/
void  LCD_voidSendLowerNibble(u8 copy_u8data){
	
	/***** Array to Store Data Pins ****/
	u8 array_pin[4]={
		LCD_D4_PIN,
		LCD_D5_PIN,
		LCD_D6_PIN,
		LCD_D7_PIN,	
	};
	u8 Loc_u8_iterator = 0;
	for(Loc_u8_iterator = 0 ; Loc_u8_iterator <4 ; Loc_u8_iterator++)
	{
		DIO_voidSetPinVal(LCD_DPORT,array_pin[Loc_u8_iterator],GET_BIT(copy_u8data,Loc_u8_iterator));
	}
	
	
}

/****** Function to Set Enable Pin ************/

void LCD_voidSetEnable(void){
	
	/******** SET EN PIN HIGH *********/
	DIO_voidSetPinVal(LCD_CPORT,LCD_EN_PIN,HIGH);
	
	_delay_ms(2);
	
	/******** SET EN PIN LOW *********/
	
	DIO_voidSetPinVal(LCD_CPORT,LCD_EN_PIN,LOW);
	
}



/************* LCD Command Send Function *************/

void LCD_voidSendCommand(u8 copy_u8command){
	/* Clear RS PIN to Send Command */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RS_PIN,LOW);
	/* Clear RW PIN to Send Data */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RW_PIN,LOW);
	
	/*** Send Command ***/
	#if LCD_MODE == _8_BITMODE
	DIO_voidSetPortVal(LCD_DPORT,copy_u8command);
	/*** Set EN PIN HIGH ***/
	LCD_voidSetEnable();
	#elif LCD_MODE == _4_BITMODE
	LCD_voidSendLowerNibble(copy_u8command>>4);
	LCD_voidSetEnable();
	LCD_voidSendLowerNibble(copy_u8command);
	LCD_voidSetEnable();
	
	#endif
	
	
}



/************* LCD Data Send Function *************/

void LCD_voidSendData(u8 copy_u8data){
	
	/* SET RS PIN to Send Command */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RS_PIN,HIGH);
	/* Clear RW PIN to Send Data */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RW_PIN,LOW);
	
	/*** Send Command ***/
	#if LCD_MODE == _8_BITMODE
	DIO_voidSetPortVal(LCD_DPORT,copy_u8data);
	/*** Set EN PIN HIGH ***/
	LCD_voidSetEnable();
	#elif LCD_MODE == _4_BITMODE
	LCD_voidSendLowerNibble(copy_u8data>>4);
	LCD_voidSetEnable();
	LCD_voidSendLowerNibble(copy_u8data);
	LCD_voidSetEnable();
	
	#endif
	
	
	
	
}



/************* LCD initialization Function 8-bit Mode *************/

void LCD_voidInit(void){
	_delay_ms(40);
	/* Send Function Set */
	#if LCD_MODE == _8_BITMODE
	
	LCD_voidSendCommand(0b00111000);
	#elif LCD_MODE == _4_BITMODE
	LCD_voidSendLowerNibble(0b0010) ;
	LCD_voidSetEnable();
	LCD_voidSendLowerNibble(0b0010) ;
	LCD_voidSetEnable();
	LCD_voidSendLowerNibble(0b1000) ;
	LCD_voidSetEnable();
	#endif
	
	/* Display on/off control */
	LCD_voidSendCommand(0b00001100);
	/* Display Clear */
	LCD_voidSendCommand(1);
	/* Entry Mode Set */
	
	
	
	
}


/************* LCD String Display Function *************/

void LCD_voidSendString(u8 *copy_u8data){
	u8 i=0;
	
	while(copy_u8data[i] !='\0'){
		LCD_voidSendData(copy_u8data[i]);
		copy_u8data++;
	}
		
}

/********** Function to Set Grid position on LCD ****/

void LCD_SetGridPos(u8 copy_u8column , u8 copy_u8row){
	
	u8 Loc_DDRAM_Address=0;
	
	Loc_DDRAM_Address = copy_u8column + copy_u8row * 0x40 ;
	
	/**** Set DDRAM ****/
	
	SET_BIT(Loc_DDRAM_Address,7);
	
	LCD_voidSendCommand(Loc_DDRAM_Address);
	
}



/************* LCD Number Display Function *************/

void LCD_voidSendNum(u8 copy_u8data){
	
	u8 buffer[7]; // Buffer to hold the string representation of the number
	u8 i = 0;
	// Convert integer to string manually
	if (copy_u8data == 0) {
		buffer[i++] = '0';
		} else {
		if (copy_u8data < 0) {
			LCD_voidSendData('-'); // Send negative sign
			copy_u8data = -copy_u8data;     // Make number positive
		}
		while (copy_u8data != 0) {
			u8 digit = copy_u8data % 10;        // Extract the least significant digit
			buffer[i] = digit + '0';   // Convert digit to ASCII and store in buffer
			copy_u8data /= 10;   
			i++;                // Move to the next digit
		}
	}
	// Send digits to LCD in reverse order
	
	while (i > 0) {
		LCD_voidSendData(buffer[--i]);
	}
	
}

/************* LCD Cursor Position Function *************/

void LCD_voidSetCursorPos(u8 copy_u8row ,u8 copy_u8column){
	
	u8 address=0x0;
	if(copy_u8row == 0){
		address=0x80;
	}
	else if (copy_u8row == 1){
		
		address=0xC0;
	}
	if(copy_u8column <16){
		address +=copy_u8column ;	
	}
	LCD_voidSendCommand(address);
	
	
}


