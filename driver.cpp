#include <iostream>
#include <string>
using namespace std;
#include "library.cpp"

void staffMenu(){
  bool sControl = true;
  while(sControl == true){
    //Staff menu display
    cout << "----------STAFF MENU----------" << endl;
    cout << "1) Add a book to the library" << endl;
    cout << "2) Remove a book from the library" << endl;
    cout << "3) " << endl;
    cout << "4) " << endl;
    cout << "5) Exit Staff Menu" << endl;
    string input;
    getline(cin, input);
    int iinput = stoi(input);

    switch(iinput){
      case 1:
        cout << endl << "Add Book" << endl;
      break;

      case 2:
        cout << endl << "Remove Book" << endl;
      break;

      case 3:
        cout << endl << "Option 3" << endl;
      break;

      case 4:
        cout << endl << "Option 4" << endl;
      break;

      case 5:
        cout << endl << "Returning to Main Menu" << endl;
        sControl = false;
      break;

      default:
        cout << "Invalid Input" << endl;
      break;
    }
  }
}


int main(){
  bool control = true;

  //While loop allows for continuous interaction with the program until the user decides to leave
  while(control == true){
    string input;
    //Main menu display and interface
    cout << "----------MENU----------" << endl;
    cout << "1) Check Out a Book" << endl;
    cout << "2) Return a Book" << endl;
    cout << "3) Search For a Book" << endl;
    cout << "4) Go to Staff Menu" << endl;
    cout << "5) Exit Program" << endl;
    cout << "Response: ";
    getline(cin, input);
    int iinput = stoi(input);
    switch(iinput){

      //Check out book Option
      //Allows the user to check out a book from the library
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

      //Check in Option
      //Allows the user to return a book to the library
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

      //Search Option
      //This option allows a user to search the library database for a book
      case 3:{
        string title;
        cout << endl << "BOOK SEARCH" << endl;
        cout << "Enter Book Title to Search: ";
        getline(cin, title);
        cout << endl;

        //Call the search function, if the book is not found, display that the book does not exist in the library
        //If the book is found, display the information of the book and whether it is checked out or not

      }
      break;

      //Staff Menu Option
      //The staff menu is password protected and allows a staff member to access the other functions and code that would not be available to the public
      case 4:{
        string inPassword;
        cout << endl << "Enter Staff Password: ";
        getline(cin, inPassword);
        //If the user's input matches the correct password, access and call the staff menu function
        if(inPassword == "ABCD"){
          staffMenu();
        }
        //If the user cannot enter the pasword correctly, display a message and return to main menu
        else{
          cout << endl << "Password Incorrect" << endl << endl;
        }
      }
      break;

      //Exits the program
      case 5:
        cout << endl <<"Exiting Program" << endl;
        control = false;
      break;

      //Default case
      default:
        cout << endl << "Invalid Input" << endl << endl;
      break;
    }

  }
}
