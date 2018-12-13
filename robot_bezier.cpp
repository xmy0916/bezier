#include "stdio.h"
#include "math.h"
#include "assert.h"

#define input_num 8
#define num 100 
#define out_num num*(input_num-1)

/*
*���� 
*/ 
typedef struct
{
    float X;
    float Y;
} PointF;


PointF in[input_num] = {{0,1.5},{1.5,2.5},{3,0.5},{4,5},{6,7},{7,9},{6,0},{8,6}}; // �����
    

PointF out[out_num];    // ���������
    
PointF ctrl_points[input_num*2-4];//���Ƶ� 

PointF combine_points[4];
/*
*�������� 
*/
float dis_btw_points(PointF P1,PointF P2);//���������� 
void bezier_produce_ctrlpoints(PointF* points);//����·���Ͽ��Ƶ�����͸��� 
PointF bezier_interpolation_func(float t, PointF* points, int count);
void draw_bezier_curves(PointF* points, int count, PointF* out_points,int out_count,int start);
 
/*
*main 
*���ױ������ǰѶ��׵Ŀ��Ƶ����ɶ�̬�ģ����Կ����ö����������׵Ŀ��Ƶ� 
*/ 
int main(int argc, char **argv)
{
	bezier_produce_ctrlpoints(in);
	
	for(int j = 0;j<=(input_num-2);j++)
    	{
    		if(j==0)//��һ������ 
    		{
    			combine_points[0] = in [0];
    			combine_points[1] = ctrl_points[0];
    			combine_points[2] = in [1]; 
    			draw_bezier_curves(combine_points,3,out,num,0);// ���ױ���������
			}
			else if(j==input_num-2)
			{
				combine_points[0] = in [j];
    			combine_points[1] = ctrl_points[input_num*2-5];
    			combine_points[2] = in [j+1]; 
    			draw_bezier_curves(combine_points,3,out,num,num*input_num-2*num);// ���ױ���������
			}else 
			{
				combine_points[0] = in [j];
    			combine_points[1] = ctrl_points[2*j-1];
    			combine_points[2] = ctrl_points[2*j];
			    combine_points[3] = in [j+1];	
				draw_bezier_curves(combine_points,4,out,num,num*j);		
			}
				
		}
		
	//���´�ӡΪ�˸�matlab����m�ļ��ã����Ժ��ԣ��������out������ 
    printf("close all;\r\n");
    printf("x=[\r\n");
    for(int j=0; j<input_num; j++)    // ������Ƶ�x 
    {
		printf("%f ",in[j].X);
    }
    printf("];\r\n");
    printf("y=[\r\n");
    for(int j=0; j<input_num; j++)    // ������Ƶ�y 
    {
		printf("%f ",in[j].Y);
    }
    printf("];\r\n");
    
    printf("plot(x,y,':');\r\n");
    printf("hold on;\r\n");
    
    printf("x=[\r\n");
    for(int j=0; j<(input_num*2-4); j++)    // ������Ƶ�x 
    {
		printf("%f ",ctrl_points[j].X);		
    }
    printf("];\r\n");
    printf("y=[\r\n");
    for(int j=0; j<(input_num*2-4); j++)    // ������Ƶ�y 
    {
		printf("%f ",ctrl_points[j].Y);
    }
    printf("];\r\n");
    
    printf("plot(x,y,':');\r\n");
    printf("hold on;\r\n");
    printf("x=[\r\n");
    for(int j=0; j<out_num-2; j++)    // ���·����
    {
    	if(j!=0)
        	printf("%f ",out[j].X);
        if(j%10==0&&j!=0)
        	printf("\r\n");
    }
    printf("];\r\n");
    printf("y=[\r\n");
    for(int j=0; j<out_num-2; j++)    // ���·����
    {
    	if(j!=0)
        	printf("%f ",out[j].Y);
        if(j%10==0&&j!=0)
        	printf("\r\n");
    }
    printf("];\r\n");
	  
	printf("plot(x,y,'r');");

    return 0;
}

/*
*���� 
*/ 
PointF bezier_interpolation_func(float t, PointF* points, int count)
{
    assert(count>0);
 
    PointF tmp_points[count];
    for (int i = 1; i < count; ++i)
    {
        for (int j = 0; j < count - i; ++j)
        {
            if (i == 1)
            {
                tmp_points[j].X = (float)(points[j].X * (1 - t) + points[j + 1].X * t);
                tmp_points[j].Y = (float)(points[j].Y * (1 - t) + points[j + 1].Y * t);
                continue;
            }
            tmp_points[j].X = (float)(tmp_points[j].X * (1 - t) + tmp_points[j + 1].X * t);
            tmp_points[j].Y = (float)(tmp_points[j].Y * (1 - t) + tmp_points[j + 1].Y * t);
        }
    }
    return tmp_points[0];
}
 
void draw_bezier_curves(PointF* points, int count, PointF* out_points,int out_count,int start)
{
    float step = 1.0 / out_count;
    float t =0;
    for(int i=start; i<(start+out_count); i++)
    {
        PointF temp_point = bezier_interpolation_func(t, points, count);    // �����ֵ��
        t += step;
        out_points[i] = temp_point;
    }
}

float dis_btw_points(PointF P1,PointF P2)
{
	return sqrt((P1.X-P2.X)*(P1.X-P2.X)+(P1.Y-P2.Y)*(P1.Y-P2.Y));
}

void bezier_produce_ctrlpoints(PointF* points)//����·���Ͽ��Ƶ�����͸��� 
{
	PointF p1,p2,p3;
	float l1,l2;
	for(int i = 0;i < (input_num-2);i++)
	{
		p1.X = (points[i].X + points[i+1].X)/2;
		p1.Y = (points[i].Y + points[i+1].Y)/2;
		p2.X = (points[i+1].X + points[i+2].X)/2;
		p2.Y = (points[i+1].Y + points[i+2].Y)/2;//
		
		l1 = dis_btw_points(points[i],points[i+1]);
		l2 = dis_btw_points(points[i],points[i+1]);
		
		p3.X = (l1*p2.X+l2*p1.X)/(l1+l2);
		p3.Y = (l1*p2.Y+l2*p1.Y)/(l1+l2);
		
		ctrl_points[2*i].X = p1.X + points[i+1].X - p3.X;
		ctrl_points[2*i].Y = p1.Y + points[i+1].Y - p3.Y;
		ctrl_points[2*i+1].X = p2.X + points[i+1].X - p3.X;
		ctrl_points[2*i+1].Y = p2.Y + points[i+1].Y - p3.Y;
	}
	
}
