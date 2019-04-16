#include <iostream>
#include <string>
using namespace std;
#include "library.cpp"

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
        cout << "Enter Book Title: ";
        getline (cin, title);
        cout << endl;

        //SEARCH FOR THE TITLE OF THE BOOK
        //IF BOOK IS FOUND, CALL THE CHECK OUT BOOK FUNCTION
        //IF THE BOOK IS NOT FOUND, PRINT AN ERROR MESSAGE AND RETURN TO MAIN MENU

      }
      break;

      case 2:{
        string title;
        cout << endl << "BOOK CHECK IN" << endl;
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << endl;

        //SEARCH FOR THE TITLE OF THE BOOK
        //IF BOOK IS FOUND, CALL THE RETURN BOOK FUNCTION
        //IF THE BOOK IS NOT FOUND, PRINT AN ERROR MESSAGE AND RETURN TO MAIN MENU


      }
      break;

      case 3:{
        string title;
        cout << endl << "BOOK SEARCH" << endl;
        cout << "Enter Book Title to Search: ";
        getline(cin, title);
        cout << endl;

      }
      break;

      case 4:{
        string inPassword;
        cout << endl << "Enter Staff Password: ";
        getline(cin, inPassword);
        if(inPassword == "ABCD"){
          //CALL A STAFF MENU FUNCTION WHICH HOLDS ALL OF THE OTHER FUNCTIONS THAT ARE NOT INCLUDED IN MAIN MENU
        }
        else{
          cout << endl << "Password Incorrect" << endl << endl;
        }
      }
      break;

      case 5:
        cout << endl <<"Exiting Program" << endl;
        control = false;
      break;

      default:
        cout << endl << "Invalid Input" << endl << endl;
      break;
    }

  }
}
