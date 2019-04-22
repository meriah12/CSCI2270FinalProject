#include <iostream>
#include <string>
using namespace std;
#include "library.cpp"


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
    cout << "4) Search For Books by Author" << endl;
    cout << "5) Go to Staff Menu" << endl;
    cout << "6) Exit Program" << endl;
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
        cout << endl << "BOOK SEARCH BY TITLE" << endl;
        cout << "Enter Book Title to Search: ";
        getline(cin, title);
        bookNode* search = l.search(title);

        if(search != nullptr){
          cout << title << " exists in the database." << endl;
          cout << "Number of books not checked out: " << search -> inCount << endl << endl;;
        }
        else
          cout << title << " does not exist in the database" << endl;

        //Call the search function, if the book is not found, display that the book does not exist in the library
        //If the book is found, display the information of the book and whether it is checked out or not

      }
      break;

      case 4:

      break;
      
      //Staff Menu Option
      //The staff menu is password protected and allows a staff member to access the other functions and code that would not be available to the public
      case 5:{
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
            cout << "3) Load in book file" << endl;
            cout << "4) Get book information" << endl;
            cout << "5) Search for checked out books" << endl;
            cout << "6) Search for checked in books" << endl;
            cout << "7) Exit Staff Menu" << endl;
            cout << "Response: ";
            string input;
            getline(cin, input);
            int iinput = stoi(input);

            switch(iinput){
              case 1:{
                cout << endl << "Add Book" << endl;
                cout << "Enter the title of the new book: ";
                string title;
                getline(cin, title);
                cout<< "Enter the author of the new book: ";
                string author;
                getline(cin,author);
                bookNode* check = l.search(title);
                if(check == nullptr){
                  l.addBook(title, author);
                  cout << title << " successfully added to the database" << endl;
                  cout << "-------------------------------" << endl;
                  cout << "Book count for " << title << ":" << endl;
                  cout << "Total books: " << check -> count << endl;
                  cout << "Books in library: " << check -> inCount << endl;
                  int co = (check -> count)-(check -> inCount);
                  cout << "Books checked out: " << co << endl;
                }

                else{
                  cout << title << " already exists in database. Adding 1 to book count" << endl;
                  check-> count = check -> count + 1;
                  check -> inCount = check -> inCount + 1;
                  cout << "-------------------------------" << endl;
                  cout << "Book count for " << title << ":" << endl;
                  cout << "Total books: " << check -> count << endl;
                  cout << "Books in library: " << check -> inCount << endl;
                  int co = (check -> count)-(check -> inCount);
                  cout << "Books checked out: " << co << endl;

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
              {
                cout << endl << "Load in a file of books" << endl;
                cout << "Enter filename: ";
                string filename;
                getline(cin, filename);

              }
              break;

              case 4:{
                cout << endl << "Print By Author" << endl;
                cout<<endl<<"Enter the author to print books by: ";
                string author;
                getline(cin,author);
                l.printByAuthor(author);
              }
              break;

              case 5:

              break;

              case 6:

              break;

              case 7:
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
      case 6:
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
