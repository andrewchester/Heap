class Heap{
	private:
		struct Node { 
			Node* left;
			Node* right;
			Node* parent;
			int data;
		};

		int num_nodes; //Tracks number of nodes in heap, used in calculating depth mathematically
		void balance(Node*, bool); //Balances the tree from a node up(down?) to the root
		void print_helper(Node* root, int current_depth, int target_depth); //A helper function for print()
		Node* search(Node* root, int current_depth, int depth); //Searches the tree for a spot to insert
		Node* search(Node* root, int data); //Searches the tree for a node with a given data parameter
		void find_last_inserted(Node* root, Node* &lastinserted, int current_depth, int depth); //Finds the leftmost node at the bottom depth
	public:
		Heap();
		Node* root;

		void insert(int data, bool print); //Inserts a node to the heap
		void remove(int data); //Removes a node by number from the heap
		
		int find_max(); //Returns max value
		int size(); //Returns size of heap
		bool is_empty(); //Returns if the heap is empty

		void print(bool); //Prints the heap
};