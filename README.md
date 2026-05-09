# Library Management System

A console-based Library Management System built in **C++** using Object-Oriented Programming.

## Features

- Add and view books
- Register and view members
- Issue and return books with borrow records
- Search books by **title** or **author** (case-insensitive)
- Borrow limit enforcement (max 3 books per member)
- 14-day loan period tracking

## Project Structure

```
Library_Management_System/
├── include/
│   ├── Book.h
│   ├── Member.h
│   ├── BorrowRecord.h
│   └── Library.h
├── src/
│   ├── main.cpp
│   ├── Book.cpp
│   ├── Member.cpp
│   ├── BorrowRecord.cpp
│   └── Library.cpp
├── Makefile
├── .gitignore
└── README.md
```

## Classes

| Class | Responsibility |
|-------|---------------|
| `Book` | Stores book details and tracks available copies |
| `Member` | Stores member details and tracks borrowed books |
| `BorrowRecord` | Records each issue/return transaction with dates |
| `Library` | Central controller — manages all operations |

## Build & Run

### Using g++ directly
```bash
g++ -std=c++17 -Iinclude src/main.cpp src/Book.cpp src/Member.cpp src/BorrowRecord.cpp src/Library.cpp -o library_system
./library_system        # Linux/Mac
library_system.exe      # Windows
```

### Using Make
```bash
make
./library_system
```

## Usage

The application launches with a menu-driven interface:

```
  ╔══════════════════════════════════════╗
  ║  LIBRARY MANAGEMENT SYSTEM           ║
  ╚══════════════════════════════════════╝
  1. Book Management
  2. Member Management
  3. Borrow / Return
  0. Exit
```

Sample data (5 books, 3 members) is pre-loaded on startup for quick testing.
