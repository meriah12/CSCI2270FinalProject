
#ifndef DEATH_HPP
#define DEATH_HPP

#include <string>

using namespace std;

struct bookNode{ //define node for each spot in hash table
  string title; //book title
  string author; //book author
  bool checkedOut; //true if book is checked out yet, false if in stock
  bookNode* next; //pointer to next node for open addressing
  int count; //Counts how many of the same book are in the library
};
struct treeNode{ //define node at each spot in the tree with titleChar and pointer to hashTable
  char titleChar; //first letter of book title
  treeNode* rightChild;
  treeNode* leftChild;
  int numBooks;
  bookNode** hashTable; //pointer to a hashTable
};
class Library{
  public:
    treeNode* createTree();
    Library(int hashTableSize); //constructor creates tree with 26 nodes and 26 hash tables
    ~Library(); //destructor
    void checkOut(string title); //check out a book and set its bool to true
    void checkIn(string title); //check in a book and set its bool to false
    bookNode* createBook(string title,string author);
    void addBook(string title,string author); //add a book to the correct tree node at the correct spot in the hash table
    //void deleteBook(string title);
    void printHashByAuthor(string author, treeNode* t);
    void printByAuthorHelper(string author, treeNode* currNode);
    void printByAuthor(string author);
    treeNode* searchTree(treeNode* curr, char titleChar); //recursive search tree
    bookNode* search(string title); //search for a book in the tree then hash table
    treeNode* createTreeNode(char titleChar); //creates a treenode and its hash table
   private:
    unsigned int hash(string title,int hashTableSize); //returns hash value
    treeNode* root; //private root variable
    // bookNode** hashTable; //private hashTable array variable
    int hashTableSize; //private hashtablesize variable
};
#endif
