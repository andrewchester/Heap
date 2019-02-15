class Heap{
	public:
		Node* root;

		void insert(int);
		void heapify(int*);
		void find(bool); //true for finding max, false for finding least


	private:
		int size;
		int calc_depth(int rsize, int depth, int pwidth, remainder, &go_left); 

		struct Node{
			Node* parent;
			Node* child;
			int num;
		}
};