#include <iostream>
#include "heap.h"

Heap::Heap(){
	//Initialize the root as a null pointer and set the number of nodes to 0
	root = nullptr;
	num_nodes = 0;
}


/* 
	This function prints the node, and all of its children recursively in a structure that mimics the heap when printed
	Parameters:
		root - The node we're operating on
		pre_spaces - The number of spaces to put before the node's data. This is only passed to nodes on the leftmost side of the tree. All right nodes get a 0 for this variable, including all their children
		new_line - A boolean value determining whether or not to indent. This is passed only to rightside nodes, all leftside nodes, and their children, will have a false for this value.
		depth - tracks the depth from the current node. This is used to determine the number of spaces we need to put inbetween each output to keep the tree lookin prestine.

	Sample Output(hopefully):
					  100
				    90   80
				  70 70 70 70	
*/
void Heap::print(Node* root, int pre_spaces, bool new_line, int depth){
	for(int i = 0; i < pre_spaces; i++) //Inserts spaces before a node, if the node isn't a leftmost node, pre_spaces will be 0
		std::cout << " ";
	std::cout << root->data; //Output the value of the node we're on
	for(int i = 0; i < depth; i++) //Output spaces on the end of the node's value depending on how deep the rest of the tree is, so the nodes at the bottom will be close together and the top will be farther apart
		std::cout << " ";
	if(new_line) //Indent if we're at the end of of a branch??????(what do you call the right edge of a tree???)
		std::cout << std::endl;
	if(root->left) //Go print out the left side if it exists
		print(root->left, --pre_spaces, false, --depth); //deincrement the number of spaces to put in the front and the depth. Pass false for new_line since we're going left, this false will be passed to all their children
	if(root->right)
		print(root->right, 0, new_line, --depth); //Same deal over here, but passing whatever we got as new_line from the node above and setting 0 for pre_spaces
}


//Prints out the whole heap using the print() recursive function when you 
std::ostream& operator<<(std::ostream& os, Heap& heap){
	int width = 1, size = heap.size(), depth = 1; //Declare the width, which is the current width of the tree at that depth, the size, which is the size of the tree, and the depth, which should be the depth of the tree
	while(size > width){ //When the width is greater than size, we're not at the bottom 
		size -= width; //Decrease size as we go further down
		width *= 2; //Calculate the total width of how many nodes should be at this depth when full
		depth++; //Increases the depth each time we go down
	}
	//When the above loop finishes, we'll have the width of the base of the tree and the total depth
	
	heap.print(heap.root, width / 2, true, depth); //Pass the top of the tree, the width of the 
}

/*
	This function is a recursive helper function to the insert method. It inserts a new node from left to right at the max depth of the tree.
	It returns a true or false value based on if it inserted a node or not, or if a node was inserted below it, meaning at the end, a true or false value is returned all the way to the top
	Parameters:
		data - The data to write to the new node
		current_depth - the depth of the current node being operated on
		insertion_depth - the depth where the new node is going to be inserted to
		go_left - whether or not to go left to right or right to left when looking for a spot to insert a node
		root - the current node

	if we're at the depth above where we need to insert:
		insert a new node
		return true
	if we need to go left before right:
		if go left: <- will return a true/false value if there was a node inserted down the left side of the tree
			return true
		if go right:
			return true
		return false
	if we need to go right before left:
		if go right: 
			return true
		if go left:
			return true
		return false
*/
bool Heap::insert_helper(int data, int current_depth, int insertion_depth, bool go_left, Node* root){
	current_depth++; //Increment the current depth, so we know what depth we're at
	if(current_depth >= (insertion_depth - 1)){ //If we're right above the depth to insert at, which is going to be the level above the bottom of the tree
		//Create a new node and insert it if there are children available
		if(!root->left){ 
			Node* node = new Node();
			node->data = data;
			root->left = node;
			return true;
		}else if(!root->right){
			Node* node = new Node();
			node->data = data;
			root->right = node;
			return true;
		}
		//If it reaches this point, both children aren't null, meaning that we aren't going to insert here, and it returns false
		return false;
	}
	if(go_left){ //If we want to go from the left of the tree to the right
		if(insert_helper(data, ++current_depth, insertion_depth, go_left, root->left)) //If we inserted a node below this node, return true
			return true; 
		if(insert_helper(data, ++current_depth, insertion_depth, go_left, root->right)) //If we inserted a node below below this node, return true
			return true;
		return false; //Return false if no nodes were inserted
	}else{
		if(insert_helper(data, ++current_depth, insertion_depth, go_left, root->right))//If we inserted a node below below this node, return true
			return true;
		if(insert_helper(data, ++current_depth, insertion_depth, go_left, root->left))//If we inserted a node below below this node, return true
			return true;
		return false; //Return false if no nodes were inserted
	}
}

//This function inserts a node at the next spot, from right to left, at the bottom of the tree. It uses insert_helper to insert the node 
void Heap::insert(int data){
	if(num_nodes == 0){ //Sets the root node's values if the tree is empty
		root->data = data;
		num_nodes++;
		return;
	}

	bool go_left = true;
	int width = 1, size = num_nodes, depth = 1; //Declare the width, which is the current width of the tree at that depth, the size, which is the size of the tree, and the depth, which should be the depth of the tree
	while(size > width){ //When the width is greater than size, we're not at the bottom 
		size -= width; //Decrease size as we go further down
		width *= 2; //Calculate the total width of how many nodes should be at this depth when full
		depth++; //Increases the depth each time we go down
	}
	if(size > width / 2)
		go_left = false;
	//When the above loop finishes, we'll have the width of the base of the tree and the total depth as well as knowing whether or not to go left
	
	if(insert_helper(data, 0, depth, go_left, root)) //Go insert the node using a recursive function that takes values from the loop 
		num_nodes++;
	else
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