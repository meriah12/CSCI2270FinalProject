#include <iostream>
#include <string>
using namespace std;
#include "death.hpp"


int main(){
  bool control = true;
  Library l(100);

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
        l.checkOut(title);
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
        l.checkIn(title);
        //SEARCH FOR THE TITLE OF THE BOOK
        //IF BOOK IS FOUND, CALL THE RETURN BOOK FUNCTION
        //IF THE BOOK IS NOT FOUND, PRINT AN ERROR MESSAGE AND RETURN TO MAIN MENU
      }
      break;

      //Search Option
      //This option allows a user to search the library database for a book and see if it exists
      case 3:{
        string title;
        cout << endl << "BOOK SEARCH" << endl;
        cout << "Enter Book Title to Search: ";
        getline(cin, title);
        cout << endl;

        if(l.search(title) != NULL)
          cout << title << " exists in the database." << endl;
        else
          cout << title << " does not exist in the database" << endl;

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
              case 1:{
                cout << endl << "Add Book" << endl;
                cout << "Enter the title of the new book: ";
                string title;
                getline(cin, title);
                if(l.search(title) == NULL){
                  l.addBook(title);
                }
                else{
                  cout << "Book already exists in the database" << endl;
                }
              }
              break;

              case 2:{
                cout << endl << "Remove Book" << endl;
                cout << endl << "Enter title of the book to be removed: ";
                string title;
                getline(cin, title);
                //deleteBook(title);
              }
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
