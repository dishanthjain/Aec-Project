#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// -------------------- Book Class --------------------
class Book {
public:
    int id;
    string title;
    bool issued;

    Book(int i, string t, bool is = false) {
        id = i;
        title = t;
        issued = is;
    }
};

// -------------------- Member Class --------------------
class Member {
public:
    int id;
    string name;

    Member(int i, string n) {
        id = i;
        name = n;
    }
};

// -------------------- Global Data --------------------
vector<Book> books;
vector<Member> members;

// -------------------- File Handling --------------------
void loadBooks() {
    books.clear();   // prevents duplicate loading
    ifstream file("books.txt");
    int id;
    string title;
    bool issued;

    while (file >> id >> issued) {
        file.ignore();
        getline(file, title);
        books.push_back(Book(id, title, issued));
    }
    file.close();
}

void saveBooks() {
    ofstream file("books.txt");
    for (auto &b : books) {
        file << b.id << " " << b.issued << endl;
        file << b.title << endl;
    }
    file.close();
}

void loadMembers() {
    members.clear();   // prevents duplicate loading
    ifstream file("members.txt");
    int id;
    string name;

    while (file >> id) {
        file.ignore();
        getline(file, name);
        members.push_back(Member(id, name));
    }
    file.close();
}

void saveMembers() {
    ofstream file("members.txt");
    for (auto &m : members) {
        file << m.id << endl;
        file << m.name << endl;
    }
    file.close();
}

// -------------------- Book Functions --------------------
void addBook() {
    int id;
    string title;

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, title);

    books.push_back(Book(id, title));
    saveBooks();

    cout << "Book added successfully!\n";
}

void viewBooks() {
    cout << "\n--- Book List ---\n";
    for (auto &b : books) {
        cout << "ID: " << b.id
             << " | Title: " << b.title
             << " | Status: " << (b.issued ? "Issued" : "Available") << endl;
    }
}

// -------------------- Member Functions --------------------
void addMember() {
    int id;
    string name;

    cout << "Enter Member ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Member Name: ";
    getline(cin, name);

    members.push_back(Member(id, name));
    saveMembers();

    cout << "Member added successfully!\n";
}

void viewMembers() {
    cout << "\n--- Member List ---\n";
    for (auto &m : members) {
        cout << "ID: " << m.id << " | Name: " << m.name << endl;
    }
}

// -------------------- Issue & Return --------------------
void issueBook() {
    int bookId;
    cout << "Enter Book ID to issue: ";
    cin >> bookId;

    for (auto &b : books) {
        if (b.id == bookId) {
            if (b.issued) {
                cout << "Book already issued!\n";
                return;
            }
            b.issued = true;
            saveBooks();
            cout << "Book issued successfully!\n";
            return;
        }
    }
    cout << "Book not found!\n";
}

void returnBook() {
    int bookId;
    cout << "Enter Book ID to return: ";
    cin >> bookId;

    for (auto &b : books) {
        if (b.id == bookId) {
            if (!b.issued) {
                cout << "Book is not issued!\n";
                return;
            }
            b.issued = false;
            saveBooks();
            cout << "Book returned successfully!\n";
            return;
        }
    }
    cout << "Book not found!\n";
}

// -------------------- Main Menu --------------------
int main() {
    loadBooks();
    loadMembers();

    int choice;
    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Add Member\n";
        cout << "4. View Members\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: addMember(); break;
            case 4: viewMembers(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
