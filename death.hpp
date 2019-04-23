
#ifndef DEATH_HPP
#define DEATH_HPP

#include <string>

using namespace std;

struct bookNode{ //define node for each spot in hash table
  string title; //book title
  string author; //book author
  bookNode* next; //pointer to next node for open addressing
  int count; //Counts how many of the same book are in the library
  int inCount; //Keeps track of the number of the same book not checked out in library
};
struct treeNode{ //define node at each spot in the tree with titleChar and pointer to hashTable
  char titleChar; //first letter of book title
  treeNode* rightChild;
  treeNode* leftChild;
  int numBooks; //number of books in the hash table
  bookNode** hashTable; //pointer to a hashTable
};
class Library{
  public:
    void printBooks(treeNode *node, bookNode *title);
    treeNode* createTree(); //creates 23 nodes, called in constructor
    void deleteHash(treeNode* t); //deletes contents of a tree nodes hash table
    void deleteTree(treeNode* currNode); //deletes each node of the BST, called in destructor
    Library(int hashTableSize); //constructor creates tree with 23 nodes and 23 hash tables
    ~Library(); //destructor
    void checkOut(string title); //check out a book and set its bool to true
    void checkIn(string title); //check in a book and set its bool to false
    bookNode* createBook(string title,string author);
    void addBook(string title,string author); //add a book to the correct tree node at the correct spot in the hash table
    void deleteBook(string title); //deletes a book from inventory
    void printHashByAuthor(string author, treeNode* t); //prints all books in hash table by author
    void printByAuthorHelper(string author, treeNode* currNode); //called by print by author
    void printByAuthor(string author); //prints every book by the same author
    treeNode* searchTree(treeNode* curr, char titleChar); //recursive search tree
    bookNode* search(string title); //search for a book in the tree then hash table
    treeNode* createTreeNode(char titleChar); //creates a treenode and its hash table
    void printHashCheckedIn(treeNode* t); //prints all nodes in a hash table that have books that are checked in
    void printCheckedInHelper(treeNode* currNode); //recursive search tree
    void printCheckedIn(); //prints all avaliable books to check out
    void printHashCheckedOut(treeNode* t); //prints all books in hash table that are checked out
    void printCheckedOutHelper(treeNode* currNode); //recursive search tree
    void printCheckedOut(); //prints all checked out books

   private:
    unsigned int hash(string title,int hashTableSize); //returns hash value
    treeNode* root; //private root variable
    int hashTableSize; //private hashtablesize variable
};
#endif
