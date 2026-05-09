#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include <string>

class BorrowRecord {
public:
    std::string recordId;
    std::string memberId;
    std::string bookId;
    std::string issueDate;
    std::string dueDate;
    std::string returnDate;
    bool isReturned;

    BorrowRecord() = default;
    BorrowRecord(const std::string& recordId, const std::string& memberId,
                 const std::string& bookId, const std::string& issueDate,
                 const std::string& dueDate);

    void markReturned(const std::string& date);
    void display() const;
};

#endif // BORROWRECORD_H
