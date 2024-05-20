/*
 * LCD+KEYPAD.c
 *
 * Created: 5/18/2024 11:51:24 PM
 * Author : ahmed
 */ 

#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"
#include "DIO_interface.h"
#define   F_CPU 16000000UL
#include <util/delay.h>



int main(void) {
	u8 Loc_KeyVal = 0;
	u8 num1 = 0;
	u8 num2 = 0;
	u8 Loc_Sum = 0;
	u8 operator = 0;

	DIO_voidSetPortDir(LCD_DPORT, 0xF0);
	DIO_voidSetPortDir(LCD_CPORT, 0x0E);
	LCD_voidInit();
	KEYPAD_init();

	while (1) {
		// Clear the screen and reset variables before starting a new calculation
		LCD_voidSendCommand(0x01); // Clear display command
		num1 = 0;
		num2 = 0;
		Loc_Sum = 0;
		operator = 0;

		// Get the first number
		do {
			num1 = KEYPAD_GetPressedKey();
		} while (num1 == 0xff);

		// Display the first number if it is a digit
		if (num1 >= 0 && num1 <= 9) {
			LCD_voidSendNum(num1);
			} else {
			continue; // If not a digit, continue to the next loop iteration
		}

		// Wait for the operator
		do {
			operator = KEYPAD_GetPressedKey();
		} while (operator == 0xff);

		// Display the operator
		if (operator == '+' || operator == '-' || operator == '*' || operator == '/' || operator == '=') {
			LCD_voidSendData(operator);
			} else if (operator == 'C') {
			LCD_voidSendCommand(0x01); // Clear the LCD display
			continue; // Skip the rest of the loop
			} else {
			continue; // If not a valid operator, continue to the next loop iteration
		}

		// Get the second number
		do {
			num2 = KEYPAD_GetPressedKey();
		} while (num2 == 0xff);

		// Display the second number if it is a digit
		if (num2 >= 0 && num2 <= 9) {
			LCD_voidSendNum(num2);
			} else {
			continue; // If not a digit, continue to the next loop iteration
		}

		// Perform the calculation
		if (operator == '+') {
			Loc_Sum = num1 + num2;
			} else if (operator == '-') {
			Loc_Sum = num1 - num2;
			} else if (operator == '*') {
			Loc_Sum = num1 * num2;
			} else if (operator == '/') {
			if (num2 != 0) { // Check for division by zero
				Loc_Sum = num1 / num2;
				} else {
				LCD_voidSendString("Err"); // Display error message
				continue; // Skip the rest of the loop
			}
		}

		// Wait for the '=' key to display the result
		do {
			Loc_KeyVal = KEYPAD_GetPressedKey();
		} while (Loc_KeyVal != '=');

		// Display the result
		LCD_voidSendData('=');
		LCD_voidSendNum(Loc_Sum);

		// Wait for 'C' key to clear the screen
		do {
			Loc_KeyVal = KEYPAD_GetPressedKey();
		} while (Loc_KeyVal != 'C');

		// Clear the screen
		LCD_voidSendCommand(0x01);
	}

	return 0;
}
	


