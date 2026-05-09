#include <iostream>
#include <string>
#include <limits>
#include "../include/Library.h"

// ── Utility ───────────────────────────────────────────────────────────────────

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printHeader(const std::string& title) {
    std::cout << "\n  ╔══════════════════════════════════════╗\n"
              << "  ║  " << title;
    int pad = 36 - (int)title.size();
    for (int i = 0; i < pad; ++i) std::cout << ' ';
    std::cout << "║\n"
              << "  ╚══════════════════════════════════════╝\n";
}

// ── Sub-menus ─────────────────────────────────────────────────────────────────

void bookMenu(Library& lib) {
    int choice;
    do {
        printHeader("BOOK MANAGEMENT");
        std::cout << "  1. Add Book\n"
                  << "  2. View All Books\n"
                  << "  3. Search by Title\n"
                  << "  4. Search by Author\n"
                  << "  0. Back\n"
                  << "  Enter choice: ";
        std::cin >> choice;
        clearInput();

        if (choice == 1) {
            std::string id, title, author, genre;
            int copies;
            std::cout << "  Book ID     : "; std::getline(std::cin, id);
            std::cout << "  Title       : "; std::getline(std::cin, title);
            std::cout << "  Author      : "; std::getline(std::cin, author);
            std::cout << "  Genre       : "; std::getline(std::cin, genre);
            std::cout << "  Total Copies: "; std::cin >> copies; clearInput();
            lib.addBook(id, title, author, genre, copies);

        } else if (choice == 2) {
            lib.displayAllBooks();

        } else if (choice == 3) {
            std::string kw;
            std::cout << "  Enter title keyword: "; std::getline(std::cin, kw);
            lib.searchByTitle(kw);

        } else if (choice == 4) {
            std::string kw;
            std::cout << "  Enter author name  : "; std::getline(std::cin, kw);
            lib.searchByAuthor(kw);
        }
    } while (choice != 0);
}

void memberMenu(Library& lib) {
    int choice;
    do {
        printHeader("MEMBER MANAGEMENT");
        std::cout << "  1. Register Member\n"
                  << "  2. View All Members\n"
                  << "  3. View Member Borrow History\n"
                  << "  0. Back\n"
                  << "  Enter choice: ";
        std::cin >> choice;
        clearInput();

        if (choice == 1) {
            std::string id, name, email, phone;
            std::cout << "  Member ID : "; std::getline(std::cin, id);
            std::cout << "  Name      : "; std::getline(std::cin, name);
            std::cout << "  Email     : "; std::getline(std::cin, email);
            std::cout << "  Phone     : "; std::getline(std::cin, phone);
            lib.addMember(id, name, email, phone);

        } else if (choice == 2) {
            lib.displayAllMembers();

        } else if (choice == 3) {
            std::string id;
            std::cout << "  Member ID : "; std::getline(std::cin, id);
            lib.displayMemberBorrowHistory(id);
        }
    } while (choice != 0);
}

void borrowMenu(Library& lib) {
    int choice;
    do {
        printHeader("BORROW / RETURN");
        std::cout << "  1. Issue Book\n"
                  << "  2. Return Book\n"
                  << "  3. View All Borrow Records\n"
                  << "  0. Back\n"
                  << "  Enter choice: ";
        std::cin >> choice;
        clearInput();

        if (choice == 1) {
            std::string mid, bid;
            std::cout << "  Member ID : "; std::getline(std::cin, mid);
            std::cout << "  Book ID   : "; std::getline(std::cin, bid);
            lib.issueBook(mid, bid);

        } else if (choice == 2) {
            std::string mid, bid;
            std::cout << "  Member ID : "; std::getline(std::cin, mid);
            std::cout << "  Book ID   : "; std::getline(std::cin, bid);
            lib.returnBook(mid, bid);

        } else if (choice == 3) {
            lib.displayBorrowRecords();
        }
    } while (choice != 0);
}

// ── Main ──────────────────────────────────────────────────────────────────────

int main() {
    Library lib;

    // Seed some sample data
    lib.addBook("B001", "The Great Gatsby",      "F. Scott Fitzgerald", "Fiction",    3);
    lib.addBook("B002", "To Kill a Mockingbird", "Harper Lee",          "Fiction",    2);
    lib.addBook("B003", "1984",                  "George Orwell",       "Dystopian",  4);
    lib.addBook("B004", "Clean Code",            "Robert C. Martin",    "Technology", 2);
    lib.addBook("B005", "The Pragmatic Programmer", "Andrew Hunt",       "Technology", 1);

    lib.addMember("M001", "Alice Johnson", "alice@email.com", "555-1001");
    lib.addMember("M002", "Bob Smith",     "bob@email.com",   "555-1002");
    lib.addMember("M003", "Carol White",   "carol@email.com", "555-1003");

    int choice;
    do {
        printHeader("LIBRARY MANAGEMENT SYSTEM");
        std::cout << "  1. Book Management\n"
                  << "  2. Member Management\n"
                  << "  3. Borrow / Return\n"
                  << "  0. Exit\n"
                  << "  Enter choice: ";
        std::cin >> choice;
        clearInput();

        switch (choice) {
            case 1: bookMenu(lib);   break;
            case 2: memberMenu(lib); break;
            case 3: borrowMenu(lib); break;
            case 0: std::cout << "\n  Goodbye!\n\n"; break;
            default: std::cout << "  [!] Invalid option. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
