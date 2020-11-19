#include "student.h"

static int cid = 0;
//static int max = 0;
//生成student ID, 便于排序
int getcid()
{
	if(cid > 9999999)
		return -1;
	cid++;
	return cid;

}

//显示单个学生信息
void showstu(const void *data)
{

	const stu_t *stu1 = (const stu_t *)data;
//	printf("cid\tname\tpass\tage\tclassid\tgphil\tgmath\tglang\torder\n");
	printf("%d\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", stu1->cid, stu1->name,
				stu1->pass, stu1->age, stu1->classid, stu1->gphil, stu1->gmath, 
				stu1->glang, stu1->order);
}

//导入学生数据
node_t *loadstu()
{
	node_t *head = create_dlist();
	FILE *fp = fopen(STUFILE, "r");
	SYSERR(NULL, ==, fp, "File open error\n", NULL);
	fscanf(fp, "%d\n", &cid);
	stu_t stu = {0};
	while(fscanf(fp, "%d %s %s %d %d %d %d %d %d\n", &stu.cid, stu.name,
				stu.pass, &stu.age, &stu.classid, &stu.gphil, &stu.gmath, 
				&stu.glang, &stu.order) != EOF)
	{
		insert_hdlist(head, &stu, sizeof(stu_t));
		bzero(&stu, sizeof(stu));
	}
	fclose(fp);
	return head;
}


int savestu(node_t *stuhead)
{
	SYSERR(NULL, ==, stuhead, "stuhead is null", -1); 
	FILE *fp = fopen(STUFILE, "w"); //要改　STUFILE
	fprintf(fp, "%d\n", cid);

	node_t *temp = stuhead->after;
	stu_t *stup = NULL;
	while(temp != stuhead)
	{
		stup = (stu_t *)temp->data;
		fprintf(fp, "%d %s %s %d %d %d %d %d %d\n", stup->cid, stup->name,
				stup->pass, stup->age, stup->classid, stup->gphil, stup->gmath, 
				stup->glang, stup->order);
		temp = temp->after;
	}
	fclose(fp);
	return 0;
}


int addstu(node_t *stuhead,const stu_t *stu)
{
		SYSERR(NULL, ==, stuhead, "stuhead is null", -1); 
		int res = insert_tdlist(stuhead, stu, sizeof(stu_t));
		printf("add finished\n");
		showstu(stu);

		return res;
}


int delstu(node_t *stuhead,int mode,const stu_t *stu)
{
	SYSERR(NULL, ==, stuhead, "stuhead is null", -1); 
	SYSERR(NULL, ==, stu, "student is null", -1);
	node_t *result = stuhead;
	int res = -1;
	switch(mode)
	{
	case 0: break;
	case 1: 
		if((result = delete_vdlist(stuhead, stu, cmp_stu_cid)) != NULL)
			res = 0;
		break;
	case 2: 
		while((result = delete_vdlist(result, stu, cmp_stu_name)) != NULL)
			res = 0;
		break;
	case 3: 	
		while((result = delete_vdlist(result, stu, cmp_stu_classid)) != NULL)
			res = 0;
		break;
	default: return -1; break;
	}
	return res;
}


int updatestu(node_t *stuhead,int mode,const stu_t *oldstu, const stu_t *newstu)
{
	SYSERR(NULL, ==, stuhead, "stuhead is null", -1); 
	SYSERR(NULL, ==, oldstu, "student is null", -1);
	SYSERR(NULL, ==, newstu, "student is null", -1);

	int res = -1;
	node_t *result = find_vdlist(stuhead, oldstu, cmp_stu_cid);
	if(NULL == result)
	{
		printf("Not found\n");
		return -1;
	}
	stu_t *stu = (stu_t *)result->data;

	switch(mode)
	{
	case 1: 
		strcpy(stu->name, newstu->name);	break;
	case 2: 
		strcpy(stu->pass, newstu->pass);	break;
	case 3:
		stu->age = newstu->age;		break;
	case 4:
		stu->classid = newstu->classid;	break;
	case 5:
		stu->gphil = newstu->gphil;	break;
	case 6:
		stu->gmath = newstu->gmath;	break;
	case 7:
		stu->glang = newstu->glang;	break;
	default: return -1; break;
	}

	res = 0;
	printf("has updated: ");
	//showstu(stu);
	return res;

}


node_t *findstu(node_t *stuhead,int mode,const stu_t *stu)
{
		SYSERR(NULL, ==, stuhead, "stuhead is null", NULL); 
		SYSERR(stuhead->after, ==, stuhead, "student list is empty", NULL); 
		SYSERR(NULL, ==, stu, "student is null", NULL);

		node_t *result = stuhead;
		node_t *stu_new_list = create_dlist();
//		stu_t *stup = (stu_t *)result->data;
		switch(mode)
		{
		case 0: break;
		case 1: result = find_vdlist(stuhead, stu, cmp_stu_cid);
				if(result)
				{
					insert_tdlist(stu_new_list, stu, sizeof(stu_t));
					showstu(result->data);
				}
				break;

		case 2: 
				while((result = find_vdlist(result, stu, cmp_stu_name)) != NULL)
				{
					insert_tdlist(stu_new_list, stu, sizeof(stu_t));
					showstu(result->data);
				}
				break;
		case 3: 	
				while((result = find_vdlist(result, stu, cmp_stu_classid)) != NULL)
				{
					insert_tdlist(stu_new_list, stu, sizeof(stu_t));
					showstu(result->data);
				}
				break;
		default: return NULL; break;
		}

		return stu_new_list;
}


int sortstu(node_t *stuhead, int mode)
{

	SYSERR(NULL, ==, stuhead, "stuhead is null", -1); 
	SYSERR(NULL, ==, stuhead->before, "student list is empty", -1); 

	switch(mode)
	{
		case 1:	blubsort(stuhead, cmp_stu_cid);	break;
		case 2: selectsort(stuhead, cmp_stu_gmath);	break;
		case 3:	selectsort(stuhead, cmp_stu_glang);	break;
		case 4: selectsort(stuhead, cmp_stu_gphil);	break;
		case 5: selectsort(stuhead, cmp_stu_gsum);	break;
		default: return -1; break;
	}	
	return 0;
}


int setstuorder(node_t *stuhead)
{
	SYSERR(NULL, ==, stuhead, "stuhead is null", -1); 
	SYSERR(NULL, ==, stuhead->after, "student list is empty", -1); 
	node_t *temp = stuhead->after;
	int i = 1;
	while(temp != stuhead)
	{
		stu_t *stup = (stu_t *)temp->data;
		stup->order = i;
		i++;
		temp = temp->after;
	}
	return 0;
}


//比较学生学号函数
int cmp_stu_cid(const void *data1,const void *data2)
{
	const stu_t *stu1 = (const stu_t *)data1;
	const stu_t *stu2 = (const stu_t *)data2;
	return stu1->cid - stu2->cid;
}

int cmp_stu_name(const void *data1,const void *data2) 
//比较学生名字函数
{
	const stu_t *stu1 = (const stu_t *)data1;
	const stu_t *stu2 = (const stu_t *)data2;
	return strcasecmp(stu1->name, stu2->name);
}

int cmp_stu_pass(const void *data1,const void *data2) 
//比较学生密码函数
{
	const stu_t *stu1 = (const stu_t *)data1;
	const stu_t *stu2 = (const stu_t *)data2;
	return strcmp(stu1->pass, stu2->pass);
}


int cmp_stu_gmath(const void *data1,const void *data2)
//比较学生数学成绩函数
{
	const stu_t *stu1 = (const stu_t *)data1;
	const stu_t *stu2 = (const stu_t *)data2;
	return stu1->gmath - stu2->gmath;
}

int cmp_stu_glang(const void *data1,const void *data2)
//比较学生C语言成绩函数
{	
	const stu_t *stu1 = (const stu_t *)data1;
	const stu_t *stu2 = (const stu_t *)data2;
	return stu1->glang - stu2->glang;
}

int cmp_stu_gphil(const void *data1,const void *data2) //比较学生语文成绩函数
{
	const stu_t *stu1 = (const stu_t *)data1;
	const stu_t *stu2 = (const stu_t *)data2;
	return stu1->gphil - stu2->gphil;
}

int cmp_stu_gsum(const void *data1,const void *data2) //比较学生总分函数
{
	const stu_t *stu1 = (const stu_t *)data1;
	const stu_t *stu2 = (const stu_t *)data2;
	return stu1->gmath - stu2->gmath + stu1->glang - stu2->glang + stu1->gphil - stu2->gphil;
}

int cmp_stu_order(const void *data1,const void *data2) //比较学生序号函数
{
	const stu_t *stu1 = (const stu_t *)data1;
	const stu_t *stu2 = (const stu_t *)data2;

	return stu1->order - stu2->order;
}

int cmp_stu_classid(const void *data1,const void *data2) //比较学生班号函数
{
	const stu_t *stu1 = (const stu_t *)data1;
	const stu_t *stu2 = (const stu_t *)data2;

	return stu1->classid - stu2->classid;
}


#if 0
int main()
{
	
	node_t *stuhead = loadstu();
	show_hdlist(stuhead, showstu);

	int res = getcid();
	printf("res = %d, cid = %d\n", res, cid);	//res = 1;

	stu_t stu = {5, "syy", "123", 22, 1, 29, 90, 99, 4};

	insert_hdlist(stuhead, &stu, sizeof(stu));
	if(addstu(stuhead, &stu) != 0)
		return -1;
//	show_hdlist(stuhead, showstu);
	printf("\n---------find-------------------\n");
	stu_t stufind = {100,"syy", "ddd", 0, 2, 66, 88, 100, 0};

#if 1
	node_t *result = findstu(stuhead, 2, &stufind);
	if(result->after != result)
	{
		printf("\nfind result = \n");
		show_hdlist(result, showstu);
	//	showstu(result->data);
	}
	else
		printf("Not found!\n");
	printf("\n---------find-------------------\n");

#endif

#if 0
	int res = delstu(stuhead,2, &stu);
	if(res == 0)
	{
		printf("delete success!\n");
		show_hdlist(stuhead, showstu);
	}
	else
		printf("delete error!\n");
#endif

#if 0
	if(updatestu(stuhead, 1, &stu, &stufind) != 0)
		return -1;

	printf("Update success!-----after update ------\n");
	show_hdlist(stuhead, showstu);
#endif

#if 0
	res = delstu(stuhead, 2, &stufind);
	if(res == 0)
	{
		printf("delete success!\n");
		show_hdlist(stuhead, showstu);
	}
	else
		printf("delete error!\n");
#endif

#if 0
	const stu_t stu1 = {6, "syl", "123", 22, 1, 29, 60, 99, 4};
	const stu_t stu2 = {7, "syz", "123", 22, 1, 29, 50, 99, 4};
	const stu_t stu3 = {8, "sytttt", "123", 22, 1, 29, 50, 99, 4};



	if(addstu(stuhead, &stu1) != 0 && addstu(stuhead, &stu2) != 0)
		return -1;
	res = addstu(stuhead, &stu2);
	res = addstu(stuhead, &stu3);

	res = sortstu(stuhead, 1);
	if(res == 0)
	{
		printf("sort success!\n");
		show_hdlist(stuhead, showstu);
	}
	else
		printf("sort error!\n");

	res = setstuorder(stuhead);
	if(res == 0)
	{
		printf("Order success!\n");
		show_hdlist(stuhead, showstu);
	}
	else
		printf("Order error!\n");
#endif

#if 0
	if(savestu(stuhead) == 0)
		show_hdlist(stuhead, showstu);
#endif 
	return 0;
}

#endif
