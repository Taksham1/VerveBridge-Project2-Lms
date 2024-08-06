#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_BOOKS = 100; // Maximum number of books

// Class to represent a book
class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    // Constructor to initialize a book
    Book(int id = 0, string title = "", string author = "", bool isIssued = false)
        : id(id), title(title), author(author), isIssued(isIssued) {}
};

// Class to represent the library
class Library {
private:
    Book books[MAX_BOOKS]; // Array to store books
    int bookCount; // Number of books in the library
    const string filename = "books.txt"; // File to store book data

    // Function to load books from file
    void loadBooks() {
        ifstream file("books.txt",ios::out);
        if (file.is_open()) {
            bookCount = 0;
            while (file >> books[bookCount].id >> ws && getline(file, books[bookCount].title) && getline(file, books[bookCount].author) && file >> books[bookCount].isIssued) {
                bookCount++;
            }
            file.close();
        }
    }

    // Function to save books to file
    void saveBooks() {
        ofstream file("books.txt",ios::app);
        if (file.is_open()) {
            for (int i = 0; i < bookCount; i++) {
                file << books[i].id << endl;
                file << books[i].title << endl;
                file << books[i].author << endl;
                file << books[i].isIssued << endl;
            }
            file.close();
        }
    }

public:
    // Constructor to initialize the library and load books from file
    Library() : bookCount(0) {
        loadBooks();
    }

    // Destructor to save books to file when the library object is destroyed
    ~Library() {
        saveBooks();
    }

    // Function to add a book to the library
    void addBook(int id, string title, string author) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount] = Book(id, title, author);
            bookCount++;
            cout << "Book added successfully!" << endl;
            saveBooks();
        } else {
            cout << "Library is full!" << endl;
        }
    }

    // Function to delete a book from the library
    void deleteBook(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }
                bookCount--;
                cout << "Book deleted successfully!" << endl;
                saveBooks();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Function to issue a book
    void issueBook(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                if (!books[i].isIssued) {
                    books[i].isIssued = true;
                    cout << "Book issued successfully!" << endl;
                    saveBooks();
                } else {
                    cout << "Book is already issued!" << endl;
                }
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Function to return a book
    void returnBook(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                if (books[i].isIssued) {
                    books[i].isIssued = false;
                    cout << "Book returned successfully!" << endl;
                    saveBooks();
                } else {
                    cout << "Book was not issued!" << endl;
                }
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Function to search for a book by ID
    void searchBook(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                cout << "Book ID: " << books[i].id << endl;
                cout << "Title: " << books[i].title << endl;
                cout << "Author: " << books[i].author << endl;
                cout << "Status: " << (books[i].isIssued ? "Issued" : "Available") << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Function to display all books in the library
    void displayBooks() {
        if (bookCount == 0) {
            cout << "No books in the library!" << endl;
            return;
        }
        for (int i = 0; i < bookCount; i++) {
            cout << "Book ID: " << books[i].id << endl;
            cout << "Title: " << books[i].title << endl;
            cout << "Author: " << books[i].author << endl;
            cout << "Status: " << (books[i].isIssued ? "Issued" : "Available") << endl;
            cout << "------------------------" << endl;
        }
    }
};

// Class to represent a user
class User {
private:
    Library& library; // Reference to the library

public:
    User(Library& lib) : library(lib) {}

    // Function to show the user menu
    void Menu() {
        int choice;
        bool condition=true;
        while(condition){
            cout << "User Menu" << endl;
            cout << "1. Search Book" << endl;
            cout << "2. Display All Books" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int id;
                    cout << "Enter book ID to search: ";
                    cin >> id;
                    library.searchBook(id);
                    break;
                }
                case 2:
                    library.displayBooks();
                    break;
                case 3:
                    condition=false;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } 
    }
};

// Class to represent an admin
class Admin {
private:
    Library& library; // Reference to the library

public:
    Admin(Library& lib) : library(lib) {}
    public:
    bool isAlphaString(const string &str){
        for(size_t i=0; i< str.length(); ++i){
            if(!isalpha(str[i])){
                return false;
            }
        }
        return true;
    }
    bool isDigitString(const string &str){
        for(size_t i=0; i< str.length(); ++i){
            if(!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }
    void login(){
        cout<<"------------------------------------Admin Login-------------------------------"<<endl;
        string user_name;
        int pass;
        const string correct_Name="admin";
        cout<<"Enter User Name:";
        cin>>user_name;
        if(user_name == correct_Name){
            cout<<endl<<"Enter Password:";
            cin>>pass;
                if(pass==123){
                    cout<<"*******************WELCOME ADMIN********************"<<endl;
                    Menu();
                }
                else{
                    cout<<"Incorrect Password"<<endl;
                }
        }
            
        }
       

    // Function to show the admin menu
    void Menu() {
        int choice;
        do {
            cout << "Admin Menu" << endl;
            cout << "1. Add Book" << endl;
            cout << "2. Delete Book" << endl;
            cout << "3. Issue Book" << endl;
            cout << "4. Return Book" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int id;
                    string title, author;
                    cout << "Enter book ID: ";
                    cin >> id;
                    cout << "Enter book title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter book author: ";
                    getline(cin, author);
                    library.addBook(id, title, author);
                    break;
                }
                case 2: {
                    int id;
                    cout << "Enter book ID to delete: ";
                    cin >> id;
                    library.deleteBook(id);
                    break;
                }
                case 3: {
                    int id;
                    cout << "Enter book ID to issue: ";
                    cin >> id;
                    library.issueBook(id);
                    break;
                }
                case 4: {
                    int id;
                    cout << "Enter book ID to return: ";
                    cin >> id;
                    library.returnBook(id);
                    break;
                }
                case 5:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 5);
    }
};

int main() {
    Library library;
    User user(library);
    Admin admin(library);

    int role;
    cout << "Enter 1 for User, 2 for Admin: ";
    cout<<"Enter 3 to exit"<<endl;
    cin >> role;
    bool condition=true; 
    while (condition){
    switch(role) {
       case 1: user.Menu();
            break;
    case 2: admin.login();
            break;
    case 3: condition=false;
    break;
    default: cout<<"invalid option"<<endl;
     break;
 }
}

    return 0;
}

