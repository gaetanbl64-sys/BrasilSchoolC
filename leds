/* 
  LEDs LD0 to LD5 are mapped to GPIO bits 0 to 5.
  Switches SW0 to SW5 are mapped to GPIO bits 8 to 13.
  Buttons BTNU, BTNL, BTND, BTNR, BTNC are mapped to GPIO bits 16 to 20.
  The PMODA port is mapped to GPIO bits 24 to 31.
  
  data e' o endereco para leitura dos pinos de entrada (Switches e Buttons)
  
  output e' o endereco para escrita nos pinos de saida (LEDs)
  
*/
  
#include <iostream>

volatile unsigned int *data = (volatile unsigned int *)0x80000a00;
volatile unsigned int *output = (volatile unsigned int *)0x80000a04;
volatile unsigned int *direction = (volatile unsigned int *)0x80000a08;

int main(void){
	  // Enable all Outputs
	  *direction = 0xffffffff;
	  // Assign value to output registers ("escreve" 101010 nos LEDs)
	  *output = 0x0000002A;
	  
	  // Realiza a leitura dos valores indicados nos pinos de entrada (Switches e Buttons)
	  std::cout << "Current value of gpio lines: 0x" << *data << std::endl;
	return 0;
}