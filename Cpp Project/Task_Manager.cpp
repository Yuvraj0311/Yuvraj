
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>

using namespace std;
const int MAX_TASKS = 100;

//structure containing task details.

struct Task 
{

    string description;
    string due_date;
    bool completed;

};

struct User 
{

    string firstName;
    string lastName;
    string username;
    string password;

};

//checking if user already exists.

bool checkIfUserExists(const string& username) 
{

    ifstream file(username + ".txt");
    string firstname, lastname, un, pw;
	getline(file, firstname);
	getline(file, lastname);
    getline(file, un);
    getline(file, pw);

    if(un == username)
    {
        file.close();
        return true;
    }    

    file.close();
    return false;
    
}

//using file handling to create file for storing users data.

bool is_Logged_In(string username, string password)
{

	string firstname, lastname, un, pw;

    if (!checkIfUserExists(username))
    {
        cout << "User does not exist! Please sign up." << endl;
        return false;
    }

	ifstream file;
	file.open(username + ".txt");
	getline(file, firstname);
	getline(file, lastname);
    getline(file, un);
    getline(file, pw);

	if(un == username && pw == password)
    {
		return true;
	}

    else
    {
        cout<<"Incorrect Username Or Password!"<<endl;	
		return false;
	}
}

//using class to help the user signup.

class signup
{ 
    public:

void signUp() 
{
    string firstName, lastName, username, password;
    
    cout << "\t\t\t Enter first name: ";
    cin >> firstName;
    
    cout << "\t\t\t Enter last name: ";
    cin >> lastName;
    
    cout << "\t\t\t Enter username: ";
    cin >> username;
    
    if (checkIfUserExists(username)) 
    {

        cout<<"\t\t\t !ERROR!"<<endl;
        cout << "\t\t\t User already exists!"<<endl;
        cout<<"\t\t\t  Please try a different username." << endl;
        return;

    }
    
    cout << "\t\t\t Enter password: ";
    cin >> password;
    
    ofstream file(username + ".txt", ios::app);
    file <<firstName << endl << lastName << endl << username << endl<< password << endl;
    file.close();
    
    cout << "\t\t\t Sign up successful!" << endl;
}

};

void createNewFile(const string& filename) 
{
    ofstream file(filename);
    
    if (file.is_open()) 
    {
        file.close();
    } 
    
    else
    {
        cout << "Error creating file: " << filename << endl;
    }
}

void updatedetails(const string& username, const string& password)
{
    string firstname, lastname, line, p1;
    cout<<"\t\t\t Enter your password : "<<endl << "\t\t\t ";

    while(1)
    {        
        cin>>p1;
        if(p1 == password)
        {
            break;
        }
        else
        {
            cout << "\t\t\t Invalid Password Please try again" <<endl << "\t\t\t ";
        }
    }

    string a = username + ".txt";
    const char* filename = a.data();
    
    string fn, ln, pw;
    ifstream file(filename);
    getline(file, firstname);
    getline(file, lastname);
    
    //updating information of existing user.

    while(1)
    {
        int choice;
        cout<<"\t\t\t What do you want to update : "<<endl;
        cout<<"\t\t\t 1. First Name"<<endl;
        cout<<"\t\t\t 2. Last Name"<<endl;
        cout<<"\t\t\t 3. Password"<<endl;
        cout<<"\t\t\t 4. Go Back"<<endl;
        cout<<"\t\t\t Enter your choice : ";
        cin>>choice;

        if(choice == 1)
        {
            ofstream out("temp.txt", ios::out);
            cout<<"\t\t\t Enter new First Name : "<<endl << "\t\t\t ";
            cin>>fn; 

            out<<fn<<endl<<lastname<<endl<<username<<endl<<password;
            cout << "\t\t\t Successfully Updated your First Name" << endl;
            file.close();
            out.close();

            remove(filename);
            rename("temp.txt", filename);
        }

        else if(choice == 2)
        {
            ofstream out("temp.txt", ios::out);
            cout<<"\t\t\t Enter new Last Name : "<<endl << "\t\t\t ";
            cin>>ln;
            
            out<<firstname<<endl<<ln<<endl<<username<<endl<<password;
            cout << "\t\t\t Successfully Updated your Last Name" << endl;
            file.close();
            out.close();
            
            remove(filename);
            rename("temp.txt", filename);
        }

        else if(choice == 3)
        {
            ofstream out("temp.txt", ios::out);
            cout<<"\t\t\t Enter new password : "<<endl << "\t\t\t ";
            cin>>pw;
            out<<firstname<<endl<<lastname<<endl<<username<<endl<<pw;
            cout << "\t\t\t Successfully Updated your password" << endl;
            file.close();
            out.close();
            remove(filename);
            rename("temp.txt", filename);
        }

        else if(choice == 4)
        {
            break;
        }

        else
        {
            cout<<"\t\t\t Invaid Choice";
        }
    }
    cout<<"\t\t\t Record Updated Successfully"<<endl; 

}

string getFirstNameFromFile(const string& filename) 
{
    ifstream file(filename);
    string firstName;
    
    if (file.is_open()) 
    {
        getline(file, firstName);
        file.close();
    } 
    
    else 
    {
        cout << "\t\t\t Error opening file: " << filename << endl;
    }
    
    return firstName;
    
}

void getNumberOfLines(const string& username) 
{
    string filename = username + "task.txt";
    ifstream file(filename);
    string line;
    int count = 0;
    
    while (getline(file, line)) 
    {
        if(line.empty())
        {
            break;
        }

        if(line == "Pending")
        {
            count++;
        }
    }
    
    file.close();

    cout<<endl<<"\t\t\t Number of task(s) remaining are "<<(count)<<endl;

}

//checking for leap year.

bool isLeapYear(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year) 
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month == 2 && isLeapYear(year))
    {
        return 29;
    }

    else
    {
        return daysInMonth[month - 1];
    }
}

int getStartingDayOfWeek(int month, int year) 
{

    if (month < 3) 
    {
        month += 12;
        year--;
    }
    
    int q = 1;
    int m = month;
    int k = year % 100;
    int j = year / 100;
    
    int h = (q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    
    return (h + 6) % 7;
}

class calendar
{ 

public:

void printCalendar(int month, int year) 
{
    string months[] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

    int daysInMonth = getDaysInMonth(month, year);

    int startingDayOfWeek = getStartingDayOfWeek(month, year);
    
    cout << "\t\t\t " << months[month - 1] << " " << year << endl;
    
    cout << "\t\t\t Sun Mon Tue Wed Thu Fri Sat" << endl;
    cout << "\t\t\t ";
    
    for (int i = 0; i < startingDayOfWeek; i++) 
    {
        cout << "    ";
    }
    
    int currentDayOfWeek = startingDayOfWeek;

    for (int day = 1; day <= daysInMonth; day++) 
    {
        cout << setw(3) << day << " ";
        
        if (currentDayOfWeek == 6) 
        {
            cout << endl << "\t\t\t ";
        }
        
        currentDayOfWeek = (currentDayOfWeek + 1) % 7;
    }
    
    cout << endl << endl;    
}
};

//displaying time.

class time_show : public calendar
{ 
public:
void showTime()
{
    chrono::system_clock::time_point currentTime = chrono::system_clock::now();
    time_t currentTimeT = chrono::system_clock::to_time_t(currentTime);
    string timeString = ctime(&currentTimeT);

    cout<<endl;
    cout<<"\t\t\t----------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t Current time: " << timeString;
    cout<<"\t\t\t----------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    while(1)
    {
        char a;
        cout << "\t\t\t Press B to Go Back" << endl << "\t\t\t ";
        cin>>a;
        if(a == 'b' || a == 'B')
        {
            break;
        }
        else
        {
            cout << "\t\t\t Invalid Choice";
        }
    }
}

 };

//class for managing tasks in program and file.

class tasks
{ 

    public:

void addTask(const string& username, int month, int year, int date) 
{

    string strYear = to_string(year);
    string strMonth = to_string(month);
    string strDate = to_string(date);
    string filename = username + "task.txt";
    ofstream file(filename, ios::app);
    
    if (!file) 
    {
        cout << "\t\t\t Error opening file : " << filename << endl;
        return;
    }
    
    Task task;
    
    cout << endl <<"\t\t\t Enter task description : ";

    getline(cin >> ws, task.description);

    task.due_date = strYear + '-' + strMonth + '-' + strDate;
    
    task.completed = false;

    string status;

    if(task.completed == 0){
        status = "Pending";
    }
    else{
        status = "Completed";
    }
    
    file << "TASK NAME : " << task.description << " , DUE DATE : " <<
    task.due_date << " , STATUS : " << endl << status << endl;
    
    file.close();
    
    cout <<endl<<"\t\t\t Task added successfully!" << endl << endl;

}

//function for viewing tasks.

void viewTask(const string& username) 
{
    string filename = username + "task.txt";

    ifstream file(filename, ios::in);
    
    if (!file) 
    {
        cout << "\t\t\t Error opening file: " << filename << endl;
        return;
    }
    
    cout << endl << "\t\t\t Tasks:" << endl;
    
    int count = 1, i = 1;

    string line;
    
    /*for (int i = 1; i < 5; i++) 
    {
        if (!getline(file, line)) 
        {
            file.close();
        }
    }*/

    while (getline(file, line)) 
    {
        if(line.empty())
        {
            break;
        }
        if(i % 2 == 0)
        {
            cout  << line << endl;
        }
        else
        {
            cout << "\t\t\t " << count++ << ". " << line;
        }
        i++;
    }
    
    file.close();
}

//deleting tasks.

void deleteTask(const string& username) 
{
    string filename = username + "task.txt";

    int tasknumber;

    ifstream file(filename);
    
    if (!file) 
    {
        cout << "\t\t\t Error opening file: " << filename << endl;
        return;
    }

    viewTask(username);

    cout << endl << "\t\t\t Enter the task number you that you want to delete : " << endl << "\t\t\t ";

    cin >> tasknumber;
    
    int count = 1;

    string line;
    
    ofstream temp("temp.txt");

    while (getline(file, line)) 
    {
        if(count == ((2*tasknumber)-1))
        {
            break;
        }  
        temp << line << endl;
        count++;
    }

    getline(file, line);

    while(getline(file, line))
    {
        if(line.empty())
        {
            break;

        }
        temp << line << endl;
    }
    
    file.close();
    temp.close();
    
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
    
    cout << endl << "\t\t\t Task deleted successfully!" << endl << endl;
}

//functions to marks tasks as completed.

void markTaskAsCompleted(const string& username) 
{
    string filename = username + "task.txt";
    int taskNumber;
    ifstream file(filename);
    
    if (!file) 
    {
        cout << "\t\t\t Error opening file: " << filename << endl;
        return;
    }
    
    viewTask(username);

    cout << "\t\t\t Enter the task number to mark as completed: ";
    cin >> taskNumber;
    
    int count = 1;
    string line;
    
    ofstream temp("temp.txt");
    
    while (getline(file, line)) 
    {        

        if(count == 2*taskNumber)
        
        {
            temp << "Completed" << endl;
        }
        
        else
        
        {
            temp << line << endl;
        }
        
        count++;
    }
    
    file.close();
    temp.close();
    
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
    cout << "\t\t\t Task Completed" << endl << endl;
    
    while(1)
    {
        char a;
        cout << endl << "\t\t\t Press B to Go Back" << endl << "\t\t\t ";
        cin>>a;
    
        if(a == 'b' || a == 'B')
        {
            break;
        }
    
        else
        {
            cout << "\t\t\t Invalid Choice" << endl << "\t\t\t ";
        }
    }
}

};

void exitProgram() 
{
    cout << "\t\t\t Exiting program..." << endl;
    exit(0);
}

//main function.

int main() 
{
    calendar ob1;
    tasks ob2;
    time_show ob3;
    signup ob4;
    int choice, count=0;
    int date2;
    Task tasks[MAX_TASKS];
    string username, password;
    int lineNumber = 1;
    //cout << "\033[1;35m" << endl;
    //cout << "\033[1;36m" << endl;

    cout<<"\t\t\t------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    cout << "\t\t\t\t\tWELCOME TO MULTI-UTILITY APPLICATION !" << endl;
    cout<<endl;
    cout<<"\t\t\t------------------------------------------------------------------------------"<<endl;
    
    //Start page , main menu.

    while (1) 
    {   
        cout << "\t\t\t 1. SIGN UP" << endl;
        cout<<endl;

        cout << "\t\t\t 2. LOG IN" << endl;
        cout<<endl;
        
        cout << "\t\t\t 3. EXIT" << endl;
        cout<<endl;

        cout<<"\t\t\t-------------------------------------------------------------------------------"<<endl;
        
        cout << "\t\t\t ENTER YOUR CHOICE : ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:

                ob4.signUp();
                break;

            case 2:

                cout<<"\t\t\t Enter Username: ";
	            cin>>username;

	            cout<<"\t\t\t Enter Password: ";
	            cin>>password;
                
                if(is_Logged_In(username, password))
                
                {
                    string filename = username +".txt";

                    int choice2;
		        
                    cout << "\t\t\t\t\tLogin successful!" << endl;
                    //cout << "\033[1;36m" << endl;
                    cout<<"\t\t\t------------------------------------------------------------------------------"<<endl;
                    cout<<endl;
                    cout << "\t\t\t\t\tWELCOME TO MULTI-UTILITY APPLICATION !" << endl;
                    cout<<endl;
                    cout<<"\t\t\t------------------------------------------------------------------------------"<<endl;

                   //asking the user what action they want to take.

                    while(1)
                    { 

                    getNumberOfLines(username);
                    cout<<endl;
                    cout<<"\t\t\t What would you like to do today?"<<endl;
                    
                    cout<<endl;
                    cout<<"\t\t\t 1. Set Task"<<endl;
                    
                    cout<<endl;
                    cout<<"\t\t\t 2. View Tasks"<<endl;
                    
                    cout<<endl;
                    cout<<"\t\t\t 3. Mark Task as Completed"<<endl;
                    
                    cout<<endl;
                    cout<<"\t\t\t 4. Delete Task" <<endl;
                    
                    cout<<endl;
                    cout<<"\t\t\t 5. View Calendar"<<endl;
                    
                    cout<<endl;
                    cout<<"\t\t\t 6. Update Details"<<endl;
                    
                    cout<<endl;
                    cout<<"\t\t\t 7. Check time"<<endl;
                    
                    cout<<endl;
                    cout<<"\t\t\t 8. Log out"<<endl;
                    
                    cout<<endl;
                    cout<<"\t\t\t Your choice: ";
                    
                    cin>>choice2;

                    switch(choice2)
                    {
                        case 1:

                         int month, date, year;
                         cout<<"\t\t\t Enter a month (1-12): ";
                         cin>>month;
                         
                         cout<<"\t\t\t Enter year: ";
                         cin>>year;
                         
                         if(month<5&&year<2023||year<2023)
                         {
                            cout<<"\t\t\t Can't set tasks in the past."<<endl;
                            cout<<endl;
                         }
                         
                         else
                         {
                            ob1.printCalendar(month, year);
                            
                            cout<<"\t\t\t Choose the Date: ";
                            cin>>date2;
                            
                            ob2.addTask(username, month, year, date2);
                         }
                         break;

                        case 2:
                        
                         ob2.viewTask(username);
                        
                         while(1)
                         {
                             char a;
                             cout << endl << "\t\t\t Press B to Go Back" << endl << "\t\t\t ";
                             cin>>a;
                             if(a == 'b' || a == 'B')
                             {
                                 break;
                             }
                             else
                             {
                                 cout << "\t\t\t Invalid Choice" << endl << "\t\t\t ";
                             }
                         }
                         break;
                        
                        case 3:
                        
                         ob2.markTaskAsCompleted(username);
                         break;

                        case 4:
                        
                         ob2.deleteTask(username);
                         break;

                        case 5:
                        
                         ob1.printCalendar(5, 2023);
                         
                         while(1)
                         {
                             char a;
                             cout << "\t\t\t Press B to Go Back" << endl << "\t\t\t ";
                             cin>>a;
                             if(a == 'b' || a == 'B')
                             {
                                 break;
                             }
                             else
                             {
                                 cout << "\t\t\t Invalid Choice" << "\t\t\t ";
                             }
                         }
                         cout<<endl;
                         break;
        
                        case 6:
                        
                         updatedetails(username, password);
                         break;

                        case 7:
                        
                          ob3.showTime();
                          break;
        
                        case 8:
                        
                         cout<<"\t\t\t Successfully Logged Out "<<endl;
                         break;
        
                        default:
                        
                          cout<<"\t\t\t Invalid choice"<<endl;
                    }
                    if(choice2 == 8)
                        {
                            choice2 = 0;
                            break;
                        }
            }

		        }
                break;
            case 3:
               
                cout << "\t\t\t Exiting program..." << endl;
                return 0;
            
            default:
             
                cout << "\t\t\t Invalid choice! Please try again." << endl;

        }
        
        cout << endl;
    }

    return 0;

}