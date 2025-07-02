#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>

using namespace std;

class ADMINISTRATION
{
    string people;

public:
    int x()
    {
        cout << "Enter Instructor Name: ";
        cin >> people;
        if (people == "admin")
        {
            int P = encrypt();
            if (P == 1)
            {
                cout << "Welcome Admin!" << endl;
                return 1; // Admin access granted
            }
            else
            {
                cout << "User  Not Found" << endl;
                return 0; // Access denied
            }
        }
        return 0; // Access denied if not admin
    }

    int encrypt()
    {
        string Adminpassword;
        cout << "Enter Password: ";
        cin >> Adminpassword;
        if (Adminpassword == "pass")
        {
            cout << "WELCOME" << endl;
            return 1;
        }
        else
        {
            cout << "Incorrect Password" << endl;
            return encrypt(); // Recursive call for re-entering password
        }
    }

    void FUNCS(int G, int C)
    {
        if (C != 0)
        {
            cout << "\n Gym trainer are currently unavailable" << endl;
        }
        else
        {
            cout << "\n Gym trainer are available" << endl;
        }
        if (G != 0)
        {
            cout << "\nChoose another gym session";
        }
    }
};

void FUNCS(char *Z)
{
    char group[10];
    int j, G_C = 3, S_C = 5;
    strcpy(group, Z);
    if (G_C != 0 || S_C != 0)
    {
        if (strcmp(group, "gold") == 0)
        {
            G_C--;
            FUNCS(group);
        }
        else if (strcmp(group, "silver") == 0)
        {
            S_C--;
            FUNCS(group);
        }
        else
        {
            cout << "Trainer is available";
        }
    }
}

class Candidate
{
    int sc_no;
    char name[20], std[20], timings[20];
    long int phone_no;
    float Fees;

public:
    int TimeSlot()
    {
        int T;
        cout << "\nSelect your preferred workout time slot:\n";
        cout << "\n1.Early Morning (6 AM - 7 AM)\n";
        cout << "2. Morning (7 AM - 8 AM)\n";
        cout << "3. MidMorning (8 AM - 9 AM)\n";
        cout << "4. Afternoon (12 PM - 1 PM)\n";
        cout << "5. Evening (5 PM - 6 PM)\n";
        cout << "6. Afternoon (6 PM - 7 PM)\n";
        cin >> T;
        switch (T)
        {
        case 1:
            cout << "You have selected Early Morning (6 AM - 7 AM)" << endl;
            strcpy(timings, "Early Morning (6 AM - 7 AM)");
            break;
        case 2:
            cout << "You have selected Morning (7 AM - 8 AM)" << endl;
            strcpy(timings, "Morning (7 AM - 8 AM)");
            break;
        case 3:
            cout << "You have selected MidMorning (8 AM - 9 AM)" << endl;
            strcpy(timings, "MidMorning (8 AM - 9 AM)");
            break;
        case 4:
            cout << "You have selected Afternoon (12 PM - 1 PM)" << endl;
            strcpy(timings, "Afternoon (12 PM - 1 PM)");
            break;
        case 5:
            cout << "You have selected Evening (5 PM - 6 PM)" << endl;
            strcpy(timings, "Evening (5 PM - 6 PM)");
            break;
        case 6:
            cout << "You have selected Afternoon (6 PM - 7 PM)" << endl;
            strcpy(timings, "Afternoon (6 PM - 7 PM)");
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
        return 0;
    }

    void CreateMember()
    {
        int k;
        cout << "Enter New Member's Name: ";
        getchar();
        cin.getline(name, 20);
        cout << "Enter New Member's contact number: ";
        cin >> phone_no;
        cout << "Enter New Member's number: ";
        cin >> sc_no;
        cout << "Enter New Member's Standard (1 for Gold / 2 for Silver): ";
        cin >> k;
        switch (k)
        {
        case 1:
            strcpy(std, "Gold");
            cout << "Welcome to Gold Standard";
            Fees = 5000;
            cout << "Your Monthly Fees is: " << Fees << endl;
            FUNCS(std);
            break;
        case 2:
            strcpy(std, "Silver");
            cout << "Welcome to Silver Standard";
            Fees = 3000;
            cout << "Your Monthly Fees is: " << Fees << endl;
            FUNCS(std);
            break;
        default:
            cout << "Invalid Standard. Please try again." << endl;
            return;
        }
        TimeSlot();
    }

    void DisplayMember()
    {
        cout << "Member Name: " << name << endl;
        cout << "Contact Number: " << phone_no << endl;
        cout << "Standard: " << std << endl;
        cout << "Time Slot: " << timings << endl;
        cout << "Membership Number: " << sc_no << endl;
    }

    int getMembershipNumber()
    {
        return sc_no;
    }

    float Getfee()
    {
        return Fees;
    }

    char *GetName()
    {
        return name;
    }

    long GetPhoneNo()
    {
        return phone_no;
    }
};

fstream fp;
Candidate M1;

void AddMember()
{
    fp.open("Member.dat", ios::out | ios::app);
    M1.CreateMember();
    fp.write((char *)&M1, sizeof(M1));
    fp.close();
    cout << "Member added successfully!" << endl;
    getchar();
}

void DisplayMembers()
{
    system("cls");
    cout << "Member List:" << endl;
    fp.open("Member.dat", ios::in);
    while (fp.read((char *)&M1, sizeof(M1)))
    {
        M1.DisplayMember();
        getchar();
    }
    fp.close();
}

void DisplayRecord(int membershipNumber)
{
    system("cls");
    bool found = false;
    fp.open("Member.dat", ios::in);
    while (fp.read((char *)&M1, sizeof(M1)))
    {
        if (M1.getMembershipNumber() == membershipNumber)
        {
            system("cls");
            M1.DisplayMember();
            found = true;
            break;
        }
    }
    fp.close();
    if (!found)
    {
        cout << "No record found for Membership Number: " << membershipNumber << endl;
    }
}

void EditMember()
{
    int membershipNumber;
    bool found = false;
    cout << "Enter Membership Number to edit: ";
    cin >> membershipNumber;
    fp.open("Member.dat", ios::in | ios::out);
    while (fp.read((char *)&M1, sizeof(M1)) && !found)
    {
        if (M1.getMembershipNumber() == membershipNumber)
        {
            M1.DisplayMember();
            cout << "Enter New Details: ";
            M1.CreateMember();
            long pos = fp.tellg();
            fp.seekp(pos - sizeof(M1), ios::beg);
            fp.write((char *)&M1, sizeof(M1));
            cout << "Member details updated successfully!" << endl;
            found = true;
        }
    }
    fp.close();
    if (!found)
        cout << "No record found for Membership Number: " << membershipNumber << endl;
    getchar();
}

void DeleteMember()
{
    int membershipNumber;
    system("cls");
    cout << "Enter Membership Number to delete: ";
    cin >> membershipNumber;
    fp.open("Member.dat", ios::in | ios::out);
    fstream tempFile;
    tempFile.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&M1, sizeof(M1)))
    {
        if (M1.getMembershipNumber() != membershipNumber)
        {
            tempFile.write((char *)&M1, sizeof(M1));
        }
    }
    fp.close();
    tempFile.close();
    remove("Member.dat");
    rename("Temp.dat", "Member.dat");
    cout << "Member deleted successfully!" << endl;
    getchar();
}

void Fmanage()
{
    for (;;)
    {
        system("cls");
        cout << "\nGym Management System\n"
             << endl;
        cout << "\n1. Add Member" << endl;
        cout << "\n2. Display Members" << endl;
        cout << "\n3. Search for a Member" << endl;
        cout << "\n4. Edit Member Details" << endl;
        cout << "\n5. Delete Member" << endl;
        cout << "\n6. Exit and Go back To Main Menu" << endl;
        cout << "\nEnter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            AddMember();
            break;
        case 2:
            DisplayMembers();
            break;
        case 3:
            int membershipNumber;
            system("cls");
            cout << "Enter Membership Number to search: ";
            cin >> membershipNumber;
            DisplayRecord(membershipNumber);
            break;
        case 4:
            EditMember();
            break;
        case 5:
            DeleteMember();
            break;
        case 6:
            cout << "Exiting to Main Menu..." << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void Fitness()
{
    cout << "\nDisplaying Fitness Tips." << endl;
    std::ifstream fitnessFile("fitness_tips.txt");
    if (fitnessFile.is_open())
    {
        std::cout << fitnessFile.rdbuf();
    }
}

void Member()
{
    for (;;)
    {
        int Memberchoice;
        cout << "\nWelcome to our Gym!\n"
             << endl;
        cout << "\n1. Join Gym Programme" << endl;
        cout << "\n2. Give up on fitness(sigh)...QUIT" << endl;
        cout << "\n3. Edit your Gym Profile" << endl;
        cout << "\n\nEnter your choice" << endl;
        cin >> Memberchoice;
        switch (Memberchoice)
        {
        case 1:
            system("cls");
            AddMember();
            break;
        case 2:
            DeleteMember();
            break;
        case 3:
            EditMember();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main()
{
    int Mode;
    cout << "Welcome to the Gym" << endl;
    cout << "\nSELECT MODE" << endl;
    cout << "\n1. Admin" << endl;
    cout << "\n2. Member" << endl;
    cin >> Mode;
    if (Mode == 1)
    {
        cout << "Welcome to the Admin Section" << endl;
        ADMINISTRATION admin;
        int k = admin.x();
        if (k == 1)
        {
            Fmanage();
        }
        else
        {
            cout << "Access Denied." << endl;
        }
    }
    else if (Mode == 2)
    {
        cout << "Welcome to the Member Section" << endl;
        Member();
    }
    else
    {
        cout << "Invalid Mode Selected" << endl;
    }
    return 0;
}
