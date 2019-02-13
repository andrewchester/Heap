#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include "list.h"

void from_file(LinkedList* input, const char* path){
	std::ifstream file(path);
	char c;
	char token[100];
	for(int i = 0; i < sizeof(token); i++) token[i] = 0;
	int position = 0;
	while(file.get(c)){
		if(c == ' '){
			input->append(atoi(token));
			position = 0;
			for(int i = 0; i < sizeof(token); i++) token[i] = 0;
		}else {
			token[position] = c;
			position++;
		}
	}
}

int main(){
	LinkedList* input = new LinkedList();
	from_file(input, "./input.txt");
	std::cout << *input << std::endl;
	return 0;
}
