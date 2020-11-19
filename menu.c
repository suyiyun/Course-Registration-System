#include "menu.h"

int login_menu(node_t *stulist)
{
	int choose = -1;
	while(choose)
	{
	
		system("clear");
		printf("1 管理员登陆\n");
		printf("2 学生登陆\n");
		printf("0 退出\n");
		printf("请输入你的选择 >> \n");

		scanf("%d", &choose);
		if(choose < 0 || choose > 2)
		{
			
			printf("你的输入有误，请重新输入 >> \n");
			getchar();
			getchar();
		}
		switch(choose)
		{
			case 0: return 0; break;
			case 1: welcomeadmin_menu(stulist);	break;//return 0;
			case 2: welcomestu_menu(stulist);	break;	//return 0;
			default: break; 
		}
	}
	return 0;

}

int admin_menu(node_t *stulist)
{
#if 1
	int choose = -1;
	while(choose)
	{
		system("clear");
		printf("----------------管理员操作菜单-----------------\n");
		printf("0 退出\t1 进入添加学生菜单\t2 进入删除学生菜单\t3 进入修改学生菜单\t4 进入查找学生菜单\t5 进入显示学生菜单\n"); 
		scanf("%d", &choose);
		switch(choose)
		{
			case 0:	break;
			case 1: addstu_menu(stulist);	break;
			case 2: deletestu_menu(stulist);	break;
			case 3: updatestu_menu(stulist);	break;
			case 4: findstu_menu(stulist);	break;
			case 5: showstu_menu(stulist);	break;

			default: 
					printf("你的输入有误，请重新输入 >> \n");	
					getchar();
					getchar();
					break;	
		}
	}
	return 0;
#endif
}


int welcomeadmin_menu(node_t *stulist)
{
	printf("欢迎来到管理员登录界面\n");
	int count = LOOPCOUNT;
	char name[16] = "";
	char pass[20] = "";

	while(count)
	{
		system("clear");
		printf("-----------------------管理员登录界面------------------------\n");

		printf("管理员登录：\n第%d次机会\n", 4-count);
		printf("请输入管理员用户名: （不区分大小写）>> ");
		scanf("%s", name);
		printf("请输入管理员密码: (区分大小写）>> ");
		scanf("%s",pass);

		if(strcasecmp(name, ADMINNAME) == 0 &&
				strcmp(pass, ADMINPASS) == 0)
		{
			printf("登陆成功！输入任意键进入管理员菜单\n");
			getchar();
			getchar();
			admin_menu(stulist);
			return 0;
		}

		printf("你的输入有误，请重新输入!, 还有%d次机会，按任意键继续\n",
				count-1);
		count--;
		getchar();
		getchar();

	}
	return 0;
}


int stu_menu(node_t *stulist, stu_t *stup)
{
	int choose = -1;
	while(choose)
	{
		system("clear");
		printf("------------------------学生操作菜单---------------------------------\n");
		printf("0 退出\t1 显示学生数据\t2 进入修改学生菜单\n");
		scanf("%d", &choose);

		switch(choose)
		{
			case 0:	break;
			case 1:
					printf("你所查找的学生数据为\n");
					printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
					findstu(stulist, 1, stup);
						
					printf("按任意键继续\n");
					getchar();
					getchar();
					break;

			case 2: 
					if(update_onestu_menu(stulist, stup) != 0)
					{
						printf("更改失败");
						return -1;
					}

					printf("更改成功，输入任意键以继续！\n");
					getchar();
					getchar();
					break;
			default: 
					printf("你的输入有误，请重新输入 >> \n");	
					getchar();
					getchar();	break;
		}
	}
	return 0;
}


int welcomestu_menu(node_t *stulist)
{
	printf("欢迎来到学生登录界面\n");
	int count = LOOPCOUNT;
	stu_t stu = {0};

	while(count)
	{
		system("clear");
		printf("-----------------------学生登录界面------------------------\n");
		printf("学生登录：\n第%d次机会\n", 4-count);
		printf("请输入学生用户名: （不区分大小写）>> ");
		scanf("%s", stu.name);
		printf("请输入学生密码: (区分大小写）>> ");
		scanf("%s",stu.pass);

		node_t *temp = find_vdlist(stulist, &stu, cmp_stu_name); 
//		node_t *temp2 = find_vdlist(stulist, &stu, cmp_stu_pass);
//		temp1 = temp1->after;
//		temp2 = temp2->after;
		
		if(temp == NULL)
			printf("你的输入有误，请重新输入!, 还有%d次机会，按任意键继续\n",
				count-1);
		else
		{
			stu_t *stup = (stu_t *)temp->data;
			if(strcmp(stu.pass, stup->pass) == 0)
			{
				printf("登陆成功！输入任意键进入学生菜单\n");
				getchar();
				getchar();
				stu.cid = stup->cid;
				stu_menu(stulist, &stu);
				return 0;
			}
			printf("密码错误，请重新输入!, 还有%d次机会，按任意键继续\n",
				count-1);
		}
		count--;
		getchar();
		getchar();
	}

	return 0;
}


int showstu_menu(node_t *stulist)
{
	int choose = -1;
	while(choose)
	{
		system("clear");
		printf("欢迎来到显示学生菜单\n");
		printf("0 退出\t1 按学生id显示\t2 按学生数学成绩排序\t3 按学生C语言成绩排序\t4 按学生语文成绩排序\t5 按学生总分排序\n");
		scanf("%d", &choose);
		int res = -1;
		switch(choose)
		{
			case 0: return 0; break;
			case 1:	printf("-------按学生id顺序-------------\n");
					res = sortstu(stulist, 1);	break;
			case 2:	printf("-------按学生数学成绩顺序(倒3)-------------\n");
					res = sortstu(stulist, 2);	break;
			case 3:	printf("-------按学生C语言成绩顺序(倒2)-------------\n");
					res = sortstu(stulist, 3);	break;

			case 4:	printf("-------按学生语文成绩顺序(倒4)-------------\n");
					res = sortstu(stulist, 4);	break;
			case 5:	printf("-------按学生总成绩顺序-------------\n");
					res = sortstu(stulist, 5);	break;
			default: 
					printf("你的输入有误，请重新输入 1-5 >> \n");	
					getchar();
					getchar();	break;

		}

		if(res != 0)
			return -1;
		res = setstuorder(stulist);
		if(res != 0)
			return -1;
		printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
		show_hdlist(stulist, showstu);

		printf("输入任意键继续\n");
		getchar();
		getchar();

	}
	return 0;
}


int addstu_menu(node_t *stulist)
{
	system("clear");
	int clear = 1;

	while(clear)
	{
		printf("欢迎来到添加学生菜单\n");
		stu_t new = {0};
		int id = getcid();
		new.cid = id;

		printf("请输入学生用户名以录入\n");  //数据检查
		scanf("%s", new.name);
		printf("请输入学生登录密码以录入\n");
		scanf("%s", new.pass);
		printf("请输入学生年龄以录入\n");  //数据检查
		scanf("%d", &new.age);
		printf("请输入学生班级以录入\n");
		scanf("%d", &new.classid);

		getchar();
		if(addstu(stulist, &new) != 0)
		{
			perror("添加错误\n");
			return -1;
		}

		printf("已成功添加，输入任意键继续！\n");
		printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
		showstu(&new);

		printf("是否继续添加？1 继续\t0 退出\n");
		scanf("%d", &clear);
		printf("-----------------------------------\n");
	}
	return 0;
}


int deletestu_menu(node_t *stulist)
{
	int choose = -1;
	while(choose)
	{
		system("clear");
		printf("欢迎来到删除学生菜单\n");
		printf("0 退出\n1 按学生id删除\n2 按学生姓名删除\n3 按学生班级删除\n");
		scanf("%d", &choose);
		stu_t stu = {0};
	//	int temp = 0;
		switch(choose)
		{
			case 0: return 0;
			case 1:
					printf("请输入要删除的学生id\n");
					scanf("%d", &stu.cid);
					getchar();
					if(delstu(stulist, 1, &stu)	!= 0)
					{	
						printf("delete error!\n");
						return -1;	
					}
					printf("delete success!\n");	break;
			case 2:
					printf("请输入要删除的学生姓名\n");
					scanf("%s", stu.name);
					getchar();
					if(delstu(stulist, 2, &stu)	!= 0)
					{	
						printf("delete error!\n");
						return -1;
					}
					printf("delete success!\n");	break;
			case 3:
					printf("请输入要删除的学生班级\n");
					scanf("%d", &stu.classid);
					getchar();
					if(delstu(stulist, 3, &stu)	!= 0)
					{	
						printf("delete error!\n");
						return -1;
					}
					printf("delete success!\n");
					break;
			default: 
					printf("你的输入有误，请重新输入 1-3 >> \n");	
					getchar();
					getchar();	break;

		}
		printf("输入任意键继续\n");

		getchar();
	}
	return 0;
}


int update_onestu_menu(node_t *stulist, stu_t *stup)
{
	int choose = -1;
	while(choose)
	{

		printf("欢迎来到修改学生菜单\n");

		printf("0 退出\n1 更改学生姓名\n2 更改学生密码\n3 更改学生年龄\n");
		scanf("%d", &choose);
		stu_t new_stu = {0};
		switch(choose)
		{

			case 0: return 0; break;
			case 1:
					printf("请输入新的学生姓名\n");
					scanf("%s", new_stu.name);
					getchar();
					if(updatestu(stulist, 1, stup, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;

			case 2:
					printf("请输入新的学生密码\n");
					scanf("%s", new_stu.pass);
					getchar();
					if(updatestu(stulist, 2, stup, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;

			case 3:
					printf("请输入新的学生年龄\n");
					scanf("%d", &new_stu.age);
					getchar();
					if(updatestu(stulist, 3, stup, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;
			default: 
					printf("你的输入有误，请重新输入 1-3 >> \n");	
					getchar();
					getchar();	break;
		}
	}
	return 0;

}


int updatestu_menu(node_t *stulist)		
{
	system("clear");
	printf("欢迎来到修改学生菜单\n");
	int choose = -1, isid = 1;
	stu_t old_stu = {0};
	while(isid)
	{
		isid = 0;
		printf("请输入要更改的学生学号!\n");
		scanf("%d", &old_stu.cid);
		node_t *temp = find_vdlist(stulist, &old_stu, cmp_stu_cid);

		if(!temp)
		{
			printf("数据库中没有学号为%d的学生，请重新输入！\n", old_stu.cid);
			isid = 1;
		}
		else
		{
			printf("学号为%d学生的原信息为: \n", old_stu.cid);
			printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
			showstu(temp->data);
		}

	}

	while(choose)
	{

		printf("欢迎来到修改学生菜单\n");

		printf("0 退出\n1 更改学生姓名\n2 更改学生密码\n3 更改学生年龄\n4 更改学生班级\n5 更改学生语文成绩\n6 更改学生数学成绩\n7 更改学生C语言成绩\n");
		scanf("%d", &choose);
		stu_t new_stu = {0};
		switch(choose)
		{

			case 0: return 0; break;
			case 1:
					printf("请输入新的学生姓名\n");
					scanf("%s", new_stu.name);
					getchar();
					if(updatestu(stulist, 1, &old_stu, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;

			case 2:
					printf("请输入新的学生密码\n");
					scanf("%s", new_stu.pass);
					getchar();
					if(updatestu(stulist, 2, &old_stu, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;

			case 3:
					printf("请输入新的学生年龄\n");
					scanf("%d", &new_stu.age);
					getchar();
					if(updatestu(stulist, 3, &old_stu, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;

			case 4:
					printf("请输入新的学生班级\n");
					scanf("%d", &new_stu.classid);
					getchar();
					if(updatestu(stulist, 4, &old_stu, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;

			case 5:
					printf("请输入新的学生语文成绩\n");
					scanf("%d", &new_stu.gphil);
					getchar();
					if(updatestu(stulist, 5, &old_stu, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;

			case 6:
					printf("请输入新的学生数学成绩\n");
					scanf("%d", &new_stu.gmath);
					getchar();
					if(updatestu(stulist, 6, &old_stu, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;

			case 7:
					printf("请输入新的学生C语言成绩\n");
					scanf("%d", &new_stu.glang);
					getchar();
					if(updatestu(stulist, 7, &old_stu, &new_stu) != 0)
					{	
						printf("update error!\n");
						return -1;
					}
					printf("update success!\n");	break;
			default:
					printf("你的输入有误，请确认修改模式属于1-7，学生学号输入正确！\n");
					getchar();
					getchar();
					break;

		}

		printf("更改成功\n");
		printf("学号为%d学生的新信息为: \n", old_stu.cid);
		node_t *temp2 = find_vdlist(stulist, &old_stu, cmp_stu_cid);
		printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
		showstu(temp2->data);

		printf("输入任意键继续\n");
		getchar();

	}

	return 0;
}


int findstu_menu(node_t *stulist)			
{
	int choose = -1;
	while(choose)
	{
		system("clear");
		printf("欢迎来到查找学生菜单\n");
		printf("0 显示所有学生并退出\n1 按学生id查找\n2 按学生姓名查找\n3 按学生班级查找\n");
		scanf("%d", &choose);
		stu_t stu = {0};
		node_t *temp = findstu(stulist, 1, &stu);

		//	int temp = 0;
		switch(choose)
		{
			case 0:
					getchar();
					printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
					show_hdlist(stulist, showstu);
					getchar();
					return 0; break;

			case 1:
					printf("请输入要查找的学生id\n"); //可能输入不是整数
					scanf("%d", &stu.cid);
					printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
					temp = findstu(stulist, 1, &stu);
					break;

			case 2:
					printf("请输入要查找的学生姓名\n");
					scanf("%s", stu.name);
					printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
					temp = findstu(stulist, 2, &stu);
					break;

			case 3:
					printf("请输入要查找的学生班级\n"); //可能输入不是整数
					scanf("%d", &stu.classid);
					printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
					temp = findstu(stulist, 3, &stu);
					break;

			default: 
					printf("你的输入有误，请重新输入 1-3 >> \n");	
					getchar();
					getchar();	break;
		}

		getchar();
		if(temp -> after != temp)
			printf("已找到\n");

		else
		{
			system("clear");
			printf("未找到!");
		}

		printf("输入任意键继续\n");
		getchar();
	}
	return 0;
}



