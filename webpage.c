#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webpage.h"

// 函数用来创建新webpage——t结构，参数：url，html，length，depth
webpage_t *webpage_create(const char *url, const char *html, size_t length, int depth)
{
    // 为新webpage——t结构分配内存
    webpage_t *new_webpage = malloc(sizeof(webpage_t));

    // 检查是否成功为新webpage结构分配内存
    if (new_webpage == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for webpage\n"); //未能成功分配内存
        exit(EXIT_FAILURE);
    }

    // 给新webpage结构赋值url
    new_webpage->url = strdup(url);
    // 检查是否成功为新webpage结构的url分配内存
    if (new_webpage->url == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for URL\n"); //未能成功分配内存
        exit(EXIT_FAILURE);
    }

    // 检查新插入的html是否为null
    if (html != NULL)
    {
        new_webpage->html = strdup(html);

	//check if allocation was succsesful
	if (new_webpage->html == NULL){
		fprintf(stderr, "Error: Unable to allocate memory for HTML");
		exit(EXIT_FAILURE);
    }	
	new_webpage->length = length;
    }
    else
    {
        new_webpage->html = NULL;
        new_webpage->length = 0;
    }

    // 给新webpage结构的length以
    new_webpage->depth = depth;

    //新的webpage——t结构创建结束，返回新的webpage结构
    return new_webpage;
}

// 函数用于在特定目录下把网址，爬行深度，网页内容输入至文件，文件名以ID命名，参数：webpage结构，目录，ID
void webpage_save(const webpage_t *page, const char *pageDirectory, const int documentID)
{
    // 创建字符组来储存文件名，通过目录/ID生成文件名
    char filename[100]; //100是储存文件路径的字符组的长度
    sprintf(filename, "%s/%d", pageDirectory, documentID); //文件名形式，目录/ID

    // 打开filename储存的文件名，并写入文件
    FILE *file = fopen(filename, "w");
    //如果该文件为空，则写入失败
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing\n"); //文件写入失败，无法打开文件
        exit(EXIT_FAILURE);
    }

    // 第一行先写入URL，参数中webpage结构获取URL
    fprintf(file, "URL: %s\n", page->url);

    // 第二行写入爬取深度，参数中webpage结构获取Depth
    fprintf(file, "Depth: %d\n", page->depth);

    // 第三行写入网页内容，参数重webpage结构获取html
    fprintf(file, "HTML:\n%s\n", page->html);

    // 写入完毕，关闭文件
    fclose(file);
}

// 为该webpage——t结构释放内存，参数为webpage——t结构
void webpage_delete(webpage_t *page)
{
    // 给URL和HTML释放内存
    free(page->url);
    free(page->html);

    // 给webpage——t释放内存
    free(page);
}

