/*-----------------------------------------------------*/
/*              ��γ����STM32ϵ�п�����                */
/*-----------------------------------------------------*/
/*                     ����ṹ                        */
/*-----------------------------------------------------*/
/*USER     �����������main��������������������      */
/*HARDWARE ��������������ֹ����������������          */
/*CORE     ������STM32�ĺ��ĳ��򣬹ٷ��ṩ�����ǲ��޸� */
/*STLIB    ���ٷ��ṩ�Ŀ��ļ������ǲ��޸�              */
/*HMAC     �����ּ����㷨                              */
/*-----------------------------------------------------*/
/*                                                     */
/*           ����main��������ں���Դ�ļ�              */
/*                                                     */
/*-----------------------------------------------------*/

#include "stm32f10x.h" //������Ҫ��ͷ�ļ�
#include "main.h"      //������Ҫ��ͷ�ļ�
#include "delay.h"     //������Ҫ��ͷ�ļ�
#include "usart1.h"    //������Ҫ��ͷ�ļ�
#include "usart3.h"    //������Ҫ��ͷ�ļ�
#include "timer2.h"    //������Ҫ��ͷ�ļ�
#include "timer3.h"    //������Ҫ��ͷ�ļ�
#include "timer4.h"    //������Ҫ��ͷ�ļ�
#include "cat1.h"      //������Ҫ��ͷ�ļ�
#include "led.h"       //������Ҫ��ͷ�ļ�
#include "mqtt.h"      //������Ҫ��ͷ�ļ�
#include "key.h"       //������Ҫ��ͷ�ļ�
#include "aht10.h"     //������Ҫ��ͷ�ļ�
#include "iic.h"       //������Ҫ��ͷ�ļ�
#include "adc.h"       //������Ҫ��ͷ�ļ�
#include "iwdg.h"      //������Ҫ��ͷ�ļ�
#include "24c02.h"     //������Ҫ��ͷ�ļ�
#include "usart9.h"    //������Ҫ��ͷ�ļ�
#include "exti.h"
#include "beep.h"
#include "stmflash.h"
#include "oled.h"
#include "cmd.h"
#include "gui.h"
#include "test.h"

extern int finaldata1;
extern int finaldata2;
extern char fina_data1[5];
unsigned int x;
unsigned int SystemTimer = 0;                        // ����ȫ�ּ�ʱ�ı���           ��λ��
unsigned int TEHUTimer   = 0;                        // ������ʪ�Ȳɼ��ļ�ʱ�ı���   ��λ��
unsigned int ADCTimer    = 0;                        // ����ADC�ɼ��ļ�ʱ�ı���      ��λ��
u8 DataString[8]         = {0x80, 0x06, 0x03, 0x77}; // ���ڲ�ѯ����
int OPEN_flag             = 0;                        // ���ͱ�־λ����
float MAX = 0.0, TEMP = 0.0, DIST = 0.0;
float Disce[150] = {0};
float LUNA       = 0;
float tempdata; // ���ڱ��洫���������¶�ֵ�������������¶�ֵ��������20��
extern int ampdata;
float adcdata; // ���ڱ���3��ADCͨ��������

int main(void)
{
    // int i; // ����forѭ��
    MQTT_Buff_Init();
    IWDG_Init(6, 625); // �������Ź� ʱ��4s
    // IWDG_Init(6, 156);   // �������Ź� ʱ��4s
    Delay_Init();        // ��ʱ���ܳ�ʼ��
    LCD_Init();	   //???��????????
	LCD_Clear(BLACK); //????

	POINT_COLOR=WHITE; 
	LCD_DrawRectangle(0,0,128-1,128-1);	//?????? 

	Show_Str(32,5,BLUE,YELLOW,"?????��??",16,0);
	Show_Str(5,25,RED,YELLOW,"????     ??",24,1);
	LCD_ShowNum2412(5+48,25,RED,YELLOW,":32",24,1);

	Show_Str(5,50,YELLOW,YELLOW,"????     ??",24,1);
	LCD_ShowNum2412(5+48,50,YELLOW,YELLOW,":20",24,1);

	Show_Str(5,75,WHITE,YELLOW,"????      ??",24,1);
	LCD_ShowNum2412(5+48,75,WHITE,YELLOW,":3.2",24,1);

	Show_Str(5,100,GREEN,YELLOW,"???��      ??",24,1);
	LCD_ShowNum2412(5+48,100,GREEN,YELLOW,":0.2",24,1);
    Usart1_Init(115200); // ����1���ܳ�ʼ����������9600
    // EXTIX_Init(); // �ⲿ�жϳ�ʼ��
    // Usart2_Init(115200);
    Usart2_IDELInit(9600);
    // beep_init();
    u1_printf("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV");
    Usart_SendArray(USART2, DataString, 4);
    Delay_Ms(500);
    Delay_Ms(500);
    Delay_Ms(500);
    data_analysis();
    // for (size_t i = 0; i < 4; i++)
    // {
    //     /* code */
    //     u2_printf("%x",DataString[i]);
    // }
    LED_Init(); // LED��ʼ��
    finaldata2 = finaldata1;
    u1_printf("finaldata2=%d\r\n",finaldata2);
    //	IIC_Init();                     //��ʼ��IIC�ӿ�
    //	AHT10_Init();                   //��ʼ��AHT10
    //	KEY_Init();                     //������ʼ��
    // Adc_Init();                                                              // ADC��ʼ��
    // OLED_Init();                                                             // OLED��Ļ��ʼ��
    // IoT_Parameter_Init();                                                    // ��ʼ��������IoTƽ̨MQTT�������Ĳ���
    // CAT1_GIPO_Init();                                                        // ��ʼ��4Gģ��Ŀ���IO
    // STMFLASH_Read(0x8010000, &test, 1);                                      // ��ȡFLASH�����У��ֵ
    // adcdata = 2 * (float)(Get_Adc_Average(ADC_Channel_4, 8)) * (3.3 / 4096); // ��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ
    while (1) // ��ѭ��
    {
        // u1_printf("��׼ֵ=%d\r\n",finaldata2);
        // u1_printf("�ο�ֵ=%d\r\n",finaldata1);
        data_analysis();
        if (finaldata2 - finaldata1 > 1000) {
            /* code */
            if (OPEN_flag == 0) {
                OPENDOOR();
                TIM2_ENABLE_1S();     // ������ʱ��2 1s�Ķ�ʱ
                BEEP_OUT(1);
                OPEN_flag++;
            } else {
                u1_printf("����");
                TIM_Cmd(TIM2, DISABLE);
                TIM2_ENABLE_1S();
                SystemTimer = 0;
                if (OPEN_flag > 100) {
                    OPEN_flag = 1;
                }
            }
        }
        CLOSEDOOR();
        // CLOSE_OUT(1);
        // OPEN_OUT(1);
        // Delay_Ms(200);
        // CLOSE_OUT(0);
        // OPEN_OUT(0);

        //     Data_State(); // ��ʱ�ϴ��������ݵ�����
        //     IWDG_Feed();  // ι��
        // }
        /*--------------------------------------------------------------------*/
        /*         Connect_flag=0ͬ�������Ͽ�������,����Ҫ���ӷ�����          */
        /*--------------------------------------------------------------------*/
        // else {
        //     u1_printf("׼�����ӷ�����\r\n"); // ���������Ϣ
        //     Usart2_Init(38400);             // ����3���ܳ�ʼ����������115200
        //     TIM_Cmd(TIM3, DISABLE);          // �ر�TIM3
        //     TIM_Cmd(TIM2, DISABLE);          // �ر�TIM2
        //     CAT1_RxCounter = 0;              // ������������������
        //     u1_printf("��ʼ�����\r\n");
        //     memset(CAT1_RX_BUF, 0, CAT1_RXBUFF_SIZE);     // ��ս��ջ�����
        //     if (CAT1_Connect_IoTServer(30) == 0) {        // ��������Ʒ�������������0����ʾ��ȷ������if
        //         u1_printf("���ӷ������ɹ�\r\n");          // ���������Ϣ
        //         Usart2_IDELInit(115200);                  // ����3 ����DMA �� �����ж�
        //         Connect_flag   = 1;                       // Connect_flag��1����ʾ���ӳɹ�
        //         SystemTimer    = 0;                       // ȫ�ּ�ʱʱ�������0
        //         TEHUTimer      = 0;                       // ��ʪ�ȼ�ʱʱ�������0
        //         ADCTimer       = 0;                       // ADC��ʱʱ�������0
        //         CAT1_RxCounter = 0;                       // ������������������
        //         memset(CAT1_RX_BUF, 0, CAT1_RXBUFF_SIZE); // ��ս��ջ�����
        //         MQTT_Buff_Init();                         // ��ʼ�����ͽ����������
        //         TIM3_ENABLE_30S();                        // ������ʱ��3 30s��PING���ʱ��
        //         TIM2_ENABLE_1S();                         // ������ʱ��2 1s�Ķ�ʱ
        //     }
        // }
    }
}
void data_analysis(void)
{
    if (MQTT_RxDataOutPtr != MQTT_RxDataInPtr) { // if�����Ļ���˵�����ջ�������������
        if (MQTT_RxDataOutPtr[2] == 0x80) {
            // for (size_t i = 2; i < 13; i++) {
            //     /* code */
            //     u1_printf("0x%x ", MQTT_RxDataOutPtr[i]);
            // }
            fina_data1[0] = MQTT_RxDataOutPtr[6]; // ʮλ��
            fina_data1[1] = MQTT_RxDataOutPtr[7]; // ��λ��
            // data[6]��С����.
            fina_data1[2] = MQTT_RxDataOutPtr[9];  // С�����һλ
            fina_data1[3] = MQTT_RxDataOutPtr[10]; // С�������λ
            fina_data1[4] = MQTT_RxDataOutPtr[11]; // С�������λ

            sscanf(fina_data1, "%d", &finaldata1); // �ַ���תint

            u1_printf("%dmm\r\n", finaldata1); // print�ô���2������1�����ͼ���ģ��ͨѶ
            memset(fina_data1, 0, 5);
        }
        MQTT_RxDataOutPtr += RBUFF_UNIT;            // ����ָ������
        IWDG_Feed();
        if (MQTT_RxDataOutPtr == MQTT_RxDataEndPtr) // �������ָ�뵽���ջ�����β����
            MQTT_RxDataOutPtr = MQTT_RxDataBuf[0];  // ����ָ���λ�����ջ�������ͷ
    }
}
void OPENDOOR(void)
{
    OPEN_OUT(0);
    Delay_Ms(200);
    OPEN_OUT(1);
}
void CLOSEDOOR(void)
{
    if (SystemTimer == 30) {
        /* code */
        TIM_Cmd(TIM2, DISABLE);
        TEHUTimer = SystemTimer;
        OPEN_flag = 0;
        CLOSE_OUT(0);
        Delay_Ms(200);
        CLOSE_OUT(1);
        BEEP_OUT(0);
        SystemTimer  = 0;
        
    }
}
