#ifndef PAGEDIR_H
#define PAGEDIR_H

#include <stdbool.h>

#include "crawler.h"

/**
 * Initializes the page directory so that webpages can be saved in it.
 * Returns true if initialization succeeded, false otherwise.
 */
bool pagedir_init(const char *pageDirectory);

#endif
