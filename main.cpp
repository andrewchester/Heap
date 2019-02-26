#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include "heap.h"

void from_file(Heap* heap, const char* path){
	std::ifstream file(path);
	char c;
	char token[100];
	for(int i = 0; i < sizeof(token); i++) token[i] = 0;
	int position = 0;
	while(file.get(c)){
		if(c == ' '){
			heap->insert(atoi(token));
			position = 0;
			for(int i = 0; i < sizeof(token); i++) token[i] = 0;
		}else {
			token[position] = c;
			position++;
		}
	}
}

int main(){
	Heap heap = Heap();
	//from_file(&heap, "./input.txt");
	heap.insert(97);
	heap.insert(58);
	heap.insert(71);
	heap.insert(31);
	heap.insert(84);
	heap.insert(46);
	heap.insert(85);
	//std::cout << heap << std::endl;
	return 0;
}
