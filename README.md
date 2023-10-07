# Ohmmeter

## Introduction

The primary goal of this project is to implement a simple digital Ohmmeter using internal ADC and GPIOs using Tiva C board and resistors as per requirement and also to make sure that the accuracy of the Ohmmeter is within the acceptable range for all ranges of resistors.
Voltage Divider circuit has been used to perform the task.

## Components

-   Tiva TM4C123GH6PM Microcontroller
-   Tools: IAR Embedded Workbench
-   Resistors

## Working

-   The concept behind a voltage divider circuit is to divide a voltage into smaller parts through a series of resistors.
-   So, here we used two resistors mainly where one of them is the reference resistor and the other one is unknown resistor.
-   The output voltage of the circuit is determined by the values of the resistors and the input voltage and then this output is checked using the ADC value of the Tiva C board. By measuring the output voltage, the resistance of the component being tested can be calculated.

## Output

For the results refer to the [output](./Photos) folder.
