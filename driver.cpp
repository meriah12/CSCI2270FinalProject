#include <iostream>
#include <string>
using namespace std;

int main(){
  bool control = true;

  while(control == true){
    string input;
    int iinput;
    cout << "----------MENU----------" << endl;
    cout << "1) Check Out a Book" << endl;
    cout << "2) Return a Book" << endl;
    cout << "3) Search For a Book" << endl;
    cout << "4) Go to Staff Menu" << endl;
    cout << "5) Exit Program" << endl;
    getline(cin, input);
    iinput = stoi(input);
    switch(iinput){

      case 1:{
        string title;
        cout << endl << "BOOK CHECK OUT" << endl;
        cout << "Book Title: ";
        getline (cin, title);

      }
      break;

      case 2:

      break;

      case 3:

      break;

      case 4:

      break;

      case 5:
        cout << "Exiting Program" << endl;
        control = false;
      break;

      default:
        cout << endl << "Invalid Input" << endl << endl;
      break;
    }

  }
}
