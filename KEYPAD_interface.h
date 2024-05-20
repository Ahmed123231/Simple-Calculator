/*
 * KEYPAD_interface.h
 *
 * Created: 5/18/2024 5:29:21 AM
 *  Author: ahmed
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_







/************* Function to intialize Keypad ************/
void KEYPAD_init(void);

/************ Function to return pressed key *************/

u8 KEYPAD_GetPressedKey(void);



#endif /* KEYPAD_INTERFACE_H_ */