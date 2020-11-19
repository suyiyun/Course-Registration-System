#include "student.h"
#include "comm.h"
#include "dlist.h"
#include "menu.h"

int main()
{
	char issave;
	node_t *stulist = loadstu();

	login_menu(stulist);
	printf("是否保存?\n(Y:保存\tN:不保存 \n");
	//issave = getchar();
	getchar();
	scanf("%c", &issave);
	if(issave == 'Y' || issave == 'y')
	{
		savestu(stulist);
		printf("成功保存！\n");
	}
	else
		printf("未保存！\n");
	destroy_dlist(&stulist);
	printf("感谢使用！\n");
}

