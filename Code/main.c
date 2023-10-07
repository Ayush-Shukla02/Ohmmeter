#include <stdio.h>
#include <stdlib.h>
#include "TM4C123GH6PM.h"

#define lim 16000000

// The delay function is created here.
void delay()
{
    volatile int counter = 0;
    while(counter < lim)
        counter += 1;
}

int main()
{
    unsigned int adc_val;                   //Initialized required parameters. 
    float voltage, current, resistance;
    
    SYSCTL -> RCGCGPIO |= (1 << 4);	        // Enable PORT E by providing the clock
    SYSCTL -> RCGCADC |= (1 << 0);          // Enabling the ADC0 module
    
    // ADC Configuration
    
    GPIOE -> AFSEL |= (1 << 3);             // Using PE3, AIN0
    GPIOE -> DEN &= ~(1 << 3);              // Disable digital functions for pin
    GPIOE -> AMSEL |= (1 << 3);             // Enable analog functions for pin
      
    // Sample Sequencer Configuration
    
    ADC0 -> ACTSS &= ~(1 << 3);             // Sample Sequencer 3 is diabled
    ADC0 -> EMUX &= ~(0xF << 12);           // SS3 set to sample continuosly
    ADC0 -> SSMUX3 = 0;                     // Input source set to AIN0
    ADC0 -> SSCTL3 |= (1 << 1) | (1 << 2);  // 0110
    ADC0 -> ACTSS |= (1 << 3);              // Enable ADC0 Sequencer 3
    
    while(1)
    {
        ADC0 -> PSSI |= (1 << 3);           // Enable SS3 conversion, start sampling data        
        while((ADC0->RIS & (1 << 3)) == 0); // Wait for the data   conversion        
        adc_val = ADC0 -> SSFIFO3;          // Read the result of ADC from SS3 FIFO
        
        ADC0 -> ISC = (1 << 3);             // Clear conversion flag bit
        
        // Values calculation
        voltage = (adc_val * 0.00081);
        current = voltage / 1000.0;
        resistance = (3.3 / current) - 1000.0;
        
        printf("Volatge is: %fV \n", voltage);
        printf("Current is: %fA \n", current);
        printf("Resistance is: %fohm \n", resistance);
        printf("\n\n");
        
        delay();                            // Providing 1 sec delay before other reading
    }  
    return 0;
}
