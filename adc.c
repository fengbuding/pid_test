/** @date			2013/8/28
    @author			Mei Jilin
	@brief		    ADC1���������3ͨ�������ݲɼ�
    @attention
       1 ----------- adc_config();                     //����adc
       2 ----------- adc_start();                      //����adc,��ʼת��
       3 ----------- get_ChannelValue(ADC_Channel_x);  //��ȡ��Ӧͨ����adcֵ
**/
#include "stm32f10x.h"
#include "adc.h"
uint16_t ad_value[N][CH_NUM]={0};
const float arr_per[8] = {0.125, 0.83333, 0.5, 0.45455, 0.45455, 0.3, 1, 0.3};
/** @para none
  * @ret  none
  * @brief adc��Ӧ��gpio��ʼ��
  */
void adc_gpio_init(void)
{
    GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE);
    gpio.GPIO_Mode = GPIO_Mode_AIN;                         //����Ϊģ������
    gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;   //ADC1 --channel0,1,2
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&gpio); 
    gpio.GPIO_Mode = GPIO_Mode_AIN;                         //����Ϊģ������
    gpio.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&gpio); 
}
/** @para none
  * @ret  none
  * @brief adc����
  */
void adc_init(void)
{
    ADC_InitTypeDef adc;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                       //����adʱ��Ϊ72/6=12M,ad���ʱ��Ƶ��Ϊ14M
    
    ADC_DeInit(ADC1);
    adc.ADC_Mode                = ADC_Mode_Independent;     //�����ڶ���ģʽ
    adc.ADC_ContinuousConvMode  = ENABLE;                   //����ת��ģʽ
    adc.ADC_DataAlign           = ADC_DataAlign_Right;      //�����Ҷ���
    adc.ADC_ExternalTrigConv    = ADC_ExternalTrigConv_None;//��ʹ���ⲿ����
    adc.ADC_NbrOfChannel        = CH_NUM ;                       //ת��3��ͨ��
    adc.ADC_ScanConvMode        = ENABLE;                   //����ת��ģʽ
    ADC_Init(ADC1,&adc);
    //�趨ָ����ADCͨ����,����ת��˳��Ͳ���ʱ��
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 3, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 4, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 5, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 6, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 7, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 8, ADC_SampleTime_55Cycles5);
    //����adc��DMA
    ADC_DMACmd(ADC1,ENABLE);
    //ʹ��ADC1
    ADC_Cmd(ADC1, ENABLE);
    /* Enable ADC1 reset calibaration register */   
    ADC_ResetCalibration(ADC1);	  //����У׼
    /* Check the end of ADC1 reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC1));  //�ȴ�����У׼���
    /* Start ADC1 calibaration */
    ADC_StartCalibration(ADC1);		//��ʼУ׼
    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1));	   //�ȴ�У׼���

}
/** @para none
  * @ret  none
  * @brief ����dma
  */
void adc_dma_init()
{
    DMA_InitTypeDef dma;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    DMA_DeInit(DMA1_Channel1);
    dma.DMA_PeripheralBaseAddr  = (u32)&(ADC1->DR);     //DMA��Ӧ���������ַ
    dma.DMA_MemoryBaseAddr      = (u32)&ad_value;       //�ڴ�洢����ַ
    dma.DMA_DIR                 = DMA_DIR_PeripheralSRC;//DMA��ת��ģʽΪSRCģʽ����������Ƶ��ڴ�
    dma.DMA_M2M                 = DMA_M2M_Disable;      //M2Mģʽ����
    dma.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_HalfWord;//�����������ݿ��Ϊ16λ
    dma.DMA_MemoryDataSize      = DMA_MemoryDataSize_HalfWord;  //DMA�������ݳߴ磬HalfWord����Ϊ16λ    
    dma.DMA_BufferSize          = CH_NUM * N;                       //DMA�����СCH_NUM��
    dma.DMA_MemoryInc           = DMA_MemoryInc_Enable;         //����һ�����ݺ�Ŀ���ڴ��ַ����
    dma.DMA_PeripheralInc       = DMA_PeripheralInc_Disable;    //����һ�����ݺ��豸��ַ��ֹ����
    dma.DMA_Mode                = DMA_Mode_Circular;            //ת��ģʽ��ѭ������ģʽ��
    dma.DMA_Priority            = DMA_Priority_High;            //DMA���ȼ���
    DMA_Init(DMA1_Channel1,&dma); 
}
/** @para none
  * @ret  none
  * @brief ���adc����
  */
void adc_config(void)
{
    adc_gpio_init();
    adc_dma_init();
    adc_init();
}
/** @para none
  * @ret  none
  * @brief ����adc,��ʼת��
  */
void adc_start(void)
{
    /* Start ADC1 Software Conversion */ 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//����ת����ʼ��ADCͨ��DMA��ʽ���ϵĸ���RAM���� 
    DMA_Cmd(DMA1_Channel1,ENABLE);    
}

void get_ChannelVale(float arr[])
{
  u32 sum = 0;
  for(u8 i = 0; i < CH_NUM; i++)
  {
    for(u8 j = 0; j < N; j++)
    {
        sum += ad_value[j][i];
    }
    sum /= N;  
    arr[i] = sum;
    arr[i] = arr[i] * 3.3 / 4096;
    arr[i] /= arr_per[i]; 
    sum = 0;
  }
}
