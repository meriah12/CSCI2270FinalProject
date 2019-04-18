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

void Library::addBook(string title){
  char titleChar = title[0];
  treeNode* foundTreeNode = searchTree(titleChar);
  numItems++;
  unsigned int index = hash(title);
  bookNode* n = createBook(title);
  if(foundTreeNode->hashTable[index]==nullptr){ //if index is empty
    n->next=nullptr;
    foundTreeNode->hashTable[index]=n;
  }
  else{ //if index is not empty
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
void Libary::checkOut(string title){
  bookNode* found = search(title);
  if(found!=nullptr&&found->checkedOut==false)
    found->checkedOut=true;
  else if(found!=nullptr&&found->checkedOut==true)
    cout<<title<<" already checked out."<<endl;
  else
    cout<<title<<" can't be checked out because it's not in the inventory."<<endl;
  return;
}
void Library::checkIn(string title){
  bookNode* found = search(title);
  if(found!=nullptr&&found->checkedOut==true)
    found->checkedOut=false;
  else if(found!=nullptr&&found->checkedOut==false)
    cout<<title<<" has not been checked out."<<endl;
  else
    cout<<title<<" can't be checked in because it's not in the inventory."
}
