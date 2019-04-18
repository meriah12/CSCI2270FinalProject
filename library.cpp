#include <iostream>

using namespace std;

#include "death.hpp"

Library::Library(int hashTableSize){
  this->hashTableSize=hashTableSize;
}

Library::~Library(){

}

void Library::checkOut(string title){
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

bookNode* Library::createBook(string title){
  bookNode* n = new bookNode;
  n->title=title;
  n->checkedOut=false;
  n->next=nullptr;
  return n;
}

void Library::addBook(string title){
  char titleChar = title[0];
  treeNode* foundTreeNode = searchTree(root,titleChar);
  if(foundTreeNode!=nullptr){
    foundTreeNode->numBooks++;
    unsigned int index = hash(title,hashTableSize);
    bookNode* n = createBook(title);
    if(foundTreeNode->hashTable[index]==nullptr){ //if index is empty
      n->next=nullptr;
      foundTreeNode->hashTable[index]=n;
    }
    else{ //if index is not empty
      n->next=foundTreeNode->hashTable[index];
      foundTreeNode->hashTable[index]=n;
    }
  }
  return;
}

treeNode* Library::searchTree(treeNode* curr, char titleChar){
  if(curr == nullptr) {
    return nullptr;
  }
  if(curr->titleChar == titleChar){
    return curr;
  }
  if(curr->titleChar > titleChar){
    return searchTree(curr->leftChild, titleChar);
  }
  if(curr->titleChar < titleChar){
    return searchTree(curr->rightChild, titleChar);
  }
  return nullptr;
}

bookNode* Library::search(string title){
  char titleChar = title[0];
  treeNode* foundTreeNode = searchTree(root,titleChar);
  if(foundTreeNode!=nullptr){//if the tree has a tree node for the title char
    unsigned int index = hash(title,hashTableSize);
    if(foundTreeNode->hashTable[index]->title==title){
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

treeNode* Library::addNode(string title){
  return addNodeHelper(root, title[0]);
}

treeNode* Library::addNodeHelper(treeNode* currNode, char title){
  treeNode* searched = searchTree(root,title);
  if(searched->titleChar == title){
    return searched;
  }
  else{
    if(currNode == nullptr){
      return createTreeNode(title);
    }
    else if(currNode->titleChar < title){
      currNode->rightChild = addNodeHelper(currNode->rightChild, title);
    }
    else if(currNode->titleChar > title){
      currNode->leftChild = addNodeHelper(currNode->leftChild, title);
    }
  }
  return nullptr;
}

unsigned int Library::hash(string title,int hashTableSize){
  unsigned int hashValue = 5381 ;
  int length = title.length();
  for(int i=0;i<length;i++){
    hashValue=((hashValue<< 5)+hashValue) + title[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}
