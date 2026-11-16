#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    string course;
    int semester;
    string email;
};

void loadStudents(vector<Student>& students) {
    students.clear();
    ifstream fin("students.txt");
    Student s;

    while (fin >> s.id) {
        fin.ignore(numeric_limits<streamsize>::max(), '|');
        getline(fin, s.name, '|');
        getline(fin, s.course, '|');
        fin >> s.semester;
        fin.ignore(numeric_limits<streamsize>::max(), '|');
        getline(fin, s.email);
        students.push_back(s);
    }
    fin.close();
}

void saveStudents(const vector<Student>& students) {
    ofstream fout("students.txt");

    for (const Student& s : students) {
        fout << s.id << '|'
             << s.name << '|'
             << s.course << '|'
             << s.semester << '|'
             << s.email << '\n';
    }
    fout.close();
}

int findStudentIndex(const vector<Student>& students, int id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

int getNextId(const vector<Student>& students) {
    int largest = 0;
    for (const Student& s : students)
        if (s.id > largest)
            largest = s.id;

    return largest + 1;
}

void addStudent(vector<Student>& students) {
    Student s;
    s.id = getNextId(students);

    cout << "Enter Name: ";
    getline(cin >> ws, s.name);

    cout << "Enter Course: ";
    getline(cin, s.course);

    cout << "Enter Semester: ";
    while (!(cin >> s.semester) || s.semester < 1) {
        cout << "Enter valid semester: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter Email: ";
    getline(cin >> ws, s.email);

    students.push_back(s);
    saveStudents(students);

    cout << "Student Added Successfully!\n";
    cout << "Student ID: " << s.id << endl;
}

void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No Records Found!\n";
        return;
    }

    cout << "\nID   Name                 Course          Semester  Email\n";

    for (const Student& s : students) {
        cout << s.id << "    "
             << s.name << "    "
             << s.course << "    "
             << s.semester << "    "
             << s.email << endl;
    }
}

void searchStudent(const vector<Student>& students) {
    int id;
    cout << "Enter Student ID: ";
    if (!(cin >> id)) {
        cout << "Invalid ID!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findStudentIndex(students, id);

    if (index == -1) {
        cout << "Student Not Found!\n";
    } else {
        Student s = students[index];

        cout << "\nStudent Found!\n";
        cout << "ID: " << s.id << endl;
        cout << "Name: " << s.name << endl;
        cout << "Course: " << s.course << endl;
        cout << "Semester: " << s.semester << endl;
        cout << "Email: " << s.email << endl;
    }
}

void updateStudent(vector<Student>& students) {
    int id;
    cout << "Enter Student ID to Update: ";
    if (!(cin >> id)) {
        cout << "Invalid ID!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findStudentIndex(students, id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        return;
    }

    cout << "Enter New Name: ";
    getline(cin >> ws, students[index].name);

    cout << "Enter New Course: ";
    getline(cin, students[index].course);

    cout << "Enter New Semester: ";
    while (!(cin >> students[index].semester) ||
           students[index].semester < 1) {
        cout << "Enter valid semester: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter New Email: ";
    getline(cin >> ws, students[index].email);

    saveStudents(students);
    cout << "Student Updated Successfully!\n";
}

void deleteStudent(vector<Student>& students) {
    int id;
    cout << "Enter Student ID to Delete: ";
    if (!(cin >> id)) {
        cout << "Invalid ID!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findStudentIndex(students, id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        return;
    }

    students.erase(students.begin() + index);
    saveStudents(students);

    cout << "Student Deleted Successfully!\n";
}

int main() {
    vector<Student> students;
    loadStudents(students);

    int choice;

    do {
        cout << "\n===== CAMPUSCONNECT =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "0. Exit\n";

        cout << "Enter Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(students);
                break;

            case 2:
                displayStudents(students);
                break;

            case 3:
                searchStudent(students);
                break;

            case 4:
                updateStudent(students);
                break;

            case 5:
                deleteStudent(students);
                break;

            case 0:
                cout << "Program Closed!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 0);

    return 0;
}