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

//Read books.txt and put into myBooks vector
void readBooks(vector<Book *> & myBooks) {
    ifstream inFile;
    inFile.open("books.txt");
    int bookID;
    string title, author, category, emptyLine;
    Book *ptr = nullptr;

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
        ptr = new Book(bookID, title, author, category);
        myBooks.push_back(ptr);
      }
    }
    inFile.close();
}

//Read person.txt and put into myCardholders vector
int readPersons(vector<Person *> & myCardholders) {
    ifstream inFile;
    inFile.open("person.txt");
    int cardID;
    bool active;
    string firstName, lastName;
    Person *ptr = nullptr;

    if (inFile.is_open())
    {
      inFile >> cardID;
      while (inFile)
      {
        inFile >> active >> firstName >> lastName;
        ptr = new Person(cardID, active, firstName, lastName);
        cout << cardID << " " << active << " " << firstName << " " << lastName << endl;
        inFile >> cardID;
        myCardholders.push_back(ptr);
      }
    }
    inFile.close();
    int nextID = cardID + 1;
    //cout << "Next available card ID: " << nextID << endl;
    return nextID;
}

// Check if card is valid function
bool validCard(vector<Person *> myCardholders, int cardID)
{
  //bool valid = false;
  //int cardID;
  //cout << "Please enter card ID: ";
  //cin >> cardID;

  for (int i = 0; i < myCardholders.size(); i++)
  {
    if (cardID == myCardholders[i]->getId())
    {
      return true;
      //valid = true;
      //cout << "Cardholders: " << myCardholders[i]->fullName() << endl;
    }
    else if (cardID != myCardholders[i]->getId() && (i+1) == myCardholders.size())
    {
      return false;
      //valid = false;
      //cout << "Card ID not found." << endl;
    }
  }
}

//Read Rentals.txt and set bookID and cardID as personPtr
void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    ifstream inFile;
    inFile.open("Rentals.txt");
    int bookID, cardID;
    bool available = true;
    Person *personPtr = nullptr;
    if (inFile.is_open())
    {
      inFile >> bookID;
      while (inFile)
      {
        inFile >> cardID;
        cout << bookID << " " << cardID << endl;
        inFile >> bookID;

        // if validCard is true
        for (int i = 0; i < myCardholders.size(); i++)
        {
          if (cardID == myCardholders[i]->getId())
          {
            personPtr = myCardholders[i];
            for (int j = 0; j < myBooks.size(); j++)
            {
              if (bookID == myBooks[j]->getId())
              {
                myBooks[j]->setPersonPtr(personPtr);
                cout << personPtr->getId() << endl;
              }
            }
          }
        }
        personPtr = nullptr;
      }
    }
    inFile.close();
}

//Open new library card
void openCard(vector<Person *> & myCardholders, int &nextID) {
  string firstName, lastName, fullName;
  bool active = false;
  cout << "Please enter the first name: ";
  cin >> firstName;
  cout << "Please enter the last name: ";
  cin >> lastName;

  Person *p = nullptr;
  p = new Person(nextID, active, firstName, lastName);

  for (int i = 0; i < myCardholders.size(); i++)
  {
    if (p->fullName() == myCardholders[i]->fullName())
    {
      myCardholders[i]->setActive(active);
      cout << "Card ID " << myCardholders[i]->getId() << " is re-activated." << endl;
      cout << "Cardholder: " << p->fullName() << endl;
      return;
    }
    else if (p->fullName() != myCardholders[i]->fullName() && (i+1) == myCardholders.size())
    {
      myCardholders.push_back(p);
      cout << "Card ID " << readPersons(myCardholders) << " activated" << endl;
      cout << "Cardholder: " << p->fullName() << endl;
      return;
    }
  }
}

//Close library card
void closeCard(vector<Person *> & myCardholders)
{
  int cardID;
  char choice;
  cout << "Please enter the card ID: ";
  cin >> cardID;

  for (int i = 0; i < myCardholders.size(); i++)
  {
    if (cardID == myCardholders[i]->getId() && myCardholders[i]->getActive() == true)
    {
      cout << "Cardholder: " << myCardholders[i]->fullName() << endl;
      cout << "Are you sure you want to deactivate card\n(y/n)? ";
      cin >> choice;
      if (choice == 'y')
      {
        myCardholders[i]->setActive(false);
        cout << "Card ID deactivated." << endl;
        return;
      }
      else if (choice == 'n')
      {
        cout << "Ok. Card will not be deactivated." << endl;
        return;
      }
      else
      {
        cout << "Please enter valid answer." << endl;
        return;
      }
    }
    else if (cardID == myCardholders[i]->getId() && myCardholders[i]->getActive() == false)
    {
      cout << "Cardholder: " << myCardholders[i]->fullName() << endl;
      cout << "Card ID is already inactive." << endl;
      return;
    }
    else if (cardID != myCardholders[i]->getId() && (i+1) == myCardholders.size())
    {
      cout << "Card ID not found." << endl;
      return;
    }
  }
}

//Pointer that points to book object
Book * searchBook(vector<Book *> & myBooks, int id) {
  for (int i = 0; i < myBooks.size(); i++)
  {
    if (myBooks[i]->getId() == id)
    {
      return myBooks[i];
    }
  }
    return nullptr;
}

// Book chechout
void bookCheckout(vector<Book *> & myBooks, vector<Person *> & myCardholders)
{
  int cardID;
  int bookID;
  int count;

  cout << "Please enter the card ID: ";
  cin >> cardID;

  for (int i = 0; i < myCardholders.size(); i++)
  {
    if (cardID == myCardholders[i]->getId())
    {
      cout << "Cardholder: " << myCardholders[i]->fullName() << endl;
      cout << "Please enter the book ID: ";
      cin >> bookID;
      for (int j = 0; j < myBooks.size(); j++)
      {
        if (bookID == myBooks[j]->getId() && myBooks[j]->getPersonPtr() == 0)
        {
          cout << "Title: " << myBooks[i]->getTitle() << endl;
          cout << "Rental Completed." << endl;
          return;
        }
        else if (bookID == myBooks[j]->getId() && myBooks[j]->getPersonPtr() != 0)
        {
          cout << "Book already checked out." << endl;
          return;
        }
        else if (bookID != myBooks[j]->getId() && (j+1) == myBooks.size())
        {
          cout << "Book ID not found." << endl;
          return;
        }
      }
    }
    else if (cardID != myCardholders[i]->getId() && (i+1) == myCardholders.size())
    {
      cout << "Card ID not found." << endl;
      return;
    }
  }
}
//View all available books
// void viewAvailableBooks(vector<Book *> myBooks)
// {
//   for (int i = 0; i < myBooks.size(); i++)
//   {
//     if (searchBook(myBooks, id))
//     {
//       cout << "Book ID: " << id;
//       cout << "Title: " << myBooks[i]->getTitle();
//     }
//   }
// }

int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int id;
    cout << "Reading books.txt" << endl;
    readBooks(books);
    cout << "Reading person.txt" << endl;
    readPersons(cardholders);
    cout << "Reading Rentals.txt" << endl;
    readRentals(books, cardholders);
    //cout << "Checking if valid card" << endl;
    //validCard(cardholders, id);
    //cout << "Opening Card:" << endl;
    //openCard(cardholders, id);
    //cout << "Closing Card:" << endl;
    //closeCard(cardholders);
    cout << "Checking out book:" << endl;
    bookCheckout(books, cardholders);




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
