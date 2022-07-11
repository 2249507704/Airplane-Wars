#include"game.h"
int main()
{
	system("mode con cols=100 lines=30");
	welcometogame();
	startup(); //数据初始化  只需要一次
	while (1)
	{
		show();  //显示画面
		updateWithoutInput();  //与用户输入无关的更新
		updateWithInput(); //与用户输入有关的更新
	}
	return 0;
}