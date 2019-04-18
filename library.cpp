#include <iostream>

using namespace std;

#include "death.hpp"

Library::Library(int hashTableSize){
  this->hashTableSize=hashTableSize;
}
Library::~Library(){
  //deletes a single hash table
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
treeNode* Library::createTreeNode(char titleChar){
  treeNode* t = new treeNode;
  t->titleChar=titleChar;
  t->numBooks=0;
  t->hashTable=new bookNode*[hashTableSize];
  for(int i=0;i<hashTableSize;i++){
    t->hashTable[i] = nullptr;
  }
  return t;
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
  if(foundTreeNode!=nullptr){
    foundTreeNode->numBooks++;
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
  }
  return;
}
treeNode* Library::searchTreeHelper(treeNode* curr, char firstChar){
  //search tree for titleChar and return the treeNode
  if(curr == NULL) {
    return NULL;
  }

  if(curr->titleChar == firstChar){
    return curr;
  }

  if(curr->titleChar > firstChar){
    return searchTreeHelper(curr->leftChild, firstChar);
  }

  if(curr->titleChar < firstChar){
    return searchTreeHelper(curr->rightChild, firstChar);
  }
}

treeNode* Library::searchTree(char titleChar){
  treeNode* tree = searchTreeHelper(root, titleChar);

  if(tree != NULL){
    return tree;
  }
  else{
    cout << "Character not present in the tree" << endl;
    return 0;
  }
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
    cout<<title<<" can't be checked in because it's not in the inventory.";
}

treeNode* Library::addNodeHelper(treeNode* currNode, char title){
  treeNode* searched = searchTree(title);
  if(searched->titleChar == title){
    return searched;
  }
  else{

    if(currNode == NULL){
      return createTreeNode(title);
    }
    else if(currNode->titleChar < title){
      currNode->rightChild = addNodeHelper(currNode->rightChild, title);
    }
    else if(currNode->titleChar > title){
      currNode->leftChild = addNodeHelper(currNode->leftChild, title);
    }
  }
}

treeNode* Library::addNode(string treeTitle){
  addNodeHelper(root, treeTitle[0]);
}