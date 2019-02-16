class Heap{
	private:
		struct Node {
			Node* left;
			Node* right;
			int data;
		};

		int num_nodes;
		bool insert_helper(int data, int current_depth, int insertion_depth, bool go_left, Node* root);

		void delete_node(Node*);
		void sift_up(Node*);
		void sift_down(Node*);
		void print(Node* root, int pre_spaces, bool new_line, int depth);
	public:
		Heap();

		Node* root;

		friend std::ostream& operator<<(std::ostream& os, Heap& list); //Printing out the heap using << 

		void insert(int data);
		void remove(int data);

		Heap* heapify(int*);
		Heap* merge(Heap*);
		Heap* meld(Heap*);
		
		int find_max();
		int size();
		bool is_empty();
};