//
//	menu.h
//	Created by Yiyun Su on 08/08/2019


#ifndef STUDENT_H
#define STUDENT_H

#include "dlist.h"
#include "comm.h"

//定义学生数据类型
typedef struct student
{
	int cid;
	char name[32];
	char pass[16];
	int age;
	int classid;  
	int gphil;
	int gmath;
	int glang;    //
	int gsum;
	int order;
}stu_t;


/*
 * 功能：获取学生ID
 * 返回值：-1表示获取失败，0表示获取成功
 */
int getcid();


/*
 *功能：创建学生链表
 *返回值：NULL表示创建失败，head->before = head->after = head 表示创建成功
 */
node_t *loadstu();


/*
* 功能：保存学生链表
* 参数：返回值：-1表示插入失败，0表示插入成功
* stuhead: 学生链表头节点
* 返回值：-1表示保存失败，0表示保存成功
*/
int savestu(node_t *stuhead);


/*
 * 功能：显示学生链表内的数据
 * 参数：data表示要显示的数据,在函数中用printf打印出来
*/
void showstu(const void *data);


/*
 * 功能：插入特定数据到学生链表的尾部
 * 参数：stuhead: 学生链表头节点, stu: 要插入的学生数据；
 * 返回值：-1表示插入失败，0表示插入成功
 */
int addstu(node_t *stuhead, const stu_t *stu);


/*
 * 功能：删除学生链表的特定数据
 * 参数：stuhead: 学生链表头节点, 
 * mode: 删除的类型1　按学生id删除;
 * 2　按学生姓名删除3　按学生班级删除
 * stu: 要删除的学生数据；
 * 返回值：-1表示删除失败，0表示删除成功
 */
int delstu(node_t *stuead,int mode,const stu_t *stu);


/*
 * 功能：修改学生链表的特定数据
 * 参数：stuhead: 学生链表头节点, 
 * mode: 修改的类型1　更改学生姓名2　更改学生密码3 更改学生年龄
 * 4　更改学生班级5 更改学生语文成绩6 更改学生数学成绩7 更改学生C语言成绩
 * oldstu: 要更改的原学生数据；newstu: 新学生数据；
 * 返回值：-1表示更新失败，0表示更新成功
 */
int updatestu(node_t *stuead,int mode,const stu_t *oldstu, const stu_t *newstu); 


/*
 * 功能：修改学生链表的特定数据
 * 参数：stuhead: 学生链表头节点, stu 要查找的数据；
 * mode :根据查找的数据确定查找方法
 * 返回值：NULL表示未找到，head->after ！= head 表示成功找到数据并存储在链表中
 */
node_t *findstu(node_t *stuhead,int mode,const stu_t *stu);


/*
 * 功能：排序学生链表
 * 参数：stuhead: 学生链表头节点, 
 * mode: 排序的数据1　按学生id显示(顺序）2　按学生数学成绩排序
 * 3 按学生C语言成绩排序4 按学生语文成绩排序5 按学生总分排序（逆序）
 * 返回值：-1表示排序失败，0表示排序成功
 */
int sortstu(node_t *stuhead, int mode);


/*
 * 功能：根据学生链表设置序号
 * 参数：stuhead: 学生链表头节点, 
 * mode: 排序的数据1　按学生id显示2　按学生数学成绩排序
 * 3 按学生C语言成绩排序4 按学生语文成绩排序5 按学生总分排序
 * 返回值：-1表示排序失败，0表示排序成功
 */
int setstuorder(node_t *stuead);


/*
 * 功能：比较学生的id
 * 参数：data1, data2要比较的两个数据的地址
 * 返回值：>0 表示data1 > data2; <0 表示data1 < data2
 */
int cmp_stu_cid(const void *data1,const void *data2); //比较学生学号函数


/*
 * 功能：比较学生的姓名
 * 参数：data1, data2要比较的两个数据的地址
 * 返回值：>0 表示data1 > data2; <0 表示data1 < data2
 */
int cmp_stu_name(const void *data1,const void *data2); //比较学生名字函数


/*
 * 功能：比较学生的数学成绩
 * 参数：data1, data2要比较的两个数据的地址
 * 返回值：>0 表示data1 > data2; <0 表示data1 < data2
 */
int cmp_stu_gmath(const void *data1,const void *data2); //比较学生数学成绩函数


/*
 * 功能：比较学生的C语言成绩
 * 参数：data1, data2要比较的两个数据的地址
 * 返回值：>0 表示data1 > data2; <0 表示data1 < data2
 */
int cmp_stu_glang(const void *data1,const void *data2); //比较学生C语言成绩函数


/*
 * 功能：比较学生的语文成绩
 * 参数：data1, data2要比较的两个数据的地址
 * 返回值：>0 表示data1 > data2; <0 表示data1 < data2
 */
int cmp_stu_gphil(const void *data1,const void *data2); //比较学生语文成绩函数


/*
 * 功能：比较学生的总分
 * 参数：data1, data2要比较的两个数据的地址
 * 返回值：>0 表示data1 > data2; <0 表示data1 < data2
 */
int cmp_stu_gsum(const void *data1,const void *data2); //比较学生总分函数


/*
 * 功能：比较学生的序号
 * 参数：data1, data2要比较的两个数据的地址
 * 返回值：>0 表示data1 > data2; <0 表示data1 < data2
 */
int cmp_stu_order(const void *data1,const void *data2); //比较学生序号函数


/*
 * 功能：比较学生的班级序号
 * 参数：data1, data2要比较的两个数据的地址
 * 返回值：>0 表示data1 > data2; <0 表示data1 < data2
 */
int cmp_stu_classid(const void *data1,const void *data2); //比较学生班号函数


/*
 * 功能：比较学生的密码
 * 参数：data1, data2要比较的两个数据的地址
 * 返回值：>0 表示data1 > data2; <0 表示data1 < data2
 */
int cmp_stu_pass(const void *data1,const void *data2); //比较学生密码函数 

#endif
