/*-----------------------------------------------------*/
/*              超纬电子STM32系列开发板                */
/*-----------------------------------------------------*/
/*                     程序结构                        */
/*-----------------------------------------------------*/
/*USER     ：包含程序的main函数，是整个程序的入口      */
/*HARDWARE ：包含开发板各种功能外设的驱动程序          */
/*CORE     ：包含STM32的核心程序，官方提供，我们不修改 */
/*STLIB    ：官方提供的库文件，我们不修改              */
/*-----------------------------------------------------*/
/*                                                     */
/*           程序main函数，入口函数头文件              */
/*                                                     */
/*-----------------------------------------------------*/

#ifndef __MAIN_H
#define __MAIN_H

#include <stdbool.h>


extern unsigned int SystemTimer; // 变量声明


void LED1_State(void); // 函数声明
void LED2_State(void); // 函数声明
void LED3_State(void); // 函数声明
void LED4_State(void); // 函数声明
void LED_State(void);  // 函数声明
void Data_State(void); // 函数声明
void data_analysis(void); // 函数声明
void OPENDOOR(void); // 函数声明
void CLOSEDOOR(void); // 函数声明

#endif
