#define KEY_C
#include "includes.h"


char read_keybord(void)
{
    static char key_state = 0;
    static char key_value, key_line;
    static char key_return = NO_KEY;
    unsigned char i;
    switch(key_state)
    {
        case 0:
           // #ifdef KEY_4X4 
           // key_line = 0x10;     // 0b0001 0000;  
            //#else
            key_line = 0x08;      //0b0000 1000;
            //#endif           
            for(i=1;i<=4;i++)    //����ɨ��
            {
                KEY_PORT = ~key_line;   //������ߵ�ƽ                
                KEY_PORT = ~key_line;   //�������
                //delay_nms(2);
                key_value = KEY_MASK & KEY_PIN;  //���е�ƽ
                if(key_value == KEY_MASK)
                {
                    key_line <<= 1;   //û�а���,����ɨ��  
                    //delay_nms(2);                  
                }
                else
                {
                    key_state++;  //�м�����,ֹͣɨ��
                    break;    //ת����ȷ��״̬
                }                
                
            }
            break;
        case 1:
            //if((key_value == KEY_MASK & KEY_PIN))  //�ٴζ��е�ƽ
            {
                //#ifdef KEY_4X4
               /* switch((key_value | key_line)) //��״̬0��ͬ,ȷ�ϰ���
                {
                    case 0x1e:              //0b00011110:
                        key_return = K1_1;
                        break;
                    case 0x1d:              //0b00011101:
                        key_return = K1_2;
                        break;
                    case 0x1b:              //0b00011011:
                        key_return = K1_3;
                        break;
                    case 0x17:               //0b00010111:
                        key_return = K1_4;
                        break;
      
                    case 0x2e:              //0b00101110:
                        key_return = K2_1;
                        break;
                    case 0x2d:              //0b00101101:
                        key_return = K2_2;
                        break;
                    case 0x2b:              //0b00101011:
                        key_return = K2_3;
                        break;
                    case 0x27:              //0b00100111:
                        key_return = K2_4;
                        break;
                        
                    case 0x4e:              //0b01001110:
                        key_return = K3_1;
                        break;
                    case 0x4d:              //0b01001101:
                        key_return = K3_2;
                        break;
                    case 0x4b:              //0b01001011:
                        key_return = K3_3;
                        break;
                    case 0x47:              //0b01000111:
                        key_return = K3_4;
                        break;
                        
                    case 0x8e:              //0b10001110:
                        key_return = K4_1;
                        break;
                    case 0x8d:              //0b10001101:
                        key_return = K4_2;
                        break;
                    case 0x8b:              //0b10001011:
                        key_return = K4_3;
                        break;
                    case 0x87:              //0b10000111:
                        key_return = K4_4;
                        break;
                }  */             
               // #else
                switch((key_value | key_line)) //��״̬0��ͬ,ȷ�ϰ���
                {
                    case 0x0e:              //0b00001110:
                        key_return = K1_1;
                        break;
                    case 0x0d:              //0b00001101:
                        key_return = K1_2;
                        break;
                    case 0x0b:              //0b00001011:
                        key_return = K1_3;
                        break;                   
      
                    case 0x16:              //0b00010110:
                        key_return = K2_1;
                        break;
                    case 0x15:              //0b00010101:
                        key_return = K2_2;
                        break;
                    case 0x13:              //0b00010011:
                        key_return = K2_3;
                        break;                  
                        
                    case 0x26:              //0b00100110:
                        key_return = K3_1;
                        break;
                    case 0x25:              //0b00100101:
                        key_return = K3_2;
                        break;
                    case 0x23:              //0b00100011:
                        key_return = K3_3;
                        break;                    
                        
                    case 0x46:              //0b01000110:
                        key_return = K4_1;
                        break;
                    case 0x45:              //0b01000101:
                        key_return = K4_2;
                        break;
                    case 0x43:              //0b01000011:
                        key_return = K4_3;
                        break;                   
                }
               // #endif
                key_state++;     //ת�밴���ͷ�״̬                                
            }
           /* else
            {
                key_state--;     //�����е�ƽ״̬��ͬ����״̬0 (��������) 
            }*/
            break;
        case 2:     //�ȴ������ͷ�
           // #ifdef KEY_4X4
            //KEY_PORT = 0x0f;      //����ȫ������͵�ƽ      
            //KEY_PORT = 0x0f;
            //#else
            KEY_PORT = 0x07;      //����ȫ������͵�ƽ      
            KEY_PORT = 0x07;
           //#endif
            if((KEY_MASK & KEY_PIN) == KEY_MASK)
            {
                key_state = 0;   //����ȫ��Ϊ�ߵ�ƽ,����״̬0
            }     
            break; 
    }
    return(key_return);
}





/*unsigned char key_scan(void)
{
    unsigned char sccode,recode;
    DDRC = 0xff;
    PORTC = 0xf0;
    if(((PINC&0xf0)!=0xf0))  //�м�����
    {
        delay_nms(15);
        if(((PINC&0xf0)!=0xf0))  //�м�����
        {
            sccode = 0xfe;    //��ɨ���ʼֵ
            while((sccode&0x10)!=0) 
            {
                PORTC = sccode;   //�����ɨ����
                if(((PINC&0xf0)!=0xf0))   //�����м�����
                {
                    recode = (PINC&0xf0)|0x0f;
                    return((~sccode)+(~recode));  //���������ֽ���
                }
                else
                {
                    sccode = (sccode<<1)|0x01;  //��ɨ��������һλ
                }
                
            }                    
        }
    }     
    return(0);   //�޼����·���0
}
*/
