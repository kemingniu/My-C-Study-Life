//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//#include<Windows.h>
//
//#define log  "□"
//
//#define INIT_X 10
//#define	INIT_Y 8
//
//enum STATE
//{
//	OK,
//	KILL_BY_WALL,
//	KILL_BY_SELF,
//	KILL_NORMAL
//};
//enum Dir
//{
//	UP,
//	DOWN,
//	LEFT,
//	RIGHT
//};
//typedef struct SnackNode
//{
//	int x;
//	int y;
//	struct SnackNode* _next;
//}SnackNode,*PSnackNode;
//
//typedef struct Snack
//{
//	PSnackNode _PSnack;//snack
//	PSnackNode _PFood; //food
//	enum STATE _state;  //state
//	enum Dir _dir;
//	int _sleeptime;
//}Snack,*PSnack;
//
//void SetPos(int x,int y)
//{
//	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD pos;
//	pos.X = x;
//	pos.Y = y;
//	SetConsoleCursorPosition(handle,pos);
//}
//
//void CreateMap()
//{
//	int i;
//	system("mode con cols=100 lines=30");
//	for( i = 0;i <= 56;i+=2)
//	{
//		SetPos(i,0);
//		printf(log);
//		SetPos(i,26);
//		printf(log);
//	}
//	for( i = 1;i < 26; i++)
//	{
//		SetPos(0,i);
//		printf(log);
//		SetPos(56,i);
//		printf(log);
//	}
//}
//
//
//
//CreateSnack(PSnack ps)
//{
//	int i;
//	PSnackNode cur = malloc(sizeof(SnackNode));
//	cur->x = INIT_X;
//	cur->y = INIT_Y;
//	cur->_next = NULL;
//
//	
//	for( i= 1;i <=4; i++)
//	{
//		ps->_PSnack = malloc(sizeof(SnackNode));
//		ps->_PSnack->_next = cur;
//		ps->_PSnack->x = INIT_X+i*2;
//		ps->_PSnack->y = INIT_Y;
//
//		cur = ps->_PSnack;
//	}
//
//	while(cur != NULL)
//	{
//		SetPos(cur->x,cur->y);
//		printf(log);
//		cur=cur->_next;
//	}
//	ps->_state = OK;
//	ps->_sleeptime = 500;
//	ps->_dir = RIGHT;
//}
//
//void CreateFood(PSnack ps)
//{
//	PSnackNode cur = NULL;
//	PSnackNode pfood = malloc(sizeof(PSnackNode));
//again:
//	do{
//    pfood->x = rand()%53 + 2;
//	}while(pfood->x % 2 != 0);
//	pfood->y = rand()%25 + 1;  //bunengcuowei
//
//	cur = ps->_PSnack;
//	while(cur != NULL)
//	{
//		if(cur->x == pfood->x && cur->y == pfood->y)
//		
//                goto again;
//				cur = cur->_next;
//		
//	}
//
//	SetPos(pfood->x,pfood->y);
//	printf(log);
//	ps->_PFood = pfood;
//
//}
//
//void welcome()
//{
//	SetPos(10,8);
//	printf("left");
//}
//
//int HasFood(PSnackNode psn,PSnack ps)
//{
//	return psn->x == ps->_PFood->x && psn->y == ps->_PFood->y;
//}
//void EatFood(PSnackNode psn,PSnack ps)
//{
//	PSnackNode  cur = ps->_PSnack;
//	psn->_next = cur;
//	ps->_PSnack = psn;
//	cur = psn;
//
//	while(cur != NULL)
//	{
//		SetPos(cur->x,cur->y);
//		printf(log);
//		cur = cur->_next;
//	}
//	CreateFood(ps);
//}
//void NoFood(PSnackNode psn,PSnack ps)
//{
//	PSnackNode  cur = ps->_PSnack;
//	psn->_next = cur;
//	ps->_PSnack = psn;
//	cur = psn;
//
//	while(cur->_next->_next != NULL)
//	{
//		SetPos(cur->x,cur->y);
//		printf(log);
//		cur = cur->_next;
//	}
//	SetPos(cur->_next->x,cur->_next->y);
//	printf(" ");
//	free(cur->_next);
//	cur->_next = NULL;
//}
//
//void SnackMove(PSnack ps)
//{
//	PSnackNode nextNode = malloc(sizeof(SnackNode));
//	nextNode->x = ps->_PSnack->x;
//	nextNode->y = ps->_PSnack->y;
//switch (ps->_dir)
//{
//case UP:
//	 	 nextNode->y -= 1;
//	break;
//case DOWN:
//		 nextNode->y +=1;
//	break;
//case LEFT:
//		 nextNode->x -= 2;
//	break;
//case RIGHT:
//		 nextNode->x +=2;
//	break;
//default:
//	break;
//}
//
//	if(HasFood(nextNode,ps))
//	EatFood(nextNode,ps);
//	else
//	NoFood(nextNode,ps);
//}
//
//void KillBySelf(PSnack ps)
//{
//	PSnackNode cur = ps->_PSnack->_next;
//	while(cur != NULL)
//	{
//		if(cur->x == ps->_PSnack->x && 
//			cur->y == ps->_PSnack->y)
//		{
//			ps->_state =  KILL_BY_SELF;
//			break;
//		}
//		cur = cur->_next;
//	}
//
//}
//void KillByWall(PSnack ps)
//{
//	if(ps->_PSnack->x == 0 || ps->_PSnack->x == 56 || ps->_PSnack->y == 0||ps->_PSnack->y == 26 )
//		ps->_state = KILL_BY_WALL;
//}
////系统提供的按键非阻塞式。
////GetAsyncKeyState(int vkey);按键返回1，
//
//void SnackRun(PSnack ps)
//{
//	do 
//	{
//		if(GetAsyncKeyState(VK_UP) && ps->_dir != DOWN)
//			ps->_dir = UP;
//		else if(GetAsyncKeyState(VK_DOWN) && ps->_dir != UP)
//			ps->_dir = DOWN;
//		else if(GetAsyncKeyState(VK_RIGHT) && ps->_dir != LEFT)
//			ps->_dir = RIGHT;
//		else if(GetAsyncKeyState(VK_LEFT) && ps->_dir != RIGHT)
//			ps->_dir = LEFT;
//		SnackMove(ps);
//		KillBySelf(ps);
//        KillByWall(ps);
//		Sleep(ps->_sleeptime);
//	} while (ps->_state == OK);
//
//	switch(ps->_state)
//	{
//	case KILL_BY_SELF:
//		printf("ziji zhuangshang ziji le \n");
//		break;
//	case KILL_BY_WALL:
//		printf("zhuangqiang ersi \n");
//		break;
//	default:
//		break;
//	}
//}
//
//
//void Start(PSnack ps)
//{
//	//Snack s;
//	srand(time(NULL));
//	CreateMap();
//
//	CreateSnack(ps);
//	CreateFood(ps);
//	printf("\n");
//}
//
//
//
//int main()
//{
//	Snack s;
//    Start(&s);
//	/*do 
//	{
//		SnackMove(&s);
//		Sleep(500);
//	} while (1);*/
//
//	SnackRun(&s);
//	return 0;
//
//}

#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>

#define U 1
#define D 2
#define L 3 
#define R 4 //蛇的状态，U：上 ；D：下；L:左 R：右

typedef struct SNAKE //蛇身的一个节点
{
	int x;
	int y;
	struct SNAKE *next;
}snake;

//全局变量//
int score=0,add=10;//总得分与每次吃食物得分。
int status,sleeptime=200;//每次运行的时间间隔
snake *head, *food;//蛇头指针，食物指针
snake *q;//遍历蛇的时候用到的指针
int endgamestatus=0; //游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。

//声明全部函数//
void Pos();
void creatMap();
void initsnake();
int biteself();
void createfood();
void cantcrosswall();
void snakemove();
void pause();
void gamecircle();
void welcometogame();
void endgame();
void gamestart();

void Pos(int x,int y)//设置光标位置
{
	COORD pos;
	HANDLE hOutput;
	pos.X=x;
	pos.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,pos);
}

void creatMap()//创建地图
{
	int i;
	for(i=0;i<58;i+=2)//打印上下边框
	{
		Pos(i,0);
		printf("■");
		Pos(i,26);
		printf("■");
	}
	for(i=1;i<26;i++)//打印左右边框
	{
		Pos(0,i);
		printf("■"); 
		Pos(56,i);
		printf("■"); 
	}
}

void initsnake()//初始化蛇身
{
	snake *tail;
	int i;
	tail=(snake*)malloc(sizeof(snake));//从蛇尾开始，头插法，以x,y设定开始的位置//
	tail->x=24;
	tail->y=5;
	tail->next=NULL;
	for(i=1;i<=4;i++)
	{
		head=(snake*)malloc(sizeof(snake));
		head->next=tail;
		head->x=24+2*i;
		head->y=5;
		tail=head;
	}
	while(tail!=NULL)//从头到为，输出蛇身
	{
		Pos(tail->x,tail->y);
		printf("■");
		tail=tail->next;
	}
}

int biteself()//判断是否咬到了自己
{
	snake *self;
	self=head->next;
	while(self!=NULL)
	{
		if(self->x==head->x && self->y==head->y)
		{
			return 1;
		}
		self=self->next;
	}
	return 0;
}

void createfood()//随机出现食物
{
	snake *food_1;
	srand((unsigned)time(NULL));
	food_1=(snake*)malloc(sizeof(snake));
	while((food_1->x%2)!=0) //保证其为偶数，使得食物能与蛇头对其
	{
		food_1->x=rand()%52+2;
	}
	food_1->y=rand()%24+1;
	q=head;
	while(q->next==NULL)
	{
		if(q->x==food_1->x && q->y==food_1->y) //判断蛇身是否与食物重合
		{
			free(food_1);
			createfood();
		}
		q=q->next;
	}
	Pos(food_1->x,food_1->y);
	food=food_1;
	printf("■");
}

void cantcrosswall()//不能穿墙
{ 
	if(head->x==0 || head->x==56 ||head->y==0 || head->y==26)
	{
		endgamestatus=1;
		endgame();
	}
}

void snakemove()//蛇前进,上U,下D,左L,右R
{
	snake * nexthead;
	cantcrosswall();

	nexthead=(snake*)malloc(sizeof(snake));
	if(status==U)  //up
	{
		nexthead->x=head->x;
		nexthead->y=head->y-1;
		if(nexthead->x==food->x && nexthead->y==food->y)//如果下一个有食物//
		{
			nexthead->next=head;
			head=nexthead;
			q=head;
			while(q!=NULL)
			{
				Pos(q->x,q->y);
				printf("■");
				q=q->next;
			}
			score=score+add;
			createfood();
		}
		else //如果没有食物//
		{
			nexthead->next=head;
			head=nexthead;
			q=head;
			while(q->next->next!=NULL)///
			{
				Pos(q->x,q->y);
				printf("■");
				q=q->next; 
			}
			Pos(q->next->x,q->next->y);
			printf(" ");
			free(q->next);
			q->next=NULL;
		}
	}
	if(status==D)  //down
	{
		nexthead->x=head->x;
		nexthead->y=head->y+1;
		if(nexthead->x==food->x && nexthead->y==food->y) //有食物
		{
			nexthead->next=head;
			head=nexthead;
			q=head;
			while(q!=NULL)
			{
				Pos(q->x,q->y);
				printf("■");
				q=q->next;
			}
			score=score+add;
			createfood();
		}
		else //没有食物
		{
			nexthead->next=head;
			head=nexthead;
			q=head;
			while(q->next->next!=NULL)
			{
				Pos(q->x,q->y);
				printf("■");
				q=q->next; 
			}
			Pos(q->next->x,q->next->y);
			printf(" ");
			free(q->next);
			q->next=NULL;
		}
	}
	if(status==L)   //left
	{
		nexthead->x=head->x-2;
		nexthead->y=head->y;
		if(nexthead->x==food->x && nexthead->y==food->y)//有食物
		{
			nexthead->next=head;
			head=nexthead;
			q=head;
			while(q!=NULL)
			{
				Pos(q->x,q->y);
				printf("■");
				q=q->next;
			}
			score=score+add;
			createfood();
		}
		else //没有食物
		{
			nexthead->next=head;
			head=nexthead;
			q=head;
			while(q->next->next!=NULL)
			{
				Pos(q->x,q->y);
				printf("■");
				q=q->next; 
			}
			Pos(q->next->x,q->next->y);
			printf(" ");
			free(q->next);
			q->next=NULL;
		}
	}
	if(status==R) //right
	{
		nexthead->x=head->x+2;
		nexthead->y=head->y;
		if(nexthead->x==food->x && nexthead->y==food->y)//有食物
		{
			nexthead->next=head;
			head=nexthead;
			q=head;
			while(q!=NULL)
			{
				Pos(q->x,q->y);
				printf("■");
				q=q->next;
			}
			score=score+add;
			createfood();
		}
		else //没有食物
		{
			nexthead->next=head;
			head=nexthead;
			q=head;
			while(q->next->next!=NULL)
			{
				Pos(q->x,q->y);
				printf("■");
				q=q->next; 
			}
			Pos(q->next->x,q->next->y);
			printf(" ");
			free(q->next);
			q->next=NULL;
		}
	}
	if(biteself()==1) //判断是否会咬到自己
	{
		endgamestatus=2;
		endgame();
	}
}

void pause()//暂停
{
	while(1)
	{
		Sleep(300);
		if(GetAsyncKeyState(VK_SPACE))
		{
			break;
		}

	}
}

void gamecircle()//控制游戏 
{

	Pos(64,15);
	printf("不能穿墙，不能咬到自己\n");
	Pos(64,16);
	printf("用↑.↓.←.→分别控制蛇的移动.");
	Pos(64,17);
	printf("F1 为加速，F2 为减速\n");
	Pos(64,18);
	printf("ESC ：退出游戏.space：暂停游戏.");
	//Pos(64,20);
	//printf("c语言研究中心 www.dotcpp.com");
	status=R;
	while(1)
	{ 
		Pos(64,10);
		printf("得分：%d ",score);
		Pos(64,11);
		printf("每个食物得分：%d分",add);
		if(GetAsyncKeyState(VK_UP) && status!=D)
		{
			status=U;
		}
		else if(GetAsyncKeyState(VK_DOWN) && status!=U)
		{
			status=D;
		}
		else if(GetAsyncKeyState(VK_LEFT)&& status!=R)
		{
			status=L;
		}
		else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)
		{
			status=R;
		}
		else if(GetAsyncKeyState(VK_SPACE))
		{
			pause();
		}
		else if(GetAsyncKeyState(VK_ESCAPE))
		{
			endgamestatus=3;
			break;
		}
		else if(GetAsyncKeyState(VK_F1))
		{
			if(sleeptime>=50)
			{
				sleeptime=sleeptime-30;
				add=add+2;
				if(sleeptime==320)
				{
					add=2;//防止减到1之后再加回来有错
				}
			}
		}
		else if(GetAsyncKeyState(VK_F2))
		{
			if(sleeptime<350)
			{
				sleeptime=sleeptime+30;
				add=add-2;
				if(sleeptime==350)
				{
					add=1; //保证最低分为1
				}
			}
		}
		Sleep(sleeptime);
		snakemove();
	}
}

void welcometogame()//开始界面
{
	Pos(40,12);

	system("title xiaoke pie");
	printf("欢迎来到贪食蛇游戏！");
	Pos(40,25);
	system("pause");
	system("cls");
	Pos(25,12);
	printf("用↑.↓.←.→分别控制蛇的移动， F1 为加速，2 为减速\n");
	Pos(25,13);
	printf("加速将能得到更高的分数。\n");
	system("pause");
	system("cls");
}

void endgame()//结束游戏
{

	system("cls");
	Pos(24,12);
	if(endgamestatus==1)
	{
		printf("对不起，您撞到墙了。游戏结束.");
	}
	else if(endgamestatus==2)
	{
		printf("对不起，您咬到自己了。游戏结束.");
	}
	else if(endgamestatus==3)
	{
		printf("您的已经结束了游戏。");
	}
	Pos(24,13);
	printf("您的得分是%d\n",score);
	exit(0);
}

void gamestart()//游戏初始化
{
	system("mode con cols=100 lines=30");
	welcometogame();
	creatMap();
	initsnake();
	createfood();
}

int main()
{
	gamestart();
	gamecircle();
	endgame();
	return 0;
}