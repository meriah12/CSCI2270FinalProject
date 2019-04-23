#include <iostream>

using namespace std;

#include "death.hpp"

Library::Library(int hashTableSize){
  this->hashTableSize=hashTableSize;
  this->root=createTree();
  return;
}

void Library::deleteHash(treeNode* t){
  for(int i=0;i<hashTableSize-1;i++){
    bookNode* current = t->hashTable[i];
    bookNode* next;
    while(current!=nullptr){
      next=current->next;
      delete current;
      current=next;
    }
  }
  return;
}

void Library::deleteTree(treeNode* currNode){
  if(currNode==nullptr)
    return;
  deleteTree(currNode->leftChild);
  deleteTree(currNode->rightChild);
  deleteHash(currNode);
  delete currNode;
}

Library::~Library(){
  deleteTree(root);
  root=nullptr;
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
  if(found!=nullptr&&found->inCount > 0){
    //found->checkedOut=true;
    found -> inCount = found -> inCount - 1;
  }
  else if(found!=nullptr&&found->inCount == 0)
    cout<< "All copies of " << title << " are already checked out."<<endl;
  else
    cout<<title<<" can't be checked out because it's not in the inventory."<<endl;
  return;
}

void Library::checkIn(string title){
  bookNode* found = search(title);
  if(found!=nullptr && found -> inCount < found -> count){
    //found->checkedOut=false;
    found -> inCount = found -> inCount + 1;
  }
  else if(found!=nullptr&&found->inCount == found -> count)
    cout << "All copies of "<< title << " are not checked out."<<endl;
  else
    cout<<title<<" can't be checked in because it's not in the inventory.";
}

bookNode* Library::createBook(string title,string author){
  bookNode* n = new bookNode;
  n->title=title;
  n->author=author;
  //n->checkedOut=false;
  n->next=nullptr;
  n->count = 1;
  n -> inCount = 1;
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
      bookNode* temp = foundTreeNode->hashTable[index];
      bool duplicate = false;
      while(temp != nullptr){
        if(temp->title == title){
          temp->count++;
          temp->inCount++;
          duplicate = true;
        }
        temp = temp -> next;
      }
      if(!duplicate){
        n->next=foundTreeNode->hashTable[index];
        foundTreeNode->hashTable[index]=n;
      }
    }
  return;
  }
}

void Library::deleteBook(string title){
  char titleChar = title[0];
  treeNode* foundNode = searchTree(root, titleChar);
  foundNode->numBooks--;
  unsigned int index = hash(title,hashTableSize);
  if(foundNode->hashTable[index]!=nullptr){
    bookNode* temp = foundNode->hashTable[index];
    bookNode* prev = nullptr;
    while(temp!=nullptr){
      if(temp->title==title){
        if(prev==nullptr){
          foundNode->hashTable[index]=nullptr;
          return;
        }
        else{
          prev->next=temp->next;
          delete temp;
          return;
        }
      }
      prev=temp;
      temp=temp->next;
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
  treeNode* foundTreeNode = searchTree(root, titleChar);
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
  for(int i=0;i<hashTableSize-1;i++){
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
      bookNode* temp = t->hashTable[i];
      while(temp!=nullptr){
        if(temp->author==author){
          if(temp->inCount>1)
            cout << " (" << temp->inCount <<" copies avaliable)"<<endl;
          else
            cout<<temp->title<<endl;
        }
        temp=temp->next;
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
      bookNode* temp = t->hashTable[i];
      while(temp!=nullptr){
        if(temp->inCount > 0){
          if(temp->inCount>1)
            cout << " (" << temp->inCount <<" copies avaliable)"<<endl;
          else
            cout<<temp->title<<endl;
        }
        temp=temp->next;
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
      bookNode* temp = t->hashTable[i];
      while(temp!=nullptr){
        if(temp->inCount<temp->count){
          if((temp->count-temp->inCount)>1)
            cout <<temp->title << " (" << temp->count-temp->inCount <<" copies checked out)"<<endl;
          else
            cout<<temp->title<<endl;
        }
        temp=temp->next;
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
