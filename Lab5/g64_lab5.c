#include<sys/time.h>
#include<stdio.h>

volatile int *led = (int *) 0xFF200400; // red LED address
volatile int *hex3_hex0 = (int *) 0xFF200420; // address of HEX0
volatile int *hex5_hex4 = (int *) 0xFF200430; // address of HEX4
volatile int *switchptr = (int *) 0xFF200410; // SW slider switch address
volatile int *pushbutton = (int *) 0xFF200440; // Pushbuttons address
volatile int *input = (int *) 0xFF200000; // address for custom component

/*
 *	
 */
int pack_hex(int hex3, int hex2, int hex1, int hex0) {
    return ((hex3 << 24) | (hex2 << 16) | (hex1 << 8) | hex0);
}

/*
 *
 */
int hex_to_7segment(int hex) {
    switch (hex) {
        case 0 :
            return 0b11000000;
        case 1 :
            return 0b11111001;
        case 2 :
            return 0b10100100;
        case 3 :
            return 0b10110000;
        case 4 :
            return 0b10011001;
        case 5 :
            return 0b10010010;
        case 6 :
            return 0b10000010;
        case 7 :
            return 0b11111000;
        case 8 :
            return 0b10000000;
        case 9 :
            return 0b10010000;
        default :
            return 0b11111111;
    }
}

/*
 *	Resets the HEX to display all zeros
 */
void hex_to_zeros() {
	*(hex3_hex0) = pack_hex(0b11000000, 0b11000000, 0b11000000, 0b11000000);
	*(hex5_hex4) = pack_hex(0, 0, 0b11000000, 0b11000000);
}

/*
 *	Main method: reads in two values from the led switches and displays the product on the HEX display
 */
int main(void) {
   	
	int i = 0;
	int display = 0;
    int switch_value = 0;
	int data1 = 0;
	int data2 = 0;
	int tmpData1 = 0;
	int tmpData2 = 0;
	int output = 0;
	int digit[6];
	int KEY1 = 13; 
	int KEY3 = 7;
	int KEY2 = 11;

	//initialize HEX display to all zero		
	hex_to_zeros();		

    while (1) {

		// TO RESET : Just multiply by 0
		// i.e. set data1 or data2 to zero using the slider switches and press the corresponding pushbutton
        
        switch_value = *(switchptr);
        *(led) = switch_value;
		
		//read in the first number and display it
		if(*pushbutton == KEY3) {
			//set the first input to the current value on the switches/leds
			data1 = *(switchptr);
			tmpData1 = data1;
			//*(input) = data1;

			//initialize digit array to all zeros
			for(i = 0; i < 6; i++) {
				digit[i] = 0;
			}
			
			//break up the value into separate digits 
			i = 0;
			while(tmpData1 > 0) {
				digit[i] = tmpData1 % 10;
				i++;
				if(i > 5) break;
				tmpData1 = tmpData1/10;
			}
		
			//display data1 on the hex display
			*(hex3_hex0) = pack_hex(hex_to_7segment(digit[3]), hex_to_7segment(digit[2]), hex_to_7segment(digit[1]), hex_to_7segment(digit[0]));
			*(hex5_hex4) = pack_hex(0, 0, hex_to_7segment(digit[5]), hex_to_7segment(digit[4]));			

		}

		//read in the second number and display
		if(*pushbutton == KEY2) {
			//set the second input to the current value on the switches/leds
			data2 = *(switchptr);
			tmpData2 = data2;
			//*(input+4) = data2;
			
			//initialize digit array to all zeros
			for(i = 0; i < 6; i++) {
				digit[i] = 0;
			}
			
			//break up data2 into separate digits 
			i = 0;
			while(tmpData2 > 0) {
				digit[i] = tmpData2 % 10;
				i++;
				if(i > 5) break;
				tmpData2 = tmpData2/10;
			}
		
			//display the value on the hex display
			*(hex3_hex0) = pack_hex(hex_to_7segment(digit[3]), hex_to_7segment(digit[2]), hex_to_7segment(digit[1]), hex_to_7segment(digit[0]));
			*(hex5_hex4) = pack_hex(0, 0, hex_to_7segment(digit[5]), hex_to_7segment(digit[4]));
			
		}		
		
		//display the product of the two input
		if(*pushbutton == KEY1) {

			output = data1*data2;	
			
			//initialize digit array to all zeros
			for(i = 0; i < 6; i++) {
				digit[i] = 0;
			}
			
			//break up the output into separate digits 
			i = 0;
			while(output > 0) {
				digit[i] = output % 10;
				i++;
				if(i > 5) break;
				output = output/10;
			}
		
			//display the product on the hex display
			*(hex3_hex0) = pack_hex(hex_to_7segment(digit[3]), hex_to_7segment(digit[2]), hex_to_7segment(digit[1]), hex_to_7segment(digit[0]));
			*(hex5_hex4) = pack_hex(0, 0, hex_to_7segment(digit[5]), hex_to_7segment(digit[4]));

		}	
    }
}
