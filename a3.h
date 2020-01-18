#include <string>
using namespace std;
const int Size = 26;

class TRies{
	// Node struct for the tree creation
	struct Node {
		Node* children[Size];
		bool terminal; // set to true if last letter of the word 
		Node(bool tr = false) { // constructor sets all the children nodes to safe state
			terminal = tr;
			for (int i = 0; i < Size; i++) {
				children[i] = nullptr;
			}
		}
	};
	Node* root_;

public:
	// constructor
	TRies(string data[],int sz);
	// adds word to the tree
	void addWord(const string& newWord);
	// looks for a word in a tree
	bool lookup(const string& word) const;
	// suggest any possible words based on partialWord
	int suggest(const string& partialWord, string suggestions[]) const;
	// supports suggest function to triverse through tree branches
	void triverse(Node* curr, string partWord, string suggestions[], int& cnt)const;
	// supports destructor
	void destroy(Node* subroot);
	// destructor
	~TRies();	
};