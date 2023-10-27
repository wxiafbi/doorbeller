/*-------------------------------------------------*/
/*            ��γ����STM32ϵ�п�����              */
/*-------------------------------------------------*/
/*                                                 */
/*              ʵ��LED���ܵ�ͷ�ļ�                */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __LED_H
#define __LED_H

// #define LED1_OUT(x)   GPIO_WriteBit(GPIOA, GPIO_Pin_8,  (BitAction)x)  //����PA8  �ĵ�ƽ�����Ե���Ϩ��LED1
#define LED2_OUT(x)   GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)x)  //����PA11 �ĵ�ƽ�����Ե���Ϩ��LED2
#define LED3_OUT(x)   GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)x)  //����PA12 �ĵ�ƽ�����Ե���Ϩ��LED3
#define CLOSE_OUT(x)   GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)x)   //����PB5  �ĵ�ƽ�����Ե���Ϩ��LED4
#define OPEN_OUT(x)   GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)x)   //����PB5  �ĵ�ƽ�����Ե���Ϩ��LED4
#define BEEP_OUT(x)   GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)x)   //����PB5  �ĵ�ƽ�����Ե���Ϩ��LED4
#define LED1_OUT(x)   GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)x)   //����PB5  �ĵ�ƽ�����Ե���Ϩ��LED4

#define LED1_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8)   //PA8  ����LED1,��ȡ��ƽ״̬�������ж�LED1�ǵ�������Ϩ��
#define LED2_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11)  //PA11 ����LED2,��ȡ��ƽ״̬�������ж�LED2�ǵ�������Ϩ��
#define LED3_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)  //PA12 ����LED3,��ȡ��ƽ״̬�������ж�LED3�ǵ�������Ϩ��
#define LED4_IN_STA   GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5)   //PB5  ����LED4,��ȡ��ƽ״̬�������ж�LED4�ǵ�������Ϩ��

#define LED1_ON       GPIO_ResetBits(GPIOA, GPIO_Pin_8)         //������������PA8��ƽ������LED1
#define LED1_OFF      GPIO_SetBits(GPIOA, GPIO_Pin_8)           //������������PA8��ƽ��Ϩ��LED1

#define LED2_ON       GPIO_ResetBits(GPIOA, GPIO_Pin_11)        //������������PA11��ƽ������LED2
#define LED2_OFF      GPIO_SetBits(GPIOA, GPIO_Pin_11)          //������������PA11��ƽ��Ϩ��LED2

#define LED3_ON       GPIO_ResetBits(GPIOA, GPIO_Pin_12)        //������������PA12��ƽ������LED3
#define LED3_OFF      GPIO_SetBits(GPIOA, GPIO_Pin_12)          //������������PA12��ƽ��Ϩ��LED3

#define CLOSE_K       GPIO_ResetBits(GPIOB, GPIO_Pin_14)         //������������PB14��ƽ���̵����ڿ�״̬
#define CLOSE_H       GPIO_SetBits(GPIOB, GPIO_Pin_14)           //������������PB14��ƽ���̵�����Ĭ��״̬

#define OPEN_K       GPIO_ResetBits(GPIOB, GPIO_Pin_15)         //������������PB5��ƽ������LED4
#define OPEN_H       GPIO_SetBits(GPIOB, GPIO_Pin_15)           //������������PB15��ƽ���̵�����Ĭ��״̬

void LED_Init(void);               //��ʼ��	
void LED_AllOn(void);              //��������LED
void LED_AllOff(void);             //Ϩ������LED

#endif
