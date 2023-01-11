#include <system.h>
#include <altera_avalon_pio_regs.h>

int push_b, push_b_old = 0, state = 0;
int slide_b;
int i = 0;
int t;

int main(int argc, char *argv[])
{
    while(1){
		//Push button state in polling mode
		push_b = (IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE)) >> 4;				// Take the 5th bit value which corresponds to the push button value

		if ((push_b == 0) && (push_b_old == 1))
		{
			state = 1 - state;
		}
		push_b_old = push_b;

		if (state == 1)															// If the push button has been pressed
		{
			//Speed determined by the slide buttons in polling mode
			slide_b = (IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE)) & 0x0F;		// Take the bit 0 to 4
			switch (slide_b)
			{
			case 1:
				t = 600000;
				break;
			case 2:
				t = 400000;
				break;
			case 4:
				t = 100000;
				break;
			case 8:
				t = 50000;
				break;
			default:
				t = 200000;
				break;
			}

			//Led chaser
			for (i=0;i<7;i++){
			   IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,1<<i);
			   usleep(t);
			}
			for (i=7;i>0;i--){
			   IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,1<<i);
			   usleep(t);
			}
		}
		else{
           IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,0);
		}
	}

    return 0;
}
