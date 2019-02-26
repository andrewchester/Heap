class Heap{
	private:
		struct Node {
			Node* left;
			Node* right;
			int data;
		};

		int num_nodes;
		void delete_node(Node*);
		void sift_up(Node*);
		void sift_down(Node*);
		void print(Node* root);
		Node* search(Node* root, int current_depth, int depth);
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