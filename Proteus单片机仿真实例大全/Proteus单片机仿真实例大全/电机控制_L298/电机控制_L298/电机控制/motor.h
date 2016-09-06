#ifndef __motor_H__
#define __motor_H__ 1

//PD4,PD5 电机方向控制
#define moto_en1 PORTD |= 0x10
#define moto_en2 PORTD |= 0x20
#define moto_uen1 PORTD &=~ 0x10
#define moto_uen2 PORTD &=~ 0x20
//启动TC2定时比较和溢出
#define TC2_EN TIMSK |= (1<<OCIE2)|(1<<TOIE2)
//禁止TC2再定时比较和溢出
#define TC2_DIS TIMSK &=~ (1<<OCIE2)|(1<<TOIE2)

//电机正转
extern void for_ward(uint8 speed);

//电机反转
extern void back_ward(uint8 speed);

//电机急停
extern void motor_stop(void);

//加速
extern void speed_add(uint8 add);

//减速
extern void speed_subtract(uint8 subtract);

#endif
