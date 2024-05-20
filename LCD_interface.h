/*
 * LCD_interface.h
 *
 * Created: 5/11/2024 11:48:36 PM
 *  Author: Ahmed Atef
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


#define  _4_BITMODE    0
#define  _8_BITMODE    1


#define  LCD_MODE    _4_BITMODE



/************* LCD initialization Function 8-bit Mode*************/

void LCD_voidInit(void);

/************* LCD Command Send Function *************/

void LCD_voidSendCommand(u8 copy_u8command);

/************* LCD Data Send Function *************/

void LCD_voidSendData(u8 copy_u8data);

/************* LCD String Display Function *************/

void LCD_voidSendString(u8 *copy_u8data);

/************* LCD Number Display Function *************/

void LCD_voidSendNum(u8 copy_u8data);


/************* LCD Number Display Function *************/

void LCD_voidSendNum_4Bit_Mode(u8 copy_u8data);


/************* LCD Cursor Position Function *************/

void LCD_voidSetCursorPos(u8 copy_u8row ,u8 copy_u8column);

/************* Function so send the lower nibble of Data ****/
void  LCD_voidSendLowerNibble(u8 copy_u8data);

/****** Function to Set Enable Pin ************/

void LCD_voidSetEnable(void);






#endif /* LCD_INTERFACE_H_ */