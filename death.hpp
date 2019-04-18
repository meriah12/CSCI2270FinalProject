#ifndef DEATH_HPP
#define DEATH_HPP

#include <string>

using namespace std;

struct bookNode{ //define node for each spot in hash table
  string title; //book title
  bool checkedOut; //true if book is checked out yet, false if in stock
  bookNode* next; //pointer to next node for open addressing
};
struct treeNode{ //define node at each spot in the tree with titleChar and pointer to hashTable
  string treeTitle;
  char titleChar; //first letter of book title
  treeNode* rightChild;
  treeNode* leftChild;
  treeNode* parent;
  int numBooks;
  bookNode** hashTable; //pointer to a hashTable
};
class Library{
  public:
    Library(int hashTableSize); //constructor creates tree with 26 nodes and 26 hash tables
    ~Library(); //destructor
    void checkOut(string title); //check out a book and set its bool to true
    void checkIn(string title); //check in a book and set its bool to false
    bookNode* createBook(string title);
    void addBook(string title); //add a book to the correct tree node at the correct spot in the hash table
    //void deleteBook(string title);
    treeNode* searchTree(treeNode* curr, char titleChar); //recursive search tree
    bookNode* search(string title); //search for a book in the tree then hash table
    treeNode* createTreeNode(char titleChar); //creates a treenode and its hash table
    treeNode* addNode(string title);//adding a new tree node
    treeNode* addNodeHelper(treeNode* currNode, char title);
   private:
    unsigned int hash(string title,int hashTableSize); //returns hash value
    treeNode* root; //private root variable
    // bookNode** hashTable; //private hashTable array variable
    int hashTableSize; //private hashtablesize variable
};
#endif
