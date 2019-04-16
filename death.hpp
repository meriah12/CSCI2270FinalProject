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
  char titleChar; //first letter of book title
  treeNode* rightChild = nullptr;
  treeNode* leftChild = nullptr;
  treeNode* parent = nullptr;
  bookNode* hashTable; //pointer to a hashTable
};
class Library{
  public:
    Library(int hashTableSize); //constructor creates tree with 26 nodes and 26 hash tables
    ~Library(); //destructor
    void checkOut(string title); //check out a book and set its bool to true
    void checkIn(string title); //check in a book and set its bool to false
    void addBook(bookNode* node); //add a book to the correct tree node at the correct spot in the hash table
    bool search(string title); //search for a book in the tree then hash table

  private:
    unsigned int hash(string title); //returns hash value
    treeNode* searchTree(char titleChar); //recursive search tree helper
    treeNode* root; //private root variable
    bookNode** hashTable; //private hashTable array variable
    int hashTableSize; //private hashtablesize variable
    int numBooks; //hashTable size (for each tree node)
};
#endif
