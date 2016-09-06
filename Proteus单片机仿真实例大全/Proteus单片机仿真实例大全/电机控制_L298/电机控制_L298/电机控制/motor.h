#ifndef __motor_H__
#define __motor_H__ 1

//PD4,PD5 ����������
#define moto_en1 PORTD |= 0x10
#define moto_en2 PORTD |= 0x20
#define moto_uen1 PORTD &=~ 0x10
#define moto_uen2 PORTD &=~ 0x20
//����TC2��ʱ�ȽϺ����
#define TC2_EN TIMSK |= (1<<OCIE2)|(1<<TOIE2)
//��ֹTC2�ٶ�ʱ�ȽϺ����
#define TC2_DIS TIMSK &=~ (1<<OCIE2)|(1<<TOIE2)

//�����ת
extern void for_ward(uint8 speed);

//�����ת
extern void back_ward(uint8 speed);

//�����ͣ
extern void motor_stop(void);

//����
extern void speed_add(uint8 add);

//����
extern void speed_subtract(uint8 subtract);

#endif
