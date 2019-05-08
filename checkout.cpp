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
        ptr = new Book(bookID, title, author, category);
        myBooks.push_back(ptr);
        inFile >> bookID;
      }
    }
    inFile.close();
}

//Read person.txt and put into myCardholders vector
int readPersons(vector<Person *> & myCardholders) {
    ifstream inFile;
    inFile.open("person.txt");
    int cardID, nextID;
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
      nextID = myCardholders.back()->getId() + 1;
    }
    inFile.close();
    cout << "Next available card ID: " << nextID << endl;
    return nextID;
}

//Read Rentals.txt and set bookID and cardID as personPtr
void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    ifstream inFile;
    inFile.open("Rentals.txt");
    int bookID, cardID;
    Person *personPtr = nullptr;

    if (inFile.is_open())
    {
      inFile >> bookID;
      while (inFile)
      {
        inFile >> cardID;
        cout << bookID << " " << cardID << endl;

        // if validCard is true
        for (int i = 0; i < myCardholders.size(); i++)
        {
          if (cardID == myCardholders[i]->getId())
          {
            personPtr = myCardholders[i];
          }
        }
        for (int j = 0; j < myBooks.size(); j++)
        {
          if (bookID == myBooks[j]->getId())
          {
            myBooks[j]->setPersonPtr(personPtr);
          }
        }
        inFile >> bookID;
      }
    }
    inFile.close();
}

//Open new library card
void openCard(vector<Person *> & myCardholders, int &nextID) {
  string firstName, lastName, fullName;
  //bool active = false;
  cout << "Please enter the first name: ";
  cin >> firstName;
  cout << "Please enter the last name: ";
  cin >> lastName;

  Person *p = nullptr;
  nextID = myCardholders.back()->getId() + 1;
  p = new Person(nextID, true, firstName, lastName);

  for (int i = 0; i < myCardholders.size(); i++)
  {
    if (p->fullName() == myCardholders[i]->fullName())
    {
      myCardholders[i]->setActive(true);
      cout << "Card ID " << myCardholders[i]->getId() << " is re-activated." << endl;
      cout << "Cardholder: " << p->fullName() << endl;
      return;
    }
    else if (p->fullName() != myCardholders[i]->fullName() && (i+1) == myCardholders.size())
    {
      myCardholders.push_back(p);
      cout << "Card ID " << nextID << " activated" << endl;
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

//Write a function that finds a person for us
//We find the person with that cardID
//Return a pointer to that person
//and get out of for-loop and function
Person *searchPerson(vector<Person *> & myCardholders, int cardID)
{
  for (int i = 0; i < myCardholders.size(); i++)
  {
    if (myCardholders[i]->getId() == cardID)
    {
      return myCardholders[i];
    }
  }
  // if i == myCardholders.size(), then cardID was never found, so return nullptr
  return nullptr;
}

//Loop through myBooks vector and compare bookID
//Pointer that points to book object
Book *searchBook(vector<Book *> & myBooks, int bookID)
{
  for (int i = 0; i < myBooks.size(); i++)
  {
    if (myBooks[i]->getId() == bookID)
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

  cout << "Please enter the card ID: ";
  cin >> cardID;

  Person *personPtr = searchPerson(myCardholders, cardID);
  if (personPtr != nullptr)
  {
    cout << "Cardholder: " << personPtr->fullName() << endl;
    cout << "Please enter the book ID: ";
    cin >> bookID;

    Book *bookPtr = searchBook(myBooks, bookID);
    // if bookPtr exists
    if (bookPtr != nullptr)
    {
      // Check to see if bookPtr has existing personPtr
      if (bookPtr->getPersonPtr() != nullptr)
      {
        cout << "Book already checked out." << endl;
      }
      else
      {
        cout << "Title: " << bookPtr->getTitle() << endl;
        cout << "Rental Completed." << endl;
        personPtr = bookPtr->getPersonPtr();
      }
    }
    else
    {
      cout << "Book ID not found." << endl;
    }
  }
  else
  {
    cout << "Card ID not found." << endl;
  }
}

void bookReturn(vector<Book *> myBooks)
{
  int bookID;

  cout << "Please enter the book ID to return: ";
  cin >> bookID;

  Person *personPtr = nullptr;
  Book *bookPtr = searchBook(myBooks, bookID);

  // Confirm that book ID is valid
  if (bookPtr != nullptr)
  {
    personPtr = bookPtr->getPersonPtr();
    cout << "Title: " << bookPtr->getTitle() << endl;
    cout << "Return Completed." << endl;
    personPtr = nullptr;
  }
  else
  {
    cout << "Book ID not found." << endl;
  }
}
//View all available books
void viewAvailableBooks(vector<Book *> myBooks)
{
  int count = 0;
  Person *personPtr = nullptr;
   for (int i = 0; i < myBooks.size(); i++)
   {
     personPtr = myBooks[i]->getPersonPtr();
       if (personPtr == nullptr)
       {
           cout << "Book ID: " << myBooks[i]-> getId() << endl;
           cout << "Title " << myBooks[i]-> getTitle() << endl;
           cout << "Author: " << myBooks[i]-> getAuthor() << endl;
           cout << "Category: " << myBooks[i] -> getCategory() << endl << endl;
           count++;
       }
   }
   if (count == 0)
   {
     cout << "No available books." << endl;
   }
}

void allRentals(vector<Book *> myBooks)
{
    int count = 0;
    Person *personptr = nullptr;
    for(int i = 0; i < myBooks.size(); i++)
    {
  		personptr = myBooks[i]->getPersonPtr();
  		if(personptr != nullptr)
  		{
  			cout << "Book ID: " << myBooks[i]->getId() << endl;
  			cout << "Title: " << myBooks[i]->getTitle() << endl;
  			cout << "Author: " << myBooks[i]->getAuthor() << endl;
  			cout << "Cardholder: " << personptr->fullName() << endl;
  			cout << "Card ID: " << personptr->getId() << endl << endl;
  			count++;
  		}
	  }
  	if(count == 0)
    {
  		cout << "No outstanding books." << endl;
    }
}

void allRentalsForCardholder(vector<Person *> myCardholders, vector<Book *> myBooks)
{
  int cardID;


  cout << "Please enter the card ID: ";
  cin >> cardID;

  Person *personPtr = searchPerson(myCardholders, cardID);
  // Confirm that card is valid and active
  if (personPtr != nullptr && personPtr->getActive() == true)
  {
    cout << "Cardholder: " << personPtr->fullName() << endl;
    for (int i = 0; i < myBooks.size(); i++)
    {
      if (myBooks[i]->getPersonPtr() == personPtr)
      {
        cout << "Book ID: " << myBooks[i]->getId() << endl;
        cout << "Title: " << myBooks[i]->getTitle() << endl;
        cout << "Author: " << myBooks[i]->getAuthor() << endl;
      }
    }
  }
  // Card is valid but not active
  else if (personPtr != nullptr && personPtr->getActive() == false)
  {
    cout << "No books currently checked out." << endl;
  }
  else
  {
    cout << "Card ID not found." << endl;
  }
}

void updateAndExit(vector<Book *> &myBooks, vector<Person *> myCardholders)
{
  fstream rentalsFile;
  rentalsFile.open("Rentals.txt");

  fstream personFile;
  personFile.open("person.txt");

  for (int i = 0; i < myBooks.size(); i++)
  {
    rentalsFile << myBooks[i]->getId() << " "
    << myBooks[i]->getPersonPtr()->getId() << endl;
  }

  for (int j = 0; j < myCardholders.size(); j++)
  {
    personFile << myCardholders[j]->getId()
      << " " << myCardholders[j]->getActive()
      << " " << myCardholders[j]->fullName() << endl;
  }
}

int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int bookID, cardID;
    int nextID = 0;

    cout << "Reading books.txt" << endl;
    readBooks(books);

    cout << "Reading person.txt" << endl;
    readPersons(cardholders);

    cout << "Reading Rentals.txt" << endl;
    readRentals(books, cardholders);

    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
                cout << "Checking out book:" << endl;
                bookCheckout(books, cardholders);
                break;

            case 2:
                // Book return
                cout << "Return book:" << endl;
                bookReturn(books);
                break;

            case 3:
                // View all available books
                cout << "Available books:" << endl;
                viewAvailableBooks(books);
                break;

            case 4:
                // View all outstanding rentals
                cout << "All outstanding rentals:" << endl;
                allRentals(books);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                cout << "All outstanding rentals for a cardholder:" << endl;
                allRentalsForCardholder(cardholders, books);
                break;

            case 6:
                // Open new library card
                cout << "Opening card:" << endl;
                openCard(cardholders, nextID);
                break;

            case 7:
                // Close library card
                cout << "Closing card:" << endl;
                closeCard(cardholders);
                break;

            case 8:
                // Must update records in files here before exiting the program
                cout << "Records are updated. Exiting program." << endl;
                updateAndExit(books, cardholders);
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
