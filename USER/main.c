/*-----------------------------------------------------*/
/*              超纬电子STM32系列开发板                */
/*-----------------------------------------------------*/
/*                     程序结构                        */
/*-----------------------------------------------------*/
/*USER     ：包含程序的main函数，是整个程序的入口      */
/*HARDWARE ：包含开发板各种功能外设的驱动程序          */
/*CORE     ：包含STM32的核心程序，官方提供，我们不修改 */
/*STLIB    ：官方提供的库文件，我们不修改              */
/*HMAC     ：各种加密算法                              */
/*-----------------------------------------------------*/
/*                                                     */
/*           程序main函数，入口函数源文件              */
/*                                                     */
/*-----------------------------------------------------*/

#include "stm32f10x.h" //包含需要的头文件
#include "main.h"      //包含需要的头文件
#include "delay.h"     //包含需要的头文件
#include "usart1.h"    //包含需要的头文件
#include "usart3.h"    //包含需要的头文件
#include "timer2.h"    //包含需要的头文件
#include "timer3.h"    //包含需要的头文件
#include "timer4.h"    //包含需要的头文件
#include "cat1.h"      //包含需要的头文件
#include "led.h"       //包含需要的头文件
#include "mqtt.h"      //包含需要的头文件
#include "key.h"       //包含需要的头文件
#include "aht10.h"     //包含需要的头文件
#include "iic.h"       //包含需要的头文件
#include "adc.h"       //包含需要的头文件
#include "iwdg.h"      //包含需要的头文件
#include "24c02.h"     //包含需要的头文件
#include "usart9.h"    //包含需要的头文件
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
unsigned int SystemTimer = 0;                        // 用于全局计时的变量           单位秒
unsigned int TEHUTimer   = 0;                        // 用于温湿度采集的计时的变量   单位秒
unsigned int ADCTimer    = 0;                        // 用于ADC采集的计时的变量      单位秒
u8 DataString[8]         = {0x80, 0x06, 0x03, 0x77}; // 串口查询命令
int OPEN_flag             = 0;                        // 发送标志位置零
float MAX = 0.0, TEMP = 0.0, DIST = 0.0;
float Disce[150] = {0};
float LUNA       = 0;
float tempdata; // 用于保存传感器表面温度值，传感器表面温度值高于气温20度
extern int ampdata;
float adcdata; // 用于保存3个ADC通道的数据

int main(void)
{
    // int i; // 用于for循环
    MQTT_Buff_Init();
    IWDG_Init(6, 625); // 独立看门狗 时间4s
    // IWDG_Init(6, 156);   // 独立看门狗 时间4s
    Delay_Init();        // 延时功能初始化
    LCD_Init();	   //???§????????
	LCD_Clear(BLACK); //????

	POINT_COLOR=WHITE; 
	LCD_DrawRectangle(0,0,128-1,128-1);	//?????? 

	Show_Str(32,5,BLUE,YELLOW,"?????à??",16,0);
	Show_Str(5,25,RED,YELLOW,"????     ??",24,1);
	LCD_ShowNum2412(5+48,25,RED,YELLOW,":32",24,1);

	Show_Str(5,50,YELLOW,YELLOW,"????     ??",24,1);
	LCD_ShowNum2412(5+48,50,YELLOW,YELLOW,":20",24,1);

	Show_Str(5,75,WHITE,YELLOW,"????      ??",24,1);
	LCD_ShowNum2412(5+48,75,WHITE,YELLOW,":3.2",24,1);

	Show_Str(5,100,GREEN,YELLOW,"???÷      ??",24,1);
	LCD_ShowNum2412(5+48,100,GREEN,YELLOW,":0.2",24,1);
    Usart1_Init(115200); // 串口1功能初始化，波特率9600
    // EXTIX_Init(); // 外部中断初始化
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
    LED_Init(); // LED初始化
    finaldata2 = finaldata1;
    u1_printf("finaldata2=%d\r\n",finaldata2);
    //	IIC_Init();                     //初始化IIC接口
    //	AHT10_Init();                   //初始化AHT10
    //	KEY_Init();                     //按键初始化
    // Adc_Init();                                                              // ADC初始化
    // OLED_Init();                                                             // OLED屏幕初始化
    // IoT_Parameter_Init();                                                    // 初始化连接云IoT平台MQTT服务器的参数
    // CAT1_GIPO_Init();                                                        // 初始化4G模块的控制IO
    // STMFLASH_Read(0x8010000, &test, 1);                                      // 读取FLASH储存的校验值
    // adcdata = 2 * (float)(Get_Adc_Average(ADC_Channel_4, 8)) * (3.3 / 4096); // 获取计算后的带小数的实际电压值
    while (1) // 主循环
    {
        // u1_printf("标准值=%d\r\n",finaldata2);
        // u1_printf("参考值=%d\r\n",finaldata1);
        data_analysis();
        if (finaldata2 - finaldata1 > 1000) {
            /* code */
            if (OPEN_flag == 0) {
                OPENDOOR();
                TIM2_ENABLE_1S();     // 启动定时器2 1s的定时
                BEEP_OUT(1);
                OPEN_flag++;
            } else {
                u1_printf("有人");
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

        //     Data_State(); // 定时上传各种数据的任务
        //     IWDG_Feed();  // 喂狗
        // }
        /*--------------------------------------------------------------------*/
        /*         Connect_flag=0同服务器断开了连接,我们要连接服务器          */
        /*--------------------------------------------------------------------*/
        // else {
        //     u1_printf("准备连接服务器\r\n"); // 串口输出信息
        //     Usart2_Init(38400);             // 串口3功能初始化，波特率115200
        //     TIM_Cmd(TIM3, DISABLE);          // 关闭TIM3
        //     TIM_Cmd(TIM2, DISABLE);          // 关闭TIM2
        //     CAT1_RxCounter = 0;              // 接收数据量变量清零
        //     u1_printf("初始化完成\r\n");
        //     memset(CAT1_RX_BUF, 0, CAT1_RXBUFF_SIZE);     // 清空接收缓冲区
        //     if (CAT1_Connect_IoTServer(30) == 0) {        // 如果连接云服务器函数返回0，表示正确，进入if
        //         u1_printf("连接服务器成功\r\n");          // 串口输出信息
        //         Usart2_IDELInit(115200);                  // 串口3 开启DMA 和 空闲中断
        //         Connect_flag   = 1;                       // Connect_flag置1，表示连接成功
        //         SystemTimer    = 0;                       // 全局计时时间变量清0
        //         TEHUTimer      = 0;                       // 温湿度计时时间变量清0
        //         ADCTimer       = 0;                       // ADC计时时间变量清0
        //         CAT1_RxCounter = 0;                       // 接收数据量变量清零
        //         memset(CAT1_RX_BUF, 0, CAT1_RXBUFF_SIZE); // 清空接收缓冲区
        //         MQTT_Buff_Init();                         // 初始化发送接收命令缓冲区
        //         TIM3_ENABLE_30S();                        // 启动定时器3 30s的PING保活定时器
        //         TIM2_ENABLE_1S();                         // 启动定时器2 1s的定时
        //     }
        // }
    }
}
void data_analysis(void)
{
    if (MQTT_RxDataOutPtr != MQTT_RxDataInPtr) { // if成立的话，说明接收缓冲区有数据了
        if (MQTT_RxDataOutPtr[2] == 0x80) {
            // for (size_t i = 2; i < 13; i++) {
            //     /* code */
            //     u1_printf("0x%x ", MQTT_RxDataOutPtr[i]);
            // }
            fina_data1[0] = MQTT_RxDataOutPtr[6]; // 十位数
            fina_data1[1] = MQTT_RxDataOutPtr[7]; // 个位数
            // data[6]是小数点.
            fina_data1[2] = MQTT_RxDataOutPtr[9];  // 小数点后一位
            fina_data1[3] = MQTT_RxDataOutPtr[10]; // 小数点后两位
            fina_data1[4] = MQTT_RxDataOutPtr[11]; // 小数点后三位

            sscanf(fina_data1, "%d", &finaldata1); // 字符串转int

            u1_printf("%dmm\r\n", finaldata1); // print用串口2，串口1用来和激光模块通讯
            memset(fina_data1, 0, 5);
        }
        MQTT_RxDataOutPtr += RBUFF_UNIT;            // 接收指针下移
        IWDG_Feed();
        if (MQTT_RxDataOutPtr == MQTT_RxDataEndPtr) // 如果接收指针到接收缓冲区尾部了
            MQTT_RxDataOutPtr = MQTT_RxDataBuf[0];  // 接收指针归位到接收缓冲区开头
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
