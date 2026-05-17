#include <iostream>
#include <fstream>
using namespace std;

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

// Add Student
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    cout << "\nEnter ID: ";
    cin >> s.id;

    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(s.name, 50);

    cout << "Enter Age: ";
    cin >> s.age;

    cout << "Enter Marks: ";
    cin >> s.marks;

    file.write((char*)&s, sizeof(s));
    file.close();

    cout << "Student added successfully!\n";
}

// Display Students
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\n--- Student Records ---\n";

    while (file.read((char*)&s, sizeof(s))) {
        cout << "ID: " << s.id
             << " | Name: " << s.name
             << " | Age: " << s.age
             << " | Marks: " << s.marks << endl;
    }

    file.close();
}

// Search Student
void searchStudent() {
    int id, found = 0;
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\nEnter ID to search: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "\n Student Found:\n";
            cout << "Name: " << s.name
                 << "\nAge: " << s.age
                 << "\nMarks: " << s.marks << endl;
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Student not found\n";

    file.close();
}

// Update Student
void updateStudent() {
    int id;
    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter ID to update: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Enter New Name: ";
            cin.ignore();
            cin.getline(s.name, 50);

            cout << "Enter New Age: ";
            cin >> s.age;

            cout << "Enter New Marks: ";
            cin >> s.marks;

            int pos = file.tellg();
            file.seekp(pos - sizeof(s));

            file.write((char*)&s, sizeof(s));

            cout << "Record updated!\n";
            file.close();
            return;
        }
    }

    cout << "Student not found\n";
    file.close();
}

// Delete Student
void deleteStudent() {
    int id;
    Student s;
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter ID to delete: ";
    cin >> id;

    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student deleted!\n";
    else
        cout << "Student not found\n";
}

// Main Function
int main() {
    int choice;

    do {
        cout << "\n====== Student Management System ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << " Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}