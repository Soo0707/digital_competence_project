#include <sqlite3.h>
#include <iostream>
#include <filesystem>
#include <string>

using namespace std;

int main(void)
{
	sqlite3* db;

	if (!filesystem::exists("movies.db"))
	{
		cout << "Expected DB file doesn't exist" << endl;
		return 1;
	}

	int db_failed_to_open = sqlite3_open("movies.db", &db);
	if (db_failed_to_open)
	{
		cout << "Failed to open database: " << sqlite3_errmsg(db) << endl;
		return 2;
	}

	while(true)
	{
		cout << "Please select one of the options below:" << endl;
		cout << "1. Search by title" << endl;
		cout << "2. Suggest a good movie" << endl;
		cout << "3. Suggest a bad movie" << endl;
		cout << "4. Quit" << endl;
		cout << "================================================" << endl;
		
		cout << "Input: " << endl;
		
		string input1;
		cin >> input1;

		int selection = 0;

		try
		{
			selection = stoi(input1);
		}
		catch (const exception &e)
		{
			cout << "Invalid Input" << endl;
			continue;
		}

		switch(selection)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				sqlite3_close(db); // Doesn't handle SIGINT properly but it's not a C++ course
				return 0;
			default:
				cout << "Invalid Input" << endl;
				break;
		}
	}
}
