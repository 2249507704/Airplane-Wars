#include"game.h"
int main()
{
	system("mode con cols=100 lines=30");
	welcometogame();
	startup(); //���ݳ�ʼ��  ֻ��Ҫһ��
	while (1)
	{
		show();  //��ʾ����
		updateWithoutInput();  //���û������޹صĸ���
		updateWithInput(); //���û������йصĸ���
	}
	return 0;
}