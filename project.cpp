#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int id, string title, string author)
        : id(id), title(title), author(author), isIssued(false) {}
};

class Student {
public:
    string name;
    int bookId;

    Student(string name, int bookId)
        : name(name), bookId(bookId) {}
};

class Library {
private:
    list<Book> books;
    queue<Student> issuedBooksQueue;

public:
    void addBook(int id, string title, string author);
    void searchBookById(int id);
    void searchBookByTitle(string title);
    void issueBook(int id, string studentName);
    void returnBook(int id);
    void listAllBooks();
    void deleteBook(int id);
    void sortBooksById();
    void sortBooksByTitle();
};

void Library::addBook(int id, string title, string author) {
    books.push_back(Book(id, title, author));
    cout << "Book added successfully.\n";
}

void Library::searchBookById(int id) {
    for (auto& book : books) {
        if (book.id == id) {
            cout << "Book found: " << book.title << " by " << book.author 
                 << (book.isIssued ? " (Issued)" : " (Available)") << "\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void Library::searchBookByTitle(string title) {
    for (auto& book : books) {
        if (book.title == title) {
            cout << "Book found: ID " << book.id << " by " << book.author 
                 << (book.isIssued ? " (Issued)" : " (Available)") << "\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void Library::issueBook(int id, string studentName) {
    for (auto& book : books) {
        if (book.id == id && !book.isIssued) {
            book.isIssued = true;
            issuedBooksQueue.push(Student(studentName, id));
            cout << "Book issued to " << studentName << ".\n";
            return;
        }
    }
    cout << "Book not available for issue.\n";
}

void Library::returnBook(int id) {
    for (auto& book : books) {
        if (book.id == id && book.isIssued) {
            book.isIssued = false;
            queue<Student> tempQueue;
            while (!issuedBooksQueue.empty()) {
                Student current = issuedBooksQueue.front();
                issuedBooksQueue.pop();
                if (current.bookId != id) {
                    tempQueue.push(current);
                }
            }
            issuedBooksQueue = tempQueue;
            cout << "Book returned successfully.\n";
            return;
        }
    }
    cout << "Book not found or not issued.\n";
}

void Library::listAllBooks() {
    cout<<"Total books: "<<books.size()<<"\n";
    if(books.empty()){
        cout<<"No book is available.\n";
    }
    sortBooksById(); 
    for (auto& book : books) {
        cout << "ID: " << book.id << ", Title: " << book.title 
             << ", Author: " << book.author 
             << (book.isIssued ? " (Issued)" : " (Available)") << "\n";
    }
}

void Library::deleteBook(int id) {
    bool found = false;
    for (auto i = books.begin(); i != books.end(); ++i) {
        if (i->id == id) {
            books.erase(i);
            cout << "Book deleted successfully.\n";
            found = true;
            break; 
        }
    }
    if (!found) {
        cout << "Book not found.\n";
    }
}


void Library::sortBooksById() {
    vector<Book> bookVector(books.begin(), books.end());

    sort(bookVector.begin(), bookVector.end(), [](const Book& a, const Book& b) {
        return a.id < b.id;
    });

    books.clear();
    for (const auto& book : bookVector) {
        books.push_back(book);
    }
}


void Library::sortBooksByTitle() {
    vector<Book> bookVector(books.begin(), books.end());

    sort(bookVector.begin(), bookVector.end(), [](const Book& a, const Book& b) {
        return a.title < b.title;
    });

    books.clear();
    for (const auto& book : bookVector) {
        books.push_back(book);
    }
}


int main() {
    Library library;
    int choice, id;
    string title, author, studentName;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add New Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. List All Books\n";
        cout << "7. Delete Book\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                library.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter Book ID: ";
                cin >> id;
                library.searchBookById(id);
                break;
            case 3:
                cout << "Enter Book Title: ";
                cin.ignore();
                getline(cin, title);
                library.searchBookByTitle(title);
                break;
            case 4:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Student Name: ";
                getline(cin, studentName);
                library.issueBook(id, studentName);
                break;
            case 5:
                cout << "Enter Book ID: ";
                cin >> id;
                library.returnBook(id);
                break;
            case 6:
                library.listAllBooks();
                break;
            case 7:
                cout << "Enter Book ID: ";
                cin >> id;
                library.deleteBook(id);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
