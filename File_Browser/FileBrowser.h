// FileBrowser.h
#ifndef _FILE_BROWSER_H_
#define _FILE_BROWSER_H_

#include <string>
#include <vector>
#include "Buffer.h"

class FileBrowser
{
public:
	void run();

private:
	void display();
	void execute_command(char command, bool & done);

	Buffer buffer_;
	int window_height_;
	int line_length_;
	std::string error_message_;
};

#endif