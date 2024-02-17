#ifndef BAG_H
#define BAG_H

#include <stdbool.h>
#include "webpage.h"

struct bag_node {
    webpage_t *page;        
    struct bag_node *next;   
};

struct bag {
    struct bag_node *front;   
    struct bag_node *rear;    
    size_t size;              
};

typedef struct bag bag_t;

bag_t *bag_new(void);

bool bag_is_empty(const bag_t *bag);

void bag_insert(bag_t *bag, webpage_t *page);

webpage_t *bag_extract(bag_t *bag);

void bag_delete(bag_t *bag);

#endif // BAG_H
