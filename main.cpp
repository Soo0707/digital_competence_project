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
		cout << "================================================" << endl;
		cout << "Please select one of the options below:" << endl;
		cout << "1. Search by title (fuzzy search)" << endl;
		cout << "2. Suggest a good movie" << endl;
		cout << "3. Suggest a bad movie" << endl;
		cout << "4. Quit" << endl;
		cout << "================================================" << endl;
		
		cout << "Input: ";
		
		string input;

		cin >> input;

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flushes stdin so that getline works later on
		
		int selection = 0;

		try
		{
			selection = stoi(input);
		}
		catch (const exception &e)
		{
			cout << "Invalid Input" << endl;
			continue;
		}

		switch(selection)
		{
			case 1:
			{
				const char* query_template = "SELECT title FROM movies WHERE title LIKE ? LIMIT 10;";

				sqlite3_stmt* statement;
				sqlite3_prepare_v2(db, query_template, -1, &statement, NULL); // statement = query_template

				cout << "================================================" << endl;
				cout << "Movie title? ";
				getline(cin, input); // std::cin only accepts until a whitespace character, getline...gets the whole line
				cout << "================================================" << endl;

				input = '%' + input + '%'; // do fuzzy search

				sqlite3_bind_text(statement, 1, input.c_str(), -1, SQLITE_TRANSIENT); // statement += user_input. accepts c-style strings not std::string

				while (sqlite3_step(statement) == SQLITE_ROW) // execute and returns each row
				{
					string title = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
					cout << title << endl;
				}

				sqlite3_finalize(statement); // does a free() on a statement, 
				break;
			}
			case 2:
			{
				const char* query_template = "SELECT title FROM movies AS m INNER JOIN ratings AS r ON m.id = r.movie_id WHERE r.rating >= 7.5 ORDER BY RANDOM() LIMIT 10;";
				
				sqlite3_stmt* statement;
				sqlite3_prepare_v2(db, query_template, -1, &statement, NULL); // statement = query_template

				sqlite3_bind_text(statement, 1, input.c_str(), -1, SQLITE_TRANSIENT); // statement += user_input. accepts c-style strings not std::string

				while (sqlite3_step(statement) == SQLITE_ROW) // execute and returns each row
				{
					string title = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
					cout << title << endl;
				}

				sqlite3_finalize(statement); // does a free() on a statement, 

				break;
			}
			case 3:
			{
				const char* query_template = "SELECT title FROM movies AS m INNER JOIN ratings AS r ON m.id = r.movie_id WHERE r.rating <= 3.0 ORDER BY RANDOM() LIMIT 10;";
				
				sqlite3_stmt* statement;
				sqlite3_prepare_v2(db, query_template, -1, &statement, NULL); // statement = query_template

				sqlite3_bind_text(statement, 1, input.c_str(), -1, SQLITE_TRANSIENT); // statement += user_input. accepts c-style strings not std::string

				while (sqlite3_step(statement) == SQLITE_ROW) // execute and returns each row
				{
					string title = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
					cout << title << endl;
				}

				sqlite3_finalize(statement); // does a free() on a statement, 

				break;
			}
			case 4:
				sqlite3_close(db);
				return 0;
			default:
				cout << "Invalid Input" << endl;
				break;
		}
	}
	sqlite3_close(db); // doesn't handle SIGINT properly but it's not a C++ course
}


