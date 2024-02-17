#include "pagedir.h"
#include <stdio.h>

bool pagedir_init(const char *pageDirectory)
{
	// Fill in with your implementation
	// 初始化判断目录是否不存在
	if (pageDirectory == NULL || pageDirectory[0] == '\0')
	{
		fprintf(stderr, "Error, invalide pageDirectory");
		return false;
	}

	return true;
}

