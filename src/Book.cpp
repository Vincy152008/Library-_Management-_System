#include "../include/Book.h"
#include <iostream>
#include <iomanip>

Book::Book(const std::string& id, const std::string& title,
           const std::string& author, const std::string& genre, int copies)
    : bookId(id), title(title), author(author), genre(genre),
      totalCopies(copies), availableCopies(copies) {}

bool Book::isAvailable() const {
    return availableCopies > 0;
}

bool Book::issueCopy() {
    if (availableCopies > 0) {
        --availableCopies;
        return true;
    }
    return false;
}

bool Book::returnCopy() {
    if (availableCopies < totalCopies) {
        ++availableCopies;
        return true;
    }
    return false;
}

void Book::display() const {
    std::cout << std::left
              << "  ID      : " << bookId << "\n"
              << "  Title   : " << title << "\n"
              << "  Author  : " << author << "\n"
              << "  Genre   : " << genre << "\n"
              << "  Copies  : " << availableCopies << " / " << totalCopies << " available\n"
              << "  Status  : " << (isAvailable() ? "Available" : "Not Available") << "\n";
}
