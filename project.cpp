#include<iostream>
#include<fstream>
#include<sstream>
#include<stdexcept>
using namespace std;

fstream fout;

int count(long int n) {
    int count = 0;
    if(n == 0) {
        return 1;
    }
    while(n != 0) {
        n = n/10;
        count++;
    }
    return count;
}

class teacher{
    string teacher_name;
    string course_code;
    public:
        teacher() {};
        teacher(string t_name, string code) {
            t_name = teacher_name;
            code = course_code;
        }
        void teacher_login();
        void teacher_menu(); 
};

class student : public teacher{
    long int student_id;
    string full_name;
    string mail_id;
    long int mobile_number;
    float sem1;
    float sem2;
    float sem3;

    public: 
        student() {
            student_id = 0;
            full_name = "";
            mail_id = "";
            mobile_number = 0;
            sem1 = 0;
            sem2 = 0;
            sem3 = 0;
        }
        void new_student();
        void show_all_student();
        void search_student();
        void edit_student();
        void delete_student();
};

void teacher :: teacher_login() {
    ifstream code;
    string line;
    bool found = false;
    code.open("code.txt");
    cout << "Enter name" << endl;
    cin >> teacher_name;
    cout << "Enter course code" << endl;
    cin >> course_code;

    while(getline(code, line)) {
        if(line == course_code) {
            found = true;
            cout << "***************WELCOME***************" << endl;
            break;
        }
    }
    if(found == false) {
        cout << "Wrong Course Code entered!!\n";
        exit(1);
    }
    code.close();
}

void teacher :: teacher_menu() {
    char c;
    int b = 0;
    student s1;
    do {
        cout << "====================================" << endl;
        cout << "\t\tMENU\t\t" << endl;
        cout << "====================================" << endl;
        cout << "[1] Add New Students" << endl;
        cout << "[2] Show All Students" << endl;
        cout << "[3] Search Students" << endl;
        cout << "[4] Edit Students" << endl;
        cout << "[5] Delete Students" << endl;
        cout << "[6] Previous Page" << endl;
        cout << "====================================" << endl;
        cin >> b;
        switch(b) {
            case 1:
                s1.new_student();
                break;
            case 2:
                s1.show_all_student();
                break;
            case 3:
                s1.search_student();
                break;
            case 4:
                s1.edit_student();
                break;
            case 5:
                s1.delete_student();
                break;
            case 6:
                cout << "Returning to previous page......." << endl;
                return;
                break;
            default:
                cout << "Invalid Option";
        }
        cout << "Press Y or y to continue\n";
        cin >> c;
    }while(c == 'y' || c == 'Y');
}

void student :: new_student() {
    fout.open("file.txt", ios::app);
    char y;

    while(fout) {
    cout << "Enter student id" << endl;
    cin >> student_id;
    try {
        if(count(student_id) != 10) {
            throw runtime_error("Invalid ID entered. ID must be of 10 digits.");
        }
        else {
            fout << student_id;
        }
    }
    catch(runtime_error &e) {
        cout << e.what() << endl;
        exit(1);
    }

    cout << "Enter student name" << endl;
    cin >> full_name;
    fout << "|" << full_name;

    cout << "Enter student's mail id" << endl;
    cin >> mail_id;
    fout << "|" << mail_id;

    cout << "Enter mobile number" << endl;
    cin >> mobile_number;
    try {
        if(count(mobile_number) != 10) {
            throw runtime_error("Invalid mobile number entered. Mobile number must be of 10 digits.");
        }
        else {
            fout << "|" << mobile_number;
        }
    }
    catch(runtime_error &e) {
        cout << e.what() << endl;
        exit(1);
    }

    cout << "Enter semester 1 marks" << endl;
    cin >> sem1;
    fout << "|" << sem1;

    cout << "Enter semester 2 marks" << endl;
    cin >> sem2;
    fout << "|" << sem2;

    cout << "Enter semester 3 marks" << endl;
    cin >> sem3;
    fout << "|" << sem3 << "|";

    fout << endl;

    cout << "Press N or n to exit" << endl;
    cin >> y;
    if(y == 'n' || y == 'N') {
        break;
    }
    }
    fout.close();
}

void student :: show_all_student() {
    fout.open("file.txt");
    string st;
    while(getline(fout, st)) {
        cout << st << endl;
    }
    fout.close();
}

void student :: search_student() {
    long int id_to_search;
    cout << "Enter student ID: " << endl;
    cin >> id_to_search;
    try {
        if(count(id_to_search) != 10) {
            throw runtime_error("Invalid ID entered. ID must be of 10 digits.");
        }
    }
    catch(runtime_error &e) {
        cout << e.what() << endl;
        exit(1);
    }

    fout.open("file.txt");
    string line;
    bool found = false;
    while(getline(fout, line)) {
        stringstream ss(line);
        long int id;
        ss >> id;
        if (id == id_to_search) {
            found = true;
            cout << "Student found: " << line << endl;
            break;
        }
    }
    if (!found) {
        cout << "Student with ID " << id_to_search << " not found." << endl;
    }
    fout.close();
}

void student :: edit_student() {
    long int id_to_edit;
    cout << "Enter student ID to edit" << endl;
    cin >> id_to_edit;
    try {
        if(count(id_to_edit) != 10) {
            throw runtime_error("Invalid ID entered. ID must be of 10 digits.");
        }
    }
    catch(runtime_error &e) {
        cout << e.what() << endl;
        exit(1);
    }

    ifstream fin("file.txt");
    stringstream buffer;
    string line;

    while(getline(fin, line)) {
        stringstream ss(line);
        long int id;
        ss >> id;
        if(id == id_to_edit) {
            cout << "Editing Student: " << line << endl;

            cout << "Enter student id" << endl;
            cin >> student_id;
            try {
                if(count(student_id) != 10) {
                    throw runtime_error("Invalid ID entered. ID must be of 10 digits.");
                }
            }
            catch(runtime_error &e) {
                cout << e.what() << endl;
                exit(1);
            }

            cout << "Enter student name" << endl;
            cin >> full_name;

            cout << "Enter student mail ID" << endl;
            cin >> mail_id;

            cout << "Enter student phone number" << endl;
            cin >> mobile_number;
            try {
                if(count(mobile_number) != 10) {
                throw runtime_error("Invalid mobile number entered. Mobile number must be of 10 digits.");
                }
            }
            catch(runtime_error &e) {
                cout << e.what() << endl;
                exit(1);
            }

            cout << "Enter semester 1 marks" << endl;
            cin >> sem1;

            cout << "Enter semester 2 marks" << endl;
            cin >> sem2;

            cout << "Enter semester 3 marks" << endl;
            cin >> sem3;

            buffer << student_id << "|" << full_name << "|" << mail_id << "|" << mobile_number << "|" << sem1 << "|" << sem2 << "|" << sem3 << "|" << endl;
            cout << "Student Details Updated!" << endl;
        }
        else {
            buffer << line << endl;
        }
    }
    fin.close();

    fout.open("file.txt", ios::out | ios::trunc);
    fout << buffer.str();
    fout.close();
}

void student :: delete_student() {
    long int delete_id;
    cout << "Enter student ID" << endl;
    cin >> delete_id;
    try {
        if(count(delete_id) != 10) {
            throw runtime_error("Invalid ID entered. ID must be of 10 digits.");
        }
    }
    catch(runtime_error &e) {
        cout << e.what() << endl;
        exit(1);
    }

    ifstream fin("file.txt");
    stringstream buffer;
    string line;

    while(getline(fin, line)) {
        stringstream ss(line);
        long int id;
        ss >> id;
        if(id == delete_id) {
            cout << "Deleting: " << line << endl;
            continue;
        }
        else {
            buffer << line << endl;
        }
    }
    fin.close();

    fout.open("file.txt", ios::out | ios::trunc);
    fout << buffer.str();
    fout.close();
}

int main() {
    int a;
    teacher t;
    student s;
  p:cout << endl << "==================MAIN MENU==================" << endl;
    cout << "Press\n1.Teacher Login\n2.Student Login\n3.Exit\n";
    cout << "=============================================" << endl;
    cin >> a;
    switch(a) {
        case 1:
            t.teacher_login();
            t.teacher_menu();
            goto p;
            break;
        case 2:
            s.search_student();
            goto p;
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Invalid Option\n";
            break;
    }

    return 0;
}
