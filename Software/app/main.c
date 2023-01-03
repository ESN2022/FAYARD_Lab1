#include<system.h>
#include<altera_avalon_pio_regs.h>

int i = 0;

int main(int argc, char *argv[])
{
    while(1){
        for (i=0;i<7;i++){
           IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,1<<i);
           usleep(100000);
        }
        for (i=7;i>0;i--){
           IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,1<<i);
           usleep(100000);
        }
    }

    return 0;
}
