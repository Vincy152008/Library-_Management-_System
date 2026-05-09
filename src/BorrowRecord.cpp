#include "../include/BorrowRecord.h"
#include <iostream>

BorrowRecord::BorrowRecord(const std::string& recordId, const std::string& memberId,
                           const std::string& bookId, const std::string& issueDate,
                           const std::string& dueDate)
    : recordId(recordId), memberId(memberId), bookId(bookId),
      issueDate(issueDate), dueDate(dueDate), returnDate(""), isReturned(false) {}

void BorrowRecord::markReturned(const std::string& date) {
    returnDate = date;
    isReturned = true;
}

void BorrowRecord::display() const {
    std::string status = isReturned ? "Returned" : "Active";
    std::cout << "  Record ID   : " << recordId << "\n"
              << "  Member ID   : " << memberId << "\n"
              << "  Book ID     : " << bookId << "\n"
              << "  Issue Date  : " << issueDate << "\n"
              << "  Due Date    : " << dueDate << "\n"
              << "  Return Date : " << (isReturned ? returnDate : "N/A") << "\n"
              << "  Status      : " << status << "\n";
}
