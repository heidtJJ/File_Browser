# File_Browser
A simple File Browser.

This project is a file browser which allows people to open files, search within files, as well as browse to other "links" within a file. 

The files are plain text files that may contain anchors that provide
links to other files. More precisely, an anchor is a string of the form:

	\<a file text\>

where file is the name of another file and text is a piece of text. The 'a' stands for anchor.
For example, here’s a line of text that contains an anchor:

    Here is more \<a info.txt information.\>"

When an anchor is displayed, it should appear as:

	\<text\>[n]

where n is a number that is unique to this anchor. Anchors should be
numbered in order, starting at 1. For example, if the above line of text
contains the 5th anchor of the file, then it should be displayed as follows:

    Here is more \<information.\>[5]

See [design  document](/File_Browser/Design_Document.txt) for implementation details
