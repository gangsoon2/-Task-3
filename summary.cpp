#include <iostream>
#include <vector>
#include <algorithm>

class Book {
private:
    std::string title;
    std::string author;
    bool isBorrowed;

public:
    Book(std::string title, std::string author) : title(std::move(title)), author(std::move(author)), isBorrowed(false) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    bool isBorrowed() const { return isBorrowed; }

    void borrow() {
        if (isBorrowed) {
            std::cerr << "Error: The book is already borrowed." << std::endl;
        }
        else {
            isBorrowed = true;
            std::cout << "The book has been borrowed successfully." << std::endl;
        }
    }

    void returnBook() {
        if (!isBorrowed) {
            std::cerr << "Error: The book is not in your borrowing list." << std::endl;
        }
        else {
            isBorrowed = false;
            std::cout << "The book has been returned successfully." << std::endl;
        }
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    std::vector<Book> searchBooks(const std::string& keyword) {
        std::vector<Book> result;
        for (const auto& book : books) {
            if (book.getTitle().find(keyword) != std::string::npos || book.getAuthor().find(keyword) != std::string::npos) {
                result.push_back(book);
            }
        }
        return result;
    }

    void borrowBook(const std::string& title, User& user) {
        for (auto& book : books) {
            if (book.getTitle() == title && !book.isBorrowed()) {
                book.borrow();
                user.borrowedBooks.push_back(book);
                break;
            }
        }
    }

    void returnBook(const std::string& title, User& user) {
        for (auto it = user.borrowedBooks.begin(); it != user.borrowedBooks.end(); ++it) {
            if ((*it).getTitle() == title) {
                (*it).returnBook();
                user.borrowedBooks.erase(it);
                break;
            }
        }
    }
};

class User {
private:
    std::string name;
    std::vector<Book> borrowedBooks;

public:
    void borrowBook(const Library& library, const std::string& title) {
        library.borrowBook(title, *this);
    }

    void returnBook(const Library& library, const std::string& title) {
        library.returnBook(title, *this);
    }
};

int main() {
    Library library;
    library.addBook(Book("C++ Primer", "Lippman"));
    library.addBook(Book("Effective Modern C++", "Scott Meyers"));
    library.addBook(Book("Clean Code", "Robert C. Martin"));

    User user1("Alice");
    user1.borrowBook(library, "C++ Primer");
    user1.borrowBook(library, "Effective Modern C++");

    std::cout << "Searching books by 'C++':" << std::endl;
    for (const auto& book : library.searchBooks("C++")) {
        std::cout << book.getTitle() << " by " << book.getAuthor() << std::endl;
    }

    user1.returnBook(library, "C++ Primer");

    return 0;
}
