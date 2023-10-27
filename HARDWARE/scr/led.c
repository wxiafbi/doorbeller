/*-------------------------------------------------*/
/*            ��γ����STM32ϵ�п�����              */
/*-------------------------------------------------*/
/*                                                 */
/*              ʵ��LED���ܵ�Դ�ļ�                */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f10x.h" //������Ҫ��ͷ�ļ�
#include "led.h"       //������Ҫ��ͷ�ļ�
#include "delay.h"

/*-------------------------------------------------*/
/*����������ʼ��LED����                            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; // ����һ������GPIO�ı���

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                  // ʹ��GPIOA�˿�ʱ��
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_13 | GPIO_Pin_12; // ׼������ PA12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // IO����50Mhz
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;                                      // ���������ʽ
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                                 // ����PA8 11 12

    CLOSE_H;
    OPEN_H;
    BEEP_OUT(0);
    LED1_OUT(1);
}

/*-------------------------------------------------*/
/*����������������LED                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void LED_AllOn(void)
{
    LED3_ON;
}

/*-------------------------------------------------*/
/*��������Ϩ������LED                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void LED_AllOff(void)
{
    LED3_ON;
    Delay_Ms(5);
    LED3_OFF;
    Delay_Ms(5);
}
