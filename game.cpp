#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include <graphics.h>
#include <conio.h>
#include<fstream>
#include<windows.h>
using namespace std;
int board[22][22],num[22][22];//棋盘 
int vis[22][22];//是否被点开 
int n,boom;//行列数与炸弹数  
int nb;//剩余雷数 
int nx,ny;//当前输入坐标 
int flag=1;//游戏是否结束 
int opt;//操作类型 
MOUSEMSG m;//鼠标
IMAGE img;
int timenow,timestart; 

void preinit();//预处理
void printboard();//显示棋盘
void getxy();//输入
void die();//死了
void survival();//活了
void dfs(int x,int y);//空格子则深搜
void anotherdfs(int x,int y);//双击时的深搜 
void check();
void play();
void save();//存盘
void reads();//读盘
void help();//帮助

void preinit()//预处理 
{
	char s1[10];
	InputBox(s1,10,"请选择棋盘大小(1-20)","选择棋盘与雷数","10",false);

	char s2[10];
	InputBox(s2,10,"请选择雷数","选择棋盘与雷数","10",false);

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

	srand(time(0));//重置随机数种子 
	for(int i=1;i<=boom;i++)//生成炸弹  
	{
		int x=rand()%n+1,y=rand()%n+1;
		while(board[x][y]) x=rand()%n+1,y=rand()%n+1;//如果已经有炸弹啦，就重新来一组随机数 
		board[x][y]=1;//放炸弹 
		
		num[x+1][y]++;
		num[x][y+1]++;
		num[x-1][y]++;
		num[x][y-1]++;
		num[x+1][y+1]++;
		num[x+1][y-1]++;
		num[x-1][y+1]++;
		num[x-1][y-1]++;//增加炸弹周围格子的数字 
	}		
}

void printboard()//显示棋盘
{
	int i,j;

	char a[] = "剩余雷数：";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(20, 20, a);

	char b[5];
	itoa(nb,b,10);
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(120, 20, b);

	char c[] = "TIME：";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(160, 20, c);
	
	setlinestyle(PS_DASHDOT);
	setlinecolor(BLUE);
	line(20*n+80 , 0 , 20*n+80 , 20*n+80);

	rectangle(20*n+130,60,20*n+230,100);
	char d[] = "存起来~";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(20*n+132, 70, d);

	rectangle(20*n+130,120,20*n+230,160);
	char e[] = "重新来吧~";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(20*n+140, 130, e);
	
	rectangle(20*n+130,180,20*n+230,220);
	char f[] = "我不玩了！";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(20*n+140, 190, f);
	
	rectangle(20*n+130,240,20*n+230,280);
	char g[] = "怎么玩呢~";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(20*n+140, 250, g);
	
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(vis[i][j]==1)//打开过的格子 
			{
				if(board[i][j] == 1)
				{
					setfillstyle(BS_SOLID);
	                setfillcolor(LIGHTRED);
			        fillroundrect(20*(j+1),20*(i+2),20*(j+1)+20,20*(i+2)+20,10,10);
				}//雷 
				else if(num[i][j]==0)
				{
					setfillstyle(BS_SOLID);
	                setfillcolor(LIGHTGRAY);
			        fillroundrect(20*(j+1),20*(i+2),20*(j+1)+20,20*(i+2)+20,10,10);
				}//四周没雷
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
			}//被标记的格子 
			else
			{
				setfillstyle(BS_SOLID);
	            setfillcolor(LIGHTBLUE);
			    fillroundrect(20*(j+1),20*(i+2),20*(j+1)+20,20*(i+2)+20,10,10);
			}//崭新的的格子啦啦啦
		}
	}
}


void getxy()//输入
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
		outtextxy(230, 20, t3);//到这里为止在输出时间
		
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
					if(m.x>=20*n+130 && m.x<=20*n+230 && m.y>=60 && m.y<=100)//保存
					{
						opt=3;
					}
					if(m.x>=20*n+130 && m.x<=20*n+230 && m.y>=120 && m.y<=160)//重新开始
					{
						opt=4;
					}
					if(m.x>=20*n+130 && m.x<=20*n+230 && m.y>=180 && m.y<=220)//退出
					{
						opt=5;
					}
					if(m.x>=20*n+130 && m.x<=20*n+230 && m.y>=240 && m.y<=280)//帮助
					{
						opt=6;
					}
					return;
				}
			}
		}
	}
}


void die()//死了 
{
	cleardevice();//清屏 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			vis[i][j]=1;//开全地图视野 
	printboard();
	
	char s[] = "你输了(╯3╰)";
	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(20*n+90, 10, s);
    
	flag=0;
	getxy();
	check();
}
void survival()//活了 
{
	cleardevice();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			vis[i][j]=1;//同样开全地图视野 
	printboard();
	
	char s[] = "你赢了~\(≧▽≦)/~";
	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(20*n+60, 10, s);
	
	flag=0;
	getxy();
	check();
}

void dfs(int x,int y)//空格子则深搜
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

void anotherdfs(int x,int y)//双击时的深搜
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
		if(board[nx][ny]) die();  //踩雷就死了
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
		preinit();//预处理

	    initgraph(20*n+280, 20*n+80);
	    setbkcolor(WHITE);
	    cleardevice();
	                
	    timestart=clock();//重设时间起点
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


	int tag=1;//是否胜利的标记 
	
	for(i=1;i<=n;i++)//判断是否通过把雷以外的格子全部打开而胜利 
		for(j=1;j<=n;j++)
			if(!board[i][j]&&!vis[i][j]) tag=0;
	if(tag) survival();
	tag=1;
	
	for(i=1;i<=n;i++)//判断是否通过恰好把雷全部标记而胜利 
		for(j=1;j<=n;j++)
			if((board[i][j]&&vis[i][j]!=2)||(!board[i][j]&&vis[i][j]==2))
				tag=0;
	if(tag) survival();	
}

void save()//存盘
{
	int i,j;
	ofstream fout; //定义输出到文件的流
    fout.open("save.txt"); //将该输出流与具体文件建立联系，这时，如果该文件不存在将被创建，如果已存在原有内容会被清空
    fout << n <<" "<< boom <<" "<< nb <<" "<< flag <<" "<<timenow<<endl;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			fout<<board[i][j]<<" "<<num[i][j]<<" "<<vis[i][j]<<endl;
    fout.close(); //关闭文件，保存到硬盘
}

void reads()//读盘
{
	int i,j;
	ifstream fin; //定义从文件输入的流
    fin.open("save.txt"); //建立联系
    fin >> n >> boom >> nb >> flag >> timenow;//有如cin，遇到空格和回车就读取完毕，读取不了空格和回车
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			fin>>board[i][j]>>num[i][j]>>vis[i][j];
    fin.close(); //关闭文件
}

void help()//帮助
{
	initgraph(500, 500);
	setbkcolor(WHITE);
	cleardevice();
	
	char a[] = "    扫雷是一款相当大众的小游戏，游戏目标是在最短";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 50, a);
	char b[] = "的时间内根据点击格子出现的数字找出所有非雷格子，";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 80, b);
	char c[] = "同时避免踩雷。";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 110, c);
	char d[] = "    游戏区包括雷区、地雷计数器（位于左上角，记录";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 140, d);
	char e[] = "剩余地雷数）和计时器（位于右上角，记录游戏时间）,";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 170, e);
	char f[] = "确定大小的方形雷区中随机布置一定数量的地雷，玩家";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 200, f);
	char g[] = "可以自己设定雷区大小和雷数，玩家需要尽快找出雷区";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 230, g);
	char h[] = "中的所有不是地雷的方块，而不许踩到地雷。";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 260, h);
	char i[] = "    游戏的基本操作包括左键单击、左键双击、右键单";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 290, i);
	char j[] = "击两三种。其中左键用于打开安全的格子，推进游戏进";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 320, j);
	char k[] = "度；右键用于标记地雷，以辅助判断，第一次右击为标";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 350, k);
	char l[] = "记，再次对相同方块右击为取消标记。";
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(10, 380, l);

	setlinestyle(PS_DASHDOT);
	setlinecolor(BLUE);
	rectangle(350,410,450,450);
	char o[] = "开始玩~";
	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
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
					preinit();//预处理

	                initgraph(20*n+280, 20*n+80);
	                setbkcolor(WHITE);
	                cleardevice();
	                
					timestart=clock();//重设时间起点
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
		printboard();//显示棋盘
		getxy(); //输入
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
	char a[] = "开   始";
	settextcolor(WHITE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(800, 260, a);

	setfillstyle(BS_SOLID);
	setfillcolor(LIGHTBLUE);
	fillellipse(750,350,950,400);
	char b[] = "继续上次游戏";
	settextcolor(WHITE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(760, 360, b);

	setfillstyle(BS_SOLID);
	setfillcolor(LIGHTBLUE);
	fillellipse(750,450,950,500);
	char c[] = "帮   助";
	settextcolor(WHITE);
	settextstyle(30, 0, _T("黑体"));
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
				    preinit();//预处理

	                initgraph(20*n+280, 20*n+80);
	                setbkcolor(WHITE);
	                cleardevice();
	                
					timestart=clock();//重设时间起点
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


