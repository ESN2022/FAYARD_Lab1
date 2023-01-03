#include<system.h>
#include<altera_avalon_pio_regs.h>
#include <stdio.h>

int b, i = 0, t;

int main(int argc, char *argv[])
{
    while(1){
        b = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);
        switch (b)
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


        for (i=0;i<7;i++){
           IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,1<<i);
           usleep(t);
        }
        for (i=7;i>0;i--){
           IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,1<<i);
           usleep(t);
        }
    }

    return 0;
}
