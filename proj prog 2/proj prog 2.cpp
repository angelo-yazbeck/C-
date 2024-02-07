
#include <iostream>
#include<cmath>
#include <iomanip>
#include<cstring>
#include <string>
#include <regex> 
#include<cstdlib>
#include<ctime>
#include<fstream>
#include <sstream> 
#include "md5.h"
#include <algorithm>
#include <cctype>
using namespace std;




struct course
{
	string Cid;
	string name;
	int credit;
};
struct enrollment
{
	int SID;
	string CID;
	int grade;
};
struct student
{
	int  ID;
	string firstname;
	string lastname;
	string password;
	string dob;
	string email;
	string phonenum;
	int Gpa;
	enrollment* a;
};
void hash(student& password) {
	password.password = md5(password.password);
}
void deletestd(int ID) {
	ifstream in("student.txt");
	ofstream out("student_new.txt");

	if (!in || !out) {
		cerr << "Error: Unable to open the input or output file" << endl;
		return;
	}
	string line;
	student temp;
	while (in >> temp.ID >> temp.firstname >> temp.lastname >> temp.password >> temp.dob >> temp.email >> temp.phonenum >> temp.Gpa) {

		stringstream ss(line);
		if (temp.ID != ID) {

			out << temp.ID << "\t" << temp.firstname << "\t" << temp.lastname << "\t" << temp.password << "\t" << temp.dob << "\t" << temp.email << "\t" << temp.phonenum << "\t" << temp.Gpa << endl;

		}
	}

	in.close();
	out.close();

	remove("student.txt");
	rename("student_new.txt", "student.txt");
	cout << "student with ID:" << ID << " has been removed";
}
bool is_valid(string email) {
	string email2;
	bool atFlag = false;
	bool comFlag = false;

	double size = email.length();

	for (int c = 0; c < email.length(); c++) {
		if (email[c] == '@') {
			atFlag = true;


			email2 = email.substr(size - (c + 2), size - 2);
			for (int i = 0; i < email2.length(); i++)
			{
				if (email2[i] == '.') {
					comFlag = true;
				}
			}



		}

	}
	if (atFlag && comFlag) {

		return true;

	}
	return false;
}
bool is_valid2(string email) {
	bool t = false;
	ifstream clintr("student.txt");
	student junk;
	while (clintr)
	{
		clintr >> junk.ID >> junk.firstname >> junk.lastname >> junk.password >> junk.dob >> junk.email >> junk.phonenum >> junk.Gpa;
		if (email == junk.email) {

			return false;
		}
	}
	return true;
}
void strongPass(string& str) {
	int lowcase = 0, upcase = 0, d = 0, s = 0;


	while (str.length() < 8)
	{
		cout << " your pass is short please inter a 8 digits at least ";
		getline(cin, str);
	}
	while (lowcase == 0 || upcase == 0 || d == 0 || s == 0) {

		for (int i = 0; i < str.length(); i++)
		{
			if (islower(str[i]))
				lowcase++;
			if (isupper(str[i]))
				upcase++;
			if (isdigit(str[i]))
				d++;
			if (!isalpha(str[i]) && !isdigit(str[i]))
				s++;
		}
		if (lowcase + upcase + d + s < 8 || (lowcase == 0 || upcase == 0 || d == 0 || s == 0))
		{
			cout << "weak password please enter a password containing numbers, letters, and special characters and at least it should be 8 charcters" << endl;
			getline(cin, str);
		}
		if (lowcase && upcase && d && s && str.length() >= 8)
		{
			break;
		}
	}
}
void studentoutput_e(student std) {
	cout << "\n\n\tWelcome " << std.firstname << " \n\n\n\nIf you would like to check your grades press 1 \nIf you would like to see your order in a class input 2\nIf you would like to check your GPA input 3\nIf you would like to check your grade for a class input 4\nIf you would like to see your courses in terms of grades input 5 \nIf you would like to add a proposition for a problem input 6 ";
}
void studentoutput_f() {
	cout << "\n\n\tBienvenue etudiant \n\n\n\nSi vous souhaitez verifier vos notes, appuyez sur 1 \nSi vous souhaitez voir votre ordre dans une  matiere Appuyez 2\nSi vous souhaitez verifier votre  GPA Appuyez 3\nSi vous souhaitez verifier votre note pour une classe Appuyez 4\nSi vous souhaitez voir vos cours en termes de notes Appuyez 5 \nSi vous souhaitez ajouter une proposition pour un probleme Appuyez 6";
}
void adminoutput() {
	cout << " \n\n\n\nIf you would like to add a student input 1\nIf you would like to update a grade input 2\nIf you would like to remove a student input 3 \nIf you would like to see the sudents in order of gpa input 4 \nIf you would like to calculate the average of a course for all students input 5";
}
int IDgen() {

	int c = 0;
	string line;
	student temp;

	ifstream std("student.txt");
	while (std) {
		std >> temp.ID >> temp.firstname >> temp.lastname >> temp.password >> temp.dob >> temp.email >> temp.phonenum >> temp.Gpa;

	}

	c = temp.ID + 1;
	std.close();
	return c;
}
bool checkPhone(string& pass) {
	if (pass.length() != 8) {
		cout << "the number must be  8 digits please reenter";

		return 0;
	}
	if ((pass[0] == '0' && pass[1] == '3') || (pass[0] == '7 ' && pass[1] == '1') || (pass[0] == '7' && pass[1] == '0') || (pass[0] == '7' && pass[1] == '6') || (pass[0] == '8' && pass[1] == '1') || (pass[0] == '7' && pass[1] == '8') || (pass[0] == '7 ' && pass[1] == '9')) {

		return 1;

	}
	else {
		cout << "The number must start with (03,70,71,76,81)";


		return 0;
	}
}
void addstudent() {
	student temp;
	temp.ID = IDgen();
	cin.clear();


	cin.ignore(INT_MAX, '\n');

	cout << "Please enter the name of the student\n ";
	getline(cin, temp.firstname);

	cout << "Please enter the family name of the student\n ";
	getline(cin, temp.lastname);
	cin.ignore(INT_MAX, '\n');
	cout << "Please enter the password of the student";

	getline(cin, temp.password);
	strongPass(temp.password);
	temp.password = md5(temp.password);


	cout << "\nPlease enter the date of birth of the student seperated by - \n ";
	getline(cin, temp.dob);

	cout << "Please enter the email of the student\n ";
	getline(cin, temp.email);
	while ((is_valid(temp.email) == 0) || (is_valid2(temp.email) == 0)) {
		while ((is_valid(temp.email) == 0))
		{
			cout << "your email is incorect please enternt correctly" << endl;
			getline(cin, temp.email);
		}
		while ((is_valid2(temp.email) == 0)) {
			cout << "your email  already exists enter please enter a new one ";
			getline(cin, temp.email);
		}
	}
	cout << "Please enter the phonenumber of the student\n ";
	getline(cin, temp.phonenum);
	while (checkPhone(temp.phonenum) == 0) {
		getline(cin, temp.phonenum);
	}
	temp.Gpa = 0;

	fstream add("student.txt", ios::in | ios::out | ios::app);
	add << temp.ID << "\t" << temp.firstname << "\t" << temp.lastname << "\t" << temp.password << "\t" << temp.dob << "\t" << temp.email << "\t" << temp.phonenum << "\t" << temp.Gpa << "\n";
	add.close();


}
bool authentication_s(student& std) {
	student temp;

	cin.ignore(INT_MAX, '\n');
	cout << "Please enter your email" << endl;
	cout << "Please enter your password" << endl;
	getline(cin, std.email);
	getline(cin, std.password);
	std.password = md5(std.password);


	fstream student("student.txt", ios::in);
	while (student) {
		student >> temp.ID >> temp.firstname >> temp.lastname >> temp.password >> temp.dob >> temp.email >> temp.phonenum >> temp.Gpa;

		if ((std.password == temp.password) && (std.email == temp.email)) {
			std.ID = temp.ID;
			std.firstname = temp.firstname;
			std.lastname = temp.lastname;
			std.phonenum = temp.phonenum;
			cout << "\n\nLOGIN SUCCESSFULL\n\n\n\nWelcome Student " << std.firstname << " " << std.lastname << endl;
			student.close();
			return true;
		}
	}
	return false;


}
bool authentication_a() {
	student temp;
	cin.ignore();
	cout << "Please enter your email ";

	getline(cin, temp.email);
	cout << "Please enter your password ";
	getline(cin, temp.password);


	if ((temp.email == "admin") && (temp.password == "password")) {
		cout << "log in successful\n\n\tWELCOME ADMIN" << endl;

		return true;
	}
	else {
		return false;
	}
}
void enrollement(student& std, int& test1) {
	int c = 0, c1 = 0;
	test1 = 0;
	string a;
	enrollment temp;
	fstream f("enrollment.txt", ios::in | ios::out);
	if (!f) {
		cerr << "Error: Unable to open the input or output file" << std::endl;
		return;
	}
	while (f) {

		f >> temp.SID >> temp.CID >> temp.grade;
		getline(f, a, '\n');

		if (temp.SID == std.ID) {

			test1++;

		}
	}
	std.a = new enrollment[test1 + 1];

	c = 0;
	fstream fi("enrollment.txt", ios::in | ios::out);
	if (!fi) {
		cerr << "Error: Unable to open the input or output file" << std::endl;
		return;
	}
	while (fi) {
		fi >> temp.SID >> temp.CID >> temp.grade;
		getline(fi, a, '\n');
		if (temp.SID == std.ID) {

			std.a[c].CID = temp.CID;

			std.a[c].SID = temp.SID;

			std.a[c].grade = temp.grade;


			c++;
		}

	}
	fi.close();

	f.close();


}
void proposition_e(student std) {
	cin.ignore(INT_MAX, '\n');
	string s;
	cout << "\n\n\n\nPlease type you propostion" << endl;
	getline(cin, s);
	fstream f("prop.txt", ios::app);
	f << "Proposition given by " << std.firstname << " " << std.lastname << endl << s << endl;

	cout << "\n\n\nThank you " << std.firstname << " for your propositon";
	f.close();
}
void proposition_f(student std) {
	cin.ignore(INT_MAX, '\n');
	string s;
	cout << "\n\n\n\nS'il vous plaît tapez votre proposition" << endl;
	getline(cin, s);
	fstream f("prop.txt", ios::app);
	f << "Proposition given by " << std.firstname << " " << std.lastname << endl << s << endl;

	cout << "\n\n\nMerci " << std.firstname << " pour votre propositon";
	f.close();
}
string coursename(string cid) {
	string a;
	string s;
	course temp;
	fstream f("course.txt", ios::app | ios::in | ios::out);
	if (!f) {
		cerr << "Error: Unable to open the input or output file" << endl;

	}
	else {
		while (f) {
			f >> temp.Cid >> temp.name >> temp.credit;

			if (temp.Cid == cid) {
				s = temp.name;
				return s;
			}
			else
				return a;
		}
	}
	f.close();


}
void stdgrades(student std, int test1) {
	string s;

	for (int i = 0;i < test1;i++) {
		s = coursename(std.a[i].CID);
		cout << s << " " << std.a[i].grade << endl;
	}
}
void stdgrade_e(student std, int test1) {
	string s;
	cin.ignore(INT_MAX, '\n');
	cout << "Please enter the name of the course you want to see the grade of\n";
	getline(cin, s);

	for (int i = 0;i < test1;i++) {
		if (coursename(std.a[i].CID) == s) {
			cout << "\n\n\n\n" << s << " " << std.a[i].grade << endl;
		}
	}

}
void stdgrade_f(student std, int test1) {
	string s;
	cin.ignore(INT_MAX, '\n');
	cout << "Veuillez appuyez le nom du cours dont vous souhaitez voir la note\n";
	getline(cin, s);

	for (int i = 0;i < test1;i++) {
		if (coursename(std.a[i].CID) == s) {
			cout << "\n\n\n\n" << s << " " << std.a[i].grade << endl;
		}
	}

}
void gpacalc() {
	string a;
	int sid = 0, c = 0, gpa = 0;
	int s[20];
	enrollment temp;
	student junk;
	student gp;

	fstream student("student.txt", ios::in);
	while (student) {
		gpa = 0, c = 0;
		student >> junk.ID >> junk.firstname >> junk.lastname >> junk.password >> junk.dob >> junk.email >> junk.phonenum >> junk.Gpa;
		sid = junk.ID;
		fstream f("enrollment.txt", ios::in | ios::out);
		while (f) {

			f >> temp.SID >> temp.CID >> temp.grade;


			if (temp.SID == junk.ID) {
				gpa = gpa + temp.grade;
				c++;
			}
		}
		f.close();
		if (c > 0)
			s[junk.ID] = gpa / c;
	}
	student.close();


	ifstream in("student.txt", ios::in);
	ofstream out("student_new.txt", ios::app);




	while (in >> gp.ID >> gp.firstname >> gp.lastname >> gp.password >> gp.dob >> gp.email >> gp.phonenum >> gp.Gpa) {



		out << gp.ID << "\t" << gp.firstname << "\t" << gp.lastname << "\t" << gp.password << "\t" << gp.dob << "\t" << gp.email << "\t" << gp.phonenum << "\t" << s[gp.ID] << endl;


	}
	in.close();
	out.close();

	remove("student.txt");
	rename("student_new.txt", "student.txt");


}
void gpa_e(student std) {
	student temp;
	fstream student("student.txt", ios::in);
	int f = 0;

	while (student) {
		student >> temp.ID >> temp.firstname >> temp.lastname >> temp.password >> temp.dob >> temp.email >> temp.phonenum >> temp.Gpa;

		if ((temp.ID == std.ID) && (f == 0)) {
			f++;
			cout << "\n\nYour GPA is  " << temp.Gpa << endl;
			student.close();
		}
	}
}
void gpa_f(student std) {
	student temp;
	fstream student("student.txt", ios::in);
	int f = 0;

	while (student) {
		student >> temp.ID >> temp.firstname >> temp.lastname >> temp.password >> temp.dob >> temp.email >> temp.phonenum >> temp.Gpa;

		if ((temp.ID == std.ID) && (f == 0)) {
			f++;
			cout << "\n\nVotre GPA est  " << temp.Gpa << endl;
			student.close();

		}
	}


}
void std_sort_courses_e(student std, int  test1) {
	student temp;
	temp.a = new enrollment[1];
	for (int i = 0;i < test1;i++) {
		for (int j = i + 1;j < test1;j++) {
			if (std.a[i].grade < std.a[j].grade) {
				temp.a[0] = std.a[i];
				std.a[i] = std.a[j];
				std.a[j] = temp.a[0];
			}
		}
	}
	cout << "\n\nYour grades in order are :\n";
	for (int i = 0;i < test1;i++) {
		cout << std.a[i].CID << " " << std.a[i].grade << "\n";
	}

}
void std_sort_courses_f(student std, int  test1) {
	student temp;
	temp.a = new enrollment[1];
	for (int i = 0;i < test1;i++) {
		for (int j = i + 1;j < test1;j++) {
			if (std.a[i].grade < std.a[j].grade) {
				temp.a[0] = std.a[i];
				std.a[i] = std.a[j];
				std.a[j] = temp.a[0];
			}
		}
	}
	cout << "\n\nVos notes dans l'ordre sont :\n";
	for (int i = 0;i < test1;i++) {
		cout << std.a[i].CID << " " << std.a[i].grade << "\n";
	}

}
void order_std_e(student std) {
	int c = 0, c1 = 0, test = 0;
	string a, s;
	enrollment temp;
	student tem, stu;

	cin.ignore(INT_MAX, '\n');
	cout << "\n\n Please enter the name of the course you want to check your order in" << endl;
	getline(cin, s);



	fstream f("enrollment.txt", ios::in | ios::out);
	if (!f) {
		cerr << "Error: Unable to open the input or output file" << std::endl;
		return;
	}
	while (f >> temp.SID >> temp.CID >> temp.grade) {


		getline(f, a, '\n');


		if (coursename(temp.CID) == s) {

			test++;


		}
	}

	tem.a = new enrollment[test + 1];
	stu.a = new enrollment[test + 1];
	f.close();

	c = 0;
	fstream fi("enrollment.txt", ios::in | ios::out);
	if (!fi) {
		cerr << "Error: Unable to open the input or output file" << std::endl;
		return;
	}
	while (fi) {
		fi >> temp.SID >> temp.CID >> temp.grade;

		if (coursename(temp.CID) == s) {

			tem.a[c].CID = temp.CID;

			tem.a[c].SID = temp.SID;

			tem.a[c].grade = temp.grade;


			c++;
		}

	}
	fi.close();
	for (int i = 0;i < test;i++) {
		for (int j = i + 1;j < test;j++) {
			if (tem.a[i].grade < tem.a[j].grade) {
				stu.a[i] = tem.a[i];
				tem.a[i] = tem.a[j];
				tem.a[j] = stu.a[i];
			}
		}
	}
	c = 1;

	for (int i = 0;i < test;i++) {
		if (tem.a[i].SID != std.ID) {
			c++;
		}
		else {
			break;
		}
	}
	cout << "\n\nYour rank in " << s << " is " << c;





}
void order_std_f(student std) {
	int c = 0, c1 = 0, test = 0;
	string a, s;
	enrollment temp;
	student tem, stu;

	cin.ignore(INT_MAX, '\n');
	cout << "\n\n Veuillez entrer le nom du cours dans lequel vous souhaitez vérifier votre rank" << endl;
	getline(cin, s);



	fstream f("enrollment.txt", ios::in | ios::out);
	if (!f) {
		cerr << "Erreur : Impossible d'ouvrir le fichier " << std::endl;
		return;
	}
	while (f >> temp.SID >> temp.CID >> temp.grade) {


		getline(f, a, '\n');


		if (coursename(temp.CID) == s) {

			test++;


		}
	}

	tem.a = new enrollment[test + 1];
	stu.a = new enrollment[test + 1];
	f.close();

	c = 0;
	fstream fi("enrollment.txt", ios::in | ios::out);
	if (!fi) {
		cerr << "Erreur : Impossible d'ouvrir le fichier " << std::endl;
		return;
	}
	while (fi) {
		fi >> temp.SID >> temp.CID >> temp.grade;

		if (coursename(temp.CID) == s) {

			tem.a[c].CID = temp.CID;

			tem.a[c].SID = temp.SID;

			tem.a[c].grade = temp.grade;


			c++;
		}

	}
	fi.close();
	for (int i = 0;i < test;i++) {
		for (int j = i + 1;j < test;j++) {
			if (tem.a[i].grade < tem.a[j].grade) {
				stu.a[i] = tem.a[i];
				tem.a[i] = tem.a[j];
				tem.a[j] = stu.a[i];
			}
		}
	}
	c = 1;

	for (int i = 0;i < test;i++) {
		if (tem.a[i].SID != std.ID) {
			c++;
		}
		else {
			break;
		}
	}
	cout << "\n\nVotre rank dans " << s << " est " << c;





}
void update_course() {
	string cname;
	int id = 0, grade = 0;
	enrollment temp;

	cin.ignore(INT_MAX, '\n');

	cout << "Please enter the course name" << endl;
	getline(cin, cname);
	cout << "Please enter the student id" << endl;
	cin >> id;
	cout << "Please enter the new grade" << endl;
	cin >> grade;


	ifstream in("enrollment.txt", ios::in);
	ofstream out("enrollment_new.txt", ios::app);




	while (in >> temp.SID >> temp.CID >> temp.grade) {
		if (temp.SID == id && coursename(temp.CID) == cname) {

			out << temp.SID << "\t" << temp.CID << "\t" << grade << endl;
			cout << "\n\nThe old grade was : " << temp.grade << " and it hass been changed to : " << grade;
		}
		else {
			out << temp.SID << "\t" << temp.CID << "\t" << temp.grade << endl;
		}
	}
	in.close();
	out.close();

	remove("enrollment.txt");
	rename("enrollment_new.txt", "enrollment.txt");


}
void gpa_sort() {
	int x = 0;
	student* s;
	s = new student[100];
	student temp;
	fstream std("student.txt", ios::in);
	while (std) {

		std >> s[x].ID >> s[x].firstname >> s[x].lastname >> s[x].password >> s[x].dob >> s[x].email >> s[x].phonenum >> s[x].Gpa;

		x++;
	}
	std.close();
	for (int i = 0;i < x;i++) {
		for (int j = i + 1;j < x;j++) {
			if (s[i].Gpa < s[j].Gpa) {
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
		}

	}
	for (int i = 0;i < x - 1;i++) {
		cout << s[i].ID << " " << s[i].firstname << " " << s[i].Gpa << "\n";
	}
}
void avecalc() {
	string a;
	int sid = 0, c = 0, gpa = 0, ave = 0;

	enrollment temp;
	cin.ignore(INT_MAX, '\n');
	cout << "please enter the name of the course you want to check the average of" << endl << endl << endl;
	getline(cin, a);

	fstream f("enrollment.txt", ios::in | ios::out);
	while (f >> temp.SID >> temp.CID >> temp.grade) {

		if (coursename(temp.CID) == a) {
			gpa = gpa + temp.grade;
			c++;
		}
	}
	f.close();
	if (c > 0)
		ave = gpa / c;
	cout << "\n\n\nThe average of this course is " << ave;

	ifstream in("student.txt", ios::in);
	ofstream out("student_new.txt", ios::app);

}
void readfromcsv() {//////////////////////////////////////////////////////////////////
	enrollment s;
	string a, token;
	fstream of("1.csv", ios::in | ios::out | ios::app);
	fstream f("enrollment.csv", ios::in | ios::out);
	while (f >> a) {
		stringstream ss(a);
		getline(ss, token, ',');
		s.SID = stoi(token);
		of << s.SID << ",";

		getline(ss, token, ',');
		s.CID = token;
		of << s.CID << ",";

		getline(ss, token, '\n');
		s.grade = stoi(token);//read
		of << s.grade << "\n";//write
		cout << s.CID << " " << s.SID << " " << s.grade << endl;
	}
	f.close();
	of.close();
}

int main()
{
	
	gpacalc();

	int sa = 0, ac = 0, sc = 0, l = 0, ao = 0, auth = 0, choice = 0, studentdelete = 0, test = 0, test1 = 0;
	student std;
	cout << "\n\n\n\t\t\t\tWelcome to SIS \n\n\n\nIf you are a student please input 1 and if you are an admin please input 2 \n";
	cin >> sa;

	while (sa != 1 && sa != 2) {
		cout << "\n\n\tPlease Enter a Valid Input";
		cin >> sa;
	}

	if (sa == 1) {
		while (authentication_s(std) == 0) {
			cout << "invalid email or password please try again\n\n";
		}
		cout << "\n\nFor english input 1 \nAppuyez sur 2 pour le francais \n\n\n ";
		cin >> l;
		while (l != 1 && l != 2) {
			cout << "Please Enter a Valid Input\nVeuillez entrer une entrée valide";
			cin >> l;
		}
		if (l == 1) {
			studentoutput_e(std);
			enrollement(std, test1);
			cin >> sc;
			while (sc != 1 && sc != 2 && sc != 3 && sc != 4 && sc != 5 && sc != 6) {
				cout << "Please Enter a Valid Input";
				cin >> sc;
			}
			if (sc == 1) {
				cout << "\n\nYour grades are :\n";
				stdgrades(std, test1);
			}
			else if (sc == 2) {
				order_std_e(std);

			}
			else if (sc == 3) {
				gpa_e(std);
			}
			else if (sc == 4) {
				stdgrade_e(std, test1);
			}
			else if (sc == 5) {
				std_sort_courses_e(std, test1);
			}
			else if (sc == 6) {
				proposition_e(std);
			}
		}
		else
		{
			enrollement(std, test1);
			studentoutput_f();
			cin >> sc;
			while (sc != 1 && sc != 2 && sc != 3 && sc != 4 && sc != 5 && sc != 6) {
				cout << "Veuillez entrer une entrée valide";
				cin >> sc;
			}
			if (sc == 1) {
				cout << "\n\nVos nottes sont :\n";
				stdgrades(std, test1);
			}
			else if (sc == 2) {
				order_std_f(std);
			}
			else if (sc == 3) {
				gpa_f(std);
			}
			else if (sc == 4) {
				stdgrade_f(std, test1);
			}
			else if (sc == 5) {
				std_sort_courses_f(std, test1);
			}
			else if (sc == 6) {
				proposition_f(std);
			}
		}


	}

	else
	{
		while (authentication_a() == 0) {
			cout << "invalid email or password please try again\n\n";

		}
		adminoutput();
		cin >> sc;
		while (sc != 1 && sc != 2 && sc != 3 && sc != 4 && sc != 5) {
			cout << "Please Enter a Valid Input";
			cin >> sc;
		}
		if (sc == 1) {
			addstudent();
		}
		else if (sc == 2) {
			update_course();
		}
		else if (sc == 3) {
			cout << "please enter the ID of the student you want to remove";
			cin >> studentdelete;
			deletestd(studentdelete);
		}
		else if (sc == 4) {
			gpa_sort();

		}
		else if (sc == 5) {

			avecalc();
		}
	}


	return 0;
}

