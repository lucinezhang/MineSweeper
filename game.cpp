#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include <graphics.h>
#include <conio.h>
#include<fstream>
#include<windows.h>
using namespace std;
int board[22][22],num[22][22];//���� 
int vis[22][22];//�Ƿ񱻵㿪 
int n,boom;//��������ը����  
int nb;//ʣ������ 
int nx,ny;//��ǰ�������� 
int flag=1;//��Ϸ�Ƿ���� 
int opt;//�������� 
MOUSEMSG m;//���
IMAGE img;
int timenow,timestart; 

void preinit();//Ԥ����
void printboard();//��ʾ����
void getxy();//����
void die();//����
void survival();//����
void dfs(int x,int y);//�ո���������
void anotherdfs(int x,int y);//˫��ʱ������ 
void check();
void play();
void save();//����
void reads();//����
void help();//����

void preinit()//Ԥ���� 
{
	char s1[10];
	InputBox(s1,10,"��ѡ�����̴�С(1-20)","ѡ������������","10",false);

	char s2[10];
	InputBox(s2,10,"��ѡ������","ѡ������������","10",false);

	n=atoi(s1);
	boom=atoi(s2);
	nb=boom;

	for(int j=0;j<22;j++)
	{
		for(int k=0;k<22;k++)
		{
			board[j][k]=0;
	        num[j][k]=0;
	        vis[j][k]=0;
		}
	}

	srand(time(0));//������������� 
	for(int i=1;i<=boom;i++)//����ը��  
	{
		int x=rand()%n+1,y=rand()%n+1;
		while(board[x][y]) x=rand()%n+1,y=rand()%n+1;//����Ѿ���ը��������������һ������� 
		board[x][y]=1;//��ը�� 
		
		num[x+1][y]++;
		num[x][y+1]++;
		num[x-1][y]++;
		num[x][y-1]++;
		num[x+1][y+1]++;
		num[x+1][y-1]++;
		num[x-1][y+1]++;
		num[x-1][y-1]++;//����ը����Χ���ӵ����� 
	}		
}

void printboard()//��ʾ����
{
	int i,j;

	char a[] = "ʣ��������";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(20, 20, a);

	char b[5];
	itoa(nb,b,10);
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(120, 20, b);

	char c[] = "TIME��";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(160, 20, c);
	
	setlinestyle(PS_DASHDOT);
	setlinecolor(BLUE);
	line(20*n+80 , 0 , 20*n+80 , 20*n+80);

	rectangle(20*n+130,60,20*n+230,100);
	char d[] = "������~";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(20*n+132, 70, d);

	rectangle(20*n+130,120,20*n+230,160);
	char e[] = "��������~";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(20*n+140, 130, e);
	
	rectangle(20*n+130,180,20*n+230,220);
	char f[] = "�Ҳ����ˣ�";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(20*n+140, 190, f);
	
	rectangle(20*n+130,240,20*n+230,280);
	char g[] = "��ô����~";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(20*n+140, 250, g);
	
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(vis[i][j]==1)//�򿪹��ĸ��� 
			{
				if(board[i][j] == 1)
				{
					setfillstyle(BS_SOLID);
	                setfillcolor(LIGHTRED);
			        fillroundrect(20*(j+1),20*(i+2),20*(j+1)+20,20*(i+2)+20,10,10);
				}//�� 
				else if(num[i][j]==0)
				{
					setfillstyle(BS_SOLID);
	                setfillcolor(LIGHTGRAY);
			        fillroundrect(20*(j+1),20*(i+2),20*(j+1)+20,20*(i+2)+20,10,10);
				}//����û��
				else
				{
					switch(num[i][j])
					{
					case 1:
						loadimage(&img,"1.jpg");
					    putimage(20*(j+1),20*(i+2),20,20, &img,0,0);
						break;
					case 2:
						loadimage(&img,"2.jpg");
					    putimage(20*(j+1),20*(i+2),20,20, &img,0,0);
						break;
					case 3:
						loadimage(&img,"3.jpg");
					    putimage(20*(j+1),20*(i+2),20,20, &img,0,0);
						break;
					case 4:
						loadimage(&img,"4.jpg");
					    putimage(20*(j+1),20*(i+2),20,20, &img,0,0);
						break;
					case 5:
						loadimage(&img,"5.jpg");
					    putimage(20*(j+1),20*(i+2),20,20, &img,0,0);
						break;
					case 6:
						loadimage(&img,"6.jpg");
					    putimage(20*(j+1),20*(i+2),20,20, &img,0,0);
						break;
					case 7:
						loadimage(&img,"7.jpg");
					    putimage(20*(j+1),20*(i+2),20,20, &img,0,0);
						break;
					case 8:
						loadimage(&img,"8.jpg");
					    putimage(20*(j+1),20*(i+2),20,20, &img,0,0);
						break;
					}
				}
			}
			else if(vis[i][j]==2)
			{
				loadimage(&img,"flag.jpg");
			    putimage(20*(j+1),20*(i+2),20,20, &img,0,0);
			}//����ǵĸ��� 
			else
			{
				setfillstyle(BS_SOLID);
	            setfillcolor(LIGHTBLUE);
			    fillroundrect(20*(j+1),20*(i+2),20*(j+1)+20,20*(i+2)+20,10,10);
			}//ո�µĵĸ���������
		}
	}
}


void getxy()//����
{
	
	char t1, t2, t3;
	settextcolor(BLUE);
	MOUSEMSG tmp;
	while(true)
	{
		timenow = (clock()-timestart) / 1000;
		t1 = char(timenow / 100 + 48);
		timenow = timenow % 100;
		t2 = char(timenow / 10 + 48);
		t3 = char(timenow % 10 + 48);
		outtextxy(210, 20, t1);
		outtextxy(220, 20, t2);
		outtextxy(230, 20, t3);//������Ϊֹ�����ʱ��
		
		if (MouseHit())
		{
		    m = GetMouseMsg();
		    if(m.x>=40 && m.x<=20*n+40 && m.y>=60 && m.y<=20*n+60)
			{
			    switch (m.uMsg)
				{
			    case WM_MOUSEMOVE:
					break;
				case WM_LBUTTONDOWN:
					nx = (m.y - 40)/ 20;
                    ny = (m.x - 20)/ 20;
				    opt=1;
				    return;	
			    case WM_RBUTTONDOWN:
					nx = (m.y - 40)/ 20;
                    ny = (m.x - 20)/ 20;
				    opt=2;
				    return;
				case WM_LBUTTONDBLCLK:
					nx = (m.y - 40)/ 20;
                    ny = (m.x - 20)/ 20;
				    opt=7;
					return;
				}
			}
		    if(!(m.x>=40 && m.x<=20*n+40 && m.y>=60 && m.y<=20*n+60))
			{
			    switch(m.uMsg)
				{
				case WM_MOUSEMOVE:
					break;
				case WM_LBUTTONDOWN:
					if(m.x>=20*n+130 && m.x<=20*n+230 && m.y>=60 && m.y<=100)//����
					{
						opt=3;
					}
					if(m.x>=20*n+130 && m.x<=20*n+230 && m.y>=120 && m.y<=160)//���¿�ʼ
					{
						opt=4;
					}
					if(m.x>=20*n+130 && m.x<=20*n+230 && m.y>=180 && m.y<=220)//�˳�
					{
						opt=5;
					}
					if(m.x>=20*n+130 && m.x<=20*n+230 && m.y>=240 && m.y<=280)//����
					{
						opt=6;
					}
					return;
				}
			}
		}
	}
}


void die()//���� 
{
	cleardevice();//���� 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			vis[i][j]=1;//��ȫ��ͼ��Ұ 
	printboard();
	
	char s[] = "������(�s3�t)";
	settextcolor(BLUE);
	settextstyle(30, 0, _T("����"));
	outtextxy(20*n+90, 10, s);
    
	flag=0;
	getxy();
	check();
}
void survival()//���� 
{
	cleardevice();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			vis[i][j]=1;//ͬ����ȫ��ͼ��Ұ 
	printboard();
	
	char s[] = "��Ӯ��~\(�R���Q)/~";
	settextcolor(BLUE);
	settextstyle(30, 0, _T("����"));
	outtextxy(20*n+60, 10, s);
	
	flag=0;
	getxy();
	check();
}

void dfs(int x,int y)//�ո���������
{                                           
	if(board[x][y]||vis[x][y]) return;
	vis[x][y]=1;
	if(num[x][y]) return;
	if(x>1) dfs(x-1,y);
	if(x<n) dfs(x+1,y);
	if(y>1) dfs(x,y-1);
	if(y<n) dfs(x,y+1);
	if(x>1&&y>1) dfs(x-1,y-1);
	if(x<n&&y>1) dfs(x+1,y-1);
	if(x>1&&y<n) dfs(x-1,y+1);
	if(x<n&&y<n) dfs(x+1,y+1);
}

void anotherdfs(int x,int y)//˫��ʱ������
{
	if(board[x][y])
	{
		die();
		return;
	}
	vis[x][y]=1;
	if(num[x][y]) return;
	if(x>1) dfs(x-1,y);
	if(x<n) dfs(x+1,y);
	if(y>1) dfs(x,y-1);
	if(y<n) dfs(x,y+1);
	if(x>1&&y>1) dfs(x-1,y-1);
	if(x<n&&y>1) dfs(x+1,y-1);
	if(x>1&&y<n) dfs(x-1,y+1);
	if(x<n&&y<n) dfs(x+1,y+1);
}



void check()
{
	int i,j;
	if(opt==1)
	{
		if(board[nx][ny]) die();  //���׾�����
		else dfs(nx,ny);
	}
	else if(opt==2)
	{
		if(vis[nx][ny]==2)
		{
			vis[nx][ny]=0;
			nb++;
		}
		else if(vis[nx][ny]==0)
		{
			vis[nx][ny]=2;
			nb--;
		}
	}
	else if(opt==3)
	{
		save();
		return;
	}
	else if(opt==4)
	{
		cleardevice();
		flag=1;
		closegraph();
		preinit();//Ԥ����

	    initgraph(20*n+280, 20*n+80);
	    setbkcolor(WHITE);
	    cleardevice();
	                
	    timestart=clock();//����ʱ�����
		play();
		return;
	}
	else if(opt==5)
	{
		flag=0;
		return;
	}
	else if(opt==6)
	{
		help();
		return;
	}
	else if(opt==7)
	{
		if(vis[nx][ny]==1)
		{
			int count=0;
			if(vis[nx-1][ny-1]==2) count++;
			if(vis[nx][ny-1]==2) count++;
			if(vis[nx+1][ny-1]==2) count++;
			if(vis[nx-1][ny]==2) count++;
			if(vis[nx+1][ny]==2) count++;
			if(vis[nx-1][ny+1]==2) count++;
			if(vis[nx][ny+1]==2) count++;
			if(vis[nx+1][ny+1]==2) count++;
			if(count==num[nx][ny])
			{
				if(vis[nx-1][ny-1]==0) anotherdfs(nx-1,ny-1);
			    if(vis[nx][ny-1]==0) anotherdfs(nx,ny-1);
			    if(vis[nx+1][ny-1]==0) anotherdfs(nx+1,ny-1);
			    if(vis[nx-1][ny]==0) anotherdfs(nx-1,ny);
			    if(vis[nx+1][ny]==0) anotherdfs(nx+1,ny);
			    if(vis[nx-1][ny+1]==0) anotherdfs(nx-1,ny+1);
			    if(vis[nx][ny+1]==0) anotherdfs(nx,ny+1);
			    if(vis[nx+1][ny+1]==0) anotherdfs(nx+1,ny+1);
			}	
		}
		return;
	}


	int tag=1;//�Ƿ�ʤ���ı�� 
	
	for(i=1;i<=n;i++)//�ж��Ƿ�ͨ����������ĸ���ȫ���򿪶�ʤ�� 
		for(j=1;j<=n;j++)
			if(!board[i][j]&&!vis[i][j]) tag=0;
	if(tag) survival();
	tag=1;
	
	for(i=1;i<=n;i++)//�ж��Ƿ�ͨ��ǡ�ð���ȫ����Ƕ�ʤ�� 
		for(j=1;j<=n;j++)
			if((board[i][j]&&vis[i][j]!=2)||(!board[i][j]&&vis[i][j]==2))
				tag=0;
	if(tag) survival();	
}

void save()//����
{
	int i,j;
	ofstream fout; //����������ļ�����
    fout.open("save.txt"); //���������������ļ�������ϵ����ʱ��������ļ������ڽ�������������Ѵ���ԭ�����ݻᱻ���
    fout << n <<" "<< boom <<" "<< nb <<" "<< flag <<" "<<timenow<<endl;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			fout<<board[i][j]<<" "<<num[i][j]<<" "<<vis[i][j]<<endl;
    fout.close(); //�ر��ļ������浽Ӳ��
}

void reads()//����
{
	int i,j;
	ifstream fin; //������ļ��������
    fin.open("save.txt"); //������ϵ
    fin >> n >> boom >> nb >> flag >> timenow;//����cin�������ո�ͻس��Ͷ�ȡ��ϣ���ȡ���˿ո�ͻس�
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			fin>>board[i][j]>>num[i][j]>>vis[i][j];
    fin.close(); //�ر��ļ�
}

void help()//����
{
	initgraph(500, 500);
	setbkcolor(WHITE);
	cleardevice();
	
	char a[] = "    ɨ����һ���൱���ڵ�С��Ϸ����ϷĿ���������";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 50, a);
	char b[] = "��ʱ���ڸ��ݵ�����ӳ��ֵ������ҳ����з��׸��ӣ�";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 80, b);
	char c[] = "ͬʱ������ס�";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 110, c);
	char d[] = "    ��Ϸ���������������׼�������λ�����Ͻǣ���¼";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 140, d);
	char e[] = "ʣ����������ͼ�ʱ����λ�����Ͻǣ���¼��Ϸʱ�䣩,";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 170, e);
	char f[] = "ȷ����С�ķ����������������һ�������ĵ��ף����";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 200, f);
	char g[] = "�����Լ��趨������С�������������Ҫ�����ҳ�����";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 230, g);
	char h[] = "�е����в��ǵ��׵ķ��飬������ȵ����ס�";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 260, h);
	char i[] = "    ��Ϸ�Ļ�����������������������˫�����Ҽ���";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 290, i);
	char j[] = "�������֡�����������ڴ򿪰�ȫ�ĸ��ӣ��ƽ���Ϸ��";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 320, j);
	char k[] = "�ȣ��Ҽ����ڱ�ǵ��ף��Ը����жϣ���һ���һ�Ϊ��";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 350, k);
	char l[] = "�ǣ��ٴζ���ͬ�����һ�Ϊȡ����ǡ�";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("����"));
	outtextxy(10, 380, l);

	setlinestyle(PS_DASHDOT);
	setlinecolor(BLUE);
	rectangle(350,410,450,450);
	char o[] = "��ʼ��~";
	settextcolor(BLUE);
	settextstyle(30, 0, _T("����"));
	outtextxy(360,420, o);

	while(true)
	{
		m = GetMouseMsg();
		switch(m.uMsg)
		{
		    case WM_MOUSEMOVE:
				putpixel(m.x, m.y, LIGHTBLUE);
			    break;
		    case WM_LBUTTONDOWN:
				if(m.x>=350&&m.x<=450&&m.y>=410&&m.y<=450)
				{
					closegraph();
					preinit();//Ԥ����

	                initgraph(20*n+280, 20*n+80);
	                setbkcolor(WHITE);
	                cleardevice();
	                
					timestart=clock();//����ʱ�����
					play();
					return;
				}
		}
	}	
}

void play()
{
	while(flag)
	{
		printboard();//��ʾ����
		getxy(); //����
		check();
		if(flag) cleardevice(); 
	}
	closegraph();
	return;
}

int main()
{
	initgraph(990, 556);
	loadimage(NULL, "picture.jpg");
	
	setfillstyle(BS_SOLID);
	setfillcolor(LIGHTBLUE);
	fillellipse(750,250,950,300);
	char a[] = "��   ʼ";
	settextcolor(WHITE);
	settextstyle(30, 0, _T("����"));
	outtextxy(800, 260, a);

	setfillstyle(BS_SOLID);
	setfillcolor(LIGHTBLUE);
	fillellipse(750,350,950,400);
	char b[] = "�����ϴ���Ϸ";
	settextcolor(WHITE);
	settextstyle(30, 0, _T("����"));
	outtextxy(760, 360, b);

	setfillstyle(BS_SOLID);
	setfillcolor(LIGHTBLUE);
	fillellipse(750,450,950,500);
	char c[] = "��   ��";
	settextcolor(WHITE);
	settextstyle(30, 0, _T("����"));
	outtextxy(800, 460, c);

	while(true)
	{
		m = GetMouseMsg();
		switch(m.uMsg)
		{
		    case WM_MOUSEMOVE:
				putpixel(m.x, m.y, WHITE);
			    break;
		    case WM_LBUTTONDOWN:
			    if (m.x>=750&&m.x<=950&&m.y>=250&&m.y<=300)
				{
					closegraph();
				    preinit();//Ԥ����

	                initgraph(20*n+280, 20*n+80);
	                setbkcolor(WHITE);
	                cleardevice();
	                
					timestart=clock();//����ʱ�����
					play();
				}
				else if(m.x>=750&&m.x<=950&&m.y>=350&&m.y<=400)
				{
					closegraph();
					reads();
					
					initgraph(20*n+280, 20*n+80);
	                setbkcolor(WHITE);
	                cleardevice();
					
					timestart=clock()-timenow*1000;
					play();
				}
				else if(m.x>=750&&m.x<=950&&m.y>=450&&m.y<=500)
				{
					closegraph();
					help();
				}
				break;
		}
	}
	return 0;
}


