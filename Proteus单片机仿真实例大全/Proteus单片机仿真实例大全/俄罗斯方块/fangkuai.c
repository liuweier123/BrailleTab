#include "t6963c.h"
#include "typedef.h"
#include "key.h"

#define X_START 5
#define Y_START 0
#define MIN_SLOW_SPEED  300
#define BX_START  30
#define BY_START  15
#define Nothing   100


//ȫ������
code uchar Game_Char[]={0x27,0x41,0x4d,0x45};
code uchar Over_Char[]={0x2f,0x56,0x45,0x52};
				                            
static uchar xx,yy;         //�����λ��
static uint  Game_Score=0;
static uchar xdata Platform[14][21];    //��Ϸƽ̨����
static uchar This_shape;				//��ǰ��״
static uchar Next_shape=0;
static uint  Game_Speed=MIN_SLOW_SPEED;	 //�ȼ��ٶȣ���������������½����ٶ�
static uchar Game_Stop=1;
static uchar Game_Level=0;

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////������״�Ķ���//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
struct POINT{
              uchar x;
              uchar y;
             };

struct SHAPE{
               struct POINT point[4];
			   uchar next;	//��һ����״
			 } 


xdata shape[19]={ 
  
                   { 1,0,0,1,1,1,2,1,1  },
				   { 1,0,1,1,2,1,1,2,2  },
				   { 0,0,1,0,2,0,1,1,3  },
				   { 1,0,0,1,1,1,1,2,0  },
				    
				   { 1,0,2,0,1,1,1,2,5  },
				   { 0,0,1,0,2,0,2,1,6  },
				   { 2,0,2,1,2,2,1,2,7  },
				   { 0,0,0,1,1,1,2,1,4  },

				   { 1,0,2,0,2,1,2,2,9  },
				   { 2,0,0,1,1,1,2,1,10 },
				   { 1,0,1,1,1,2,2,2,11 },
				   { 0,0,1,0,2,0,0,1,8  },

				   { 0,0,0,1,1,1,1,2,13 },
				   { 1,0,2,0,0,1,1,1,12 },

				   { 2,0,1,1,2,1,1,2,15 },
				   { 0,0,1,0,1,1,2,1,14 },

				   { 1,0,1,1,1,2,1,3,17 },
				   { 0,1,1,1,2,1,3,1,16 },

				   { 1,0,2,0,1,1,2,1,18 }, 	
				   	 
				};   

////////////////////////////////////////////////////////////////////////////
//**************************************************************************
//= ����ԭ��:void Init_GamePlatform()
//= ��    ��: ��ʼ����Ϸƽ̨
//= ��    ��: ��			
//= �� �� ֵ: ��
//= �������ʣ����к���
//= ע    �⣺
//*************************************************************************** 
void Show_score(uchar);
void Init_GamePlatform()
{
  uchar i;
  uchar j;
  uchar N_Hanzi;
  
  Wr_line(1,33,13,64,1 );	//��ʼ����Ϸƽ̨�߽�	����Ϸ����
  Wr_line(1,33,14,64,1 );   //���Ϻ���
  Wr_line(0,33,15,100,1);
  Wr_line(0,34,15,100,1);  //��������
  Wr_line(1,33,115,64,1);  
  Wr_line(1,33,116,64,1);  //���º���
  Wr_line(0,95,15,100,1);
  Wr_line(0,96,15,100,1);  //��������
//--------------------------------------------------------
  for(i=1;i<13;i++)		//��Ϸƽ̨��������
  {
    for(j=0;j<20;j++)
	  {
	    Platform[i][j]=0;
	  }
   }
   for(i=1;i<13;i++)
   {
      Platform[i][20]=1;   //��Ϸƽ̨������һ�е�ÿһ������λ��Ϊ������Ϊ�±߽�
	}
   
   for(j=0;j<20;j++)		//��Ϸƽ̨���ҷ���λ���ã�����Ϊ���ұ߽�
   {
      Platform[0][j]=1;
	  Platform[13][j]=1;
   }
//--------------------------------------------------------- 
  N_Hanzi=0;             
  for(j=3;j<=12;j=j+2)	   //���롰���������������
  {
     hanzhi(1,j,N_Hanzi,1);
	 N_Hanzi++;   //ָ����һ������
  }
  
  hanzhi(13,3,6,1);	 //���롰�֡�����
  hanzhi(13,8,8,1);   //���롰��������

  Show_score(0);        //��ʾ��ʼ����
  Show_num(13,11,Game_Level);	 //��ʾ��ʼ�ȼ�ˮƽ
  Game_Speed=MIN_SLOW_SPEED/(Game_Level+1);  //����ˮƽȷ���ٶ�

//------------------------------------------------------------------
  Game_Score=0;
  xx=X_START ;
  yy=Y_START ;
}
////////////////////////Init_Game/////////////////////
void Init_Game()
{
  Game_Stop=1;
  Init_GamePlatform();
  hanzhi(7,3,9,1);	 //���롰��������
  Show_num(7,6,7);	 //��ʾ7
  hanzhi(7,8,10,1);	 //���롰��������
  hanzhi(7,10,11,1);	 //���롰ʼ������
}
//**************************************************************************
//= ����ԭ��:void XiaoFengKuai(uchar x,uchar y,uchar mode)
//= ��    ��: ��ʾһ��С����
//= ��    ��: С����ĺ�x��������y,mode=1:��ʾС����,mode=0:ɾ��С����			
//= �� �� ֵ:
//= �������ʣ�˽�к���
//= ע    �⣺
//*************************************************************************** 
void XiaoFengKuai(uchar x,uchar y,bit mode)
{
   uchar x1=5*x+BX_START;	//��������ƽ̨��λ��ת���ɣ̣ãĵĵ�����(��ַת����
   uchar y1=5*y+BY_START;	  
   uchar i;

   if(mode==1)
   {

       for(i=0;i<5;i++)
       {
          Point(x1+i,y1,1); //��һ������
       }


       	y1+=4;

        for(i=0;i<5;i++)
        {
           Point(x1+i,y1,1); //���ڶ�������
         }

        for(i=0;i<5;i++)
        {
           Point(x1,y1-i,1); //����1������
         }

         x1+=4;

        for(i=0;i<5;i++)
        {
           Point(x1,y1-i,1); //����2������
         }

        y1-=4;
        for(i=0;i<5;i++)
        {
           Point(x1-i,y1+i,1); //��б��
        }
   }

  else
  {
  	   for(i=0;i<5;i++)
        {
          Point(x1+i,y1,0); //��һ������
      	}

       	y1+=4;
        for(i=0;i<5;i++)
         {
           Point(x1+i,y1,0); //���ڶ�������
         }

         for(i=0;i<5;i++)
         {
            Point(x1,y1-i,0); //����1������
          }

         x1+=4;
        for(i=0;i<5;i++)
          {
             Point(x1,y1-i,0); //����2������
          }

        y1-=4;
        for(i=0;i<5;i++)
         {
           Point(x1-i,y1+i,0); //��б��
         }
	}
}
//////////////////////////////////////////////////////////////////////////
////////////////���ͻ���//////////////////////////////////////////////
bit Left_Anti()
{
  uchar i;
  for(i=0;i<4;i++)
	{
	  if(Platform[xx+shape[This_shape].point[i].x-1][yy+shape[This_shape].point[i].y]==1) 
	    return 1;
	}
  return 0;
}	   

////////////////�ҳ�ͻ���///////////////////////////////////////////
bit Right_Anti()
{
  uchar i;
  for(i=0;i<4;i++)
	{
	  if(Platform[xx+shape[This_shape].point[i].x+1][yy+shape[This_shape].point[i].y]==1)
	    return 1;
	}			   
  return 0;
  
}

////////////////////////////////////////�³�ͻ���//////////////////////////
bit Bottom_Anti()
{
   uchar i;
   for(i=0;i<4;i++)
	{
	  if(Platform[xx+shape[This_shape].point[i].x][yy+shape[This_shape].point[i].y+1]==1)
	    return 1;
    }
  return 0;			  
}
//////////////////////////////////�ı���״ʱ�����ĳ�ͻ���////////////////////
bit Change_Shape_Anti()
{
   uchar i;
   for(i=0;i<4;i++)
	{
	  if(Platform[xx+shape[shape[This_shape].next].point[i].x][yy+shape[shape[This_shape].next].point[i].y]==1)
	    return 1;	   //���һ����״�ĳ�ͻ���
    }
   return 0;
}
//////////////////////////////////����һ�������,����һ�������///////////////
uchar Random()
{
  static uchar m;
  m+=49;
  return (m%19);
}

//////////////�Ʒֺ���,����Ϊ ��������n///////////////////////////////////////

void Show_score(uchar n)
{
  Game_Score=Game_Score+10*n;

  if(Game_Score<10)
  {
     Show_num(13,6,Game_Score%10);		//��ʾ��λ
  }
  else if(Game_Score<100)
  {  
     Show_num(14,6,Game_Score%10);
	 Show_num(13,6,Game_Score/10%100);	//��ʾ��λ,ʮλ
  }
  else if(Game_Score<1000)
  {
     Show_num(14,6,Game_Score%10);
	 Show_num(13,6,Game_Score/10%10);
	 Show_num(12,6,Game_Score/100%10);	//��ʾ��λ ,ʮλ,��λ
  }
  else
  {  
	 Show_num(15,6,Game_Score%10);
	 Show_num(14,6,Game_Score/10%10);
	 Show_num(13,6,Game_Score/100%10);	//��ʾ��λ ,ʮλ,��λ,ǧλ
	 Show_num(12,6,Game_Score/1000);
  }
  
  if(Game_Score%1000==0)
  {
    if(Game_Score>0)
	{
       Game_Level++;
       if(Game_Level==10)
	   {
	      Game_Stop=1;
	      hanzhi(7,5,12,1);	 //	�����̫����"
          hanzhi(7,7,13,1);	 
		  hanzhi(7,9,14,1);
		  
	   }
       Show_num(13,11,Game_Level);	 //��ʾˮƽ
	
    }
  }
}

//**************************************************************************
//= ����ԭ��:void Undisplay_line()
//= ��    ��: ������
//= ��    ��: ��			
//= �� �� ֵ: ��
//= �������ʣ�˽�к���
//= ע    �⣺
//***************************************************************************   
void UnDisplay_line()
{
   uchar Del_Line;      //��ʶҪɾ������
   uchar Del_Line_Num=0;     //��ʶɾ��������
   uchar i,j,k;
   bit HavePoint;		    //��ʶһ�����Ƿ��пհ׵�

   for(i=0;i<4;i++)
   {
      for(j=1;j<13;j++)
	  {
	     if(Platform[j][yy+i]==0) 
		    break;                   //�����һ������һ��Ϊ�գ����˳���һ�е�ѭ��
		 else if(j==12)
		 {
		    Del_Line=yy+i;  	       //ȷ��Ҫɾ������
			if(Del_Line<20)
			{
			   Del_Line_Num++;	           //���㹲ɾ��������
			for(k=1;k<13;k++)
			{
			    XiaoFengKuai(k,Del_Line,0);   	//ɾ����
				Platform[k][Del_Line]=0;         //ƽ̨��������
			}
			while(1)     //����
			{
			   HavePoint=0;
			   for(k=1;k<13;k++)
			   {
			      if(Platform[k][Del_Line-1]==1)
				  {
				     HavePoint=1;            //��ʶ��һ����Ҫ���Ƶĵ�
				     XiaoFengKuai(k,Del_Line-1,0);   	//ɾ��С����
					 Platform[k][Del_Line-1]=0;         //ƽ̨��������
					 XiaoFengKuai(k,Del_Line,1) ;  	//��С��������
					 Platform[k][Del_Line]=1;         //ƽ̨������1,������λ���ѱ�ռ��
				   }
			   }
			   if(HavePoint==0) break;  //û��Ҫ���Ƶ��У��˳���ѭ��
			   Del_Line--;   //������һ��
			}
			}
		 }
      }		
   }
   if(Del_Line_Num)
	 {
	    Show_score(Del_Line_Num);	  //ˢ�·�����ʾ
	 }
}			    
			   
//**************************************************************************
//= ����ԭ��:void Show_shape(uchar x1,uchar y1,uchar Tshape,bit mode)
//= ��    ��: ��ʾһ��������״��ɾ��һ��������״
//= ��    ��: (x1,y1)Ϊ��ʾλ��,TshapeΪ��ʾ����״,mode=1Ϊ��ʾ,mode=0����ʾ			
//= �� �� ֵ:
//= �������ʣ�˽�к���
//= ע    �⣺
//*************************************************************************** 
void Show_shape(uchar x1,uchar y1,uchar Tshape,bit mode)
{
  if(mode==1)
  {

     XiaoFengKuai(x1+shape[Tshape].point[0].x,y1+shape[Tshape].point[0].y,1);	 //��ʾ��״
	 XiaoFengKuai(x1+shape[Tshape].point[1].x,y1+shape[Tshape].point[1].y,1);
	 XiaoFengKuai(x1+shape[Tshape].point[2].x,y1+shape[Tshape].point[2].y,1);
	 XiaoFengKuai(x1+shape[Tshape].point[3].x,y1+shape[Tshape].point[3].y,1);
  }
  else
  {
     XiaoFengKuai(x1+shape[Tshape].point[0].x,y1+shape[Tshape].point[0].y,0);  //ɾ����״
	 XiaoFengKuai(x1+shape[Tshape].point[1].x,y1+shape[Tshape].point[1].y,0);
	 XiaoFengKuai(x1+shape[Tshape].point[2].x,y1+shape[Tshape].point[2].y,0);
	 XiaoFengKuai(x1+shape[Tshape].point[3].x,y1+shape[Tshape].point[3].y,0);
  }
}

//**************************************************************************
//= ����ԭ��:void Fangkuai_down()
//= ��    ��: �����½�����
//= ��    ��: 			
//= �� �� ֵ:
//= �������ʣ����к���
//= ע    �⣺
//***************************************************************************   
static uint DSpeed=MIN_SLOW_SPEED;		   //��ʶ�½��ٶ�
static uint Now_Speed=MIN_SLOW_SPEED;         //��ǰ�ٶ�
void Fangkuai_down()
{ 
  uchar i;
  static bit New_shape=1;		 //��ʶ�Ƿ�Ҫ��������״
  if(Game_Stop==1) return;
  if(New_shape==1)
  {
    New_shape=0;
    xx=X_START;
	yy=Y_START;
    This_shape=Next_shape;			    //��ǰ�������Ԥ����
	Show_shape(15,18,Next_shape,0);	    // ����һ�¸�����ǰ����Ԥ����ɾ��
	Next_shape=Random();		        //������һ������
	Show_shape(xx,yy,This_shape,1);		 //��ʾ��ǰ����
	Show_shape(15,18,Next_shape,1);		 //Ԥ��ʾ��һ������
	if(Bottom_Anti())
	{
	   Game_Stop=1;
       Show_Image(35,15,94,114,0); 	  //����
	   char_wr(6,6,Game_Char,0,4); //��ʾGame 
	   char_wr(6,8,Over_Char,0,4); //��ʾover
	   return;
	} 
  }
  else
  {
      if(DSpeed==0)
	    {
	       DSpeed=Now_Speed;	//ȷ������������ٶ�
	       if(Bottom_Anti())
	         {
	             New_shape=1;//�����µ���״
	            for(i=0;i<4;i++)
	             {
	               Platform[xx+shape[This_shape].point[i].x][yy+shape[This_shape].point[i].y]=1;//д��ƽ̨
		          
		         }
				 UnDisplay_line();//���мƷ�
				 return;
              }
	       else
	         {
	           Show_shape(xx,yy,This_shape,0); //ɾ����ǰ��״
	           yy++;
               Show_shape(xx,yy,This_shape,1); //��ʾ��״(��״����һ��λ��)
	           return;
	          }
       	}
      else
       {
          DSpeed--;
	      
        }
	
    }
}

//**************************************************************************
//= ����ԭ��:void Fangkuai_Control()
//= ��    ��: ������Ϸ����
//= ��    ��: 			
//= �� �� ֵ:
//= �������ʣ����к���
//= ע    �⣺
//*************************************************************************** 
#define Move_Left    4
#define Move_Right 	 6
#define Add_Speed    5
#define Change_Shape 8
#define Game_Star    7
#define Game_Pause   9

void Fangkuai_Control()
{
   	
	 switch(Key)    //��Ϣ����
	 {
	     case  Move_Left: 
		       {
			      Key=Nothing;  //��Ϣ�ѱ�����������
	              if(!Left_Anti())
	              {
	   	             Show_shape(xx,yy,This_shape,0); //ɾ����ǰ��״
	                 xx--;
		             Show_shape(xx,yy,This_shape,1); //��ʾ�ƶ������״
	              }
			   }break;
	     case  Move_Right:
		      {
			     Key=Nothing;  //��Ϣ�ѱ�����������
	             if(!Right_Anti())
	             {
	   	            Show_shape(xx,yy,This_shape,0); //ɾ����ǰ��״
	                xx++;
		            Show_shape(xx,yy,This_shape,1); //��ʾ�ƶ������״
	             }
			  }break;
	     case  Add_Speed:
		       {
			       Key=Nothing;		  //��Ϣ�ѱ�����������
				   if(Game_Stop==1)
					{
					   if(Game_Level==0)
					   {
					      Game_Level=9;
						  Show_num(13,11,9);	 //��ʾ�ȼ�ˮƽ
						  Game_Speed=MIN_SLOW_SPEED/(Game_Level+1);  //����ˮƽȷ���ٶ�
						}
						else
						{
						   Game_Level--;
						   Show_num(13,11,Game_Level);	 //��ʾ�ȼ�ˮƽ
						   Game_Speed=MIN_SLOW_SPEED/(Game_Level+1);  //����ˮƽȷ���ٶ�
						}
					 }
					else
					{
				      Now_Speed=1;			   //����λ�ú󣬼����½�
				      DSpeed=Now_Speed;
					}
			   }break;
	     case  Change_Shape:
		        {
				    Key=Nothing;	   //��Ϣ�ѱ�����������
					if(Game_Stop==1)
					{
					   if(Game_Level==9)
					   {
					      Game_Level=0;
						  Show_num(13,11,0);	 //��ʾ�ȼ�ˮƽ
						  Game_Speed=MIN_SLOW_SPEED/(Game_Level+1);  //����ˮƽȷ���ٶ�
						}
						else
						{
						   Game_Level++;
						   Show_num(13,11,Game_Level);	 //��ʾ�ȼ�ˮƽ
						   Game_Speed=MIN_SLOW_SPEED/(Game_Level+1);  //����ˮƽȷ���ٶ�
						}
					 }
					else
					{

				       if(!Change_Shape_Anti())
				       {
				          Show_shape(xx,yy,This_shape,0); //ɾ����ǰ��״
			              This_shape=shape[This_shape].next;
				          Show_shape(xx,yy,This_shape,1); //��ʾ�仯�����״
				        }
					}
			    }break;
		case  Game_Star:
		      {
			     Key=Nothing;		  //��Ϣ�ѱ�����������
				 ClrGraphic();
				 Show_Image(35,15,94,114,0);
			     Init_GamePlatform();
				 Game_Stop=0;
			  }break;
		case  Game_Pause:
		      {
			     Key=Nothing;		  //��Ϣ�ѱ�����������
			     Game_Stop=!Game_Stop;
			  }
		default:Now_Speed=Game_Speed;
	  }
}



