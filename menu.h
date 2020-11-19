
//
//	menu.h
//	Created by Yiyun Su on 08/08/2019

#ifndef	MENU_H
#define MENU_H

#include "comm.h"
#include "dlist.h"
#include "student.h"


/*
 * 功能：登录界面
 * 返回值：-1表示登录失败，0表示登录成功
 */
int login_menu(node_t *stulist);


/*
 * 功能：管理员操作界面
 * 参数：stulist: 学生链表头节点,
 * 返回值：-1表示登录失败，0表示登录成功
 */
int admin_menu(node_t *stulist);


/*
 * 功能：欢迎管理员界面
 * 参数：stulist: 学生链表头节点,
 * 返回值：-1表示登录失败，0表示登录成功
 */
int welcomeadmin_menu(node_t *stulist);


/*
 * 功能：学生操作界面
 * 参数：stulist: 学生链表头节点, stup: 存储所登录学生数据的地址
 * 返回值：-1表示登录失败，0表示登录成功
 */
int stu_menu(node_t *stulist,stu_t *stup);


/*
 * 功能：欢迎学生登录界面 
 * 参数：stulist: 学生链表头节点,
 * 返回值：-1表示登录失败，0表示登录成功
 */
int welcomestu_menu(node_t *stulist);


/*
 * 功能：插入特定数据到学生链表的尾部
 * 参数：stulist: 学生链表头节点,
 * 返回值：-1表示插入失败，0表示插入成功
 */
int addstu_menu(node_t *stulist);


/*
 * 功能：删除学生链表的特定数据
 * 参数：stulist: 学生链表头节点,
 * 返回值：-1表示删除失败，0表示删除成功
 */
int deletestu_menu(node_t *stulist);		//删除学生菜单


/*
 * 功能：修改学生链表的特定数据
 * 参数：stulist: 学生链表头节点,
 * 返回值：-1表示更新失败，0表示更新成功
 */
int updatestu_menu(node_t *stulist);		//修改学生菜单


/*
 * 功能：显示学生链表内的数据
 * 参数：stulist: 学生链表头节点,
 * 返回值：-1表示显示失败，0表示显示成功
*/
int showstu_menu(node_t *stulist);		//显示学生菜单


/*
 * 功能：查找学生链表的特定数据
 * 参数stulist: 学生链表头节点,
 * 返回值：-1表示查找失败，0表示查找成功
 */
int findstu_menu(node_t *stulist);			//查找学生菜单


/*
 * 功能：修改学生链表的特定数据
 * 参数：stulist: 学生链表头节点, stup: 存储所登录学生数据的地址
 * 返回值：-1表示更新失败，0表示更新成功
 */
int update_onestu_menu(node_t *stulist,stu_t *stup);	//学生操作界面的修改学生菜单

#endif
