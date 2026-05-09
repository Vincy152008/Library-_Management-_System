#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>

class Member {
public:
    static const int MAX_BORROW_LIMIT = 3;

    std::string memberId;
    std::string name;
    std::string email;
    std::string phone;
    std::vector<std::string> borrowedBookIds;

    Member() = default;
    Member(const std::string& id, const std::string& name,
           const std::string& email, const std::string& phone);

    bool canBorrow() const;
    bool borrowBook(const std::string& bookId);
    bool returnBook(const std::string& bookId);
    void display() const;
};

#endif // MEMBER_H
