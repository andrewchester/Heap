#include <iostream>
#include "heap.h"

Heap::Heap(){
	//Initialize the root as a null pointer and set the number of nodes to 0
	root = 0;
	num_nodes = 0;
}

void Heap::print(Node* root){
	if(root == 0)
		return;
	std::cout << root->data << " ";
	print(root->left);
	print(root->right);
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
	heap.print(heap.root); //Pass the top of the tree, the width of the 
}

Heap::Node* Heap::search(Node* root, int current_depth, int depth){
	if(current_depth == depth - 1 && root->right == 0)
		return root;
	if(current_depth >= depth - 1 && root->right != 0){
		std::cout << "Returning zero at " << root->data << " Got a depth of: " << depth << " At depth of " << current_depth << std::endl; 
		return 0;
	}
	Node* new_root = search(root->left, ++current_depth, depth);
	if(new_root != 0)
		return new_root;
	return search(root->right, ++current_depth, depth);
}

//This function inserts a node at the next spot, from right to left, at the bottom of the tree. It uses insert_helper to insert the node 
void Heap::insert(int data){
	if(num_nodes == 0){ //Sets the root node's values if the tree is empty
		root = new Node();
		root->right = 0;
		root->left = 0;
		root->data = data;
		num_nodes++;
		std::cout << "Inserted " << data << " at 0" << std::endl;
		return;
	}
	int width = 1, size = num_nodes, depth = 1; //Declare the width, which is the current width of the tree at that depth, the size, which is the size of the tree, and the depth, which should be the depth of the tree
	while(size > width){ //When the width is greater than size, we're not at the bottom 
		size -= width; //Decrease size as we go further down
		width *= 2; //Calculate the total width of how many nodes should be at this depth when full
		depth++; //Increases the depth each time we go down
	}
	if (size == 1) //It doesn't go through the loop
		depth++;
	
	Node* insert_node = search(root, 1, depth);
	if(insert_node == 0){
		//std::cout << "Couldn't find a spot to insert" << std::endl;
		return;
	}
	Node* new_node = new Node();
	new_node->data = data;
	new_node->left = 0;
	new_node->right = 0;
	if(insert_node->left == 0){
		insert_node->left = new_node;
		num_nodes++;
		std::cout << "Inserted " << data << " to the left of " << insert_node->data << std::endl;
		return;
	}
	if(insert_node->right == 0){
		insert_node->right = new_node;
		num_nodes++;
		std::cout << "Inserted " << data << " to the right of " << insert_node->data << std::endl;
		return;
	}
	delete new_node;
	//std::cout << "Couldn't insert node" << std::endl;
}
//Returns to total size of the heap
int Heap::size(){
	return num_nodes;
}
//Returns the max value of the heap, on a max heap it's just the root node
int Heap::find_max(){
	return root->data;
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

bool Heap::insert_helper(int data, int current_depth, int insertion_depth, bool go_left, Node* root){
	current_depth++; //Increment the current depth, so we know what depth we're at
	std::cout << "Depth: " << current_depth << " got passed an insertion_depth of " << insertion_depth << " trying to insert: " << data << std::endl; 
	if(current_depth >= insertion_depth - 1){ //If we're right above the depth to insert at, which is going to be the level above the bottom of the tree
		//Create a new node and insert it if there are children available
		if(root->left == 0){ 
			Node* node = new Node();
			node->data = data;
			root->left = node;
			node->right = 0;
			node->left = 0;
			std::cout << "Inserted " << data << " at " << current_depth << " on the left side" << std::endl;
			return true;
		}else if(root->right == 0){
			Node* node = new Node();
			node->data = data;
			root->right = node;
			node->right = 0;
			node->left = 0;
			std::cout << "Inserted " << data << " at " << current_depth << " on the right side" << std::endl;
			return true;
		}
		//If it reaches this point, both children aren't null, meaning that we aren't going to insert here, and it returns false
		return false;
	} else if(go_left){ //If we want to go from the left of the tree to the right
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
*/