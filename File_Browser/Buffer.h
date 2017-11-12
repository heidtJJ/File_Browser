// Buffer.h
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <vector>
#include <string>

class Buffer
{
public:
	void display() const;
	const std::string & file_name() const { return file_name_; }
	void move_to_next_page();
	void move_to_previous_page();
	bool go_to_link(const int& link_num);
	bool go_back();
	bool open(const std::string & file_name);
	void set_window_height(const int& h) { window_height_ = h; }
	void set_line_length(const int& l) { line_length_ = l; }
	bool search(const std::string & input);

private:
	std::vector<std::string> v_lines_;
	std::vector<std::string> links_on_page;
	std::vector<std::string> prev_links;
	int ix_top_line_ = 0;
	std::string file_name_;
	int window_height_;
	int line_length_;
};

inline void Buffer::move_to_next_page()
{
	if (ix_top_line_ + window_height_ < v_lines_.size())
		ix_top_line_ += window_height_;
}

#endif // !_BUFFER_H_
