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
			heap->insert(atoi(token), false);
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
	char* input = new char[10];
	while(true){
		std::cout << "Enter command(input, exit, print, output): ";
		std::cin.get(input, 10);
		std::cin.clear();
		std::cin.ignore(100, '\n');

		if(strcmp(input, "input") == 0){
			std::cout << "File or Manual input(file,manual): ";
			std::cin.get(input, 10);
			std::cin.clear();
			std::cin.ignore(100, '\n');

			if(strcmp(input, "file") == 0){
				char* filepath = new char[200];
				std::cout << "Enter path: ";
				std::cin.get(filepath, 200);
				std::cin.clear();
				std::cin.ignore(100, '\n');

				from_file(&heap, filepath);
				delete[] filepath;
			}else if(strcmp(input, "manual") == 0){
				char* number = new char[10];
				while(true){
					std::cout << "Enter number(type exit to leave): ";
					std::cin >> number;
					std::cin.clear();
					std::cin.ignore(100, '\n');

					if(strcmp(number, "exit") == 0)
						break;
					heap.insert(atoi(number), true);
				}
				delete[] number;
			}
		}else if(strcmp(input, "exit") == 0){
			break;
		}else if(strcmp(input, "print") == 0){
			heap.print(true);
		}else if(strcmp(input, "output") == 0){
			heap.print(false);
		}else{
			std::cout << "Not sure what that command is..." << std::endl;
		}
	}
	delete[] input;
	/*
	//from_file(&heap, "./input.txt");
	heap.insert(97);
	heap.insert(58);
	heap.insert(71);
	heap.insert(31);
	heap.insert(84);
	heap.insert(46);
	heap.insert(85);
	//std::cout << heap << std::endl;
	*/
	return 0;
}
