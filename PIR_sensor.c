/*
 * Project to program for the raspberry Pi to snap a picture when 
 * motion is detected on the PIR sensor
 * 
 * ECE477 Alyssa Wardwell 
*/


#include <bcm2835.h>
#include <stdlib.h>
#include <stdio.h>

// Assign the PIR sensor GPIO pin 
#define PIR_Sensor RPI_GPIO_P1_11

int main(int argc, char **argv)
{
    // First initialize the BCM2835 Library
    if (!bcm2835_init())
    return 1;

    // Set the PIR_Sensor as an input
    bcm2835_gpio_fsel(PIR_Sensor, BCM2835_GPIO_FSEL_INPT);
   
    // Print a statement to ensure the program is running in the terminal
    printf("Program has started running...\n");

    while(1)
    {
        if (bcm2835_gpio_lev(PIR_Sensor))
        {
            system("raspistill -q 5 -o pic.jpg -t 1 -th 0:0:0");
            printf("Motion detected, picture has been taken!\n");
            while (bcm2835_gpio_lev(PIR_Sensor));
        }
        // Add 10 second delay to allow PIR sensor to reset
        bcm2835_delay(10000);
    }
}
