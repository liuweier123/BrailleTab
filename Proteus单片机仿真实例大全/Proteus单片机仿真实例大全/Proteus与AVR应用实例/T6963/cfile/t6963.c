#define T6963_C
#include "includes.h"


/************************************************/
/* ȡ��ǰ������*/
/************************************************/
unsigned char fnGetRow(void)
{
    return(gCurRow);
}
/************************************************/
/* ȡ��ǰ������*/
/************************************************/
unsigned char fnGetCol(void)
{
    return(gCurCol);
}
/************************************************/
/* ��״̬*/
/************************************************/
unsigned char RD_LCM(void)
{
    unsigned char temp;
    dir_datap=0x00;
    port_conp  |= (1 <<LCM ); //LCM=LCMCW;
    port_conp &= ~(1 << RD);  //RD=0;
    NOP();
    temp=LCD_IN;
    port_conp |= (1<<RD);     //RD=1;
    dir_datap = 0xff;
    return(temp);
}
/************************************************/
/* ������*/
/************************************************/
unsigned char RD_DAT(void)
{
    unsigned char temp;
    dir_datap = 0x00;
    port_conp &= ~(1<<LCM);     //LCM=LCMDW;
    port_conp &= ~(1 << RD);    //RD=0;
    NOP();
    temp = LCD_IN;
    port_conp |= (1<<RD);       //RD=1;
    dir_datap = 0xff;
    return(temp);
}
/************************************************/
/* д����*/
/************************************************/
void WR_DAT(unsigned char val)
{
    dir_datap = 0xff;
    port_conp &= ~(1<<LCM);     //LCM=LCMDW;
    LCD_OUT = val;
    port_conp &= ~(1<<WR);      //WR=0;
    NOP();
    NOP();
    port_conp |= (1<<WR);       //WR=1;
}
/************************************************/
/* д����*/
/************************************************/
void WR_CMD(unsigned char val)
{
    dir_datap = 0xff;
    port_conp  |= (1 << LCM);    //LCM=LCMCW;
    LCD_OUT = val;
    port_conp &= ~(1<<WR);       //WR=0;
    NOP();
    NOP();
    port_conp |= (1<<WR);        //WR=1;
}
/************************************************/
/* ״̬λSTA1,STA0�ж϶�дָ��Ͷ�д����*/
/* �ڶ�д���ݻ���д������ǰ���뱣֤��Ϊ1 */
/************************************************/
unsigned char fnSTA01(void)
{
    unsigned char i;
    for(i=10;i>0;i--)
    {
        if((RD_LCM() & 0x03) == 0x03) // ��ȡ״̬
        {
            break;
        }
    }
    return(i); // ��������˵������
}
/********************************************/
/* ���STA2,���STA2=1 Ϊ�Զ���״̬*/
/********************************************/
unsigned char fnSTA2(void)
{
    unsigned char i;
    for(i=10;i>0;i--)
    {
        if((RD_LCM() & 0x04) == 0x04)
        {
            break;
        }
    }
    return(i); // ��������˵������
}
/***********************************************/
/* ״̬λSTA3 �ж�STA3 = 1 �����Զ�д״̬*/
/***********************************************/
unsigned char fnSTA3(void)
{
    unsigned char i;
    for(i=10;i>0;i--)
    {
        if((RD_LCM() & 0x08) == 0x08)
        {
            break;
        }
    }
    return(i); // ��������˵������
}
/************************************************/
/* ״̬λSTA6 �ж�STA6 =1 ����/������״̬*/
/************************************************/
unsigned char fnSTA6(void)
{
    unsigned char i;
    for(i=10;i>0;i--)
    {
        if((RD_LCM() & 0x40) == 0x40)
        {
            break;
        }
    }
    return(i); // ��������˵������
}
/************************/
/* д˫������ָ��*/
/************************/
unsigned char fnPR1(unsigned char uCmd,unsigned char uPar1,unsigned char uPar2)
{
    if(fnSTA01() == 0)
    {
        return 1;
    }
    WR_DAT(uPar1);
    if(fnSTA01() == 0)
    {
        return 2;
    }
    WR_DAT(uPar2);
    if(fnSTA01() == 0)
    {
        return 3;
    }
    WR_CMD(uCmd);
    return(0); // ����0 �ɹ�
}
/************************/
/* д��������ָ��*/
/************************/
unsigned char fnPR11(unsigned char uCmd,unsigned char uPar1)
{
    if(fnSTA01() == 0)
    {
        return 1;
    }
    WR_DAT(uPar1);
    if(fnSTA01() == 0)
    {
        return 2;
    }
    WR_CMD(uCmd);
    return(0); // ����0 �ɹ� 
}
/************************/
/* д�޲�����ָ��*/
/************************/
unsigned char fnPR12(unsigned char uCmd)
{   
    if(fnSTA01() == 0)
    {
        return 1;
    }
    WR_CMD(uCmd);
    return(0); // ����0 �ɹ�
}
/************************/
/* д����*/
/************************/
unsigned char fnPR13(unsigned char uData)
{
    if(fnSTA3() == 0)
    {
        return 1;
    }
    WR_DAT(uData);
    return(0); // ����0 �ɹ�
}
/************************/
/* ������*/
/************************/
unsigned char fnPR2(void)
{
    unsigned char temp;
    if(fnSTA01() == 0)
    {
         return 1; // ��ȡ״̬���״̬��
    }
    temp=RD_DAT();
    return(temp); // ��������
}
/************************/
/* ���õ�ǰ��ַ*/
/************************/
void fnSetPos(unsigned char urow, unsigned char ucol)
{
    unsigned int iPos;
    iPos = (unsigned int)urow * 30 + ucol;
    fnPR1(LC_ADD_POS,iPos & 0xFF,iPos / 256);
    gCurRow = urow;
    gCurCol = ucol;
}
/**********************/
/* ���õ�ǰ��ʾ����*/
/**********************/
void cursor(unsigned char uRow, unsigned char uCol)
{
    fnSetPos(uRow * 16, uCol);
}
/*********************/
/* ����*/
/*********************/
void cls(void)
{
    unsigned int i;
    fnPR1(LC_ADD_POS,0x00,0x00); // �õ�ַָ��Ϊ���㿪ʼ
    fnPR12(LC_AUT_WR); // �Զ�д
    for(i=0;i<240*128/8;i++) // ��һ��
    {
        fnSTA3();
        fnPR13(0x0); // д����ʵ��ʹ��ʱ�뽫0x55 �ĳ�0x0
    }
    fnPR12(LC_AUT_OVR); // �Զ�д����
    fnPR1(LC_ADD_POS,0x00,0x00); // ���õ�ַָ��
    gCurRow = 0; // �õ�ַָ��洢����
    gCurCol = 0;
}
/************************/
/* LCM ��ʼ��*/
/************************/
char fnLCMInit(void)
{
    if(fnPR1(LC_TXT_STP,0x00,0x00) != 0) // �ı���ʾ���׵�ַ
    {
        return (0xff);
    }
    fnPR1(LC_TXT_WID,0x1E,0x00); // �ı���ʾ�����
    fnPR1(LC_GRH_STP,0x00,0x00); // ͼ����ʾ���׵�ַ
    fnPR1(LC_GRH_WID,0x1E,0x00); // ͼ����ʾ�����
    fnPR12(LC_CUR_SHP | 0x01); // �����״
    fnPR12(LC_MOD_OR); // ��ʾ��ʽ����
    fnPR12(LC_DIS_SW | 0x08); // ��ʾ��������
    return(0);
}
/********************************************************/
/* ASCII(8*16) �� ����(16*16) ��ʾ����      */
/********************************************************/
unsigned char dprintf(unsigned char x,unsigned char y, char *ptr)
{
    unsigned char c1,c2,cData;
    unsigned char i,j,uLen,uRow,uCol;
    unsigned int  k;
    uLen=0;
    i=0;
    uRow = y;
    uCol = x;
    fnSetPos(uRow*16,uCol);      //��㶨λ
    while (ptr[uLen]!=0) //̽���ִ�����
    {
        uLen++;
    }	
    while(i<uLen)
    {
    	c1 = ptr[i];
    	c2 = ptr[i+1];
        //ascii�ַ��뺺���������������128���ֽ磬���ڽ��ߵ�Ϊ������
    	uRow = fnGetRow();    
    	uCol = fnGetCol();
    	if(c1 <=128)	// ASCII
      	{
            for(j=0;j<16;j++) //д16��
            {
        	fnPR12(LC_AUT_WR);    			// д����(����)
        	if (c1 >= 0x20)
          	{
            	    fnPR13( ASC_MSK[(c1-0x20)*ASC_CHR_HEIGHT+j-(16-ASC_CHR_HEIGHT)] );
          	}
        	else
        	{
          	    fnPR13(cData);
          	}
         	fnPR12(LC_AUT_OVR);  			//д���ݽ���
                fnSetPos(uRow+j+1,uCol);
             }
            if(c1 != BS)  	// ���˸�
            {
                uCol++;   // ������1
            }
          			   				
        }
    	else    	// ����
      	{
            for(j=0;j<sizeof(GB_16)/sizeof(GB_16[0]);j++)  	// ���Ҷ�λ
            {
                if(c1 == GB_16[j].Index[0] && c2 == GB_16[j].Index[1])
                {
                    break;
                }
          				
            }
            for(k=0;k<sizeof(GB_16[0].Msk)/2;k++)
            {
                fnSetPos(uRow+k,uCol);
        	fnPR12(LC_AUT_WR);      		// д����
        	if(j < sizeof(GB_16)/sizeof(GB_16[0]))
          	{
          	    fnPR13(GB_16[j].Msk[k*2]);
          	    fnPR13(GB_16[j].Msk[k*2+1]);
          	}
        	else   		// δ�ҵ�����
          	{
          	    if(k < sizeof(GB_16[0].Msk)/4)
            	    {
                        fnPR13(0x00);
            		fnPR13(0x00);
            	     }
         	    else
            	    {
            		fnPR13(0xff);
			fnPR13(0xff);
            	    }
                }
        	fnPR12(LC_AUT_OVR);
            }
      	    uCol += 2;
      	    i++;
        };
    	if(uCol >= 30)      					// ������
      	{
      	    uRow += 16;
            if(uRow < 0x80)
            {
                uCol -= 30;
            }
      	    else
            {
        	uRow = 0;
        	uCol = 0;
            }
      	 }
         fnSetPos(uRow,uCol);
    	 i++;
    }
    return uLen;        //�����ִ����ȣ����ְ�2�ֽڼ���
}  
/*======================*/
/* ��ʱ*/
/*======================*/
void shortdelay(unsigned int tt)
{
    unsigned char i;
    while (tt)
    {
        i=100;
        while (i)
        {
            i--;
        }
    tt--;
    }
}
/*************************/
/* ����*/
/*************************/
void point(unsigned char x,unsigned char y,unsigned char s)
{
    unsigned char x1;
    x1 = x >> 3; // ȡY�����ҳ��ַ
    fnSetPos(y,x1); // ��㶨λ
    x1 = turnf[ x & 0x07 ];
    x1 = 0xF0 | x1 | s; // �ֽ���λ�ü���
    fnPR12(x1); // ������ĻS��ʾ����8 ����0 ������
}
/************************************************/
/* �������ⷽ���б��,ֱ����ѧ����aX+bY=1 */
/************************************************/
void Linexy(unsigned char x0,unsigned char y0,unsigned char xt,unsigned char yt,unsigned char s)
{
    register unsigned char t;
    int xerr = 0,yerr = 0;
    int delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;
    delta_x = xt-x0; // ������������
    delta_y = yt-y0;
    uRow = x0;
    uCol = y0;
    if(delta_x>0)
    {
        incx = 1; // ���õ�������
    }
    else if( delta_x==0 )
    {
        incx=0; // ��ֱ��
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
     
    }
    if(delta_y>0)
    {
        incy=1;
    }
    else if( delta_y==0 ) 
    {
        incy=0; // ˮƽ��
    }
    else 
    {
        incy=-1;
        delta_y=-delta_y;
    }
    if( delta_x > delta_y ) 
    {
        distance=delta_x; // ѡȡ��������������
    }
    else 
    {
        distance=delta_y;
    }
    for( t=0;t <= distance+1; t++ )   // �������
    { 
        point(uRow,uCol,s); // ����
        xerr += delta_x;
        yerr += delta_y;
        if( xerr > distance )
        {
            xerr -= distance;
            uRow += incx;
        }
        if( yerr > distance )
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}
/********************************************/
/* ��Բ��ѧ����(X-Ox)^2+(Y-Oy)^2=Rx^2 */
/********************************************/
void circle(unsigned char Ox,unsigned char Oy,unsigned char Rx,unsigned char s)
{
    unsigned int xx,rr;
    unsigned int xt,yt;
    unsigned int rs,row,col;
    yt = Rx;
    rr = (unsigned int)Rx*Rx+1; // ����1 ��������
    rs = (yt+(yt>>1))>>1; // (*0.75)�ֿ�1/8Բ������
    for (xt=0;xt<=rs;xt++)
    {
        xx = xt*xt;
        while ((yt*yt)>(rr-xx))
        {
            yt--;
        }
        row = Ox+xt; // ��һ����
        col = Oy-yt;
        point(row,col,s);
        row = Ox-xt; // �ڶ�����
        point(row,col,s);
        col = Oy+yt; // ��������
        point(row,col,s);
        row = Ox+xt; // ��������
        point(row,col,s);
        /***************45�Ⱦ�����һ��***************/
        row = Ox+yt; // ��һ����
        col = Oy-xt;
        point(row,col,s);
        row = Ox-yt; // �ڶ�����
        point(row,col,s);
        col = Oy+xt; // ��������
        point(row,col,s);
        row = Ox+yt; // ��������
        point(row,col,s);
    }
}
