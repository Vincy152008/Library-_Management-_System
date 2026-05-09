#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"
#include "Member.h"
#include "BorrowRecord.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<BorrowRecord> borrowRecords;
    int nextRecordId;

    std::string getCurrentDate() const;
    std::string getDueDate() const;

public:
    Library();

    // Book operations
    void addBook(const std::string& id, const std::string& title,
                 const std::string& author, const std::string& genre, int copies);
    void displayAllBooks() const;
    Book* findBookById(const std::string& id);
    void searchByTitle(const std::string& keyword) const;
    void searchByAuthor(const std::string& keyword) const;

    // Member operations
    void addMember(const std::string& id, const std::string& name,
                   const std::string& email, const std::string& phone);
    void displayAllMembers() const;
    Member* findMemberById(const std::string& id);

    // Borrow / Return
    void issueBook(const std::string& memberId, const std::string& bookId);
    void returnBook(const std::string& memberId, const std::string& bookId);
    void displayBorrowRecords() const;
    void displayMemberBorrowHistory(const std::string& memberId) const;
};

#endif // LIBRARY_H
