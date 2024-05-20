/*
 * KEYPAD_prog.c
 *
 * Created: 5/18/2024 5:29:41 AM
 *  Author: ahmed
 */ 
#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "DIO_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"




/************** Mapping Keypad Buttons *********************/
u8 KEYPAD_ButtonValues[KEYPAD_ROWS][KEYPAD_COLUMNS]={
	{1,2,3,'+'},
	{4,5,6,'-'},
	{7,8,9,'C'},
	{'*',0,'=','/'},
	
};

/************* Function to intialize Keypad ************/
void KEYPAD_init(void){
	
	u8 Loc_u8_arr_col[4]={ KEYPAD_COLUMN_1_PIN,
						   KEYPAD_COLUMN_2_PIN,
						   KEYPAD_COLUMN_3_PIN,	
						   KEYPAD_COLUMN_4_PIN	
	};

	u8 Loc_u8_arr_row[4]={ KEYPAD_ROW_1_PIN,
		                   KEYPAD_ROW_2_PIN,
		                   KEYPAD_ROW_3_PIN,
		                   KEYPAD_ROW_4_PIN
	};
	
	u8 Loc_u8_row_iterator =0;
	u8 Loc_u8_column_iterator =0;
	
	for(Loc_u8_column_iterator =0 ; Loc_u8_column_iterator < KEYPAD_COLUMNS ;Loc_u8_column_iterator++){
		
		/******** SET Column Pins OUTPUT High *********/
		DIO_voidSetPinDir(KEYPAD_COLUMN_PORT,Loc_u8_arr_col[Loc_u8_column_iterator],OUTPUT);	
		
		DIO_voidSetPinVal(KEYPAD_COLUMN_PORT,Loc_u8_arr_col[Loc_u8_column_iterator],HIGH);
		
	}
	
	for(Loc_u8_row_iterator =0 ;Loc_u8_row_iterator < KEYPAD_ROWS ;Loc_u8_row_iterator++){
		
		/***** SET ROW PINS INPUT High ********/
		
		DIO_voidSetPinDir(KEYPAD_ROW_PORT,Loc_u8_arr_row[Loc_u8_row_iterator],INPUT);
		
		DIO_voidSetPinVal(KEYPAD_ROW_PORT,Loc_u8_arr_row[Loc_u8_row_iterator],HIGH);
	}
	
	
	
	
}

/************ Function to return pressed key *************/

u8 KEYPAD_GetPressedKey(void){
	
	u8 Loc_rand_var = 0xFF;
	
	u8 Loc_u8_arr_col[4]={ KEYPAD_COLUMN_1_PIN,
		KEYPAD_COLUMN_2_PIN,
		KEYPAD_COLUMN_3_PIN,
		KEYPAD_COLUMN_4_PIN
	};

	u8 Loc_u8_arr_row[4]={ KEYPAD_ROW_1_PIN,
		KEYPAD_ROW_2_PIN,
		KEYPAD_ROW_3_PIN,
		KEYPAD_ROW_4_PIN
	};
	
	u8 Loc_u8_row_iterator =0;
	u8 Loc_u8_column_iterator =0;
	
	for(Loc_u8_column_iterator = 0 ; Loc_u8_column_iterator < KEYPAD_COLUMNS ; Loc_u8_column_iterator++){
		
		/********* SET COLUMNS LOW **********/
		DIO_voidSetPinVal(KEYPAD_COLUMN_PORT , Loc_u8_arr_col[Loc_u8_column_iterator] , LOW );
		
		for(Loc_u8_row_iterator = 0 ;Loc_u8_row_iterator < KEYPAD_ROWS ;Loc_u8_row_iterator++){
			
			
			if(DIO_u8GetPinVal(KEYPAD_ROW_PORT ,Loc_u8_arr_row[Loc_u8_row_iterator])==0){
				
				Loc_rand_var=KEYPAD_ButtonValues[Loc_u8_row_iterator][Loc_u8_column_iterator];
				while(DIO_u8GetPinVal(KEYPAD_ROW_PORT,Loc_u8_arr_row[Loc_u8_row_iterator])==0);
			}
			
		}
		/********* SET Column High ******/
		
		DIO_voidSetPinVal(KEYPAD_COLUMN_PORT,Loc_u8_arr_col[Loc_u8_column_iterator],HIGH);
		
		
		
	}
	
	return Loc_rand_var;
	
}