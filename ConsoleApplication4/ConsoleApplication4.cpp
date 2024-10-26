//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//struct Student {
//    string surname; 
//    string name;    
//    float grade;    
//};
//
//void printMessage(const string& message) {
//    cout << message << endl;
//}
//
//void addStudent(vector<Student>& students) {
//    ofstream file("students.txt", ios::app);
//    Student temp;
//
//    printMessage("Enter the student's surname: ");
//    cin >> temp.surname;
//    printMessage("Enter the student's name: ");
//    cin >> temp.name;
//    printMessage("Enter the grade: ");
//    cin >> temp.grade;
//
//    file << temp.surname << ' ' << temp.name << ' ' << temp.grade << endl;
//    students.push_back(temp);
//    file.close();
//}
//
//void displayStudents(const vector<Student>& students, float threshold) {
//    printMessage("Students with grades lower than " + to_string(threshold) + ":");
//    for (const auto& student : students) {
//        if (student.grade < threshold) {
//            cout << student.surname << ' ' << student.name << ": " << student.grade << endl;
//        }
//    }
//}
//
//float calculateAverage(const vector<Student>& students) {
//    float total = 0;
//    for (const auto& student : students) {
//        total += student.grade;
//    }
//    return students.empty() ? 0 : total / students.size();
//}
//
//void loadStudents(vector<Student>& students) {
//    ifstream file("students.txt");
//    if (!file) {
//        printMessage("File not found!");
//        return;
//    }
//
//    Student temp;
//    while (file >> temp.surname >> temp.name >> temp.grade) {
//        students.push_back(temp);
//    }
//    file.close();
//}
//
//int main() {
//    vector<Student> students;
//    loadStudents(students);
//
//    int choice;
//    do {
//        printMessage("\n1. Add Student\n2. Display Students\n3. Average Grade\n0. Exit\nYour choice: ");
//        cin >> choice;
//
//        switch (choice) {
//        case 1:
//            addStudent(students);
//            break;
//        case 2: {
//            float threshold;
//            printMessage("Enter the grade threshold: ");
//            cin >> threshold;
//            displayStudents(students, threshold);
//            break;
//        }
//        case 3:
//            printMessage("Average Grade: " + to_string(calculateAverage(students)));
//            break;
//        case 0:
//            printMessage("Exiting...");
//            break;
//        default:
//            printMessage("Invalid choice! Please try again.");
//            break;
//        }
//    } while (choice != 0);
//
//    return 0;
//} 
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <codecvt>
#include <locale>

using namespace std;

void printMessage(const string& message) {
    cout << message << endl;
}

string transliterate(const string& input) {
    unordered_map<char, string> translitMap = {
        {'�', "A"}, {'�', "B"}, {'�', "V"}, {'�', "H"}, {'�', "G"},
        {'�', "D"}, {'�', "E"}, {'�', "Ye"}, {'�', "Zh"}, {'�', "Z"},
        {'�', "Y"}, {'�', "I"}, {'�', "Yi"}, {'�', "Y"}, {'�', "K"},
        {'�', "L"}, {'�', "M"}, {'�', "N"}, {'�', "O"}, {'�', "P"},
        {'�', "R"}, {'�', "S"}, {'�', "T"}, {'�', "U"}, {'�', "F"},
        {'�', "Kh"}, {'�', "Ts"}, {'�', "Ch"}, {'�', "Sh"}, {'�', "Shch"},
        {'�', ""}, {'�', "Yu"}, {'�', "Ya"},
        {'�', "a"}, {'�', "b"}, {'�', "v"}, {'�', "h"}, {'�', "g"},
        {'�', "d"}, {'�', "e"}, {'�', "ye"}, {'�', "zh"}, {'�', "z"},
        {'�', "y"}, {'�', "i"}, {'�', "yi"}, {'�', "y"}, {'�', "k"},
        {'�', "l"}, {'�', "m"}, {'�', "n"}, {'�', "o"}, {'�', "p"},
        {'�', "r"}, {'�', "s"}, {'�', "t"}, {'�', "u"}, {'�', "f"},
        {'�', "kh"}, {'�', "ts"}, {'�', "ch"}, {'�', "sh"}, {'�', "shch"},
        {'�', ""}, {'�', "yu"}, {'�', "ya"}
    };

    string result;
    for (char ch : input) {
        if (translitMap.count(ch)) {
            result += translitMap[ch];
        }
        else {
            result += ch;
        }
    }
    return result;
}

void transliterateFile(const string& inputFile, const string& outputFile) {
    wifstream inFile(inputFile);
    ofstream outFile(outputFile);

    inFile.imbue(locale(inFile.getloc(), new codecvt_utf8<wchar_t>()));
    outFile.imbue(locale(outFile.getloc(), new codecvt_utf8<wchar_t>()));

    if (!inFile) {
        printMessage("�� ������� ������� ���� ��� �������!");
        return;
    }

    wstring line;
    while (getline(inFile, line)) {
        string utf8Line = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(line);
        outFile << transliterate(utf8Line) << endl;
    }

    printMessage("������������� ���������. ��������� ��������� � " + outputFile);
}

int main() {
    string inputFile = "input.txt";  
    string outputFile = "output.txt";  

    transliterateFile(inputFile, outputFile);

    return 0;
}
