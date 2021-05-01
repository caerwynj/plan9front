#include <u.h>
#include <libc.h>
#include <fcall.h>
#include <thread.h>
#include <9p.h>

void
srvforker(void (*fn)(void*), void *arg, int flag)
{
	switch(rfork(RFPROC|RFMEM|RFNOWAIT|flag)){
	case -1:
		sysfatal("rfork: %r");
	default:
		return;
	case 0:
		fn(arg);
		_exits(0);
	}
}
