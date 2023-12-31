/*-------------------------------------------------*/
/*            超纬电子STM32系列开发板              */
/*-------------------------------------------------*/
/*                                                 */
/*              实现LED功能的头文件                */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __LED_H
#define __LED_H

// #define LED1_OUT(x)   GPIO_WriteBit(GPIOA, GPIO_Pin_8,  (BitAction)x)  //设置PA8  的电平，可以点亮熄灭LED1
#define LED2_OUT(x)   GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)x)  //设置PA11 的电平，可以点亮熄灭LED2
#define LED3_OUT(x)   GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)x)  //设置PA12 的电平，可以点亮熄灭LED3
#define CLOSE_OUT(x)   GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)x)   //设置PB5  的电平，可以点亮熄灭LED4
#define OPEN_OUT(x)   GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)x)   //设置PB5  的电平，可以点亮熄灭LED4
#define BEEP_OUT(x)   GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)x)   //设置PB5  的电平，可以点亮熄灭LED4
#define LED1_OUT(x)   GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)x)   //设置PB5  的电平，可以点亮熄灭LED4

#define LED1_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8)   //PA8  控制LED1,读取电平状态，可以判断LED1是点亮还是熄灭
#define LED2_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11)  //PA11 控制LED2,读取电平状态，可以判断LED2是点亮还是熄灭
#define LED3_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)  //PA12 控制LED3,读取电平状态，可以判断LED3是点亮还是熄灭
#define LED4_IN_STA   GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5)   //PB5  控制LED4,读取电平状态，可以判断LED4是点亮还是熄灭

#define LED1_ON       GPIO_ResetBits(GPIOA, GPIO_Pin_8)         //共阳极，拉低PA8电平，点亮LED1
#define LED1_OFF      GPIO_SetBits(GPIOA, GPIO_Pin_8)           //共阳极，拉高PA8电平，熄灭LED1

#define LED2_ON       GPIO_ResetBits(GPIOA, GPIO_Pin_11)        //共阳极，拉低PA11电平，点亮LED2
#define LED2_OFF      GPIO_SetBits(GPIOA, GPIO_Pin_11)          //共阳极，拉高PA11电平，熄灭LED2

#define LED3_ON       GPIO_ResetBits(GPIOA, GPIO_Pin_12)        //共阳极，拉低PA12电平，点亮LED3
#define LED3_OFF      GPIO_SetBits(GPIOA, GPIO_Pin_12)          //共阳极，拉高PA12电平，熄灭LED3

#define CLOSE_K       GPIO_ResetBits(GPIOB, GPIO_Pin_14)         //共阳极，拉低PB14电平，继电器在开状态
#define CLOSE_H       GPIO_SetBits(GPIOB, GPIO_Pin_14)           //共阳极，拉高PB14电平，继电器在默认状态

#define OPEN_K       GPIO_ResetBits(GPIOB, GPIO_Pin_15)         //共阳极，拉低PB5电平，点亮LED4
#define OPEN_H       GPIO_SetBits(GPIOB, GPIO_Pin_15)           //共阳极，拉高PB15电平，继电器在默认状态

void LED_Init(void);               //初始化	
void LED_AllOn(void);              //点亮所有LED
void LED_AllOff(void);             //熄灭所有LED

#endif
