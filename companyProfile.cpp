#include "pch.h"
#include <iostream>
#include <string>     
#include <vector>
#include <fstream>
#include <Windows.h>
#include <stdio.h>
#include<cstdio>
using namespace std;
static const size_t npos = -1;

struct Date
{
	int day;
	int month;
	int year;
};
struct projects
{
	int id;
	string title;
	string brief;
	Date startDate;
	Date endDate;
}  p[100];

struct Newss
{
	int id;
	string title;
	string brief;
	int project_id;
	Date publishingDate;
} n[100];

void loadingMessage()
{
	cout << "Loading";
	Sleep(300);
	cout << ".";
	Sleep(300);
	cout << ".";
	Sleep(300);
	cout << ".";
	Sleep(300);
	cout << endl;
}
void textArrayProject(projects p[], int& globalCounter)
{
	ifstream in("projectfile.txt", ios::app);
	string str;
	int counter = 0;
	while (getline(in, str))
	{
		if (str == "PROJECT")
		{
			counter++;
			globalCounter = counter;
			continue;
		}
		if (str == "__")
			continue;
		else
		{
			if (str.find("id : ") != string::npos)// build in function from the net to read file line by line
			{                                                    //string counting start from 0 
				string idValue = str.substr(5, str.find(" : ")); //catch the number of Id after 5 letter
																 // stoi convert from string to integer
				p[counter].id = stoi(idValue); // now p[counter].id carries idValue which is 1 in first loop
			}
			else if (str.find("title : ") != string::npos)
			{
				string titleValue = str.substr(str.find(" : ") + 3);
				p[counter].title = titleValue;
			}
			else if (str.find("startDate : ") != string::npos)
			{
				string dateValue = str.substr(str.find(" : ") + 3);    //  now date value holds    11/3/2000
				string dayValue = dateValue.substr(0, dateValue.find("/"));
				string monthValue = dateValue.substr(dateValue.find("/") + 1, dateValue.find("/"));
				string yearValue = dateValue.substr(dateValue.length() - 4);

				p[counter].startDate.day = stoi(dayValue);
				p[counter].startDate.month = stoi(monthValue);
				p[counter].startDate.year = stoi(yearValue);

			}
			else if (str.find("endDate : ") != string::npos)
			{
				string dateValue = str.substr(str.find(" : ") + 3);    //11/3/2000
				string dayValue = dateValue.substr(0, dateValue.find("/"));
				string monthValue = dateValue.substr(dateValue.find("/") + 1, dateValue.find("/"));
				string yearValue = dateValue.substr(dateValue.length() - 4);

				p[counter].endDate.day = stoi(dayValue);
				p[counter].endDate.month = stoi(monthValue);
				p[counter].endDate.year = stoi(yearValue);

			}
			else if (str.find("brief : ") != string::npos)
			{
				string briefValue = str.substr(str.find(" : ") + 3);
				p[counter].brief = briefValue;
			}
		}
	}
	for (int i = 1; i <= counter; i++)
	{
		cout << "This is PROJECT number " << i << endl;
		cout << "id : " << p[i].id << endl;
		cout << "title : " << p[i].title << endl;
		cout << "startDate : " << p[i].startDate.day << "/" << p[i].startDate.month << "/" << p[i].startDate.year << endl;
		cout << "endDate : " << p[i].endDate.day << "/" << p[i].endDate.month << "/" << p[i].endDate.year << endl;
		cout << "brief : " << p[i].brief << endl;
		cout << "__" << endl;
	}
	// output the line
	// now we loop back and get the next line in 'str'
	in.close();
}
void textArrayNews(Newss n[], int& globalNews)
{
	ifstream inNews("newsfile.txt", ios::app);
	string str;
	int nCount = 0;
	while (getline(inNews, str))
	{
		if (str == "NEWS")
		{
			nCount++;
			globalNews = nCount;
			continue;
		}

		if (str == "__")
			continue;
		else
		{
			if (str.find("project_id : ") != string::npos)
			{
				string projectIdValue = str.substr(13, str.find(" : ")); //convert from string to int
				n[nCount].project_id = stoi(projectIdValue); // now n[nCount].id carries idValue which is 1 in fo\irst loop
			}
			else if (str.find("id : ") != string::npos)
			{
				string idValue = str.substr(5, str.find(" : ")); //convert from string to int
				n[nCount].id = stoi(idValue); // now n[nCount].id carries idValue which is 1 in fo\irst loop
			}
			else if (str.find("title : ") != string::npos)
			{
				string titleValue = str.substr(str.find(" : ") + 3);
				n[nCount].title = titleValue;
			}
			else if (str.find("publishingDate : ") != string::npos)
			{
				string dateValue = str.substr(str.find(" : ") + 3);    //11/3/2000
				string dayValue = dateValue.substr(0, dateValue.find("/"));
				string monthValue = dateValue.substr(dateValue.find("/") + 1, dateValue.find("/"));
				string yearValue = dateValue.substr(dateValue.length() - 4);

				n[nCount].publishingDate.day = stoi(dayValue);
				n[nCount].publishingDate.month = stoi(monthValue);
				n[nCount].publishingDate.year = stoi(yearValue);

			}
			else if (str.find("brief : ") != string::npos)
			{
				string briefValue = str.substr(str.find(" : ") + 3);
				n[nCount].brief = briefValue;
			}
		}

	}
	for (int i = 1; i <= nCount; i++)
	{
		cout << " This is NEWS number: " << i << endl;
		cout << "id : " << n[i].id << endl;
		cout << "title : " << n[i].title << endl;
		cout << "startDate : " << n[i].publishingDate.day << "/" << n[i].publishingDate.month << "/" << n[i].publishingDate.year << endl;
		cout << "brief : " << n[i].brief << endl;
		cout << "__" << endl;
	}
	// output the line
	// now we loop back and get the next line in 'str'
	inNews.close();
}
void save_project(projects p[], int& counter)
{
	remove("projectfile.txt");
	ofstream out("projectfile.txt", ios::app);

	int x = counter;

	for (counter = 1; counter <= x; counter++)
	{
		out << "PROJECT" << endl;
		out << "id : " << p[counter].id << endl;
		out << "title : " << p[counter].title << endl;
		out << "startDate : " << p[counter].startDate.day << "/" << p[counter].startDate.month << "/" << p[counter].startDate.year << endl;
		out << "endDate : " << p[counter].endDate.day << "/" << p[counter].endDate.month << "/" << p[counter].endDate.year << endl;
		out << "brief : " << p[counter].brief << endl;
		out << "__" << endl;
	}
	out.close();
}

void save_news(Newss n[], int& nCount)
{
	remove("newsfile.txt");
	ofstream outn("newsfile.txt", ios::app);
	int x = nCount;


	for (nCount = 1; nCount <= x; nCount++)
	{
		outn << "NEWS" << endl;
		outn << "id : " << n[nCount].id << endl;
		outn << "project_id : " << n[nCount].project_id << endl;
		outn << "title : " << n[nCount].title << endl;
		outn << "publishingDate : " << n[nCount].publishingDate.day << "/" << n[nCount].publishingDate.month << "/" << n[nCount].publishingDate.year << endl;
		outn << "brief : " << n[nCount].brief << endl;
		outn << "____" << endl;
	}
	outn.close();
}

void projectedit(int& counter)
{
	int answer, tempCounter = counter;
	char choice;
	cout << "_____\n";
	cout << "                                 You are editing the project \n";
	do
	{
		cout << "What do you want to edit (1)Title, (2)Start Date, (3)End Date, (4)Brief \n ";
		cin >> answer;
		while (cin.fail())
		{
			cin.clear(); //clear input buffer to restore cin to a usable state 
			cin.ignore(INT_MAX, '\n'); //ignore last input 
			cout << "You Can Only Enter Numbers!\n";
			cout << "Enter A Number Please\n";
			continue;
		}
		switch (answer)
		{
		case 1:
			cout << "Enter the Id of the project you want to edit \n";
			cin >> counter;
			while (cin.fail())
			{
				cin.clear(); //clear input buffer to restore cin to a usable state 
				cin.ignore(INT_MAX, '\n'); //ignore last input 
				cout << "You Can Only Enter Numbers!\n";
				cout << "Enter A Number Please\n";
				continue;
			}
			cout << "Enter the New title \n";
			cin.ignore();
			getline(cin, p[counter].title);
			cout << "Edit is done ! \n";
			break;
		case 2:
			cout << "Enter the Id of the project you want to edit \n";
			cin >> counter;
			while (cin.fail())
			{
				cin.clear(); //clear input buffer to restore cin to a usable state 
				cin.ignore(INT_MAX, '\n'); //ignore last input 
				cout << "You Can Only Enter Numbers!\n";
				cout << "Enter A Number Please\n";
				continue;
			}
			cout << "Enter new startdate\n";
			cin >> p[counter].startDate.day >> p[counter].startDate.month >> p[counter].startDate.year;
			cout << "Edit is done ! \n";
			break;
		case 3:
			cout << "Enter the Id of the project you want to edit \n";
			while (cin.fail())
			{
				cin.clear(); //clear input buffer to restore cin to a usable state 
				cin.ignore(INT_MAX, '\n'); //ignore last input 
				cout << "You Can Only Enter Numbers!\n";
				cout << "Enter A Number Please\n";
				continue;
			}
			cin >> counter;
			cout << "Enter Enddate\n";
			cin >> p[counter].endDate.day >> p[counter].endDate.month >> p[counter].endDate.year;
			cout << "Edit is done ! \n";
			break;
		case 4:
			cout << "Enter the Id of the project you want to edit \n";
			while (cin.fail())
			{
				cin.clear(); //clear input buffer to restore cin to a usable state 
				cin.ignore(INT_MAX, '\n'); //ignore last input 
				cout << "You Can Only Enter Numbers!\n";
				cout << "Enter A Number Please\n";
				continue;
			}
			cin >> counter;
			cout << "Enter the project brief \n";
			cin.ignore();
			getline(cin, p[counter].brief);
			cout << "Edit is done ! \n";
			break;
		default:
			cout << "Invalid entry\n";
			break;
		}
		cout << "Do you want to edit anything else? (y/n)\n";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
	counter = tempCounter;
}

void Newsedit(int& nCount)
{
	int answer;
	char choice;
	cout << "_____\n";
	cout << "                                You are editing the News \n";
	do
	{
		cout << "What do you want to edit (1)Title, (2)Publishing Date, (3)Brief \n ";
		cin >> answer;
		while (cin.fail())
		{
			cin.clear(); //clear input buffer to restore cin to a usable state 
			cin.ignore(INT_MAX, '\n'); //ignore last input 
			cout << "You Can Only Enter Numbers!\n";
			cout << "Enter A Number Please\n";
			continue;
		}
		switch (answer)
		{
		case 1:
			cout << "Enter the Id of the News you want to edit \n";
			cin >> nCount;
			while (cin.fail())
			{
				cin.clear(); //clear input buffer to restore cin to a usable state 
				cin.ignore(INT_MAX, '\n'); //ignore last input 
				cout << "You Can Only Enter Numbers!\n";
				cout << "Enter A Number Please\n";
				continue;
			}
			cout << "Enter the New title \n";
			cin.ignore();
			getline(cin, n[nCount].title);
			cout << "Edit is done ! \n";
			break;
		case 2:
			cout << "Enter the Id of the News you want to edit \n";
			cin >> nCount;
			while (cin.fail())
			{
				cin.clear(); //clear input buffer to restore cin to a usable state 
				cin.ignore(INT_MAX, '\n'); //ignore last input 
				cout << "You Can Only Enter Numbers!\n";
				cout << "Enter A Number Please\n";
				continue;
			}
			cout << "Enter new Publishing date\n";
			cin >> n[nCount].publishingDate.day >> n[nCount].publishingDate.month >> n[nCount].publishingDate.year;
			cout << "Edit is done ! \n";
			break;
		case 3:
			cout << "Enter the Id of the News you want to edit \n";
			cin >> nCount;
			while (cin.fail())
			{
				cin.clear(); //clear input buffer to restore cin to a usable state 
				cin.ignore(INT_MAX, '\n'); //ignore last input 
				cout << "You Can Only Enter Numbers!\n";
				cout << "Enter A Number Please\n";
				continue;
			}
			cout << "Enter the New brief \n";
			cin.ignore();
			getline(cin, n[nCount].brief);
			cout << "Edit is done ! \n";
			break;
		default:
			cout << "Invalid entry\n";
			break;
		}
		cout << "Do you want to edit anything else? (y/n)\n";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}

void project(int& counter, int startdate[500], int enddate[500])
{
	char answer;
	do
	{
		counter++;
		cout << "_____\n";
		cout << "                             You will add Project\n";
		cout << "This Is Project Number " << counter << endl;
		cout << "Enter The Project Name " << endl;
		cin.ignore();
		getline(cin, p[counter].title);
		cout << "This Is Project ID: " << counter << endl;
		p[counter].id = counter;
		cout << "Enter Start Date" << endl;
		cin >> p[counter].startDate.day >> p[counter].startDate.month >> p[counter].startDate.year;
		startdate[counter] = ((p[counter].startDate.year * 365) + (p[counter].startDate.month * 30) + (p[counter].startDate.day));

		cout << "Enter End Date Of The Project" << endl;
		cin >> p[counter].endDate.day >> p[counter].endDate.month >> p[counter].endDate.year;
		enddate[counter] = ((p[counter].endDate.year * 365) + (p[counter].endDate.month * 30) + (p[counter].endDate.day));

		cout << "Enter The Brief Of Your Project" << endl;
		cin.ignore();
		getline(cin, p[counter].brief);


		cout << "Do you want to add more projects (y/n) ?" << endl;
		cin >> answer;
		if (answer != 'y' && answer != 'Y')
			break;

	} while (answer == 'y' || answer == 'Y');
}

void news(int counter, int& news_num, int& nCount)
{

	char answer;
	cout << "___\n";
	cout << "                             You will add News\n";
	do
	{
		nCount++;
		n[nCount].project_id = counter;
		news_num++;
		cout << "This Is News For Project " << counter << endl;
		cout << "This Is News ID: " << nCount << endl;
		cout << "Please Enter News Title" << endl;
		cin.ignore();
		getline(cin, n[nCount].title);
		n[nCount].id = nCount;
		cout << "Enter the Publishing date\n";
		cin >> n[nCount].publishingDate.day >> n[nCount].publishingDate.month >> n[nCount].publishingDate.year;
		cout << "Enter The Brief Of Your News:" << endl;
		cin.ignore();
		getline(cin, n[nCount].brief);
		cout << " Do you want to add more news (y/n) ? \n";
		cin >> answer;
	} while (answer == 'y' || answer == 'Y');
}

void IDfilter(int& nCount)
{
	int project_id;
	int idValue;
	cin >> idValue;
	while (cin.fail())
	{
		cin.clear(); //clear input buffer to restore cin to a usable state 
		cin.ignore(INT_MAX, '\n'); //ignore last input 
		cout << "You Can Only Enter Numbers!\n";
		cout << "Enter A Number Please\n";
		continue;
	}
	for (int i = 1; i <= nCount; i++)
	{
		if (n[i].project_id == idValue)
		{
			cout << "NEWS" << endl;
			cout << "ID: " << n[i].id << endl;
			cout << "News Title:  " << n[i].title << endl;
			cout << "Publishing Date:  " << n[i].publishingDate.day << '/' << n[i].publishingDate.month << '/' << n[i].publishingDate.year << endl;
			cout << "News Brief:  " << n[i].brief << endl;
			cout << "__________" << endl;
		}
	}
}

void Search_filter(int& nCount, int& news_num, Newss n[], int&counter, projects p[])
{
	int x = nCount;
	string word;
	int id;
	cout << "What Do You Want To Filter By :" << "Press 'I' For Project ID & 'T' For Title " << endl;
	char answer;
	cin >> answer;
	if (answer == 'i' || answer == 'I')
	{
		cout << "enter the project Id that you want to display its news \n";
		IDfilter(nCount);
	}

	else if (answer == 't' || answer == 'T')
	{
		cout << "Enter A Specific Word You Want To Search By In Project Title: " << endl;
		cin.ignore();
		getline(cin, word);
		nCount = 1;
		while (nCount <= counter)
		{
			if (p[nCount].title.find(word) != string::npos)
			{
				cout << "ID " << p[nCount].id << endl;
				cout << "project Title \t" << p[nCount].title << endl;
				cout << "brief \t" << p[nCount].brief << endl;
				nCount++;
			}
			else
				nCount++;
		}
	}
}
void Date_filter(int startdate[500], int enddate[500], int& counter)
{
	int numC = counter;
	int start_date_to_list_project = 0, s_day = 0, s_month = 0, s_year = 0;
	cout << "Enter Date To List All Projects That Will Start After This Date" << endl;
	cin >> s_day >> s_month >> s_year;
	start_date_to_list_project = ((s_year * 365) + (s_month * 30) + (s_day));


	for (counter = 1; counter <= numC; counter++)
	{
		if (start_date_to_list_project < startdate[counter])
		{
			cout << "Project Name: " << endl;
			cout << p[counter].title << endl;
		}
	}

	int end_date_to_list_project = 0, e_day = 0, e_month = 0, e_year = 0;
	cout << "Enter Date To List All The Projects That Will Expire After This Date" << endl;
	cin >> e_day >> e_month >> e_year;
	end_date_to_list_project = ((e_year * 365) + (e_month * 30) + (e_day));


	for (counter = 1; counter <= numC; counter++)
	{
		if (end_date_to_list_project > enddate[counter])
		{
			cout << "Project Number: " << counter << endl;
		}
	}
	counter = numC;
}

void Newslist(int& nCount, int& counter, int& news_num)
{
	loadingMessage();
	cout << "_____\n";
	cout << "                              List of all News\n";
	if (news_num == 0)
		cout << "there is no news" << endl;
	else
	{
		for (int i = 1; i <= news_num; i++)
		{
			cout << "ID: " << i << endl;
			cout << "News Title:  " << n[i].title << endl;
			cout << "Publishing Date:  " << n[i].publishingDate.day << '/' << n[i].publishingDate.month << '/' << n[i].publishingDate.year << endl;
			cout << "News Brief:  " << n[i].brief << endl;
			//cout << "This news for project " << p[i].title << endl;
		}
	}
}
void projectlist(int& counter, int& news_num, int& nCount, char& b)
{
	cout << "____\n";
	cout << "                              List of all project\n";
	for (int i = 0; i < counter; i++)
	{
		int index = i + 1;
		cout << "ID: " << index << endl;
		cout << "Title: " << p[index].title << endl;
		cout << "Start Date: " << p[index].startDate.day << '/' << p[index].startDate.month << '/' << p[index].startDate.year << endl;
		cout << "End Date: " << p[index].endDate.day << '/' << p[index].endDate.month << '/' << p[index].endDate.year << endl;
		cout << "Brief:  " << p[index].brief << endl;


	}
	if (b == 'b' || b == 'B')
		Newslist(nCount, counter, news_num);
}
void saveAll(char answer, int counter, int nCount)
{
	if (answer == 'p' || answer == 'P')
		save_project(p, counter);

	else if (answer == 'n' || answer == 'N')
		save_news(n, nCount);

	else if (answer == 'b' || answer == 'B')
	{
		save_project(p, counter);
		save_news(n, nCount);
	}
}

int main(int arcg, char* argv[])
{

	cout << "                                         The project you got in the program \n";
	int project_id_counter = 0, startdate[500], enddate[500], nCount = 0;
	int choice, counter = 0, news_num = 0;
	char answer = 'p', ans;

	textArrayProject(p, counter);
	textArrayNews(n, nCount);

	do
	{
		cout << " What process you want to make ?" << endl << "Press (1) add, (2) edit, (3) list, (4) filter, (5) Exit and Save data " << endl;
		cin >> choice;
		while (cin.fail())
		{
			cin.clear(); //clear input buffer to restore cin to a usable state 
			cin.ignore(INT_MAX, '\n'); //ignore last input 
			cout << "You Can Only Enter Numbers!\n";
			cout << "Enter A Number Please\n";
			continue;
		}
		if (choice == 1)
		{
			cout << "What do you want to add" << endl << " Enter p for project , n for news and b for both" << endl;
			cin >> answer;
			if (answer == 'p' || answer == 'P')
			{
				project(counter, startdate, enddate);
			}
			else if (answer == 'n' || answer == 'N')
			{
				news(counter, news_num, nCount);
			}
			else if (answer == 'b' || answer == 'B')
			{
				project(counter, startdate, enddate);
				news(counter, news_num, nCount);
			}
			else
			{
				cout << " invalid input " << endl;
				break;
			}
		}
		else if (choice == 2)
		{
			int z;
			cout << "What do you want to edit (1)Project (2)project News \n";
			cin >> z;
			while (cin.fail())
			{
				cin.clear(); //clear input buffer to restore cin to a usable state 
				cin.ignore(INT_MAX, '\n'); //ignore last input 
				cout << "You Can Only Enter Numbers!\n";
				cout << "Enter A Number Please\n";
				continue;
			}
			switch (z)
			{
			case 1:
			{
				projectedit(counter);
				answer = 'p';
				break;
			}

			case 2:
			{
				Newsedit(nCount);
				answer = 'n';
				break;
			}

			default:
				cout << "Invalid entry\n";
				break;
			}
		}
		else if (choice == 3)
		{
			char b;
			cout << "What do you want to list (P) All Project (N) All project News (B) both \n";
			cin >> b;
			switch (b)
			{
			case 'p':
			case 'P':
				projectlist(counter, news_num, nCount, b); break;
			case 'N':
			case 'n':
				Newslist(nCount, counter, news_num); break;
			case 'b':
			case'B':
				projectlist(counter, news_num, nCount, b);	break;
			default:
				cout << "Invalid entry\n"; break;
			}
		}
		else if (choice == 4)
		{
			int t;
			cout << "what do you want to filter (1) By Date, (2) By Project ID and Title  \n";
			cin >> t;
			while (cin.fail())
			{
				cin.clear(); //clear input buffer to restore cin to a usable state 
				cin.ignore(INT_MAX, '\n'); //ignore last input 
				cout << "You Can Only Enter Numbers!\n";
				cout << "Enter A Number Please\n";
				continue;
			}
			switch (t)
			{
			case 1:
				Date_filter(startdate, enddate, counter); break;
			case 2:
				Search_filter(nCount, news_num, n, counter, p); break;
			default:
				cout << "Invalid entry\n"; break;
			}
		}

		else if (choice == 5)
		{
			cout << " Thank you for working with us" << endl;
			break;

		}


		else
		{
			cout << " Invalid entry " << endl << " Please enter valid choice " << endl;
		}
		cout << "  (Y)Another Operation      (E) Save and Exit  \n";
		cin >> ans;
	} while (ans == 'y' || ans == 'Y');

	saveAll(answer, counter, nCount);

	system("pause");
}
