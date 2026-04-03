#include "SPI.h"
#include "RCC_STM32.h"
#include "NVIC.h"
/* Buffer de gui du lieu cho Raspberry Pi */
//static unsigned char *spi_tx_buffer = 0;
//static unsigned short spi_tx_length = 0;
//static unsigned short spi_tx_index = 0;
void SPI1_Init(void)
{	
	CLK_CONTROL->APB2ENR |= (1U << 12); 		/* CLOCK SPI1 */
	/* Disable CR1 */
	SPI1_CONTROL->CR1 	 &= ~(1U << 6); 		/* SPI_CR1_disabled 	*/
	/* Clear 
	   Slave mode
     CPOL = 0
     CPHA = 0
     8-bit data
     hardware NSS */
		/* Hardware NSS */ 
	SPI1_CONTROL->CR1 &= ~(1U << 9); 
	SPI1_CONTROL->CR1 = 0;
	/* Enable RX interrupt */
  SPI1_CONTROL->CR2 |= (1 << 6);
	/* Enable interrupt trong NVIC */
//	NVIC_ClearPending	(35);
//	NVIC_SetPriority	(35, 1);
//	NVIC_EnableIRQn		(35); 		/* SPI1 : IRQn = 35) */
	/* SPI_CR1_enable 		*/
	SPI1_CONTROL->CR1		 |= (1U << 6);			
  SPI1_CONTROL->DR = 0xBB;
}
void SPI1_Run(void)
{
    if (SPI1_CONTROL->SR & (1 << 0)) // RXNE
    {
        volatile unsigned char dummy = SPI1_CONTROL->DR;

        SPI1_CONTROL->DR = 0xBB; // luôn send 0xBB
    }

    // clear OVR
    if (SPI1_CONTROL->SR & (1 << 6))
    {
        volatile unsigned char temp;
        temp = SPI1_CONTROL->DR;
        temp = SPI1_CONTROL->SR;
    }
}