#include "mpu6050.h"

volatile int flag_dma ;
uint8_t Raw_Data[12];

void I2C1_Init(void) 
{
	RCC->APB1ENR |= (1 << 21);         // bat clock i2c1
	GPIO(PORTB, 6, 3, 6);              //cau hinh PB6 va PB7 la SCL va SDA
	GPIO(PORTB, 7, 3, 6);
	I2C1->CR1    &= ~(1 << 0);         // tat truoc khi cau hinh
	I2C1->CR1    |= (1 << 10);         // cho phep gui ACK
	I2C1->CR2    &= ~(0x3F << 0);      //xoa truoc khi cau hinh tan so  
	I2C1->CR2    |= (0x24 << 0);       //cau hinh tan so nguon clock APB1 36MHz cho SCL
	I2C1->CCR    &= ~(1 << 15);        // Sm mode
	I2C1->CCR    &= ~(0xFFF << 0);     // xoa truoc khi cau hinh
	I2C1->CCR    |= (0xB4 << 0);       // he so nhan cua nguon clock cho SCL len 100kHz
	I2C1->TRISE  &= ~(0x2F << 0);
	I2C1->TRISE  |= (0x25 << 0);       // thoi gian canh len o 100kHz max la 1us
	I2C1->CR1    |= (1 << 0);          // bat ngoai vi
	if (I2C1->SR2 & (1 << 1))
	{
    I2C1_ResetCLK();
		for (volatile int i = 0; i < 4; i ++)
		{
			TogglePin(PORTB, 1);
			delayms(500);
		}
		WritePin(PORTB, 1, 0);
	}
}
void I2C1_ResetCLK (void) 
{
	RCC->APB1ENR &= ~(1U << 21);        
	RCC->APB1ENR |= (1 << 21);        
  I2C1->CR1 &= ~(1 << 0);   
  GPIO(PORTB, 6, 3, 4);
	GPIO(PORTB, 7, 3, 4);
  for(int i = 0; i < 10; i++)
  {
     GPIOB->ODR |=  (1 << 6); 
     delayms(1);
     GPIOB->ODR &= ~(1U << 6); 
     delayms(1);
    }
  GPIOB->ODR &= ~(1U << 6); // SCL Low
  GPIOB->ODR &= ~(1U << 7); // SDA Low
  delayms(1);
  GPIOB->ODR |= (1 << 6);  // SCL High (Trong khi SDA dang Low)
  delayms(1);
  GPIOB->ODR |= (1 << 7);  // SDA High (Trong khi SCL dang High) -> STOP Condition
  GPIOB->ODR |= (1 << 7);
  GPIO(PORTB, 6, 3, 6);   //cau hinh ve lai SCL SDA
  GPIO(PORTB, 7, 3, 6);
  I2C1->CR1 |=  (1 << 0);   // PE = 1
}
void MPU_Init(void) 
{
 GPIO(PORTB, 15, 3, 3);                       //keo chan ADO xuong 0
 WritePin(PORTB, 15, 0);
 MPU_W(0x6B, 0x80);                       //reset tat ca thanh ghi ve mac dinh
 delayms(100);
 MPU_W(0x6B, 0x01);                        // thoat khoi che do sleep(thanh ghi 107)
 delayms(100);
 MPU_W(0x19, 0x4);                        //cau hinh tan so lay mau la 200Hz (thanh ghi 25)
 MPU_W(0x1A, 0x3);                       //cau hinh bo loc tan so (thanh ghi 1A)
 MPU_W(0x1B, 0x8);                       //cau hinh scale range gyroscope (thanh ghi 1B)
 MPU_W(0x1C, 0x08);                       //cau hinh scale range accelerometer (thanh ghi 1C)
}
void MPU_RW(uint8_t address, uint8_t RW) 
{
	I2C1->DR = (uint8_t)((address << 1) | RW);  // goi dia chi cua mpu
	while(!((I2C1->SR1 >> 1) & 1));       // cho mpu phan hoi
	(void)I2C1->SR2;                      //clear co mpu phan hoi
}
void I2C1_Start(void) 
{
	I2C1->CR1 |= (1 << 8);             // gui start
	while(!((I2C1->SR1 >> 0) & 1));    //cho start duoc gui
}
void I2C1_Stop(void) 
{
	I2C1->CR1 |= (1 << 9);            //gui stop
	//while(I2C1->CR1 & (1 << 9));      //cho stop duoc gui
}
void I2C1_Send1Byte(uint8_t data) 
{
	while(!((I2C1->SR1 >> 7) & 1));   //cho thanh ghi DR trong
	I2C1->DR = data;                  //gui data
	while(!((I2C1->SR1 >> 2) & 1));   //cho gui xong (cho ACK) 
}
void MPU_W (uint8_t address, uint8_t data) 
{
	I2C1_Start();                           //gui tin hieu start
	MPU_RW(0x68, WRITE);                    //goi dia chi cua MPU
	I2C1_Send1Byte(address);                //gui dia chi thanh ghi muon ghi vao
	I2C1_Send1Byte(data);                   //gui du lieu muon ghi
	I2C1_Stop();                            //gui tin hieu stop
}
void FIFO_INT(void) 
{
	MPU_W(0x6A, 0x00);                     // tat FIFO truoc khi cau hinh
  MPU_W(0x6A, 0x04);                     // FIFO reset
  delayms(100);
	MPU_W(0x23, 0x78);                     //cau hinh FIFO(thanh ghi 0x23)
	MPU_W(0x6A, 0x40);                      //bat FIFO
	MPU_W(0x37, 0x20);                     //cau hinh chan ngat
	MPU_W(0x38, 0x1);                      //cau hinh nguon ngat
}
void EXTI_Config(void) 
{
	RCC->APB2ENR  |= (1 << 0);             //cap clock cho AFIO
	GPIO(PORTB, 14, INPUT, PUPD);          //chon chan PB14 lam input pull up pull down
	GPIOB->ODR &= ~(1U << 14);              //chon tro keo xuong
	AFIO->EXTICR[3] &= ~(0xFU << 8);       //chon chan PB14 nhan ngat ngoai
	AFIO->EXTICR[3] |= (0x1 << 8);
	EXTI->IMR  |= (1 << 14);               // nhan line 14 lam ngat
	EXTI->RTSR |= (1 << 14);               //ngat canh len
	NVIC_EnableIRQ(EXTI15_10_IRQn);        //bat ngat
	NVIC_SetPriorityGrouping(2);           //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(2, 1, 1)); //cung nhom uu tien 2, pre = 1, sub = 1
}
void EXTI15_10_IRQHandler(void) 
{
    if (EXTI->PR & (1 << 14))   //neu co ngat chan PB12
    {
        EXTI->PR = (1 << 14);   // clear co stm32
			  //WritePin(0, 8 , 1);
        DMA_Read();				
    }
}
void DMA1_I2C1_Config(uint8_t *pdata)
{
	//Bat clock DMA1
	RCC->AHBENR |= (1 << 0);
	//Tat kenh truoc khi cau hinh
	DMA1_Channel7->CCR &= ~(1U << 0);
	//Bat ngat khi truyen xong du lieu
	DMA1_Channel7->CCR |= (1 << 1);
	//Doc du lieu tu ngoai vi 
	DMA1_Channel7->CCR &= ~(1U << 4);
	//Tat lien tuc luu xoay vong trong mang
	DMA1_Channel7->CCR &= ~(1U << 5);
	//Sau khi luu tang dia chi cua mang len 1 
	DMA1_Channel7->CCR |= (1 << 7);
	//Kich thuoc du lieu lay tu I2C1 la 8 bit
	DMA1_Channel7->CCR &= ~(3U << 8);
	//Kich thuoc cua 1 phan tu trong mang
	DMA1_Channel7->CCR &= ~(3U << 10);
	//Muc do uu tien 
	DMA1_Channel7->CCR &= ~(3U << 12);
	DMA1_Channel7->CCR |= (2 << 12);
	//So luong du lieu can chuyen doi = so phan tu cua mang
	DMA1_Channel7->CNDTR = 12;
	//Dia chi thanh ghi luu du lieu I2C1
	DMA1_Channel7->CPAR = (uint32_t)&(I2C1->DR);
	//Dia chi mang luu du lieu
	DMA1_Channel7->CMAR = (uint32_t)pdata;
	//bat NVIC
	NVIC_EnableIRQ(DMA1_Channel7_IRQn);
	/*//Bat I2C2 RX DMA
  I2C2->CR2 |= (1 << 11);
	//Bat DMA
	DMA1_Channel5->CCR |= (1 << 0);	*/
}
void DMA_Read(void) 
{
	//Bat I2C2 RX DMA
  I2C1->CR2 |= (1 << 11);
	I2C1->CR1 |= (1 << 10);              //set de moi lan nhan 1 byte stm32 se tu dong ACK
	I2C1->CR2 |= (1 << 12);               //bat last 
  DMA1_Channel7->CCR &= ~(1U << 0);    //tat DMA de cau hinh
  DMA1_Channel7->CNDTR = 12;          // Nap lai luong byte can nhan
	//Bat DMA
	DMA1_Channel7->CCR |= (1 << 0);	
	I2C1_Start();                           //gui tin hieu start
	MPU_RW(0x68, WRITE);                     //gui dia chi MPU ghi
	I2C1_Send1Byte(0x74);                   //gui dia chi thanh ghi muon doc
	I2C1_Start();                           //gui start lan 2
	MPU_RW(0x68, READ);                     //gui dia chi MPU doc
}
void DMA1_Channel7_IRQHandler(void) 
{
    if (DMA1->ISR & (1 << 25))   //neu co ngat DMA1 I2C1 RECEIVED
    {
      DMA1->IFCR = (1 << 25);   // clear co stm32
			I2C1_Stop();
			flag_dma = 1;
      uint8_t x = MPU_R1Byte(0x3A); //clear co trong MPU
			 (void)x;  
}
}
uint8_t MPU_R1Byte (uint8_t address)
{
	uint8_t kq;
	I2C1_Start();                           //gui tin hieu start
	MPU_RW(0x68, WRITE);                    //gui dia chi cua MPU ghi
	I2C1_Send1Byte(address);                //gui dia chi thanh ghi muon doc
	I2C1_Start();                           //gui start lan 2
	MPU_RW(0x68, READ);                     //gui dia chi MPU doc
  I2C1->CR1    &= ~(1 << 10);             //NACK
	I2C1_Stop();                            //gui stop
  kq = I2C1_Read1Byte();                  //doc 1 byte
	return kq;
}
uint8_t I2C1_Read1Byte(void)
{
	while(!((I2C1->SR1 >> 6) & 1));         //cho thanh ghi DR co du lieu
	return (uint8_t)I2C1->DR;
}
void MPU_FIFO_INT_Config(void) 
{
	GPIO(PORTB, 1, 3, 3);
	I2C1_Init();
	MPU_Init();
	FIFO_INT();
	EXTI_Config();
	DMA1_I2C1_Config(Raw_Data);
}
void Data_MPU(float *dulieudachuyendoi)
{
	int16_t ax = (int16_t)((Raw_Data[0] << 8) | Raw_Data[1]);
	int16_t ay = (int16_t)((Raw_Data[2] << 8) | Raw_Data[3]);
	int16_t az = (int16_t)((Raw_Data[4] << 8) | Raw_Data[5]);
	int16_t gx = (int16_t)((Raw_Data[6] << 8) | Raw_Data[7]);
	int16_t gy = (int16_t)((Raw_Data[8] << 8) | Raw_Data[9]);
	int16_t gz = (int16_t)((Raw_Data[10] << 8) | Raw_Data[11]);
 	dulieudachuyendoi[0] = (float)((4.0 / 32768) * ax);
 	dulieudachuyendoi[1] = (float)((4.0 / 32768) * ay);
 	dulieudachuyendoi[2] = (float)((4.0 / 32768) * az);
 	dulieudachuyendoi[3] = (float)((500.0 / 32768) * gx);
 	dulieudachuyendoi[4] = (float)((500.0 / 32768) * gy);
	dulieudachuyendoi[5] = (float)((500.0 / 32768) * gz);
	flag_dma = 0;
}
