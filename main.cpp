#include <iostream>
#include <cstdlib>
#include <fstream>
#include "list.h"


void from_file(LinkedList* input, const char* path){
	std::ifstream file(path);
	char c;
	char token[100];
	for(int i = 0; i < sizeof(token); i++) token[i] = 0;
	int position = 0;
	while(file >> c) {
		if(c != ' '){
			token[position] = c;
			position++;
		}else{
			input->append(std::atoi(token));
			for(int i = 0; i < sizeof(token); i++) token[i] = 0;
			position = 0;
		}
	}
}

int main(){
	LinkedList* input = new LinkedList();
	from_file(input, "./input.txt");
	std::cout << *input << std::endl;
	return 0;
}