#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

class Student
{
private:
    string admissionNo;
    string name;
    string subject;
    string address;

public:
    Student()
    {
        admissionNo = "";
        name = "";
        subject = "";
        address = "";
    }

    void setAdmissionNo(string admissionNo)
    {
        this->admissionNo = admissionNo;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setsubject(string subject)
    {
        this->subject = subject;
    }
    void setAddress(string address)
    {
        this->address = address;
    }

    string getAdmissionNo()
    {
        return this->admissionNo;
    }
    string getName()
    {
        return this->name;
    }
    string getSubject()
    {
        return this->subject;
    }
    string getAddress()
    {
        return this->address;
    }
};

void addStudent(Student &student)
{
    string admissionNo, name, subject, address;

    cout << "\tEnter Admission Number: ";
    cin.ignore();
    getline(cin, admissionNo);

    cout << "\tEnter Name: ";
    getline(cin, name);

    cout << "\tEnter Subject: ";
    getline(cin, subject);

    cout << "\tEnter Address: ";
    getline(cin, address);

    student.setAdmissionNo(admissionNo);
    student.setName(name);
    student.setsubject(subject);
    student.setAddress(address);

    ofstream out("data.txt", ios::app);
    if (!out)
    {
        cout << "\tError:failed to add student" << endl;
    }
    else
    {
        out << student.getAdmissionNo() << " : " << student.getName() << " : " << student.getSubject() << " : " << student.getAddress() << endl;
        out.close();
        cout << "\t*********Student added!*********" << endl;
    }
}

bool searchStudent(string admissionNo)
{

    ifstream in("data.txt");
    if (!in)
    {
        cout << "\tError opening file for search." << endl;
        return false;
    }

    string line;
    bool found = false;

    while (getline(in, line))
    {
        if (line.find(admissionNo) != string::npos)
        {
            cout << "\tStudent Record Found: " << endl;
            cout << "\t" << line << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\tStudent not found with this Admission No." << endl;
        return false;
    }

    in.close();
    return true;
}

void updateStudent(int choice, Student &targetStudent)
{
    ifstream inFile("data.txt");
    if (!inFile)
    {
        cout << "\tError opening file for reading." << endl;
        return;
    }

    vector<string> updatedRecords;
    string line;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string admissionNo, name, subject, address;

        getline(ss, admissionNo, ':');
        ss.ignore(1); // skip space
        getline(ss, name, ':');
        ss.ignore(1);
        getline(ss, subject, ':');
        ss.ignore(1);
        getline(ss, address);

        // Trim leading/trailing spaces
        auto trim = [](string &s)
        {
            while (!s.empty() && s.front() == ' ')
                s.erase(s.begin());
            while (!s.empty() && s.back() == ' ')
                s.pop_back();
        };
        trim(admissionNo);
        trim(name);
        trim(subject);
        trim(address);

        // If this is the record to update
        if (admissionNo == targetStudent.getAdmissionNo())
        {
            cout << "\tEnter new value: ";
            string newValue;
            cin.ignore();
            getline(cin, newValue);

            switch (choice)
            {
            case 1:
                admissionNo = newValue;
                break;
            case 2:
                name = newValue;
                break;
            case 3:
                subject = newValue;
                break;
            case 4:
                address = newValue;
                break;
            default:
                break;
            }
        }

        string updatedLine = admissionNo + " : " + name + " : " + subject + " : " + address;
        updatedRecords.push_back(updatedLine);
    }

    inFile.close();

    ofstream outFile("data.txt");
    for (const string &record : updatedRecords)
    {
        outFile << record << endl;
    }
    outFile.close();

    cout << "\tStudent record updated successfully!" << endl;
}
int main()
{
    Student student;

    bool exit = false;
    while (!exit)
    {
        system("cls");

        int val;
        cout << "\tWelcome To University Management System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t1. Add Student." << endl;
        cout << "\t2. Search Student with AdmissionNo." << endl;
        cout << "\t3. Update Data Of Student." << endl;
        cout << "\t4. Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> val;

        if (val == 1)
        {
            system("cls");

            addStudent(student);
            Sleep(6000);
        }
        else if (val == 2)
        {
            system("cls");
            string admissionNo;
            cout << "\tEnter Admission No: ";
            cin >> admissionNo;
            system("cls");
            searchStudent(admissionNo);
            Sleep(3000);
        }
        else if (val == 3){
            system("cls");
            string admissionNo;
            cout << "\tEnter Admission No: ";
            cin >> admissionNo;

            bool f = searchStudent(admissionNo);
            if (f)
            {
                student.setAdmissionNo(admissionNo);

                cout << "\n\tPress Enter to continue...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get(); // Now it will truly wait for Enter

                system("cls");

                int value;
                cout << "\tWhat do you want to update?" << endl;
                cout << "\t1. Admission No" << endl;
                cout << "\t2. Name" << endl;
                cout << "\t3. Subject" << endl;
                cout << "\t4. Address" << endl;
                cout << "\t5. Exit" << endl;
                cout << "\tEnter Your Choice: ";
                cin >> value;

                if (value >= 1 && value <= 4)
                {
                    updateStudent(value, student);
                    Sleep(6000);
                }
            }
            else
            {
                cout << "\n\tPress Enter to continue...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get(); // Now it will truly wait for Enter

                system("cls");
            }
        }
        else 
        {
            exit=true;
            system("cls");
            Sleep(3000);    
        }
    }
}
