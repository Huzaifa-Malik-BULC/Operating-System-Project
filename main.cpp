#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<conio.h>
#include<algorithm>
#include<Windows.h>
using namespace std;

class Student {
public:
	// Data Members
	char studentName[30]; // Name of the student
	int studentAge; // Age of the student
	char studentCNIC[20]; // CNIC of the student
	char studentPhoneNo[20]; // Phone Number of the student
	char studentAddress[150]; // Address of the student
	float studentFee; // Fee of the student
	float takeTime; // Time to be spent on interview
	char houseType[10]; // Possible Options: 'r' for Rental and 'n' for Non-Rental
	char instituteName[30]; // Name of the institute
	char fatherName[30]; // Name of the father
	char fatherCNIC[20]; // CNIC of the father
	char selectedFrom[150]; // From where the student is selected
	char fatherStatus[10]; // Possible Options: 'a' for Alive and 'd' for deceased
	float monthlyIncome; // Income per month
	float netExpense; // Expeneses per year
	int priority; // Priority of the student
	int numberOfSibllings; // Number of siblings of the student
	bool interview; // true if called for interview, else false


	// Member Functions
	Student(); // Default Constructor
	static void getPreviousStudentData(); // Get data from file when we run program
	void insertStudent(Student, string type); // Insert a student into the database
	bool isEmpty(); // Check if the student data base is empty or not
	void searchForm(string studentCNIC); // Used to Search data of a student
	bool doesExist(string studentCNIC); // Check if a student exists in the database or not
	void deleteStudentApplication(string studentCNIC);
	void prioritySelection(); // Prioritizes the students on the basis of their attributes
	void display() const; // Displays the student data
	void displayAll(); // Display the data of all students
	bool validate(); // Checks if the data entered by the student is valid or not
	void submitAnApplication(); // Adds the student data into the database
};

class Drawer
{
public:
	void CordXY(int x, int y);
	void DesignFirst(int x, int y, int z, int g);
	void Line(int col);
};

void Drawer::CordXY(int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD position{ };
	position.X = x;
	position.Y = y;

	SetConsoleCursorPosition(console, position);
}

void Drawer::DesignFirst(int x, int y, int z, int g)
{
	int a, b, c, d;
	a = x;
	b = y;
	c = z, d = g;
	// We draw FRAME for the bar
	for (int i = x; i < y; i++)
	{
		CordXY(i, z);
		cout << char(205); // 2 horizontal lines
		CordXY(i, g);
		cout << char(205);
	}
	for (int i = z + 1; i < g; i++) // 2 vertical lines
	{
		CordXY(a, i);
		cout << char(186);
		CordXY(b, i);
		cout << char(186);
	}
	CordXY(a, z); // top left
	cout << char(201);
	CordXY(b, z); // top right
	cout << char(187);
	CordXY(a, g); // bottom left
	cout << char(200);
	CordXY(b, g); // bottom right
	cout << char(188);
}

void Drawer::Line(int col)
{
	for (int i = 1; i <= col; i++)
	{
		if (i == 1 || i == col)
		{
			cout << "+";
		}
		else
		{
			cout << "-";
		}
	}
}

Drawer drawer;

vector<Student> student_data; // All student data will be stored here

vector<Student> sortVector(vector<Student> arr) { // Picked from ChatGPT
	// Sorting in ascending order based on priority
	sort(arr.begin(), arr.end(), [](const Student& a, const Student& b) {
		return a.priority < b.priority;
		});
	return arr;
}

int main() {
	Student::getPreviousStudentData();
	Student temp;
	char choice = 'N';

	drawer.CordXY(30, 12);
	system("color F4");
	cout << "Loading:";
	char x = 219;
	for (int i = 0; i < 30; i++)
	{
		cout << x;
		Sleep(30);
		if (i == 5)
		{
			Sleep(500);
		}
		if (i == 20)
		{
			Sleep(200);
		}
	}

restart:
	system("cls"); // Clears the Screen

	// Show options
	system("color F0");
	drawer.DesignFirst(25, 100, 2, 6);
	drawer.CordXY(43, 4);
	cout << "WELCOME TO STUDENT SCHOLARSHIP PROGRAM";
	drawer.CordXY(28, 9);
	cout << "1.Submit An Application";
	drawer.CordXY(29, 10);
	drawer.Line(30);
	drawer.CordXY(28, 12);
	cout << "2.Check An Application";
	drawer.CordXY(29, 13);
	drawer.Line(30);
	drawer.CordXY(28, 15);
	cout << "3.Delete An Application";
	drawer.CordXY(29, 16);
	drawer.Line(30);
	drawer.CordXY(28, 18);
	cout << "4.Application Database";
	drawer.CordXY(29, 19);
	drawer.Line(30);
	drawer.CordXY(28, 21);
	cout << "5.To Exit From Program";
	drawer.CordXY(29, 22);
	drawer.Line(30);
	drawer.DesignFirst(29, 42, 23, 25);
	drawer.CordXY(30, 24);
	cout << "Choose: ";
	cin >> choice;
	cin.ignore();
	system("cls"); // Clears the Screen

	if (choice == '1') {
		temp.submitAnApplication();

	}
	else if (choice == '2') {
		cout << "\n\nEnter Student CNIC to Search Form: ";
		cin >> temp.studentCNIC;

		temp.searchForm(temp.studentCNIC);


	}
	else if (choice == '3') {
		cout << "\n\nEnter Student CNIC to Search Form: ";
		cin >> temp.studentCNIC;
		temp.deleteStudentApplication(temp.studentCNIC);
	}
	else if (choice == '4') {
		temp.displayAll();
	}
	else if (choice == '5') {
		exit(0);
	}
	else {
		cout << "\n\n\n\t\tError!  Invalid Selection.......";

	}
	cout << "\n";
	system("pause");
	system("CLS");
	goto restart;
}

bool Student::isEmpty() {
	return (student_data.size() == 0);
}

Student::Student() : studentFee(0), netExpense(0), studentAge(0), takeTime(0), numberOfSibllings(0), monthlyIncome(0), interview(false), priority(-1) {}

void Student::getPreviousStudentData() {
	fstream getStudentData("students_data.dat", ios::binary | ios::in);
	if (getStudentData.is_open()) {
		Student temp;
		while (getStudentData.read((char*)&temp, sizeof(Student))) {
			temp.insertStudent(temp, "file");
		}
	}
	else {
		fstream createFile("students_data.dat", ios::binary | ios::app); // Create a file if it does not exist
		createFile.close();
	}
	getStudentData.close();
}

void Student::insertStudent(Student data, string type) {
	if (type != "file") {
		data.prioritySelection();
		fstream addStudentData("students_data.dat", ios::binary | ios::app);
		addStudentData.write((char*)&data, sizeof(Student));
		addStudentData.close();
	}

	student_data.push_back(data);
}


void Student::searchForm(string studentCNIC) {
	bool found = false;
	if (isEmpty()) {
		cout << "\n\n________________________________________________________________________________________________________________________";
		cout << "\n\n\t\t\t\t\t\tRecord List is empty ";
		cout << "\n________________________________________________________________________________________________________________________";
	}
	else {
		for (Student student : student_data) {
			if (student.studentCNIC == studentCNIC) {
				found = true;
				student.display();
				break;
			}
		}
	}

	if (!found && !isEmpty()) {
		cout << "\n\n\nNo Form Exist with Student CNIC: " << studentCNIC;
		char choice;
		cout << "\n\n\n\t\t1. Go to Application Database";
		cout << "\n\n\n\t\t2. To Exit From Search Menu\n\n\n\t\t";
		cout << "\n\t\tChoose: ";
		cin >> choice;
		if (choice == '1') {
			Student s;
			s.displayAll();
		}
		else if (choice == '2') {
			cin.ignore();
		}
		else {
			cout << "\n\n\n\t\tError!  Invalid Selection.......";
		}
	}

}

bool Student::doesExist(string studentCNIC) {
	for (Student student : student_data) {
		if (student.studentCNIC == studentCNIC) {
			return true;
		}
	}
	return false;
}

void Student::prioritySelection() {
	if (this->monthlyIncome > 45000 && netExpense > 300000) {
		this->priority = 5;
		strcpy(this->selectedFrom, "Not Selected as income Or Gross Expenses are much");
		this->interview = false;
		takeTime = 0;
	}
	else if (this->monthlyIncome <= 20000 && this->netExpense <= 200000) {
		this->priority = 0;
		strcpy(this->selectedFrom, "Income in Range of 20000 and Net And Gross Expenses in Range of 200000");
		this->interview = true;
		takeTime = 5;
	}
	else if (this->monthlyIncome <= 30000 && this->netExpense <= 250000 && (this->fatherStatus[0] == 'd' || this->fatherStatus[0] == 'D')) {
		this->priority = 0;
		strcpy(this->selectedFrom, "Income in Range of 30000 and Net And Gross Expenses in Range of 250000 and Father status Deceased");
		this->interview = true;
		takeTime = 5;
	}
	else if (this->monthlyIncome <= 30000 && this->netExpense <= 300000 && (this->fatherStatus[0] == 'A' || this->fatherStatus[0] == 'a')) {
		this->priority = 1;
		strcpy(this->selectedFrom, "Income in Range of 30000 and Net And Gross Expenses Less than 300000");
		this->interview = true;
		takeTime = 8;
	}
	else if (this->monthlyIncome <= 45000 && this->monthlyIncome > 30000 && this->netExpense <= 300000 && (this->fatherStatus[0] == 'd' || this->fatherStatus[0] == 'D')) {
		this->priority = 1;
		strcpy(this->selectedFrom, "Income in Range of 45000 and Father Status Deceased");
		this->interview = true;
		takeTime = 8;
	}
	else if (this->monthlyIncome <= 40000 && this->monthlyIncome > 30000 && this->netExpense <= 300000 && this->numberOfSibllings >= 3 && (this->fatherStatus[0] == 'd' || this->fatherStatus[0] == 'D')) {
		this->priority = 2;
		strcpy(this->selectedFrom, "Income in range of 45000 and Net And Gross Expenses (300000) Having Sibling more than 3");
		this->interview = true;
		takeTime = 10;
	}
	else if (this->monthlyIncome <= 40000 && this->monthlyIncome > 30000 && this->netExpense <= 300000 && this->numberOfSibllings >= 3 && (this->fatherStatus[0] == 'A' || this->fatherStatus[0] == 'a')) {
		this->priority = 3;
		strcpy(this->selectedFrom, "Income in range of 45000 and Net And Gross Expenses (300000) Having Sibling more than 3");
		this->interview = true;
		takeTime = 12;
	}
	else if (this->monthlyIncome <= 45000 && this->monthlyIncome > 30000 && this->netExpense <= 300000 && this->numberOfSibllings < 3 && tolower(this->houseType[0]) == 'r' && (this->fatherStatus[0] == 'A' || this->fatherStatus[0] == 'a')) {
		this->priority = 2;
		strcpy(this->selectedFrom, "Income in range of 45000 and Net And Gross Expenses (300000) Having Sibling less than 3 And House is Rental");
		this->interview = true;
		takeTime = 10;
	}
	else if (this->monthlyIncome <= 45000 && this->monthlyIncome > 30000 && this->netExpense <= 300000 && this->numberOfSibllings < 3 && tolower(this->houseType[0]) != 'r' && (this->fatherStatus[0] == 'A' || this->fatherStatus[0] == 'a')) {
		this->priority = 3;
		strcpy(this->selectedFrom, "Income in range of 45000 and Net And Gross Expenses (300000) Having Sibling more than 3 And House is not Rental");
		this->interview = true;
		takeTime = 12;
	}
	else {
		this->priority = -1;
		strcpy(this->selectedFrom, "Unexpected Error");
		this->interview = false;
		takeTime = -1;
	}
}

void Student::deleteStudentApplication(string studentCNIC) {
	if (this->isEmpty()) {
		cout << "\n\n________________________________________________________________________________________________________________________";
		cout << "\n\n\t\t\t\t\t\tRecord List is empty ";
		cout << "\n________________________________________________________________________________________________________________________";
	}
	else if (this->doesExist(studentCNIC)) {
		vector<string> CNICs;
		student_data.erase(std::remove_if(student_data.begin(), student_data.end(), [studentCNIC](const Student& s) {
			return s.studentCNIC == studentCNIC;
			}), student_data.end());

		fstream get("students_data.dat", ios::binary | ios::in);
		fstream set("temp_students_data.dat", ios::binary | ios::app);
		Student temp;
		while (!get.eof()) {
			get.read((char*)&temp, sizeof(Student));
			if (find(CNICs.begin(), CNICs.end(), studentCNIC) == CNICs.end()) {
				if (temp.studentCNIC != studentCNIC) {
					CNICs.push_back(temp.studentCNIC);
					set.write((char*)&temp, sizeof(Student));
				}
			}
		}
		get.close();
		set.close();
		remove("students_data.dat");
		rename("temp_students_data.dat", "students_data.dat");
	}
	else {
		cout << "\n\n\nNo Form is submitted with CNIC: " << studentCNIC;
	}
}

void Student::display() const {

	cout << "\n\n________________________________________________________________________________________________________________________";
	cout << "\n\n\t\t\t\t\tDisplaying Record for Student CNIC: " << this->studentCNIC;
	cout << "\n________________________________________________________________________________________________________________________";
	cout << "\n\t\tName: " << this->studentName << endl;
	cout << "\t\tAge: " << this->studentAge << endl;
	cout << "\t\tCNIC: " << this->studentCNIC << endl;
	cout << "\t\tPhone Number: " << this->studentPhoneNo << endl;
	cout << "\t\tStudent Fee: " << this->studentFee << endl;
	cout << "\t\tInstitute: " << this->instituteName << endl;
	cout << "\t\tAddress: " << this->studentAddress << endl;
	cout << "\t\tFather Name: " << this->fatherName << endl;
	cout << "\t\tFather CNIC: " << this->fatherCNIC << endl;
	cout << "\t\tMonthly Income: " << this->monthlyIncome << endl;
	cout << "\t\tExpenses: " << this->netExpense << endl;
	cout << "\t\tType of House: " << this->houseType << endl;
	cout << "\t\tPriority of Student: " << this->priority << endl;
	cout << "\t\tTime you should spend on the interview: " << this->takeTime << endl;
	cout << "\t\tComments: " << this->selectedFrom << endl;
	if (interview == true) {
		cout << "\n\n\tApplication Status:\tApplicant is asked for the interview";
	}
	else {
		cout << "\n\n\n\tApplication Status:\tApplicant has been rejected";
	}

}

void Student::displayAll() {
	if (isEmpty()) {
		cout << "\n\n________________________________________________________________________________________________________________________";
		cout << "\n\n\t\t\t\t\t\t Database is empty ";
		cout << "\n________________________________________________________________________________________________________________________";
	}
	else {
		int choice;
	restart:
		system("cls");
		drawer.CordXY(30, 2);
		cout << "1) Show all applications";
		drawer.CordXY(30, 3);
		drawer.Line(30);
		drawer.CordXY(30, 4);
		cout << "2) Show Applications that have been asked for an interview";
		drawer.CordXY(30, 5);
		drawer.Line(65);
		drawer.CordXY(30, 6);
		cout << "3) Show Rejected Applications";
		drawer.CordXY(30, 7);
		drawer.Line(34);
		drawer.CordXY(30, 8);
		cout << "4) Show Applications with Priority 0";
		drawer.CordXY(30, 9);
		drawer.Line(40);
		drawer.CordXY(30, 10);
		cout << "5) Show Applications with Priority 1";
		drawer.CordXY(30, 11);
		drawer.Line(40);
		drawer.CordXY(30, 12);
		cout << "6) Show Applications with Priority 2";
		drawer.CordXY(30, 13);
		drawer.Line(40);
		drawer.CordXY(30, 14);
		cout << "7) Show Applications with Priority 3";
		drawer.CordXY(30, 15);
		drawer.Line(40);
		drawer.CordXY(30, 16);
		cout << "8) See who got selected";
		drawer.CordXY(30, 17);
		drawer.Line(30);
		drawer.CordXY(30, 18);
		cout << "9) Exit from Database";
		drawer.CordXY(30, 19);
		drawer.Line(30);
		drawer.DesignFirst(29, 42, 20, 22);
		drawer.CordXY(30, 21);
		cout << "Choose: ";
		cin >> choice;
		if (choice < 1 || choice > 9) goto restart;

		student_data = sortVector(student_data); // Sort the vector based on priority

		int selectedCount = 0;
		vector<Student> selectedStudents; // Vector to store the first 5 selected students
		system("cls");
		for (Student student : student_data) {

			if (choice == 1) {
				student.display();
			}
			else if (choice == 2 && student.interview == true) {
				student.display();
			}
			else if (choice == 3 && student.interview == false) {
				student.display();
			}
			else if (choice == 4 && student.priority == 0) {
				student.display();
			}
			else if (choice == 5 && student.priority == 1) {
				student.display();
			}
			else if (choice == 6 && student.priority == 2) {
				student.display();
			}
			else if (choice == 7 && student.priority == 3) {
				student.display();
			}
			else if (choice == 8 && selectedCount < 5 && student.priority != 5) {
				// Select the first 5 students
				selectedStudents.push_back(student);
				selectedCount++;
			}
		}

		// Display the congratulations message along with the list of the first 5 selected students
		if (selectedCount > 0 && choice == 8) {
			system("cls");
			cout << "\n\n\t\tList of Students Who Got Selected:\n";
			for (const auto& selectedStudent : selectedStudents) {
				cout << "\n\t\tName: " << selectedStudent.studentName
					<< "\n\t\tCNIC: " << selectedStudent.studentCNIC
					<< "\n\t\tPriority: " << selectedStudent.priority
					<< "\n\n";
			}
		}
	}
}

bool Student::validate() {
	vector<string> errors;
	if (this->doesExist(this->studentCNIC))
		errors.push_back("Student Record Already Exists");

	if (this->studentFee < 0)
		errors.push_back("Student Fee cannot be zero");

	if (this->fatherStatus[0] != 'a' && this->fatherStatus[0] != 'd')
		errors.push_back("Father Status can either be Alive (a) or Deceased (d)");

	if (tolower(this->houseType[0]) != 'n' && tolower(this->houseType[0]) != 'r')
		errors.push_back("House Type can either be Rental or Non Rental");

	if (this->studentAge < 0) {
		errors.push_back("Age cannot be less than zero");
	}

	if (this->monthlyIncome < 0)
		errors.push_back("Monthly Income cannot be less than zero");

	if (this->netExpense < 0)
		errors.push_back("Net and Gross cannot be less than zero");

	if (this->numberOfSibllings < 0)
		errors.push_back("Number and Siblings cannot be less than zero");

	if (errors.size() > 0) { // Means errors are found and we need to display them
		cout << "\n\n\t\t\tCould not Register.";
		cout << "\n\n\t\t\tErrors Found:";

		for (string error : errors)
			cout << "\n\t\t\t" << error;
		return false; // Means errors were found and we cannot register this student
	}
	else return true; // Means no errors are found and we need to register the student
}

void Student::submitAnApplication() {
	Student student_data;

	cout << "\n\n\t\tEnter Name Of The Student: ";
	cin.getline(student_data.studentName, 150);

	cout << "\n\n\t\tEnter Age Of The Student: ";
	cin >> student_data.studentAge;

	cin.ignore(); // Because the last input was an integer we need to do this while taking input as a string
	cout << "\n\n\t\tEnter CNIC Of The Student: ";
	cin.getline(student_data.studentCNIC, 150);

	cout << "\n\n\t\tEnter phone number of the Student: ";
	cin.getline(student_data.studentPhoneNo, 150);

	cout << "\n\n\t\tEnter address of the Student: ";
	cin.getline(student_data.studentAddress, 150);

	cout << "\n\n\t\tEnter name of the University of the Student: ";
	cin.getline(student_data.instituteName, 150);

	cout << "\n\n\t\tEnter Student Fee: ";
	cin >> student_data.studentFee;

	cin.ignore();
	cout << "\n\n\t\tEnter Father Name: ";
	cin.getline(student_data.fatherName, 150);

	cout << "\n\n\t\tEnter Father CNIC: ";
	cin.getline(student_data.fatherCNIC, 150);

	cout << "\n\n\t\tFather is Alive? 'a' for Alive 'd' for Deceased: ";
	cin.getline(student_data.fatherStatus, 150);

	cout << "\n\n\t\tEnter House Type and Size Of Student Mention Rental (r)/Non Rental (n) in Start: ";
	cin.getline(student_data.houseType, 150);

	cout << "\n\n\t\tEnter Monthly Income: ";
	cin >> student_data.monthlyIncome;

	cout << "\n\n\t\tEnter Net Expenses Of your House: ";
	cin >> student_data.netExpense;

	cout << "\n\n\t\tEnter Number Of Siblings Of Student: ";
	cin >> student_data.numberOfSibllings;

	if (student_data.validate())
		insertStudent(student_data, ""); // Pass the Student object to the insertStudent function
}