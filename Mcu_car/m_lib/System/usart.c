#include "usart.h"
#include "stdio.h"


// data = 3;

struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
int _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数   printf 是一个宏
//int fputc(int ch, FILE *f)
//{ 	
//	USART_SendData(USART1,ch);
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);      
//	return ch;
//}

int fputc(int ch, FILE *f)
{ 	
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);      
	return ch;
}

u32 data;

void USART1_init(void)
{
	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//1.打开时钟  USART1  GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);	
	
 
   //2.配置GPIO + 初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TX  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出   //一个引脚有多个功能，使用另外的功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //RX  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	//3.配置USART1 + 初始化
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);

	
	//4.配置NVIC + 初始化
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	//5.使能串口中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	//6.打开串口
	USART_Cmd(USART1, ENABLE);  

}



void USART2_init(u32 baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//1.使能GPIO外设、IO复用时钟、USART1时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//2.配置GPIO + 初始化GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //  PA2   TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //  PA3   RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入   PA10  RX
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	//3.配置USART1 + 初始化USART1
	USART_InitStructure.USART_BaudRate = baud;//波特率自定义
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶检验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
	USART_Init(USART2, &USART_InitStructure);
	
	//4.配置NVIC + 初始化NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//5.使能串口中断
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//接收到数据触发中断
	
	//6.使能串口
	USART_Cmd(USART2,ENABLE);


}




void USART1_IRQHandler(void)//串口中断1，中断服务函数
{
	
	if ( USART_GetITStatus(USART1,USART_IT_RXNE) != RESET )//判断中断是否发生
	{
		//执行想要执行的功能
		
		data = USART_ReceiveData(USART1);
		
		USART_SendData(USART1,data);
		
		while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //直到发送完毕，才退出while();
		
		//清除中断标志
		USART_ClearITPendingBit(USART1,USART_IT_RXNE); //软件清0
	
	
	}

}


//void USART2_IRQHandler(void)
//{
//	u8 n;
//	if( USART_GetITStatus(USART2,USART_IT_RXNE) == SET )//如果接收到数据
//	{
//		n = USART_ReceiveData(USART2);//接收从USART2发送过来的中断
//		data =n;
//		printf("%d",data);
//

//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//	}
//}
void USART2_IRQHandler(void)
{
	
	if( USART_GetITStatus(USART2,USART_IT_RXNE) == SET )//如果接收到数据
	{
		data = USART_ReceiveData(USART2);
		USART_SendData(USART2,data);
		printf("%d",data);
		while( USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}

