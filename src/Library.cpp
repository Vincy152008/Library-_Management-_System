#include "../include/Library.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>

// ── Helpers ──────────────────────────────────────────────────────────────────

std::string Library::getCurrentDate() const {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    std::ostringstream oss;
    oss << std::setfill('0')
        << (1900 + t->tm_year) << "-"
        << std::setw(2) << (1 + t->tm_mon) << "-"
        << std::setw(2) << t->tm_mday;
    return oss.str();
}

std::string Library::getDueDate() const {
    time_t now = time(nullptr) + 14 * 24 * 3600; // 14 days from today
    tm* t = localtime(&now);
    std::ostringstream oss;
    oss << std::setfill('0')
        << (1900 + t->tm_year) << "-"
        << std::setw(2) << (1 + t->tm_mon) << "-"
        << std::setw(2) << t->tm_mday;
    return oss.str();
}

// ── Constructor ───────────────────────────────────────────────────────────────

Library::Library() : nextRecordId(1) {}

// ── Book Operations ───────────────────────────────────────────────────────────

void Library::addBook(const std::string& id, const std::string& title,
                      const std::string& author, const std::string& genre, int copies) {
    // Prevent duplicate book IDs
    if (findBookById(id)) {
        std::cout << "  [!] A book with ID '" << id << "' already exists.\n";
        return;
    }
    books.emplace_back(id, title, author, genre, copies);
    std::cout << "  [+] Book '" << title << "' added successfully.\n";
}

void Library::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "  No books in the library.\n";
        return;
    }
    std::cout << "\n  ===== All Books (" << books.size() << ") =====\n";
    for (const auto& b : books) {
        std::cout << "  " << std::string(40, '-') << "\n";
        b.display();
    }
    std::cout << "  " << std::string(40, '-') << "\n";
}

Book* Library::findBookById(const std::string& id) {
    for (auto& b : books)
        if (b.bookId == id) return &b;
    return nullptr;
}

void Library::searchByTitle(const std::string& keyword) const {
    std::string kw = keyword;
    std::transform(kw.begin(), kw.end(), kw.begin(), ::tolower);

    bool found = false;
    std::cout << "\n  ===== Search Results (Title: \"" << keyword << "\") =====\n";
    for (const auto& b : books) {
        std::string title = b.title;
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        if (title.find(kw) != std::string::npos) {
            std::cout << "  " << std::string(40, '-') << "\n";
            b.display();
            found = true;
        }
    }
    if (!found) std::cout << "  No books found matching title '" << keyword << "'.\n";
    std::cout << "  " << std::string(40, '-') << "\n";
}

void Library::searchByAuthor(const std::string& keyword) const {
    std::string kw = keyword;
    std::transform(kw.begin(), kw.end(), kw.begin(), ::tolower);

    bool found = false;
    std::cout << "\n  ===== Search Results (Author: \"" << keyword << "\") =====\n";
    for (const auto& b : books) {
        std::string author = b.author;
        std::transform(author.begin(), author.end(), author.begin(), ::tolower);
        if (author.find(kw) != std::string::npos) {
            std::cout << "  " << std::string(40, '-') << "\n";
            b.display();
            found = true;
        }
    }
    if (!found) std::cout << "  No books found by author '" << keyword << "'.\n";
    std::cout << "  " << std::string(40, '-') << "\n";
}

// ── Member Operations ─────────────────────────────────────────────────────────

void Library::addMember(const std::string& id, const std::string& name,
                        const std::string& email, const std::string& phone) {
    if (findMemberById(id)) {
        std::cout << "  [!] A member with ID '" << id << "' already exists.\n";
        return;
    }
    members.emplace_back(id, name, email, phone);
    std::cout << "  [+] Member '" << name << "' registered successfully.\n";
}

void Library::displayAllMembers() const {
    if (members.empty()) {
        std::cout << "  No members registered.\n";
        return;
    }
    std::cout << "\n  ===== All Members (" << members.size() << ") =====\n";
    for (const auto& m : members) {
        std::cout << "  " << std::string(40, '-') << "\n";
        m.display();
    }
    std::cout << "  " << std::string(40, '-') << "\n";
}

Member* Library::findMemberById(const std::string& id) {
    for (auto& m : members)
        if (m.memberId == id) return &m;
    return nullptr;
}

// ── Borrow / Return ───────────────────────────────────────────────────────────

void Library::issueBook(const std::string& memberId, const std::string& bookId) {
    Member* member = findMemberById(memberId);
    if (!member) {
        std::cout << "  [!] Member ID '" << memberId << "' not found.\n";
        return;
    }
    Book* book = findBookById(bookId);
    if (!book) {
        std::cout << "  [!] Book ID '" << bookId << "' not found.\n";
        return;
    }
    if (!book->isAvailable()) {
        std::cout << "  [!] Book '" << book->title << "' is not available right now.\n";
        return;
    }
    if (!member->canBorrow()) {
        std::cout << "  [!] Member '" << member->name
                  << "' has reached the borrow limit (" << Member::MAX_BORROW_LIMIT << " books).\n";
        return;
    }

    book->issueCopy();
    member->borrowBook(bookId);

    std::string recId = "REC" + std::to_string(nextRecordId++);
    borrowRecords.emplace_back(recId, memberId, bookId, getCurrentDate(), getDueDate());

    std::cout << "  [✓] Book '" << book->title << "' issued to '" << member->name << "'.\n"
              << "      Record ID: " << recId << " | Due: " << getDueDate() << "\n";
}

void Library::returnBook(const std::string& memberId, const std::string& bookId) {
    Member* member = findMemberById(memberId);
    if (!member) {
        std::cout << "  [!] Member ID '" << memberId << "' not found.\n";
        return;
    }
    Book* book = findBookById(bookId);
    if (!book) {
        std::cout << "  [!] Book ID '" << bookId << "' not found.\n";
        return;
    }

    // Find the active borrow record
    BorrowRecord* activeRecord = nullptr;
    for (auto& rec : borrowRecords) {
        if (rec.memberId == memberId && rec.bookId == bookId && !rec.isReturned) {
            activeRecord = &rec;
            break;
        }
    }
    if (!activeRecord) {
        std::cout << "  [!] No active borrow record found for this member and book.\n";
        return;
    }

    book->returnCopy();
    member->returnBook(bookId);
    activeRecord->markReturned(getCurrentDate());

    std::cout << "  [✓] Book '" << book->title << "' returned by '" << member->name << "'.\n"
              << "      Record ID: " << activeRecord->recordId << " | Returned: " << getCurrentDate() << "\n";
}

void Library::displayBorrowRecords() const {
    if (borrowRecords.empty()) {
        std::cout << "  No borrow records found.\n";
        return;
    }
    std::cout << "\n  ===== All Borrow Records (" << borrowRecords.size() << ") =====\n";
    for (const auto& rec : borrowRecords) {
        std::cout << "  " << std::string(40, '-') << "\n";
        rec.display();
    }
    std::cout << "  " << std::string(40, '-') << "\n";
}

void Library::displayMemberBorrowHistory(const std::string& memberId) const {
    Member* member = nullptr;
    for (const auto& m : members)
        if (m.memberId == memberId) { member = const_cast<Member*>(&m); break; }

    if (!member) {
        std::cout << "  [!] Member ID '" << memberId << "' not found.\n";
        return;
    }

    std::cout << "\n  ===== Borrow History for " << member->name << " =====\n";
    bool found = false;
    for (const auto& rec : borrowRecords) {
        if (rec.memberId == memberId) {
            std::cout << "  " << std::string(40, '-') << "\n";
            rec.display();
            found = true;
        }
    }
    if (!found) std::cout << "  No borrow history found.\n";
    std::cout << "  " << std::string(40, '-') << "\n";
}
