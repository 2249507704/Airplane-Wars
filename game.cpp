#include"game.h"
//游戏初始化
int position_x, position_y; //飞机位置
int bullit_x, bullit_y; //子弹位置
int enemy_x[NUM], enemy_y[NUM]; //敌人位置

//int high, width; //画面大小
int score; //获得分数
int canvas[high][width];  //用二维数组记录游戏画面中对应的元素 并且给他初始化为0输出空格，1输出飞机 2输出子弹 3输出敌人

/**
 * 文字颜色函数
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);    //更改文字颜色
	return 0;
}
void gotoxy(int x, int y)//光标移动到xy的位置  要用头文件windows.h
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//解决光标闪烁的函数
void HideCursor()//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_infor = { 1,0 }; //第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_infor);
}

void welcometogame() //开始界面
{
	int n;
	color(15);
	gotoxy(43, 10);
	printf("飞 机 大 战");
	color(11);
	gotoxy(25, 22);
	printf("1.开始游戏");
	gotoxy(45, 22);
	printf("2.游戏说明");
	gotoxy(65, 22);
	printf("3.退出游戏");
	gotoxy(40, 27);
	color(3);
	printf("请选择 1 2 3:");
	color(14);
	scanf("%d", &n);   //输入选项
	switch (n)
	{
	case 1:
		system("cls");
		show();
		break;
	case 2:
		explation();    //游戏说明函数
		break;
	case 3:
		exit(0);    //退出游戏
		break;
	default:
		color(12);
		gotoxy(40, 28);
		printf("请输入1-3之间的数!");
		_getch();  //输入任意键
		system("cls"); //清屏
		welcometogame();
	}
}

void explation() //游戏提示 
{
	int i, j = 1;
	system("cls");
	color(10);
	gotoxy(44, 1);
	printf("游戏说明");
	color(2);
	for (i = 3; i <= 28; i++)  //输出上下边框===
	{
		for (j = 6; j <= 80; j++) //输出左右边框||
		{
			gotoxy(j, i);
			if (i == 3 || i == 28) printf("=");
			else if (j == 6 || j == 80) printf("||");
		}
	}
	color(3);
	gotoxy(20, 5);
	printf("1. W,A,S,D 分别控制飞机的上下左右移动");
	color(10);
	gotoxy(20, 8);
	printf("2. 按空格发射子弹，打中敌机即可得到一分");
	color(14);
	gotoxy(20, 11);
	printf("3.碰到敌机子弹死亡");
	color(11);
	gotoxy(20, 14);
	printf("4. ESC ：退出游戏");
	color(4);
	gotoxy(20, 17);
	printf("5. 玩的愉快！！！");
	color(7);
	gotoxy(20, 20);
	printf("/*****按任意键返回主页面*****/");
	_getch();        //按任意键返回主界面
	system("cls");
	welcometogame();
}

void scoreandtips()//游戏侧边提示 
{
	gotoxy(50, 8);
	color(14);
	printf("游戏得分：%d ", score);
	gotoxy(50, 10);
	printf("用W A S D 分别控制飞机的移动");
	gotoxy(50, 12);
	printf("按下空格键即为发射炮弹");
	gotoxy(50, 14);
	printf("@ 的样子就是敌人的飞机");
}
//初始化数据的函数
void startup()
{
	//飞机位置
	position_x = high / 2;
	position_y = width / 2;

	//最后要输出二维数组 初始化飞机位置
	canvas[position_x][position_y] = 1;

	//敌人位置
	for (int k = 0; k < NUM; k++)
	{
		enemy_x[k] = rand() % 3;
		enemy_y[k] = rand() % width;
		canvas[enemy_x[k]][enemy_y[k]] = 3;
	}

	//子弹位置
	/*bullit_x = -1;
	bullit_y = position_y;*/
	canvas[bullit_x][bullit_y] = 2;

	//初始分数
	score = 0;

	HideCursor();  //这个函数只需要执行一次  所以放在初始化就好
}

//在合适的位置找到飞机
void show()
{
	gotoxy(0, 0); //光标移动到原点位置，以下重画清屏
	//system("cls"); //清屏操作  这个清屏操作会一闪一闪 上边用一个gotoxy(int x,int y)的函数来代替

	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (canvas[i][j] == 1)
			{
				printf("*");  //输出飞机
			}
			else if (canvas[i][j] == 2)
			{
				printf("|"); //输出子弹
			}
			else if (canvas[i][j] == 3)
			{
				printf("@");
			}
			else
				printf(" ");
		}
		printf("\n");
	}

	printf("得分：%d\n", score);
}

//和输入无关的函数
void updateWithoutInput()
{
	//问题 加了延时后 飞机和敌人都变慢了 解决方法 加入 一个静态变量

	//让子弹向上移动
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (canvas[i][j] == 2)
			{
				for (int k = 0; k < NUM; k++)
				{
					if ((i == enemy_x[k]) && (j == enemy_y[k])) //击中敌人
					{
						canvas[enemy_x[k]][enemy_y[k]] = 0;  //让敌人归零
						//随机再生敌人
						enemy_x[k] = 0;
						enemy_y[k] = rand() % width;
						canvas[enemy_x[k]][enemy_y[k]] = 3;  //显示再生的敌人
						score++; //加分
					}
				}
				canvas[i][j] = 0;  //清楚现在的子弹 
				if (i > 0)
					canvas[i - 1][j] = 2;  //打印下一个子弹
			}
		}
	}


	for (int k = 0; k < NUM; k++)
	{
		if (enemy_x[k] > high) //敌人跑出下边界 随机重新生成一个敌人
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k] = 0; //落完之后重新生成
			enemy_y[k] = rand() % width;
			canvas[enemy_x[k]][enemy_y[k]] = 3;

			score--; //跑出下边界 作为惩罚 减一分
		}
	}

	//改变敌人下落时间 
	static int speed = 10;  //每运行10次 敌人下落一次
	if (speed < 10)
	{
		speed++;
	}
	if (speed == 10)
	{	
		//敌人自动下落
		for (int k = 0; k < NUM; k++)
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k]++;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
		}
		speed = 0;
	}

	//敌人撞到了我  游戏结束
	for (int k = 0; k < NUM; k++)
	{
		if ((enemy_x[k] == position_x) && (enemy_y[k] == position_y))
		{
			score = 0;
			exit(0);
		}
	}
	
}

//和输入有关的函数
void updateWithInput()
{
	char input;
	if (kbhit()) // 当按键时执行
	{
		input = getch(); //把输入的字符给input
		if (input == 'a')
		{
			canvas[position_x][position_y] = 0;
			position_y--;
			canvas[position_x][position_y] = 1;
		}
		if (input == 'd')
		{
			canvas[position_x][position_y] = 0;
			position_y++;
			canvas[position_x][position_y] = 1;
		}
		if (input == 'w')
		{
			canvas[position_x][position_y] = 0;
			position_x--;
			canvas[position_x][position_y] = 1;
		}
		if (input == 's')
		{
			canvas[position_x][position_y] = 0;
			position_x++;
			canvas[position_x][position_y] = 1;
		}
		if (input == ' ')
		{
			bullit_x = position_x - 1;
			bullit_y = position_y;
			canvas[bullit_x][bullit_y] = 2;
		}
			

	}
}
