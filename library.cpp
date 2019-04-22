#include <iostream>

using namespace std;

#include "death.hpp"

Library::Library(int hashTableSize){
  this->hashTableSize=hashTableSize;
  this->root=createTree();
}

Library::~Library(){

}

treeNode* Library::createTree(){
  //creating tree excluding letters F, Q, X
  treeNode* root = createTreeNode('M');
  root->leftChild = createTreeNode('K');
  root->rightChild = createTreeNode('O');
  root->leftChild->leftChild = createTreeNode('I');
  root->leftChild->rightChild = createTreeNode('L');
  root->leftChild->leftChild->rightChild = createTreeNode('J');
  root->leftChild->leftChild->leftChild = createTreeNode('G');
  root->leftChild->leftChild->leftChild->rightChild = createTreeNode('H');
  root->leftChild->leftChild->leftChild->leftChild = createTreeNode('D');
  root->leftChild->leftChild->leftChild->leftChild->rightChild = createTreeNode('E');
  root->leftChild->leftChild->leftChild->leftChild->leftChild = createTreeNode('B');
  root->leftChild->leftChild->leftChild->leftChild->leftChild->rightChild = createTreeNode('C');
  root->leftChild->leftChild->leftChild->leftChild->leftChild->leftChild = createTreeNode('A');

  root->rightChild->leftChild = createTreeNode('N');
  root->rightChild->rightChild = createTreeNode('R');
  root->rightChild->rightChild->leftChild = createTreeNode('P');
  root->rightChild->rightChild->rightChild = createTreeNode('T');
  root->rightChild->rightChild->rightChild->leftChild = createTreeNode('S');
  root->rightChild->rightChild->rightChild->rightChild = createTreeNode('V');
  root->rightChild->rightChild->rightChild->rightChild->leftChild = createTreeNode('U');
  root->rightChild->rightChild->rightChild->rightChild->rightChild = createTreeNode('Y');
  root->rightChild->rightChild->rightChild->rightChild->rightChild->leftChild = createTreeNode('W');
  root->rightChild->rightChild->rightChild->rightChild->rightChild->rightChild = createTreeNode('Z');
  return root;
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

bookNode* Library::createBook(string title,string author){
  bookNode* n = new bookNode;
  n->title=title;
  n->author=author;
  n->checkedOut=false;
  n->next=nullptr;
  return n;
}

void Library::addBook(string title,string author){
  char titleChar = title[0];
  treeNode* foundTreeNode = searchTree(root,titleChar);
  if(foundTreeNode!=nullptr){
    foundTreeNode->numBooks++;
    unsigned int index = hash(title,hashTableSize);
    bookNode* n = createBook(title,author);
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
    if(foundTreeNode->hashTable[index]==nullptr){
      return nullptr;
    }
    else if(foundTreeNode->hashTable[index]->title==title){
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
      return nullptr;
    }
  }
  else
    return nullptr;
}

treeNode* Library::createTreeNode(char titleChar){
  treeNode* t = new treeNode;
  t->titleChar=titleChar;
  t->rightChild=nullptr;
  t->leftChild=nullptr;
  t->numBooks=0;
  t->hashTable=new bookNode*[hashTableSize];
  for(int i=0;i<hashTableSize;i++){
    t->hashTable[i] = nullptr;
  }
  return t;
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

void Library::printHashByAuthor(string author, treeNode* t){
  for(int i=0;i<hashTableSize-1;i++){
    if(t->hashTable[i]!=nullptr){
      if(t->hashTable[i]->author==author){
        cout<<t->hashTable[i]->title<<endl;
      }
      while(t->hashTable[i]->next!=nullptr){
        if(t->hashTable[i]->author==author){
          cout<<t->hashTable[i]->title<<endl;
        }
      }
    }
  }
  return;
}

void Library::printByAuthorHelper(string author, treeNode* currNode){
  if(currNode==nullptr){
    return;
  }
  else{
    if(currNode->leftChild!=nullptr){
      printByAuthorHelper(author,currNode->leftChild);
    }
    printHashByAuthor(author,currNode);
    if(currNode->rightChild!=nullptr){
      printByAuthorHelper(author,currNode->rightChild);
    }
    return;
  }
}

void Library::printByAuthor(string author){
  cout<<"All books written by "<<author<<":"<<endl;
  printByAuthorHelper(author,root);
  return;
}

void Library::printHashCheckedIn(treeNode* t){
  for(int i=0;i<hashTableSize-1;i++){
    if(t->hashTable[i]!=nullptr){
      if(!t->hashTable[i]->checkedOut){
        cout<<t->hashTable[i]->title<<endl;
      }
      while(t->hashTable[i]->next!=nullptr){
        if(!t->hashTable[i]->checkedOut){
          cout<<t->hashTable[i]->title<<endl;
        }
      }
    }
  }
  return;
}

void Library::printCheckedInHelper(treeNode* currNode){
  if(currNode==nullptr)
    return;
  else{
    if(currNode->leftChild!=nullptr)
      printCheckedInHelper(currNode->leftChild);
    printHashCheckedIn(currNode);
    if(currNode->rightChild!=nullptr)
      printCheckedInHelper(currNode->rightChild);
  }
}

void Library::printCheckedIn(){
  cout<<"All books currently avaliable to be checked out:"<<endl;
  printCheckedInHelper(root);
  return;
}

void Library::printHashCheckedOut(treeNode* t){
  for(int i=0;i<hashTableSize-1;i++){
    if(t->hashTable[i]!=nullptr){
      if(t->hashTable[i]->checkedOut){
        cout<<t->hashTable[i]->title<<endl;
      }
      while(t->hashTable[i]->next!=nullptr){
        if(t->hashTable[i]->checkedOut){
          cout<<t->hashTable[i]->title<<endl;
        }
      }
    }
  }
  return;
}

void Library::printCheckedOutHelper(treeNode* currNode){
  if(currNode==nullptr)
    return;
  else{
    if(currNode->leftChild!=nullptr)
      printCheckedOutHelper(currNode->leftChild);
    printHashCheckedOut(currNode);
    if(currNode->rightChild!=nullptr)
      printCheckedOutHelper(currNode->rightChild);
  }
}

void Library::printCheckedOut(){
  cout<<"All books currently checked out:"<<endl;
  printCheckedOutHelper(root);
  return;
}
