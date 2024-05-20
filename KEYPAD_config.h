/*
 * KEYPAD_config.h
 *
 * Created: 5/18/2024 5:30:09 AM
 *  Author: ahmed
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_




#define KEYPAD_ROWS         4
#define KEYPAD_COLUMNS      4



#define KEYPAD_ROW_PORT		        DIO_PORTC

#define KEYPAD_ROW_1_PIN			DIO_PIN3
#define KEYPAD_ROW_2_PIN			DIO_PIN4
#define KEYPAD_ROW_3_PIN			DIO_PIN5
#define KEYPAD_ROW_4_PIN			DIO_PIN6

#define KEYPAD_COLUMN_PORT		    DIO_PORTB
									
#define KEYPAD_COLUMN_1_PIN			DIO_PIN4
#define KEYPAD_COLUMN_2_PIN			DIO_PIN5
#define KEYPAD_COLUMN_3_PIN			DIO_PIN6
#define KEYPAD_COLUMN_4_PIN			DIO_PIN7



#endif /* KEYPAD_CONFIG_H_ */