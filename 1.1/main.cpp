//
//  main.cpp
//  1.1
//
//  Created by 何忆源 on 2020/4/21.
//  Copyright © 2020 何忆源. All rights reserved.
//优先数调度算法
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<iostream>
struct PCB // 定义一个进程结点数据域
{
    char name[3]; // 进程名
    int run_time; // 运行时间
    int level; // 优先数
    char state;  // 运行状态
    struct PCB *next; // 指向下一个结点的指针
};
struct PCB *creat()  // 创建一个函数，用于返回一个链表
{
    int i = 1;
    int time, slevel; // 用来存储用户输入
    struct PCB *head, *tail, *temp, *previous; // 申明指针
    char PCB_name[5][3]= {"P1", "P2", "P3", "P4", "P5"}; // 初始化进程名数组
    temp = (struct PCB *)malloc(sizeof(struct PCB)); // 给 temp 指针分配内存
    printf(" 请输入第 1 个结点的优先数 : "); scanf("%d", &slevel);
    printf(" 请输入第 1 个结点的运行时间 : ");scanf("%d", &time);
    temp->level = slevel; // 将输入的优先数赋值给 temp 结点的优先数
    strcpy(temp->name, PCB_name[0]); // 将 PCB_name[0]复制给 temp 结点
    temp->next = NULL; //temp 结点的下一个为空
    temp->run_time = time; // 获取输入的运行时间
    temp->state = 'R'; // 运行状态为就绪
    head = tail = temp;  // 指向当前第一个结点
    while (i != 5) //i 的初值为 1，这里不等于 5，意思就是继 续添加四个结点
    {
        temp = (struct PCB *)malloc(sizeof(struct PCB)); // 分配一段新的 内存给 temp
        printf(" 请输入第 %d个结点的优先数 : ", i + 1);
        scanf("%d", &slevel);
        printf(" 请输入第 %d个结点的运行时间 : ", i + 1);
        scanf("%d", &time);
        temp->level = slevel; // 同上
        strcpy(temp->name, PCB_name[i]);
        temp->run_time = time;
        temp->state = 'R';
        if (temp->level > head->level) // 比较当前定义的结 点的优先数与 head 的优先数，同时 head 指向的结点的优先数是最大的
        {
            temp->next = head; // 如果前定义的结点的优先数 与 head 的优先数大，则 head 指向当前定义的结点
            head = temp;
        }
        else
        {
            previous = head;
            while (previous->next != NULL) // 如果比优先数最大的结点小,则继续与后面的节点进行比较， 知道找到一个合适的位置， 即为比前面结点的优先数大， 比 后面的小
            {
                if ((temp->level <= previous->level) && (temp->level >=(previous->next)->level))
                {
                    temp->next = previous->next; // 交换两个结点的位置
                    previous->next = temp;
                    break;
                    
                }
                else
                {
                    previous = previous->next; // 实现往后移
                    
                }
                
            }
            if (previous->next == NULL)  // 如果没有找到比当前结点小的， 则将当 前结点放在最后面
            {
                tail->next = temp;
                temp->next = NULL;
                tail = temp;
                
            }
            
        }
        i++;
    }
    return (head); // 返回一个链表的头结点
}
void display(struct PCB *p){  // 用于输出当前链表中各结点的状态
    while (p != NULL){
        printf("\t%s", p->name);
        printf("\t%d", p->run_time);
        printf("\t%d", p->level);
        printf("\t%c", p->state);
        printf("\t%s\n", p->next->name);
        p = p->next; // 实现往后移
    }
    
}
int main()
{
    struct PCB *head, *tail, *p;
    head = creat();  // 调用函数 creat ，head 指向头结点
    p = head;
    printf(" 初始进程的情况 : \n");
    display(p);  // 显示当前结点的情况
    while(head->next != NULL) // 判断当前链表中的结点是否不止一个
    {
        struct PCB *q = head;
        struct PCB *previous;
        tail = head;
        while (tail->next != NULL) // 将 tail 指针指向尾结点
        {
            tail = tail->next;
            
        }
        printf(" 最新进程调度的情况 :  \n");
        printf("%s--->",head->name); // 输出最近调用的进程名
        display(q);  // 显示当前调用情况
        head->level--; // 优先数减 1
        head->run_time--; // 运行时间减 1
        if(head->run_time <= 0)  // 如果优先数最大的结点的运行时间小于或者等于0，则将该节点从链表中移除
        {
            head->state='E';
            head = head->next;
            
        }
        else
        {
            previous = head; // 判断其他情况
            p = previous->next;
            if (previous->level > p->level) //如果当前运行过的结点的优先数仍然是最大的，跳出本次循环
            {
                continue;
                
            }
            else
            {
                while (p->next != NULL)  // 否则，在链表中重新找到当前运行结点的位置
                {// 这个用于判断， 运行过的结点与后面的比较情况是否为比前一个结 点的优先数大比后一个结点的优先数小，如果是，将该节点插入其中，否则，往后移，直到 找到一个这样的位置，或者运行到链表结束
                    if ((previous->level <= p->level) &&
                        (previous->level >=p->next->level))
                    {
                        head = previous->next;
                        previous->next = p->next;
                        p->next = previous;
                        break;
                    }
                    else
                    {
                        p = p->next; // 实现往后移
                        
                    }
                    
                }
                if (p->next == NULL) // 如果 p->next 为空的话，表示当前运行 的结点的优先数最小，则将它放在链表的尾部
                {
                    head = previous->next;
                    tail->next = previous;
                    previous->next = NULL;
                }
            }
        }
    }
    if (head->next == NULL)  // 如果当前链表中只存在一个结点则进入判断内部
    {
        while (head->run_time != 0)  // 一直循环，将唯一一个结点的运行时间减到0 位置
        {
            printf(" 最新进程调度的情况 : \n");
            printf("%s--->",head->name);
            head->level--;
            head->run_time--;
            display(head);
        }
    }
    printf("END!\n");
    system("pause");
}
