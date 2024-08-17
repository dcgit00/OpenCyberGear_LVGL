#include "adc.h"



static uint8_t FLAG_ADC1InitOK = 0;                     // ADC1��ʼ����ǣ�0��δ��ʼ����1���ѳ�ʼ��



static void delay_us(uint32_t us)                       // ����һ��us��ʱ������������ֲʱ���ⲿ�ļ�����;
{
    while (us--)                                        // ע�⣬�������Ǽ�����ʱ���Ǿ�׼��ʱ
        for (uint32_t i = 0; i < 7; i++);               // 72MHzϵͳʱ���£���Լ���ٸ���ѭ����ʱ1us
}



/******************************************************************************
 * ��  ���� configADC1
 * ��  �ܣ� ��ʼ��ADC
 * ��  ����
 * ����ֵ��
 *
 * ��  ע�� 1-ADC�¶�ͨ���Ĳ���ʱ�䣬оƬ�ֲ����Ƽ�Ϊ17.1us, ԶС�ڴ�ֵʱ���ݳ���
 *
 ******************************************************************************/
static void  configADC1(void)
{
    RCC->APB2ENR  |= 1 << 8;           // ADC1ʱ��ʹ��
    RCC->APB2RSTR |= 1 << 8;           // ADC1��λ
    RCC->APB2RSTR &= ~(1 << 8);        // ��λ����

    ADC->CCR &= ~(3 << 16);            // ��Ƶ��������
    ADC->CCR |= 1 << 16;               // ADC1ʱ������=ADCCLK=APB2/4=84/4=21Mhz,ADC���ʱ�Ӳ��ܳ���30M!

    ADC1->CR1  = 0 ;                   // ��0 , CR1���ù���ģʽ
    ADC1->CR1 |= 0 << 8;               // ɨ��ģʽ(���ͨ��)  0:�ر�   1��ʹ��
    ADC1->CR1 |= 0 << 24;              // 12λ�ֱ��ʣ�15ADCCLK����

    ADC1->CR2  = 0;                    // ��0, CR2���ù�������
    ADC1->CR2 |= 0 << 1;               // ����ת��   0������ת��   1������ת��
    ADC1->CR2 |= 0 << 11;              // �Ҷ���
    ADC1->CR2 |= 0 << 28;              // ������ƣ���ֹ��ƽ����

    ADC1->SQR1 &= ~(0x0F<<20);         // ��0ת��ͨ������
    ADC1->SQR1 |= 0 << 20;             // ��Ҫת����ͨ������ �״�����=N+1

    ADC1->SMPR1 = 0x07FF6DB6;          // ͨ��18~16Ϊ480����������(Լ23us)��ͨ��15~10Ϊ144����������(Լ7us)
    ADC1->SMPR2 = 0x36DB6DB6;          // ͨ�� 9~ 0Ϊ144����������(Լ7us)

    ADC1->CR2  |= 1 << 0;              // ����ADת����

    FLAG_ADC1InitOK = 1;               // ��ʼ���󣬱�־��1
}



// ��ʼ������Ҫ������
static void adc_GPIOInit(GPIO_TypeDef *GPIOx, uint32_t PINx)
{   
    // ʹ���������Ŷ˿�ʱ�ӣ�ʹ�ö˿��жϵķ���ʹ��ʱ��, ��ʹ������ֲ������
    if (GPIOx == GPIOA)  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    if (GPIOx == GPIOB)  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    if (GPIOx == GPIOC)  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    if (GPIOx == GPIOD)  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    if (GPIOx == GPIOE)  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

    // �����������Ϊģ������ģʽ; ADC1��15��ͨ�����ֲ���PA��PB��PC��0~7����
    if (PINx == GPIO_Pin_0)   GPIOx->MODER |= (0x03<<0*0);  // GPIO_Pin_0��ģ������
    if (PINx == GPIO_Pin_1)   GPIOx->MODER |= (0x03<<1*2);  // GPIO_Pin_1��ģ������
    if (PINx == GPIO_Pin_2)   GPIOx->MODER |= (0x03<<2*2);  // GPIO_Pin_2��ģ������
    if (PINx == GPIO_Pin_3)   GPIOx->MODER |= (0x03<<3*2);  // GPIO_Pin_3��ģ������
    if (PINx == GPIO_Pin_4)   GPIOx->MODER |= (0x03<<4*2);  // GPIO_Pin_4��ģ������
    if (PINx == GPIO_Pin_5)   GPIOx->MODER |= (0x03<<5*2);  // GPIO_Pin_5��ģ������
    if (PINx == GPIO_Pin_6)   GPIOx->MODER |= (0x03<<6*2);  // GPIO_Pin_6��ģ������
    if (PINx == GPIO_Pin_7)   GPIOx->MODER |= (0x03<<7*2);  // GPIO_Pin_7��ģ������
}



// ������ADC1��2��ͨ��GPIO�˿ڡ����źţ�����ͨ����
// ���أ�������0~15��ʧ�ܣ�99
static uint8_t adc_PinConvertChannel(GPIO_TypeDef *GPIOx, uint32_t PINx)
{
    if ((GPIOx == GPIOA) && (PINx == GPIO_Pin_0))    return  0; // PA0 = ͨ�� 0
    if ((GPIOx == GPIOA) && (PINx == GPIO_Pin_1))    return  1; // PA1 = ͨ�� 1
    if ((GPIOx == GPIOA) && (PINx == GPIO_Pin_2))    return  2; // PA2 = ͨ�� 2
    if ((GPIOx == GPIOA) && (PINx == GPIO_Pin_3))    return  3; // PA3 = ͨ�� 3
    if ((GPIOx == GPIOA) && (PINx == GPIO_Pin_4))    return  4; // PA4 = ͨ�� 4
    if ((GPIOx == GPIOA) && (PINx == GPIO_Pin_5))    return  5; // PA5 = ͨ�� 5
    if ((GPIOx == GPIOA) && (PINx == GPIO_Pin_6))    return  6; // PA6 = ͨ�� 6
    if ((GPIOx == GPIOA) && (PINx == GPIO_Pin_7))    return  7; // PA7 = ͨ�� 7
    if ((GPIOx == GPIOB) && (PINx == GPIO_Pin_0))    return  8; // PB0 = ͨ�� 8
    if ((GPIOx == GPIOB) && (PINx == GPIO_Pin_1))    return  9; // PB1 = ͨ�� 9
    if ((GPIOx == GPIOC) && (PINx == GPIO_Pin_0))    return 10; // PC0 = ͨ��10
    if ((GPIOx == GPIOC) && (PINx == GPIO_Pin_1))    return 11; // PC1 = ͨ��11
    if ((GPIOx == GPIOC) && (PINx == GPIO_Pin_2))    return 12; // PC2 = ͨ��12
    if ((GPIOx == GPIOC) && (PINx == GPIO_Pin_3))    return 13; // PC3 = ͨ��13
    if ((GPIOx == GPIOC) && (PINx == GPIO_Pin_4))    return 14; // PC4 = ͨ��14
    if ((GPIOx == GPIOC) && (PINx == GPIO_Pin_5))    return 15; // PC5 = ͨ��15
    return 99; // ���û�ҵ� ƥ��Ĳ������ͷ��ش����
}


// Ϊ��ֲʱ��������ṹ�������ù�ϵ������������Ϊȫ�ֺ���
// ��ͨ�����ж�β�ֵ��������ƽ��ֵ
// ������  uint8_t channel: ͨ��ֵ����ѡ��Χ0~17
//         uint8_t times:   ��ֲ����
// ����ֵ����β�ֵ���ƽ��ֵ��ֵ��Χ��0~4095
static uint16_t getADC1Value(uint8_t channel, uint8_t times)
{
    uint32_t valueSUM = 0;                        // ADC�Ķ��ȡֵ�ۼӽ��

    if (FLAG_ADC1InitOK == 0)  configADC1();      // ����ADC1�Ĺ���ģʽ

    if (channel == 16 || channel == 17)           // ����ǵ�16��17ͨ������ʹ��TSVREFEλ
        ADC->CCR |= 1 << 23;                      // ʹ�� �¶ȴ�����ͨ�����ڲ��ο���ѹͨ��

    ADC1->SQR3 = channel;                         // ��1��Ҫת����ͨ��,�ڲ��ο���ѹת��ֵͨ��

    for (u8 t = 0; t < times; t++)                // �����ֵ�����ۼӳɽ��ֵ
    {
        ADC1->CR2 |= 1 << 30;                     // ��������ת��ͨ��
        while (!(ADC1->SR & 1 << 1));             // �ȴ�����ת������
        valueSUM = valueSUM + ADC1->DR;           // ���ӱ��β�ֵ
        delay_us(5);                              // ��Ϊ��ʱһ��
    }

    return valueSUM / times;                      // ����ƽ��ֵ
}



/******************************************************************************
 * ��  ���� ADC1_GetInternalTemperature
 * ��  �ܣ� ��ȡоƬ�ڲ��¶�ֵ����ADC1ͨ��16
 *          ��������ֱ�ӵ��ü�����������������ǰ��ADC��ʼ��
 * ��  ����
 * ����ֵ�� float ���϶�ֵ
 *
 * ��  ע�� 1-�˺�����ֱ�ӵ��ü��ɣ��������ⲿ��ADC��GPIO��ʼ��; �����ؽ���¶�ֵ��
 *          2-�����е�1�ε��ô˺����������ڹ�����ʱԼ2ms����Ϊ����Ҫ��ADC����ʼ��;
 *          3-��2���𣬵��ô˺�����ÿ�κ�ʱԼ: 19us*5�� = 100us����;
 *          4-��ϵͳʵʱ��Ҫ��ϸߣ�������жϡ�DMA;��
 *          5-�¶�ֵ��Χ��-40~125�ȣ����ȣ��� 1.5������
 *
 ******************************************************************************/
float  ADC1_GetInternalTemperature(void)
{
    uint16_t adcValue;
    float TEMP = 0.0;

    adcValue = getADC1Value(16, 10);;        // ���ض�β�ֵ���ƽ��ֵ
    TEMP = (float)adcValue * (3.3 / 4096);   // ���ѹ
    TEMP = (TEMP-0.76f) / 0.0025f + 25;      // ���ݹ�ʽ������ѹת�������ϵ�
    return TEMP;
}



/******************************************************************************
 * ��  ���� ADC1_GetVoltage
 * ��  �ܣ� ��ȡͨ�������ϵĵ�ѹֵ
 *
 * ��  ���� GPIO_TypeDef*  GPIOx   GPIO�˿�, ��ѡ������GPIOA ~ GPIOG
 *          uint32_t       PINx    ���ţ�    ��ѡ������GPIO_Pin_0 ~ GPIO_Pin_15
 *
 * ����ֵ�� flloat ��ѹֵ����Χ��0~3.3V
 *
 * ��  ע�� 1-�˺�����ֱ�ӵ��ü��ɣ��������ⲿ��ADC��GPIO��ʼ��; �����ؽ����ѹֵ��
 *          2-�����е�1�ε��ô˺����������ڹ�����ʱԼ2ms����Ϊ����Ҫ��ADC����ʼ��;
 *          3-��2���𣬵��ô˺�����ÿ�κ�ʱԼ: 25us;
 *          4-��ϵͳʵʱ��Ҫ��ϸߣ�������жϡ�DMA;��
 *
 ******************************************************************************/
float ADC1_GetVoltage(GPIO_TypeDef *GPIOx, uint32_t PINx)
{
    static uint8_t  channel  = 0;                 // ͨ����
    static uint16_t adcValue = 0;                 // ADC�ɼ����ƽ��ֵ�����ڼ����ѹֵ

    channel = adc_PinConvertChannel(GPIOx, PINx); // �������ţ��ж�����ADC1��ͨ��
    if (channel == 99)  return 0;                 // ����������ź������˳�������0

    adc_GPIOInit(GPIOx, PINx);                    // ��ʼ������Ϊģ������ģʽ
    adcValue = getADC1Value(channel, 3);          // ��β�ֵ���, ���ص�ƽ��ֵ

    return (float)adcValue / 1241.2f;             // ���ص�ѹֵ; �� adcValue*(3.3/4096)�ļ�ֵ;
}




