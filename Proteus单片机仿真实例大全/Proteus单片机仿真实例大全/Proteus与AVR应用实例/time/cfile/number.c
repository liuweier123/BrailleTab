#define NUMBER_C
#include "includes.h"

//����������
//����p1��ʱ��������
//����p2����ʾ������
//���ܣ�������ֵ���ΪBCD���10�֣��֣�10�룬��
void process(unsigned char *p1,unsigned char *p2)
{
    p2[0] = p1[0]/10;
    p2[1] = p1[0]-p2[0]*10;
    p2[2] = p1[1]/10;
    p2[3] = p1[1]-p2[2]*10;
}