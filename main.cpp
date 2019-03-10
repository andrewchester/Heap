#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include "heap.h"

//Gets integers from a file
//Format: 1 2 3 4 
void from_file(Heap* heap, const char* path){
	std::ifstream file(path);
	char c; //Holds the current character being read
	char token[100]; //Characters are added to a token
	for(int i = 0; i < sizeof(token); i++) token[i] = 0; //Reset token's values
	int position = 0; //Track the position inside of token to add
	while(file.get(c)){
		if(c == ' '){ //If we get a space
			heap->insert(atoi(token), false); //Add token to the heap
			position = 0; //Reset the position in token
			for(int i = 0; i < sizeof(token); i++) token[i] = 0; //And reset token to all zeros
		}else { //If another character
			token[position] = c;//Add it to token
			position++; //Increment position
		}
	}
}

int main(){
	Heap heap = Heap();
	char* input = new char[10]; //Holds the input of the user
	while(true){
		std::cout << "Enter command(input, exit, print, output, remove, size, max): ";
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
		}else if(strcmp(input, "remove") == 0){
			std::cout << "Enter number to remove: ";
			std::cin.get(input, 100);
			std::cin.clear();
			std::cin.ignore(100, '\n');

			heap.remove(atoi(input));
		}else if(strcmp(input, "size") == 0){
			std::cout << heap.size() << std::endl;
		}else if(strcmp(input, "max") == 0){
			std::cout << heap.find_max() << std::endl;
		}else{
			std::cout << "Not sure what that command is..." << std::endl;
		}
	}
	delete[] input;
	return 0;
}
