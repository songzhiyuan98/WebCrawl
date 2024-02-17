#include <stdlib.h>
#include <stdbool.h>
#include "bag.h"
#include "webpage.h" // 包含网页结构的文件


// 函数用来新建一个包，包含前节点和后节点，以及大小，节点包含webpage—t和下一个包节点的指针
struct bag *bag_new(void)
{
    struct bag *new_bag = malloc(sizeof(struct bag)); //为新包分配内存
    if (new_bag == NULL)
    {
        exit(EXIT_FAILURE); //分配内存失败
    }

    new_bag->front = NULL;
    new_bag->rear = NULL;
    new_bag->size = 0;

    return new_bag;//返回新包
}

// 函数用来判断该包是否为空，如果是，则返回true，参数为包结构
bool bag_is_empty(const struct bag *bag)
{
    return bag->size == 0; 
}

// 函数用来插入新的网页结构，参数：要加入的包名称，webpage—t结构（url，html，length，depth）
void bag_insert(struct bag *bag, webpage_t *page)
{
    struct bag_node *new_node = malloc(sizeof(struct bag_node)); //为新的包节点分配内存
    if (new_node == NULL)
    {
        exit(EXIT_FAILURE); // 分配内存失败
    }

    new_node->page = page; //插入参数webpage——t进入新节点
    new_node->next = NULL; 

    //判断该包是否为空
    if (bag_is_empty(bag))
    {
        bag->front = new_node; //该包为空，则新节点同时更新为前后节点
        bag->rear = new_node;
    }
    else
    {
        bag->rear->next = new_node; //在最后一个节点更新next节点为新插入的节点
        bag->rear = new_node; //更新最后一个节点rear指针指向新的节点
    }

    bag->size++; //更新包结构大小
}

// 函数根据先进先出FIFO的原则，返回最前面节点的webpage——t结构，参数为包结构名称
webpage_t *bag_extract(struct bag *bag)
{
    if (bag_is_empty(bag)) //判断如果包结构为空，则返回NULL，没有节点可返回
    {
        return NULL; // 返回NULL如果包结构为空
    }

    struct bag_node *front_node = bag->front; //创建一个节点用来储存包结构中最前面的节点
    webpage_t *front_page = front_node->page; //创建一个webpage——t来储存该新节点的网页结构

    bag->front = front_node->next; //根据先进先出的原则，先处理了第一个网页，next节点更新为包结构中最前面的节点
    free(front_node); //释放这个被抓取的节点，该节点抓取已完成

    bag->size--; //被抓取webpage——t之后更新包结构大小

    return front_page; //返回被抓取的最前面的节点的webpage——t
}

// 删除包结构，参数：包结构名称
void bag_delete(struct bag *bag)
{
    while (!bag_is_empty(bag))//当包结构中仍然存在节点时
    {
        bag_extract(bag); // 通过抓取函数删除剩余节点
    }

    free(bag); // 释放该包函数
}

