#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdio.h>
#include <stdlib.h>

//#define __DEBUG__

#ifdef __DEBUG__
	#define DBUG_SHOW(...) printf(__VA_ARGS__)
#else
	#define DBUG_SHOW(...)
#endif

#endif

