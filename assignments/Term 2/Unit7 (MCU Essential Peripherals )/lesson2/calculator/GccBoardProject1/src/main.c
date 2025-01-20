#include "LCD_driver/LCD.h"
#include "keypad_driver/keypad.h"

int calc(int n1, char s , int n2)
{
	switch(s)
	{
		case('+'):
			return n1+n2;
		case('-'):
			return n1-n2;
		case('/'):
			if(n2==0){return 0;}
			return n1/n2;
		case('*'):
			return n1*n2;
	}
}

int main(void) {
	LCD_INIT();
	Keypad_init();
	int sec=0;
	int num1=0;
	int num2=0;
	int res=0;
	char sign='-1';
	char pressed_key='-1';
	while (1)
	{
		pressed_key=Keypad_getkey();
		if (pressed_key >= '0' && pressed_key <= '9') {
			LCD_WRITE_CHAR(pressed_key);
			if (sec == 0) {
				num1 = num1 * 10 + (pressed_key - '0');
				} else if (sec == 1) {
				num2 = num2 * 10 + (pressed_key - '0');
			}
		}
		
		if(pressed_key=='!')
		{
			LCD_clear_screen();
			num1=0;
			num2=0;
			res=0;
			sign='-1';
		}
		if((pressed_key=='+' || pressed_key=='-' || pressed_key=='/' || pressed_key=='*') && (sec==0))
		{
			switch(pressed_key){
				case ('+'):
					LCD_WRITE_CHAR('+');
					sign='+';
					sec=1;
					break;
				case ('-'):
					LCD_WRITE_CHAR('-');
					sign='-';
					sec=1;
					break;
				case ('*'):
					LCD_WRITE_CHAR('*');
					sign='*';
					sec=1;
					break;
				case ('/'):
					LCD_WRITE_CHAR('/');
					sign='/';
					sec=1;
					break;
			}
		}
		if (pressed_key == '=' && sec == 1) {
			LCD_WRITE_CHAR('=');
			LCD_GOTO_XY(2, 0);

			res =calc(num1,sign,num2);

			if (res == 0) {
				LCD_WRITE_CHAR('0');
			} else {
				int temp = res;
				int digits = 0;
				while (temp != 0) {
					temp /= 10;
					digits++;
				}
				temp = res;
				for (int i = digits - 1; i >= 0; i--) {
				int digit = temp % 10;
				LCD_GOTO_XY(2, i);
				LCD_WRITE_CHAR(digit + '0');
				temp /= 10;
			}
		}

			_delay_ms(3000);

			num1 = 0;
			num2 = 0;
			res = 0;
			sign = '-1';
			sec = 0;

			LCD_clear_screen();
		}
	}
}