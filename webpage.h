// WEBPAGE_H

#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <stdlib.h>

// 定义webpage——t结构：包含URL，HTML网页，legnth，深度
struct webpage {
    char *url;
    char *html;
    size_t length;
    int depth;
};

typedef struct webpage webpage_t;


webpage_t *webpage_create(const char *url, const char *html, size_t length, int depth);

void webpage_save(const webpage_t *page, const char *pageDirectory, const int documentID);

void webpage_delete(webpage_t *page);

#endif

