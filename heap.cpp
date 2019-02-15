#include "heap.h"

int Heap::calc_depth(int rsize, int depth, int pwidth, int remainder, bool &go_left){
	rsize -= pwidth;
	int cwidth = pwidth * 2;
	if(rsize < 0){
		remainder = rsize * -1;
		go_left = remainder > cwidth / 2 ? true : false;
		return depth;
	}
	if(rsize == 0){
		go_left = true;
		return ++depth;
	}
	return calc_depth(rsize, ++depth, cwidth, remainder, go_left); 
}