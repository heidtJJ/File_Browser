// Buffer.cpp

#include "Buffer.h"

#include <fstream>
#include <iomanip>
#include <iostream>
using std::cout;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;


void Buffer::display() const
{
	unsigned int ix_stop_line_ = ix_top_line_ + window_height_;
	for (unsigned int i = ix_top_line_; i < ix_stop_line_; ++i) {
		if (i < v_lines_.size())
			cout << std::setw(6) << i + 1 << "  " << v_lines_[i];
		cout << '\n';
	}
}


bool Buffer::open(const string & new_file_name)
{
	std::ifstream file(new_file_name);
	if (!file)
		return false;

	file_name_ = new_file_name;
	ix_top_line_ = 0;
	v_lines_.clear();
	links_on_page.clear();
	// Note: the vector is cleared only after we know the file
	// opened successfully.

	string word_tracker = "";
	while (file) {
		string word;
		file >> word;

		if (word == "<a") {// handles a file link (also called anchor)
			string file_link;
			string next_word;
			string new_word;

			file >> file_link;
			links_on_page.push_back(file_link);

			file >> next_word;// this word is a part of the paragraph

							  // change "word" to format the specified displayed link
			word = '<' + next_word + '[' + std::to_string(links_on_page.size()) + ']';
		}

		if ((word_tracker.size() + word.size() + 1) <= line_length_) {//  +1 for a space 
			word_tracker += word + ' ';
		}
		else {
			v_lines_.push_back(word_tracker);
			word_tracker = word + ' ';
		}

		while (file.peek() == '\n') {// look for \n after word
			file.get();
			v_lines_.push_back(word_tracker);
			word_tracker = "";
		}
	}
	v_lines_.push_back(word_tracker);
	return true;
}

bool Buffer::search(const std::string& input) {
	for (int index = ix_top_line_; index < v_lines_.size(); ++index) {
		if (v_lines_[index].find(input) != std::string::npos) {
			ix_top_line_ = index;
			return true;
		}
	}
	return false;
}

void Buffer::move_to_previous_page()
{
	if (ix_top_line_ > 0) {
		if (ix_top_line_ - window_height_ >= 0) {
			ix_top_line_ -= window_height_;
		}
		else {
			ix_top_line_ = 0;
		}
	}
}

bool Buffer::go_to_link(const int& link_num) {
	if (link_num > links_on_page.size() || link_num <= 0) {// validate link number
		return false;
	}

	string cur_file_name = file_name_;
	string next_file_name_ = links_on_page[link_num - 1];

	bool succesful_open = open(next_file_name_);
	if (!succesful_open) {// bad open
		return false;
	}
	else {// good open
		prev_links.push_back(cur_file_name);
		file_name_ = next_file_name_;
		ix_top_line_ = 0;
		return true;
	}
}

bool Buffer::go_back() {

	if (prev_links.size() >= 1) {
		string cur_file_name = file_name_;
		string prev_file_name_ = prev_links[prev_links.size() - 1];

		bool succesful_open = open(prev_file_name_);
		if (!succesful_open) {
			return false;
		}
		else {
			file_name_ = prev_file_name_;
			prev_links.pop_back();
			ix_top_line_ = 0;
			return true;
		}
	}
	else {
		return false;
	}
}
