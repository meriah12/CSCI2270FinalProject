#include <iostream>

using namespace std;

#include "death.hpp"

Library::Library(int hashTableSize){

  //initilizes a hash table
  numBooks=0;
  this->hashTaleSize=hashTableSize;
  hashTable = new bookNode*[hashTableSize];
  for(int i=0;i<hashTableSize;i++){
    hashTable[i]=nullptr;
  }
}
Library::~Library(){

  //deletes a hash table
  for (int i=0; i<hashTableSize; i++){
    bookNode* head = hashTable[i];
    while(head!=nullptr){
      bookNode *current = head->next;
      head->next = nullptr;
      delete head;
      head = current;
    }
  }
  delete[] hashTable;
}

bookNode* Library::createBook(string title){
  bookNode* n = new bookNode;
  n->title=title;
  n->checkedOut=false;
  n->next=nullptr;
  return n;
}

void Library::addBook(string title,bookNode* hashTable[]){


  //add a book to the hash table
  numItems++;
  unsigned int index = hash(title);
  bookNode* n = createBook(title);
  if(hashTable[index]==nullptr){
    n->next=nullptr;
    hashTable[index]=n;
  }
  else{
    n->next=hashTable[index];
    hashTable[index]=n;
  }
  return;
}
treeNode* Library::searchTree(char titleChar){
  //search tree for titleChar and return the treeNode
}
bookNode* Library::search(string title){
  char titleChar = title[0];
  treeNode* foundTreeNode = searchTree(titleChar);
  if(foundTreeNode!=nullptr){//if the tree has a tree node for the title char
    unsigned int index = hash(title);
    if(foundTreeNode->hashTable[index]==title){
      return foundTreeNode->hashTable[index];
    }
    else{
      bookNode* temp = foundTreeNode->hashTable[index];
      while(temp!=nullptr){
        if(temp->title==title){
          return temp;
        }
        temp=temp->next;
      }
    }
  }
  return nullptr;
}
