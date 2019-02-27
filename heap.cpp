#include <iostream>
#include "heap.h"

Heap::Heap(){
	//Initialize the root as a null pointer and set the number of nodes to 0
	root = 0;
	num_nodes = 0;
}
//Helper for the print function, it prints all nodes at a certain depth, left to right
void Heap::print_helper(Node* root, int current_depth, int target_depth){
	if(current_depth > target_depth) //If we're too deep into the tree, return
		return;
	if(current_depth == target_depth){ //If this is the right depth, then print out the data of the node
		std::cout << root->data << " ";
		return;
	}
	if(current_depth < target_depth){ //If we need to go deeper
		if(root->left != 0) //Make sure left exists
			print_helper(root->left, current_depth + 1, target_depth); //Go down the left side
		if(root->right != 0) //Make sure right exists
			print_helper(root->right, current_depth + 1, target_depth); //Go down the right side
	}
}
//Prints the heap one layer at a time
void Heap::print(bool tree_output){
	int width = 1, size = num_nodes, total_depth = 1; //Declare the width, which is the current width of the tree at that depth, the size, which is the size of the tree, and the depth, which should be the depth of the tree
	while(size > width){ //When the width is greater than size, we're not at the bottom 
		size -= width; //Decrease size as we go further down
		width *= 2; //Calculate the total width of how many nodes should be at this depth when full
		total_depth++; //Increases the depth each time we go down
	}
	if(tree_output){
		int print_depth = 1; //The current depth of the heap we're printing
		width = 1; //Current width of the print depth
		while(print_depth <= total_depth){ 
			print_helper(root, 1, print_depth); //Prints out all nodes in the heap at the right depth
			std::cout << std::endl; 
			if(print_depth != total_depth){ //If we're not at the bottom of the list print out the right number of '/\'
				for(int i = 0; i < width; i++)
					std::cout << "/\\ ";
				std::cout << std::endl;
			}
			width *= 2; //Increase the width of the tree
			print_depth++; //Increase the print depth
		}
	}else{
		for(int i = 1; i <= total_depth; i++) //Loop through the layers and output it all in one go
			print_helper(root, 1, i);
		std::cout << std::endl;
	}
}

//Balances the heap from one node all the way to the top, checking the immediate right of the parent
void Heap::balance(Node* root, bool print){
	if(root == 0) //Just to make sure
		return;
	int root_data = root->data; //Set up temp variable for the root's data
	if(root->left != 0){
		int left_data = root->left->data; //Set up temp variable for the left nodes data
		if(left_data > root_data){
			// Swap the data if need be and output to logs 
			root->left->data = root_data;
			root->data = left_data;
			if(print)
				std::cout << "Swapped the position of " << root_data << " and " << left_data << std::endl;
		}
	}
	if(root->right != 0){
		int right_data = root->right->data; //Set up temp variable for the root's data
		if(right_data > root_data){
			// Swap data if need be an output to logs
			root->right->data = root_data;
			root->data = right_data;
			if(print)
				std::cout << "Swapped the position of " << root_data << " and " << right_data << std::endl;
		} 
	}
	if(root->parent != 0) //Call the same function on the parent if it isn't the top of the list
		balance(root->parent, print);
}

//Searches the heap for a spot to insert, from left to right, and then returns the node above the place where the new node will be inserted
Heap::Node* Heap::search(Node* root, int current_depth, int depth){ //Takes the node, the current depth of the node, and the insertion depth
	if(current_depth > depth - 1) //If we're too far in just return
		return 0;
	if(current_depth == depth - 1 && root->right == 0) //If there's an empty spot(fills from left to right so if right is null there's an empty space), then return the node
		return root;
	if(current_depth == depth - 1 && root->right != 0) //If it's full but we're at the insertion depth, return
		return 0;

	Node* new_root = search(root->left, current_depth + 1, depth); //Try going down the left side first
	if(new_root == 0) //If left side found no places to insert, go down the right side
		new_root = search(root->right, current_depth + 1, depth);
	return new_root; //Return whatever we've got in the end
}

//This function inserts a node at the next spot, from right to left, at the bottom of the tree. It uses insert_helper to insert the node 
void Heap::insert(int data, bool print){ //Determines whether or not we should print logs
	if(num_nodes == 0){ //Sets the root node's values if the tree is empty
		root = new Node();
		root->right = 0;
		root->left = 0;
		root->parent = 0;
		root->data = data;
		num_nodes++;
		return;
	}
	int width = 1, size = num_nodes, depth = 1; //Declare the width, which is the current width of the tree at that depth, the size, which is the size of the tree, and the depth, which should be the depth of the tree
	while(size > width){ //When the width is greater than size, we're not at the bottom 
		size -= width; //Decrease size as we go further down
		width *= 2; //Calculate the total width of how many nodes should be at this depth when full
		depth++; //Increases the depth each time we go down
	}
	if (num_nodes == 1 || width == size) //It doesn't go through the loop
		depth++;
	
	Node* insert_node = search(root, 1, depth); //Get the node above where we want to insert
	if(insert_node == 0){ 
		if(print)
			std::cout << "Couldn't find a spot to insert" << std::endl;
		return;
	}
	//Create a new node with the data to insert
	Node* new_node = new Node();
	new_node->data = data;
	new_node->left = 0;
	new_node->right = 0;
	new_node->parent = insert_node;
	if(insert_node->left == 0){ //If the left side is open, insert there
		insert_node->left = new_node;
		num_nodes++;
		if(print)
			std::cout << "Inserted " << data << " to the left of " << insert_node->data << std::endl;
		balance(insert_node, print);
		return;
	}
	if(insert_node->right == 0){ //If the right side is open, insert there after checking the left
		insert_node->right = new_node;
		num_nodes++;
		if(print)
			std::cout << "Inserted " << data << " to the right of " << insert_node->data << std::endl;
		balance(insert_node, print);
		return;
	}
	delete new_node; //This means we couldn't insert it so we just delete the node
	if(print)
		std::cout << "Couldn't insert node" << std::endl;
}
//Returns to total size of the heap
int Heap::size(){
	return num_nodes;
}
//Returns the max value of the heap, on a max heap it's just the root node
int Heap::find_max(){
	return root->data;
}