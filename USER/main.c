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

extern int finaldata1;
extern int finaldata2;
extern char fina_data1[5];
unsigned int x;
unsigned int SystemTimer = 0;               // 用于全局计时的变量           单位秒
unsigned int TEHUTimer   = 0;               // 用于温湿度采集的计时的变量   单位秒
unsigned int ADCTimer    = 0;               // 用于ADC采集的计时的变量      单位秒
u8 DataString[3]         = {'i', 'S', 'M'}; // 串口查询命令
u8 TX_flag               = 0;               // 发送标志位置零
float MAX = 0.0, TEMP = 0.0, DIST = 0.0;
float Disce[150] = {0};
float LUNA       = 0;
float tempdata; // 用于保存传感器表面温度值，传感器表面温度值高于气温20度
extern int ampdata;
float adcdata; // 用于保存3个ADC通道的数据



int main(void)
{
    int i; // 用于for循环

    IWDG_Init(6, 625); // 独立看门狗 时间4s
    Delay_Init();      // 延时功能初始化
    Usart1_Init(115200); // 串口1功能初始化，波特率9600
    u1_printf("第一步");
    // EXTIX_Init(); // 外部中断初始化
    Usart2_Init(38400);
    Usart2_IDELInit(38400);
    // beep_init();
    u2_printf("iSM");
    // LED_Init(); // LED初始化
    //	IIC_Init();                     //初始化IIC接口
    //	AHT10_Init();                   //初始化AHT10
    //	KEY_Init();                     //按键初始化
    // Adc_Init();                                                              // ADC初始化
    // OLED_Init();                                                             // OLED屏幕初始化
    // IoT_Parameter_Init();                                                    // 初始化连接云IoT平台MQTT服务器的参数
    // CAT1_GIPO_Init();                                                        // 初始化4G模块的控制IO
    // STMFLASH_Read(0x8010000, &test, 1);                                      // 读取FLASH储存的校验值
    // adcdata = 2 * (float)(Get_Adc_Average(ADC_Channel_4, 8)) * (3.3 / 4096); // 获取计算后的带小数的实际电压值
    while (1)                                                                // 主循环
    {

        
        // if (Connect_flag == 1) {
        //     /*-------------------------------------------------------------*/
        //     /*                     处理发送缓冲区数据                      */
        //     /*-------------------------------------------------------------*/
        //     if (MQTT_TxDataOutPtr != MQTT_TxDataInPtr) { // if成立的话，说明发送缓冲区有数据了
        //         // 3种情况可进入if
        //         // 第1种：0x10 连接报文
        //         // 第2种：0x82 订阅报文，且ConnectPack_flag置位，表示连接报文成功
        //         // 第3种：SubcribePack_flag置位，说明连接和订阅均成功，其他报文可发
        //         if ((DMA_flag == 0) && ((MQTT_TxDataOutPtr[2] == 0x10) || ((MQTT_TxDataOutPtr[2] == 0x82) && (ConnectPack_flag == 1)) || (SubcribePack_flag == S_TOPIC_NUM))) {
        //             u1_printf("发送数据:0x%x\r\n", MQTT_TxDataOutPtr[2]); // 串口提示信息
        //             MQTT_TxData(MQTT_TxDataOutPtr);                       // 发送数据
        //             MQTT_TxDataOutPtr += TBUFF_UNIT;                      // 指针下移
        //             if (MQTT_TxDataOutPtr == MQTT_TxDataEndPtr)           // 如果指针到缓冲区尾部了
        //                 MQTT_TxDataOutPtr = MQTT_TxDataBuf[0];            // 指针归位到缓冲区开头
        //         }
        //     } // 处理发送缓冲区数据的else if分支结尾
        //     /*-------------------------------------------------------------*/
        //     /*                     处理接收缓冲区数据                      */
        //     /*-------------------------------------------------------------*/
        //     if (MQTT_RxDataOutPtr != MQTT_RxDataInPtr) { // if成立的话，说明接收缓冲区有数据了
        //         u1_printf("接收到数据:");                // 串口提示信息
        //         /*-----------------------------------------------------*/
        //         /*                    处理CONNACK报文                  */
        //         /*-----------------------------------------------------*/
        //         // if判断，如果第一个字节是0x20，表示收到的是CONNACK报文
        //         // 接着我们要判断第4个字节，看看CONNECT报文是否成功
        //         if (MQTT_RxDataOutPtr[2] == 0x20) {
        //             switch (MQTT_RxDataOutPtr[5]) {
        //                 case 0x00:
        //                     u1_printf("CONNECT报文成功\r\n"); // 串口输出信息
        //                     ConnectPack_flag = 1;             // CONNECT报文成功
        //                     beep_on_500ms();
        //                     break; // 跳出分支case 0x00
        //                 case 0x01:
        //                     u1_printf("连接已拒绝，不支持的协议版本，准备重启\r\n"); // 串口输出信息
        //                     Connect_flag = 0;                                        // Connect_flag置零，重启连接
        //                     break;                                                   // 跳出分支case 0x01
        //                 case 0x02:
        //                     u1_printf("连接已拒绝，不合格的客户端标识符，准备重启\r\n"); // 串口输出信息
        //                     Connect_flag = 0;                                            // Connect_flag置零，重启连接
        //                     break;                                                       // 跳出分支case 0x02
        //                 case 0x03:
        //                     u1_printf("连接已拒绝，服务端不可用，准备重启\r\n"); // 串口输出信息
        //                     Connect_flag = 0;                                    // Connect_flag置零，重启连接
        //                     break;                                               // 跳出分支case 0x03
        //                 case 0x04:
        //                     u1_printf("连接已拒绝，无效的用户名或密码，准备重启\r\n"); // 串口输出信息
        //                     Connect_flag = 0;                                          // Connect_flag置零，重启连接
        //                     break;                                                     // 跳出分支case 0x04
        //                 case 0x05:
        //                     u1_printf("连接已拒绝，未授权，准备重启\r\n"); // 串口输出信息
        //                     Connect_flag = 0;                              // Connect_flag置零，重启连接
        //                     break;                                         // 跳出分支case 0x05
        //                 default:
        //                     u1_printf("连接已拒绝，未知状态，准备重启\r\n"); // 串口输出信息
        //                     Connect_flag = 0;                                // Connect_flag置零，重启连接
        //                     break;                                           // 跳出分支case default
        //             }
        //         }
        //         /*-----------------------------------------------------*/
        //         /*                    处理SUBACK报文                   */
        //         /*-----------------------------------------------------*/
        //         // if判断，第一个字节是0x90，表示收到的是SUBACK报文
        //         // 接着我们要判断订阅回复，看看是不是成功
        //         else if (MQTT_RxDataOutPtr[2] == 0x90) {
        //             for (i = 0; i < S_TOPIC_NUM; i++) { // 循环查询订阅结果
        //                 switch (MQTT_RxDataOutPtr[6 + i]) {
        //                     case 0x00:
        //                     case 0x01:
        //                         u1_printf("订阅成功%d ", i + 1); // 串口输出信息
        //                         SubcribePack_flag++;             // SubcribePack_flag++
        //                         break;                           // 跳出分支
        //                     default:
        //                         u1_printf("订阅失败，准备重启\r\n"); // 串口输出信息
        //                         Connect_flag = 0;                    // Connect_flag置零，重启连接
        //                         break;                               // 跳出分支
        //                 }
        //             }
        //             u1_printf("\r\n"); // 串口输出信息
        //         }
        //         /*-----------------------------------------------------*/
        //         /*                  处理PINGRESP报文                   */
        //         /*-----------------------------------------------------*/
        //         // if判断，第一个字节是0xD0，表示收到的是PINGRESP报文
        //         else if (MQTT_RxDataOutPtr[2] == 0xD0) {
        //             u1_printf("PING报文回复\r\n"); // 串口输出信息
        //             if (Ping_flag == 1) {          // 如果Ping_flag=1，表示第一次发送
        //                 Ping_flag = 0;             // 要清除Ping_flag标志
        //             } else if (Ping_flag > 1) {    // 如果Ping_flag>1，表示是多次发送了，而且是2s间隔的快速发送
        //                 Ping_flag = 0;             // 要清除Ping_flag标志
        //                 TIM3_ENABLE_30S();         // PING定时器重回30s的时间
        //             }
        //         }
        //         /*-----------------------------------------------------*/
        //         /*                  处理数据推送报文                   */
        //         /*-----------------------------------------------------*/
        //         // if判断，如果第一个字节是0x30，表示收到的是服务器发来的推送数据
        //         // 我们要提取控制命令
        //         else if (MQTT_RxDataOutPtr[2] == 0x30) {
        //             u1_printf("服务器等级0推送\r\n");         // 串口输出信息
        //             MQTT_DealPushdata_Qs0(MQTT_RxDataOutPtr); // 处理等级0推送数据
        //         }
        //         MQTT_RxDataOutPtr += RBUFF_UNIT;            // 接收指针下移
        //         if (MQTT_RxDataOutPtr == MQTT_RxDataEndPtr) // 如果接收指针到接收缓冲区尾部了
        //             MQTT_RxDataOutPtr = MQTT_RxDataBuf[0];  // 接收指针归位到接收缓冲区开头
        //     }

        //     /*-------------------------------------------------------------*/
        //     /*                     处理命令缓冲区数据                      */
        //     /*-------------------------------------------------------------*/
        //     if (MQTT_CMDOutPtr != MQTT_CMDInPtr) {            // if成立的话，说明命令缓冲区有数据了
        //         u1_printf("命令:%s\r\n", &MQTT_CMDOutPtr[2]); // 串口输出信息
        //         Dynamic_check_value = (getvalu(&MQTT_CMDOutPtr[2])) * 10.0;
        //         u1_printf("%f\r\n", Dynamic_check_value);
        //         STMFLASH_Write(0x8010000, &Dynamic_check_value, 1);
        //         GPIO_ResetBits(GPIOA, GPIO_Pin_7);
        //         Delay_Ms(50);
        //         GPIO_SetBits(GPIOA, GPIO_Pin_7);
        //         Delay_Ms(50);
        //         /*-------------------------------------------------------------------*/
        //         /*--如果搜索到"\"params\":{\"valu\":100}说明服务器下发增大校验值1mm--*/
        //         /*-------------------------------------------------------------------*/
        //         if (strstr((char *)MQTT_CMDOutPtr + 2, "\"params\":{\"valu\":100}")) {
        //             GPIO_ResetBits(GPIOA, GPIO_Pin_6);
        //             Delay_Ms(50);
        //             GPIO_SetBits(GPIOA, GPIO_Pin_6);
        //             Delay_Ms(50);
        //         }
        //         /*-------------------------------------------------------------------*/
        //         /*--如果搜索到"\"params\":{\"valu\":99}说明服务器下发减小校验值1mm---*/
        //         /*-------------------------------------------------------------------*/
        //         else if (strstr((char *)MQTT_CMDOutPtr + 2, "\"params\":{\"valu\":99}")) {
        //             GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        //             Delay_Ms(50);
        //             GPIO_SetBits(GPIOA, GPIO_Pin_5);
        //             Delay_Ms(50);
        //         }
        //         MQTT_CMDOutPtr += CBUFF_UNIT;         // 指针下移
        //         if (MQTT_CMDOutPtr == MQTT_CMDEndPtr) // 如果指针到缓冲区尾部了
        //             MQTT_CMDOutPtr = MQTT_CMDBuf[0];  // 指针归位到缓冲区开头
        //     }                                         // 处理命令缓冲区数据的else if分支结尾

        //     /*-------------------------------------------------------------*/
        //     /*                     处理定时上传任务                        */
        //     /*-------------------------------------------------------------*/
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
/*-------------------------------------------------*/
/*函数名：判断开关1状态，并发布给服务器            */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED1_State(void)
{
    char temp[TBUFF_UNIT]; // 定义一个临时缓冲区

    memset(temp, 0, TBUFF_UNIT);
    if (LED1_IN_STA)
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"SwitchSta1\":0,\"Switch1\":0},\"version\":\"1.0.0\"}"); // 如果LED1是高电平，说明是熄灭状态，需要回复关闭状态给服务器
    else
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"SwitchSta1\":1,\"Switch1\":1},\"version\":\"1.0.0\"}"); // 如果LED1是低电平，说明是点亮状态，需要回复打开状态给服务器
    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                                                                                                      // 添加数据，发布给服务器
}
/*-------------------------------------------------*/
/*函数名：判断开关2状态，并发布给服务器            */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED2_State(void)
{
    char temp[TBUFF_UNIT]; // 定义一个临时缓冲区

    memset(temp, 0, TBUFF_UNIT);
    if (LED2_IN_STA)
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"SwitchSta2\":0,\"Switch2\":0},\"version\":\"1.0.0\"}"); // 如果LED2是高电平，说明是熄灭状态，需要回复关闭状态给服务器
    else
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"SwitchSta2\":1,\"Switch2\":1},\"version\":\"1.0.0\"}"); // 如果LED2是低电平，说明是点亮状态，需要回复打开状态给服务器
    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                                                                                                      // 添加数据，发布给服务器
}
/*-------------------------------------------------*/
/*函数名：判断开关3状态，并发布给服务器            */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED3_State(void)
{
    char temp[TBUFF_UNIT]; // 定义一个临时缓冲区

    memset(temp, 0, TBUFF_UNIT);
    if (LED3_IN_STA)
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"SwitchSta3\":0,\"Switch3\":0},\"version\":\"1.0.0\"}"); // 如果LED3是高电平，说明是熄灭状态，需要回复关闭状态给服务器
    else
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"SwitchSta3\":1,\"Switch3\":1},\"version\":\"1.0.0\"}"); // 如果LED3是低电平，说明是点亮状态，需要回复打开状态给服务器
    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                                                                                                      // 添加数据，发布给服务器
}
/*-------------------------------------------------*/
/*函数名：判断开关4状态，并发布给服务器            */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED4_State(void)
{
    char temp[TBUFF_UNIT]; // 定义一个临时缓冲区

    memset(temp, 0, TBUFF_UNIT);
    if (LED4_IN_STA)
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"SwitchSta4\":0,\"Switch4\":0},\"version\":\"1.0.0\"}"); // 如果LED4是高电平，说明是熄灭状态，需要回复关闭状态给服务器
    else
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"SwitchSta4\":1,\"Switch4\":1},\"version\":\"1.0.0\"}"); // 如果LED4是低电平，说明是点亮状态，需要回复打开状态给服务器
    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                                                                                                      // 添加数据，发布给服务器
}
/*-------------------------------------------------*/
/*函数名：判断4个开关状态，并发布给服务器          */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED_State(void)
{
    char temp[TBUFF_UNIT];       // 定义一个临时缓冲区
    char sta1, sta2, sta3, sta4; // 定义4个变量保存各个led的状态

    if (LED1_IN_STA)
        sta1 = 0; // 如果是高电平，是关闭状态，状态值=0
    else
        sta1 = 1; // 如果是低电平，是打开状态，状态值=1
    if (LED2_IN_STA)
        sta2 = 0; // 如果是高电平，是关闭状态，状态值=0
    else
        sta2 = 1; // 如果是低电平，是打开状态，状态值=1
    if (LED3_IN_STA)
        sta3 = 0; // 如果是高电平，是关闭状态，状态值=0
    else
        sta3 = 1; // 如果是低电平，是打开状态，状态值=1
    if (LED4_IN_STA)
        sta4 = 0; // 如果是高电平，是关闭状态，状态值=0
    else
        sta4 = 1; // 如果是低电平，是打开状态，状态值=1

    memset(temp, 0, TBUFF_UNIT);
    sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"SwitchSta1\":%d,\"SwitchSta2\":%d,\"SwitchSta3\":%d,\"SwitchSta4\":%d,\"Switch1\":%d,\"Switch2\":%d,\"Switch3\":%d,\"Switch4\":%d},\"version\":\"1.0.0\"}", sta1, sta2, sta3, sta4, sta1, sta2, sta3, sta4); // 需要回复状态给服务器

    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp)); // 添加数据，发布给服务器
}
/*-------------------------------------------------*/
/*函数名：定时上传各种数据的任务                   */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void Data_State(void)
{
    int u = 0;
    char temp[256];                        // 报文有效负载缓冲区
    if ((SystemTimer - TEHUTimer) >= 19) { // 全局时间 和 温湿度计时时间至少差25s，进入if
        TEHUTimer = SystemTimer;           // 把当前的全局时间，记录到温湿度计时变量	                           //读取温湿度值
        while (u == 0) {
            Usart_SendArray(USART3, (unsigned char *)"iSM", 3);
            Delay_Ms(1000);

            result = finaldata1*1.0 / 10;

            ampdata = finaldata2;
            DIST    = result;
            u1_printf("距离值：%.2f\r\n", DIST);
            tempdata = dis_status;
            u1_printf("温度值：%.2f\r\n", tempdata);
            // ampdata = Signal_Strength;
            u1_printf("反射强度：%d\r\n", ampdata);
            u += 1;
            if (ampdata < 0 || ampdata == 65535 || DIST > 550.00 || tempdata == 255 || DIST <= 0) {
                u1_printf("错误\r\n");
                u = 0;
            }
        }
        if (TX_flag == 0) {
            memset(temp, 0, 256);                                                                                                                                                                                    // 清空缓冲区
            u1_printf("液位高：%.2f\r\n", Dynamic_check_value * Step_size * 1.0 - DIST);                                                                                                                             // 串口输出数据
            sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Distance\":%.2f,\"amp\":%d},\"version\":\"1.0.0\"}", Dynamic_check_value * Step_size * 1.0 - DIST, ampdata); // 构建数据
            MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                                                                                                                                                       // 添加数据到发送缓冲区
        }
        if (TX_flag == 1) {
            memset(temp, 0, 256);                                                                                                                                                                                      // 清空缓冲区
            u1_printf("液位高1：%.2f\r\n", Dynamic_check_value * Step_size * 1.0 - DIST);                                                                                                                              // 串口输出数据
            sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Distance1\":%3.2f,\"amp\":%d},\"version\":\"1.0.0\"}", Dynamic_check_value * Step_size * 1.0 - DIST, ampdata); // 构建数据
            MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                                                                                                                                                         // 添加数据到发送缓冲区
        }
        if (TX_flag == 2) {
            memset(temp, 0, 256);                                                                                                                                                                                      // 清空缓冲区
            u1_printf("液位高2：%.2f\r\n", Dynamic_check_value * Step_size * 1.0 - DIST);                                                                                                                              // 串口输出数据
            sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Distance2\":%3.2f,\"amp\":%d},\"version\":\"1.0.0\"}", Dynamic_check_value * Step_size * 1.0 - DIST, ampdata); // 构建数据
            MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                                                                                                                                                         // 添加数据到发送缓冲区
        }
        TX_flag++;
        if (TX_flag == 3) {
            TX_flag = 0;
        }
        if (!flag) {
            OLED_SHOW();
        }
    }

    if ((SystemTimer - ADCTimer) >= 39) {                                        // 全局时间 和 温湿度计时时间至少差65s，进入if
        ADCTimer = SystemTimer;                                                  // 把当前的全局时间，记录到温湿度计时变量
        memset(temp, 0, 256);                                                    // 清空缓冲区
        adcdata = 2 * (float)(Get_Adc_Average(ADC_Channel_4, 8)) * (3.3 / 4096); // 获取计算后的带小数的实际电压值
        u1_printf("valu：%.2f\r\n", Dynamic_check_value * Step_size * 1.0);      // 串口输出数据
        u1_printf("ADC：%.2f\r\n", adcdata);
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"valu\":%3.2f,\"temp\":%.2f,\"electricity\":%.2f},\"version\":\"1.0.0\"}", Dynamic_check_value * Step_size * 1.0, tempdata, adcdata); // 构建数据
        MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                                                                                                                                                                               // 添加数据到发送缓冲区
    }
}
