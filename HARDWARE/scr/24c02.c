/*-------------------------------------------------*/
/*            超纬电子STM32系列开发板              */
/*-------------------------------------------------*/
/*                                                 */
/*             实现24c02功能的源文件               */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f10x.h"  //包含需要的头文件
#include "24c02.h"      //包含需要的头文件
#include "delay.h" 	    //包含需要的头文件			 
#include "iic.h"        //包含需要的头文件
#include "led.h"        //包含需要的头文件

/*-------------------------------------------------*/
/*函数名：从24c02指定的地址读一字节数据            */
/*参  数：ReadAddr:需要读数据的地址                */
/*返回值：读到的数据                               */
/*-------------------------------------------------*/
unsigned char AT24C02_ReadOneByte(unsigned char ReadAddr)
{				  
	unsigned char receive;         //定义一个变量用于保存接收到的数据
		
	receive = 0;                   //清除receive，准备接收数据
	IIC_Start();                   //IIC开始信号
	IIC_Send_Byte(AT24C02_WADDR);  //发送24c02器件地址+写操作	   	
	IIC_Wait_Ack();                //等待应答
    IIC_Send_Byte(ReadAddr);       //发送需要读数据的地址 
	IIC_Wait_Ack();	               //等待应答 
	IIC_Start();  	 	           //IIC开始信号
	IIC_Send_Byte(AT24C02_RADDR);  //发送24c02器件地址+读操作				   
	IIC_Wait_Ack();	               //等待应答
    receive=IIC_Read_Byte(0);	   //读一字节数据，保存在receive变量中   
    IIC_Stop();                    //停止信号
	Delay_Ms(5);                   //延迟
	return receive;                //返回读取的数据
}

/*-------------------------------------------------*/
/*函数名：指定地址写入一个数据                     */
/*参  数：WriteAddr  :写入数据的目的地址           */
/*参  数：DataToWrite:要写入的数据                 */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AT24C02_WriteOneByte(unsigned char WriteAddr,unsigned char DataToWrite)
{				   	  	    																 
    IIC_Start();                    //开始信号
	IIC_Send_Byte(AT24C02_WADDR);   //发送器件地址+写操作	 
	IIC_Wait_Ack();	                //等待应答
    IIC_Send_Byte(WriteAddr);       //发送写入数据的目的地址
	IIC_Wait_Ack(); 	 	        //等待应答									  		   
	IIC_Send_Byte(DataToWrite);     //发送要写入的数据							   
	IIC_Wait_Ack();  		        //等待应答	   
    IIC_Stop();                     //停止信号  
	Delay_Ms(5);                    //延迟
}

/*-------------------------------------------------*/
/*函数名：指定地址写入一页数据（8字节）            */
/*参  数：WriteAddr  :写入数据的起始地址           */
/*参  数：DataToWrite:要写入的数据（8个字节）      */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AT24C02_WritePage(unsigned char WriteAddr,unsigned char *DataToWrite)
{				   	  	    																 
	unsigned char i;                   //定义一个变量用于for循环   
 
	IIC_Start();                       //开始信号
	IIC_Send_Byte(AT24C02_WADDR);      //发送器件地址+写操作	 
	IIC_Wait_Ack();	                   //等待应答
    IIC_Send_Byte(WriteAddr);          //发送写入数据的目的地址
	IIC_Wait_Ack(); 	 	           //等待应答	
			Delay_Us(20);
	for(i=0;i<8;i++){                  //24c02一页8个字节，循环写入
		IIC_Send_Byte(DataToWrite[i]); //发送要写入的数据							   
		IIC_Wait_Ack();  		       //等待应答

	}	
    IIC_Stop();                        //停止信号 
	Delay_Ms(5);                       //延迟	
}
/*-------------------------------------------------*/
/*函数名：从指定的地址读一页数据(8字节)            */
/*参  数：ReadAddr:需要读数据的地址                */
/*参  数：Redata:保存接收到的数据                  */
/*返回值：读到的数据                               */
/*-------------------------------------------------*/
void AT24C02_ReadPage(unsigned char ReadAddr, unsigned char *Redata)
{				  		
	unsigned char i;               //定义一个变量用于for循环   
	
	IIC_Start();                   //IIC开始信号
	IIC_Send_Byte(AT24C02_WADDR);  //发送器件地址+写操作	   	
	IIC_Wait_Ack();                //等待应答
    IIC_Send_Byte(ReadAddr);       //发送需要读数据的地址 
	IIC_Wait_Ack();	               //等待应答 
	IIC_Start();  	 	           //IIC开始信号
	IIC_Send_Byte(AT24C02_RADDR);  //发送器件地址+读操作				   
	IIC_Wait_Ack();	               //等待应答
	for(i=0;i<7;i++){              //24c02一页8个字节，循环读取前7个字节	
		Redata[i]=IIC_Read_Byte(1);//读一字节数据，发送ACK信号 
    }	
	Redata[7]=IIC_Read_Byte(0);    //读最后一字节数据，不发送ACK信号 
    IIC_Stop();                    //停止信号
	Delay_Ms(5);                   //延迟
}
/*-------------------------------------------------*/
/*函数名：保存开关LED的状态                        */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AT24C02_SaveLEDSta(void)
{
	char sta;                                    //定义1个变量保存4个led的状态
	
	sta = 0;
	if(!LED1_IN_STA) sta |= 0x01;                //如果是低电平，是打开状态，进入if，sta变量位0置位
	if(!LED2_IN_STA) sta |= 0x02;                //如果是低电平，是打开状态，进入if，sta变量位1置位
	if(!LED3_IN_STA) sta |= 0x04;                //如果是低电平，是打开状态，进入if，sta变量位2置位
	if(!LED4_IN_STA) sta |= 0x08;                //如果是低电平，是打开状态，进入if，sta变量位3置位
	
	AT24C02_WriteOneByte(0,0x55);                //24C02 地址0 写入0x55
	AT24C02_WriteOneByte(1,sta);                 //24C02 地址1 写入4个led的状态
}
/*-------------------------------------------------*/
/*函数名：回复开关LED的状态                        */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AT24C02_ResumeLEDSta(void)
{
	char key,sta;
	
	key = AT24C02_ReadOneByte(0);       //24C02 地址0 读出数据
	if(key == 0x55){                    //如果24C02地址0 读出的是0x55，进入if
		sta = AT24C02_ReadOneByte(1);   //24C02 地址1 读出4个led的状态		
		if(sta&0x01) LED1_ON;           //如果sta变量位0置位，打开LED1
		if(sta&0x02) LED2_ON;           //如果sta变量位1置位，打开LED2
		if(sta&0x04) LED3_ON;           //如果sta变量位2置位，打开LED3
		// if(sta&0x08) LED4_ON;           //如果sta变量位3置位，打开LED4
	}else{                              //反之24C02地址0 读出的不是0x55，进入else
		Delay_Ms(500);                  //延迟
		NVIC_SystemReset();	            //重启
	}
}







