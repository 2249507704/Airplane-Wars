#include"game.h"
//��Ϸ��ʼ��
int position_x, position_y; //�ɻ�λ��
int bullit_x, bullit_y; //�ӵ�λ��
int enemy_x[NUM], enemy_y[NUM]; //����λ��

//int high, width; //�����С
int score; //��÷���
int canvas[high][width];  //�ö�ά�����¼��Ϸ�����ж�Ӧ��Ԫ�� ���Ҹ�����ʼ��Ϊ0����ո�1����ɻ� 2����ӵ� 3�������

/**
 * ������ɫ����
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);    //����������ɫ
	return 0;
}
void gotoxy(int x, int y)//����ƶ���xy��λ��  Ҫ��ͷ�ļ�windows.h
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//��������˸�ĺ���
void HideCursor()//���ع��
{
	CONSOLE_CURSOR_INFO cursor_infor = { 1,0 }; //�ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_infor);
}

void welcometogame() //��ʼ����
{
	int n;
	color(15);
	gotoxy(43, 10);
	printf("�� �� �� ս");
	color(11);
	gotoxy(25, 22);
	printf("1.��ʼ��Ϸ");
	gotoxy(45, 22);
	printf("2.��Ϸ˵��");
	gotoxy(65, 22);
	printf("3.�˳���Ϸ");
	gotoxy(40, 27);
	color(3);
	printf("��ѡ�� 1 2 3:");
	color(14);
	scanf("%d", &n);   //����ѡ��
	switch (n)
	{
	case 1:
		system("cls");
		show();
		break;
	case 2:
		explation();    //��Ϸ˵������
		break;
	case 3:
		exit(0);    //�˳���Ϸ
		break;
	default:
		color(12);
		gotoxy(40, 28);
		printf("������1-3֮�����!");
		_getch();  //���������
		system("cls"); //����
		welcometogame();
	}
}

void explation() //��Ϸ��ʾ 
{
	int i, j = 1;
	system("cls");
	color(10);
	gotoxy(44, 1);
	printf("��Ϸ˵��");
	color(2);
	for (i = 3; i <= 28; i++)  //������±߿�===
	{
		for (j = 6; j <= 80; j++) //������ұ߿�||
		{
			gotoxy(j, i);
			if (i == 3 || i == 28) printf("=");
			else if (j == 6 || j == 80) printf("||");
		}
	}
	color(3);
	gotoxy(20, 5);
	printf("1. W,A,S,D �ֱ���Ʒɻ������������ƶ�");
	color(10);
	gotoxy(20, 8);
	printf("2. ���ո����ӵ������ел����ɵõ�һ��");
	color(14);
	gotoxy(20, 11);
	printf("3.�����л��ӵ�����");
	color(11);
	gotoxy(20, 14);
	printf("4. ESC ���˳���Ϸ");
	color(4);
	gotoxy(20, 17);
	printf("5. �����죡����");
	color(7);
	gotoxy(20, 20);
	printf("/*****�������������ҳ��*****/");
	_getch();        //�����������������
	system("cls");
	welcometogame();
}

void scoreandtips()//��Ϸ�����ʾ 
{
	gotoxy(50, 8);
	color(14);
	printf("��Ϸ�÷֣�%d ", score);
	gotoxy(50, 10);
	printf("��W A S D �ֱ���Ʒɻ����ƶ�");
	gotoxy(50, 12);
	printf("���¿ո����Ϊ�����ڵ�");
	gotoxy(50, 14);
	printf("@ �����Ӿ��ǵ��˵ķɻ�");
}
//��ʼ�����ݵĺ���
void startup()
{
	//�ɻ�λ��
	position_x = high / 2;
	position_y = width / 2;

	//���Ҫ�����ά���� ��ʼ���ɻ�λ��
	canvas[position_x][position_y] = 1;

	//����λ��
	for (int k = 0; k < NUM; k++)
	{
		enemy_x[k] = rand() % 3;
		enemy_y[k] = rand() % width;
		canvas[enemy_x[k]][enemy_y[k]] = 3;
	}

	//�ӵ�λ��
	/*bullit_x = -1;
	bullit_y = position_y;*/
	canvas[bullit_x][bullit_y] = 2;

	//��ʼ����
	score = 0;

	HideCursor();  //�������ֻ��Ҫִ��һ��  ���Է��ڳ�ʼ���ͺ�
}

//�ں��ʵ�λ���ҵ��ɻ�
void show()
{
	gotoxy(0, 0); //����ƶ���ԭ��λ�ã������ػ�����
	//system("cls"); //��������  �������������һ��һ�� �ϱ���һ��gotoxy(int x,int y)�ĺ���������

	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (canvas[i][j] == 1)
			{
				printf("*");  //����ɻ�
			}
			else if (canvas[i][j] == 2)
			{
				printf("|"); //����ӵ�
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

	printf("�÷֣�%d\n", score);
}

//�������޹صĺ���
void updateWithoutInput()
{
	//���� ������ʱ�� �ɻ��͵��˶������� ������� ���� һ����̬����

	//���ӵ������ƶ�
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (canvas[i][j] == 2)
			{
				for (int k = 0; k < NUM; k++)
				{
					if ((i == enemy_x[k]) && (j == enemy_y[k])) //���е���
					{
						canvas[enemy_x[k]][enemy_y[k]] = 0;  //�õ��˹���
						//�����������
						enemy_x[k] = 0;
						enemy_y[k] = rand() % width;
						canvas[enemy_x[k]][enemy_y[k]] = 3;  //��ʾ�����ĵ���
						score++; //�ӷ�
					}
				}
				canvas[i][j] = 0;  //������ڵ��ӵ� 
				if (i > 0)
					canvas[i - 1][j] = 2;  //��ӡ��һ���ӵ�
			}
		}
	}


	for (int k = 0; k < NUM; k++)
	{
		if (enemy_x[k] > high) //�����ܳ��±߽� �����������һ������
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k] = 0; //����֮����������
			enemy_y[k] = rand() % width;
			canvas[enemy_x[k]][enemy_y[k]] = 3;

			score--; //�ܳ��±߽� ��Ϊ�ͷ� ��һ��
		}
	}

	//�ı��������ʱ�� 
	static int speed = 10;  //ÿ����10�� ��������һ��
	if (speed < 10)
	{
		speed++;
	}
	if (speed == 10)
	{	
		//�����Զ�����
		for (int k = 0; k < NUM; k++)
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k]++;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
		}
		speed = 0;
	}

	//����ײ������  ��Ϸ����
	for (int k = 0; k < NUM; k++)
	{
		if ((enemy_x[k] == position_x) && (enemy_y[k] == position_y))
		{
			score = 0;
			exit(0);
		}
	}
	
}

//�������йصĺ���
void updateWithInput()
{
	char input;
	if (kbhit()) // ������ʱִ��
	{
		input = getch(); //��������ַ���input
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
