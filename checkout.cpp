// Kayla Nguyen
// Section 2

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

void readBooks(vector<Book *> & myBooks) {
    ifstream inFile;
    inFile.open("books.txt");
    int bookID;
    string title, author, category, emptyLine;

    if (inFile.is_open())
    {
      inFile >> bookID;
      while (inFile)
      {
        cout << bookID << endl;
        getline(inFile, emptyLine);
        getline(inFile, title);
        cout << title << endl;
        getline (inFile, author);
        cout << author << endl;
        getline (inFile, category);
        cout << category << endl;
        cout << endl;
        inFile >> bookID;
      }
    }
    inFile.close();
}

int readPersons(vector<Person *> & myCardholders) {
    ifstream inFile;
    inFile.open("person.txt");
    int cardID;
    bool active;
    string firstName, lastName;
    Person *p = nullptr;
    p = new Person(cardID, active, firstName, lastName);

    if (inFile.is_open())
    {
      inFile >> cardID;
      while (inFile)
      {
        inFile >> active >> firstName >> lastName;
        cout << cardID << " " << active << " " << firstName << " " << lastName << endl;
        inFile >> cardID;
        myCardholders.push_back(p);
      }
    }
    inFile.close();
    int nextID = cardID + 1;
    cout << nextID << endl;
    return nextID;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    ifstream inFile;
    inFile.open("Rentals.txt");
    int bookID, cardID;

    if (inFile.is_open())
    {
      inFile >> bookID;
      while (inFile)
      {
        inFile >> cardID;
        cout << bookID << " " << cardID << endl;
        inFile >> bookID;
      }
    }
    inFile.close();
}

void openCard(vector<Person *> & myCardholders, int &nextID) {
  string firstName, lastName, fullName;
  bool active = 1;
  cout << "Please enter the first name: ";
  cin >> firstName;
  cout << "Please enter the last name: ";
  cin >> lastName;

  Person *p = new Person(nextID, active, firstName, lastName);

for (int i = 0; i < myCardholders.size(); i++)
{
  if (p->fullName() == myCardholders[i]->fullName())
  {
    myCardholders[i]->setActive(active);
    cout << "Card ID\n " << myCardholders[i]->getId() << " is re-activated" << endl;
    cout << "Cardholder: " << p->fullName();
  }
}
myCardholders.push_back(p);
cout << "Card ID\n" << readPersons(myCardholders) << " activated" << endl;
cout << "Cardholder: " << p->fullName();
}

void closeCard(vector<Person*> & myCardholders)
{
    int cardID;
    char choice;
    bool active = true;

    cout << "Please enter the card ID: ";
    cin >> cardID;

    for (int i = 0; i < myCardholders.size(); i++)
    {
         if (cardID == myCardholders[i]->getId() && myCardholders[i]->isActive())
         {
            active = true;
            cout << "Cardholder: " << myCardholders[i]->fullName() << endl;

            cout << "Are you sure you want to deactive card\n (y/n)? ";
            cin >> choice;

                if (choice == 'y')
                {
                    myCardholders[i]->setActive(false);
                    cout << "Card ID deactivated" << endl;
                }
                else if (choice == 'n')
                {
                    cout << "Card ID will not be deactivated" << endl;
                }
          }
          else if (cardID == myCardholders[i]->getId() && !active)
          {
            cout << "Card ID is already inactive" << endl;
          }
          else
          {
              cout << "Card ID not found" << endl;
          }
      }
}
Book * searchBook(vector<Book *> myBooks, int id) {
  for (int i = 0; i < myBooks.size(); i++)
  {
    if (myBooks[i]->getId() == id)
    {
      return myBooks[i];
    }
  }
    return nullptr;
}

int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int nextID;
    //cout << "Reading books.txt" << endl;
    //readBooks(books);
    cout << "Reading person.txt" << endl;
    readPersons(cardholders);
    //cout << "Reading Rentals.txt" << endl;
    //readRentals(books, cardholders);
    cout << "Opening Card" << endl;
    openCard(cardholders, nextID);
    //cout << "Closing Card" << endl;
    //closeCard(cardholders);


   //  int choice;
   //  do
   //  {
   //      // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
   //      // the user pressed when entering a menu option. This is still in the input stream.
   //      printMenu();
   //      cin >> choice;
   //      switch(choice)
   //      {
   //          case 1:
   //              // Book checkout
   //              break;
   //
   //          case 2:
   //              // Book return
   //              break;
   //
   //          case 3:
   //              // View all available books
   //              break;
   //
   //          case 4:
   //              // View all outstanding rentals
   //              break;
   //
   //          case 5:
   //              // View outstanding rentals for a cardholder
   //              break;
   //
   //          case 6:
   //              // Open new library card
   //              break;
   //
   //          case 7:
   //              // Close library card
   //              break;
   //
   //          case 8:
   //              // Must update records in files here before exiting the program
   //              break;
   //
   //          default:
   //              cout << "Invalid entry" << endl;
   //              break;
   //      }
   //      cout << endl;
   // } while(choice != 8);
      return 0;
}
