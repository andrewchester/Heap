class Heap{
	private:
		struct Node {
			Node* left;
			Node* right;
			Node* parent;
			int data;
		};

		int num_nodes;
		void delete_node(Node*);
		void sift_up(Node*);
		void sift_down(Node*);
		void balance(Node*);
		void print_helper(Node* root, int current_depth, int target_depth);
		Node* search(Node* root, int current_depth, int depth);
	public:
		Heap();
		Node* root;

		void insert(int data);
		void remove(int data);

		Heap* heapify(int*);
		Heap* merge(Heap*);
		Heap* meld(Heap*);
		
		int find_max();
		int size();
		bool is_empty();

		void print(bool);
};