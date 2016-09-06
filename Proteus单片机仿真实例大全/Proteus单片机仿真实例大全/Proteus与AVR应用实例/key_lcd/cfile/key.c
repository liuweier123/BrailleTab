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
            for(i=1;i<=4;i++)    //按键扫描
            {
                KEY_PORT = ~key_line;   //输出行线电平                
                KEY_PORT = ~key_line;   //输出两次
                //delay_nms(2);
                key_value = KEY_MASK & KEY_PIN;  //读列电平
                if(key_value == KEY_MASK)
                {
                    key_line <<= 1;   //没有按键,继续扫描  
                    //delay_nms(2);                  
                }
                else
                {
                    key_state++;  //有键按下,停止扫描
                    break;    //转消抖确认状态
                }                
                
            }
            break;
        case 1:
            //if((key_value == KEY_MASK & KEY_PIN))  //再次读列电平
            {
                //#ifdef KEY_4X4
               /* switch((key_value | key_line)) //与状态0相同,确认按键
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
                switch((key_value | key_line)) //与状态0相同,确认按键
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
                key_state++;     //转入按键释放状态                                
            }
           /* else
            {
                key_state--;     //两次列电平状态不同返回状态0 (消抖处理) 
            }*/
            break;
        case 2:     //等待按键释放
           // #ifdef KEY_4X4
            //KEY_PORT = 0x0f;      //行线全部输出低电平      
            //KEY_PORT = 0x0f;
            //#else
            KEY_PORT = 0x07;      //行线全部输出低电平      
            KEY_PORT = 0x07;
           //#endif
            if((KEY_MASK & KEY_PIN) == KEY_MASK)
            {
                key_state = 0;   //列线全部为高电平,返回状态0
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
    if(((PINC&0xf0)!=0xf0))  //有键按下
    {
        delay_nms(15);
        if(((PINC&0xf0)!=0xf0))  //有键按下
        {
            sccode = 0xfe;    //逐含扫描初始值
            while((sccode&0x10)!=0) 
            {
                PORTC = sccode;   //输出行扫描码
                if(((PINC&0xf0)!=0xf0))   //本行有键按下
                {
                    recode = (PINC&0xf0)|0x0f;
                    return((~sccode)+(~recode));  //返回特征字节码
                }
                else
                {
                    sccode = (sccode<<1)|0x01;  //行扫描码左移一位
                }
                
            }                    
        }
    }     
    return(0);   //无键按下返回0
}
*/
