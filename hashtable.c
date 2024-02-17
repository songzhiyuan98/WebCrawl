#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"

// hash function to calculate hash value
size_t hash_function(const char *key, size_t capacity)
{
    size_t hash = 0;
    const unsigned int prime = 31; // A common prime number used in hash functions

    // calculate the hash value
    while (*key != '\0')
    {
        hash = (hash * prime) + (*key);
        key++;
    }

    // Modulo to ensure the result is within the capacity of the hashtable
    return hash % capacity;
}

// function to create new hashtable
struct hashtable *hashtable_new(size_t capacity)
{
    struct hashtable *ht = malloc(sizeof(struct hashtable)); //assign space for hashtable
    //determine the hashtable was null
    if (ht == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for hashtable\n");
        exit(EXIT_FAILURE);
    }

    //assign space for each value in the hashtable
    ht->keys = calloc(capacity, sizeof(char *));
    ht->documentIDs = malloc(capacity * sizeof(int));
    ht->occupied = calloc(capacity, sizeof(bool));
    ht->capacity = capacity;
    ht->size = 0;

    //determine if its successful
    if (ht->keys == NULL || ht->documentIDs == NULL || ht->occupied == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for hashtable\n");
        exit(EXIT_FAILURE);
    }

    //return new hashtable
    return ht;
}

// add hashtable with id
bool hashtable_insert_with_id(struct hashtable *ht, const char *key, int documentID)
{
    // determine if its full
    if (ht->size >= ht->capacity)
    {
        fprintf(stderr, "Error: Hashtable is full\n");
        return false;
    }

    // assign key by hash function
    size_t index = hash_function(key, ht->capacity);

    // loop to check if its occupied alrady 
    while (ht->occupied[index])
    {
        // 查看该哈希值的布尔函数，查看该URL是否已经存在，再进行对比以防止出现冲突
        if (strcmp(ht->keys[index], key) == 0)
        {
            return false; // 返回false该URL已经存在
        }

        // 移动index到下一位，循环查找是否有某个Key已经存在？？不确定有没有必要移动到下一位
        index = (index + 1) % ht->capacity;
    }

    // 该参数Key没有出现在哈希表里，复制新的参数Key到该哈希值里
    ht->keys[index] = strdup(key);
    //未能成功分配内存
    if (ht->keys[index] == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for key\n");
        exit(EXIT_FAILURE);
    }

    // 将参数ID储存到新哈希值的变量中
    ht->documentIDs[index] = documentID;

    // 将已储存的哈希值，布尔值更改为true
    ht->occupied[index] = true;

    // 哈希表大小加一
    ht->size++;

    return true;
}

// 函数用于获取ID，参数为哈希表，Key
int hashtable_get_document_id(struct hashtable *ht, const char *key)
{
    // 获取该参数Key的哈希值并赋值给变量index
    size_t index = hash_function(key, ht->capacity);

    // 循环查找，该哈希值的布尔值为true，已存在的哈希值
    while (ht->occupied[index])
    {
        if (strcmp(ht->keys[index], key) == 0)
        {
            return ht->documentIDs[index]; //确认URL相同，并返回该Key值的ID
        }

        // 哈希值移到下一位
        index = (index + 1) % ht->capacity;
    }

    // 该Key未找到
    return -1;
}

// 函数用于删除哈希表，释放空间
void hashtable_delete(struct hashtable *ht)
{
    // 释放空间
    for (size_t i = 0; i < ht->capacity; i++)
    {
        //如果该值存在，则释放空间
        if (ht->occupied[i])
        {
            free(ht->keys[i]);
        }
    }

    free(ht->keys);
    free(ht->documentIDs);
    free(ht->occupied);
    free(ht);
}

