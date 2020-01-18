#include "a3.h"
#include <string>

// Constructor
TRies::TRies(string data[],int sz){
	root_ = new Node();
	for (int i = 0; i < sz; i++) {
		addWord(data[i]);
	}
}

// Adds each word char by char into a tree and sets last letter to be terminal 
void TRies::addWord(const string& newWord){

	Node* curr = root_;

	for (size_t i = 0; i < newWord.length(); i++) {
		
		int index = newWord[i] - 'a';
		
		if (curr->children[index] == nullptr) {
			curr->children[index] = new Node();
		}

		curr = curr->children[index];
	}

	curr->terminal = true;

}

// Looks up a word in a tree if found returns true if not then false 
// If found the word but last letter is not terminal then also returns false
bool TRies::lookup(const string& word) const{

	Node* curr = root_;
	bool check = true;

	for (size_t i = 0; i < word.length(); i++) {

		int index = word[i] - 'a';

		if (curr->children[index] == nullptr) {
			check = false;
		}
		else {
			curr = curr->children[index];
		}
		
	}

	if (curr->terminal != true)
		check = false;

	return check;

}

// Recursive function to triverse through every branch of the tree that is related to the part of the word
// Serves suggest function
void TRies::triverse(Node* curr, string partWord, string suggestions[], int& cnt) const {

	if (curr->terminal == true) {
		suggestions[cnt++] = partWord;
	}

	for (int i = 0; i < Size; i++) {

		
		if (curr->children[i]) {
			char letter = char('a' + i);
			partWord.push_back(letter);
			triverse(curr->children[i], partWord, suggestions, cnt);
			partWord.pop_back();
		}
	}
}

// itterates through the part of the word, if all the letters are found calls the triverse function on the last letter..
// to check what other options are available for this partial word
int TRies::suggest(const string& partialWord, string suggestions[]) const{

	Node* curr = root_;
	int count = 0;
	bool check = true;

	for (size_t i = 0; i < partialWord.length(); i++) {

		int index = partialWord[i] - 'a';

		if (curr->children[index] != nullptr) {
			curr = curr->children[index];
		}
	
	}

	triverse(curr, partialWord, suggestions, count);


	return count;
}

// recursive function to assist constructor in node destruction
 void TRies::destroy(Node* subroot) {
	 for (size_t i = 0; i < Size; i++) {
		 if (subroot->children[i]) {
			 destroy(subroot->children[i]);
		 }
	 }
	 delete subroot;
}

// destructor
TRies::~TRies(){
	destroy(root_);
}