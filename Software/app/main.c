#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <sys/alt_irq.h>
#include <alt_types.h>

int push_b, push_b_old = 0, state = 0;
int slide_b;
int i = 0;
int t = 200000;


static void push_b_ISR (void * context, alt_u32 id)
{
	//Speed determined by the slide buttons in polling mode
	slide_b = (IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE)) & 0x0F;		// Take the bit 0 to 4
	switch (slide_b)
	{
	case 1:																//Bit 0
		t = 600000;
		break;
	case 2:																//Bit 1
		t = 400000;
		break;
	case 4:																//Bit 2
		t = 100000;
		break;
	case 8:																//Bit 3
		t = 50000;
		break;
	default:
		t = 200000;
		break;
	}
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE,0x0F);
}


int main(int argc, char *argv[])
{
	//Set the input that trigger interrupts (slide buttons)
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE, 0x0F);

	//Reset the edge capture register
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE,0x0F);

	//Register the ISR to the corresponding interrupt
	alt_irq_register (BUTTONS_IRQ, NULL, (void*) push_b_ISR);

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
