#include <bits/stdc++.h>
using namespace std;

/*
Classes:
1. Book
2. User
3. Library
*/

// ---------------- Book ----------------
class Book {
private:
    int bookId;
    string title;
    string author;
    bool available;

public:
    Book(int id, string t, string a) {
        bookId = id;
        title = t;
        author = a;
        available = true;
    }

    int getId() const {
        return bookId;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    bool isAvailable() const {
        return available;
    }

    void issueBook() {
        available = false;
    }

    void returnBook() {
        available = true;
    }
};

// ---------------- User ----------------
class User {
private:
    int userId;
    string name;
    vector<int> issuedBooks; // store bookIds

public:
    User(int id, string n) {
        userId = id;
        name = n;
    }

    int getId() const {
        return userId;
    }

    string getName() const {
        return name;
    }

    bool hasBook(int bookId) {
        return find(issuedBooks.begin(), issuedBooks.end(), bookId) != issuedBooks.end();
    }

    bool canIssueMore() {
        return issuedBooks.size() < 2; // max 2 books allowed
    }

    void issueBook(int bookId) {
        issuedBooks.push_back(bookId);
    }

    void returnBook(int bookId) {
        issuedBooks.erase(
            remove(issuedBooks.begin(), issuedBooks.end(), bookId),
            issuedBooks.end()
        );
    }
};

// ---------------- Library ----------------
class Library {
private:
    unordered_map<int, Book*> books;
    unordered_map<int, User*> users;

public:
    void addBook(Book* book) {
        books[book->getId()] = book;
    }

    void addUser(User* user) {
        users[user->getId()] = user;
    }

    void searchBook(const string& title) {
        cout << "Searching for book: " << title << endl;
        bool found = false;

        for (auto& pair : books) {
            if (pair.second->getTitle() == title) {
                cout << "Book Found | ID: " << pair.second->getId()
                     << " | Author: " << pair.second->getAuthor()
                     << " | Available: " << (pair.second->isAvailable() ? "Yes" : "No") << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Book not found\n";
        }
    }

    void issueBook(int userId, int bookId) {
        if (!users.count(userId) || !books.count(bookId)) {
            cout << "Invalid user or book ID\n";
            return;
        }

        User* user = users[userId];
        Book* book = books[bookId];

        if (!book->isAvailable()) {
            cout << "Book is already issued\n";
            return;
        }

        if (!user->canIssueMore()) {
            cout << "User has reached maximum book limit\n";
            return;
        }

        book->issueBook();
        user->issueBook(bookId);

        cout << "Book issued successfully to " << user->getName() << endl;
    }

    void returnBook(int userId, int bookId) {
        if (!users.count(userId) || !books.count(bookId)) {
            cout << "Invalid user or book ID\n";
            return;
        }

        User* user = users[userId];
        Book* book = books[bookId];

        if (!user->hasBook(bookId)) {
            cout << "This user did not issue this book\n";
            return;
        }

        book->returnBook();
        user->returnBook(bookId);

        cout << "Book returned successfully\n";
    }
};

// ---------------- Main ----------------
int main() {
    Library library;

    // Add Books
    library.addBook(new Book(1, "Clean Code", "Robert C. Martin"));
    library.addBook(new Book(2, "Design Patterns", "GoF"));
    library.addBook(new Book(3, "Effective C++", "Scott Meyers"));

    // Add Users
    library.addUser(new User(101, "Alice"));
    library.addUser(new User(102, "Bob"));

    // Demo
    library.searchBook("Clean Code");

    library.issueBook(101, 1);
    library.issueBook(101, 2);
    library.issueBook(101, 3); // should fail (limit reached)

    library.returnBook(101, 1);
    library.issueBook(101, 3); // now works

    return 0;
}
