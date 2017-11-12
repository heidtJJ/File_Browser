// FileBrowser.cpp

#include "FileBrowser.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

void FileBrowser::display()
{
	const string long_separator(50, '-');
	const string short_separator(8, '-');

	if (!error_message_.empty()) {
		cout << "ERROR: " + error_message_ << endl;
		error_message_.clear();
	}

	string file_name = buffer_.file_name();
	if (file_name.empty())
		cout << "<no file opened>\n";
	else
		cout << file_name << endl;

	cout << long_separator << endl;
	buffer_.display();
	cout << long_separator << endl;
	cout << "  next  previous  open  quit  search  go  back\n";
	cout << short_separator << endl;
}

void FileBrowser::execute_command(char command, bool & done)
{
	switch (command) {
	case 'n': {
		buffer_.move_to_next_page();
		break;
	}
	case 'g': {
		cout << "link number: ";
		int link_num = -1;
		cin >> link_num;
		bool good_link = buffer_.go_to_link(link_num);
		if (!good_link) {
			error_message_ = "Link " + std::to_string(link_num) + " is invalid";
		}
		break;
	}

	case 'o': {
		cout << "file name: ";
		string file_name;
		getline(cin, file_name);
		if (!buffer_.open(file_name))
			error_message_ = "Could not open " + file_name;
		break;
	}

	case 'p': {
		buffer_.move_to_previous_page();
		break;
	}

	case 's': {
		cout << "search for: ";
		string user_search;
		getline(cin, user_search);
		if (!buffer_.search(user_search))
			error_message_ = "string " + user_search + " was not found.";
		break;
	}

	case 'q': {
		done = true;
		break;
	}

	case 'b': {
		bool valid_page = buffer_.go_back();
		if (!valid_page) {
			error_message_ = "Invalid previous page.";
		}
	}

	}
}

void FileBrowser::run()
{
	cout << "Window height? ";
	cin >> window_height_;
	cin.get();  // '\n'
	cout << '\n';
	buffer_.set_window_height(window_height_);

	cout << "Line length? ";
	cin >> line_length_;
	cin.get();  // '\n'
	cout << '\n';
	buffer_.set_line_length(line_length_);


	bool done = false;
	while (!done) {
		display();

		cout << "choice: ";
		char command;
		cin >> command;
		cin.get(); // '\n'

		execute_command(command, done);

		cout << endl;
	}
}

