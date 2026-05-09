#include "../include/Member.h"
#include <iostream>
#include <algorithm>

Member::Member(const std::string& id, const std::string& name,
               const std::string& email, const std::string& phone)
    : memberId(id), name(name), email(email), phone(phone) {}

bool Member::canBorrow() const {
    return (int)borrowedBookIds.size() < MAX_BORROW_LIMIT;
}

bool Member::borrowBook(const std::string& bookId) {
    if (!canBorrow()) return false;
    // Prevent duplicate borrow
    for (const auto& id : borrowedBookIds)
        if (id == bookId) return false;
    borrowedBookIds.push_back(bookId);
    return true;
}

bool Member::returnBook(const std::string& bookId) {
    auto it = std::find(borrowedBookIds.begin(), borrowedBookIds.end(), bookId);
    if (it != borrowedBookIds.end()) {
        borrowedBookIds.erase(it);
        return true;
    }
    return false;
}

void Member::display() const {
    std::cout << "  ID       : " << memberId << "\n"
              << "  Name     : " << name << "\n"
              << "  Email    : " << email << "\n"
              << "  Phone    : " << phone << "\n"
              << "  Borrowed : " << borrowedBookIds.size()
              << " / " << MAX_BORROW_LIMIT << " books\n";
}
