#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    std::string bookId;
    std::string title;
    std::string author;
    std::string genre;
    int totalCopies;
    int availableCopies;

    Book() = default;
    Book(const std::string& id, const std::string& title,
         const std::string& author, const std::string& genre, int copies);

    bool isAvailable() const;
    bool issueCopy();
    bool returnCopy();
    void display() const;
};

#endif // BOOK_H
