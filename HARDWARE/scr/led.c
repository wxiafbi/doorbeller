/*-------------------------------------------------*/
/*            超纬电子STM32系列开发板              */
/*-------------------------------------------------*/
/*                                                 */
/*              实现LED功能的源文件                */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f10x.h" //包含需要的头文件
#include "led.h"       //包含需要的头文件
#include "delay.h"

/*-------------------------------------------------*/
/*函数名：初始化LED函数                            */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; // 定义一个设置GPIO的变量

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                  // 使能GPIOA端口时钟
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_13 | GPIO_Pin_12; // 准备设置 PA12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // IO速率50Mhz
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;                                      // 推免输出方式
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                                 // 设置PA8 11 12

    CLOSE_H;
    OPEN_H;
    BEEP_OUT(0);
    LED1_OUT(1);
}

/*-------------------------------------------------*/
/*函数名：点亮所有LED                              */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED_AllOn(void)
{
    LED3_ON;
}

/*-------------------------------------------------*/
/*函数名：熄灭所有LED                              */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED_AllOff(void)
{
    LED3_ON;
    Delay_Ms(5);
    LED3_OFF;
    Delay_Ms(5);
}
