#include "usart.h"
#include "stdio.h"


// data = 3;

struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
int _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����   printf ��һ����
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
	
	//1.��ʱ��  USART1  GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);	
	
 
   //2.����GPIO + ��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TX  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������   //һ�������ж�����ܣ�ʹ������Ĺ���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //RX  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	//3.����USART1 + ��ʼ��
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);

	
	//4.����NVIC + ��ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	//5.ʹ�ܴ����ж�
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	//6.�򿪴���
	USART_Cmd(USART1, ENABLE);  

}



void USART2_init(u32 baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//1.ʹ��GPIO���衢IO����ʱ�ӡ�USART1ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//2.����GPIO + ��ʼ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //  PA2   TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //  PA3   RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������   PA10  RX
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	//3.����USART1 + ��ʼ��USART1
	USART_InitStructure.USART_BaudRate = baud;//�������Զ���
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����ż����
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure);
	
	//4.����NVIC + ��ʼ��NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//5.ʹ�ܴ����ж�
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//���յ����ݴ����ж�
	
	//6.ʹ�ܴ���
	USART_Cmd(USART2,ENABLE);


}




void USART1_IRQHandler(void)//�����ж�1���жϷ�����
{
	
	if ( USART_GetITStatus(USART1,USART_IT_RXNE) != RESET )//�ж��ж��Ƿ���
	{
		//ִ����Ҫִ�еĹ���
		
		data = USART_ReceiveData(USART1);
		
		USART_SendData(USART1,data);
		
		while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //ֱ��������ϣ����˳�while();
		
		//����жϱ�־
		USART_ClearITPendingBit(USART1,USART_IT_RXNE); //�����0
	
	
	}

}


//void USART2_IRQHandler(void)
//{
//	u8 n;
//	if( USART_GetITStatus(USART2,USART_IT_RXNE) == SET )//������յ�����
//	{
//		n = USART_ReceiveData(USART2);//���մ�USART2���͹������ж�
//		data =n;
//		printf("%d",data);
//

//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//	}
//}
void USART2_IRQHandler(void)
{
	
	if( USART_GetITStatus(USART2,USART_IT_RXNE) == SET )//������յ�����
	{
		data = USART_ReceiveData(USART2);
		USART_SendData(USART2,data);
		printf("%d",data);
		while( USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}

