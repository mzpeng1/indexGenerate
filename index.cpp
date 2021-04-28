#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct Title {
	string title;
	int number;
	bool startsThe;
	bool startsA;
};

struct TitleComp {
	bool operator()(Title lhs, Title rhs) {

	if (lhs.title < rhs.title) return true;
	}
};

// read through the tex file and make a vector of titles
// (found by the "\song") sort the vector and iterate through it
// outputting each to the index file formatted correctly
int main () {
  vector<Title> titles; // vector of titles
  string line; // string to get one line at a time
  int counter = 1; // keeps track of the number of the song
  ifstream myfile ("dump.txt"); // opening the input file
  ofstream outfile ("output.txt");
  outfile << '\\' << "begin{theindex}\n\n\\indexspace\n\n"; // first line of index file
  string compareString = "\\song(";

  // do stuff with the input file
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
		stringstream ss(line);
		
		if (line.rfind("\\song{The ", 0) == 0) {
			size_t index = 10;
			Title newTitle;
			Title secondTitle;
			secondTitle.title = "";
			newTitle.number = counter;
			while (line[index] != '}' && line[index] != '(') { 
				newTitle.title += line[index];
				index++;
			}
			while (index < line.size()) {
				if (line[index] == '(') {
					secondTitle.number = counter;
					index++;
					while (line[index] != ')') {
						secondTitle.title += line[index];
						index++;
					}
				}
				index++;
			}
			if (secondTitle.title != "") {
				string temp = newTitle.title;
				newTitle.title += " (";
				newTitle.title += secondTitle.title;
				newTitle.title += ")";
				secondTitle.title += " (";
				secondTitle.title += temp;
				secondTitle.title += ")";
				secondTitle.startsThe = false;
				secondTitle.startsA = false;
				titles.push_back(secondTitle);
			}
			newTitle.startsThe = true;
			newTitle.startsA = false;
			titles.push_back(newTitle);
			counter++;
		} else if (line.rfind("\\song{A ", 0) == 0) {
			size_t index = 8;
			Title newTitle;
			Title secondTitle;
			secondTitle.title = "";
			newTitle.number = counter;
			while(line[index] != '}') {
				newTitle.title += line[index];
				index++;
			}
			while (index < line.size()) {
				if (line[index] == '(') {
					secondTitle.number = counter;
					index++;
					while (line[index] != ')') {
						secondTitle.title += line[index];
						index++;
					}
				}
				index++;
			}
			if (secondTitle.title != "") {
				string temp = newTitle.title;
				newTitle.title += " (";
				newTitle.title += secondTitle.title;
				newTitle.title += ")";
				secondTitle.title += " (";
				secondTitle.title += temp;
				secondTitle.title += ")";
				secondTitle.startsThe = false;
				secondTitle.startsA = false;
				titles.push_back(secondTitle);
			}
			newTitle.startsThe = false;
			newTitle.startsA = true;
			titles.push_back(newTitle);
			counter++;
		} else if (line.rfind("\\song{", 0) == 0) {
			size_t index = 6;
			Title newTitle;
			Title secondTitle;
			secondTitle.title = "";
			newTitle.number = counter;
			while (line[index] != '}' && index < line.size()) {
				if (index != 6 || line[index] != '\'')
				newTitle.title += line[index];
				index++;
			}
			while (index < line.size()) {
				if (line[index] == '(') {
					secondTitle.number = counter;
					index++;
					while (line[index] != ')') {
						secondTitle.title += line[index];
						index++;
					}
				}
				index++;
			}
			if (secondTitle.title != "") {
				string temp = newTitle.title;
				newTitle.title += " (";
				newTitle.title += secondTitle.title;
				newTitle.title += ")";
				secondTitle.title += " (";
				secondTitle.title += temp;
				secondTitle.title += ")";
				secondTitle.startsThe = false;
				secondTitle.startsA = false;
				titles.push_back(secondTitle);
			}
		
			newTitle.startsThe = false;
			newTitle.startsA = false;
			titles.push_back(newTitle);	
			counter++;
		}


    }
	TitleComp c;
	sort(titles.begin(), titles.end(), c);
		char firstLetter = titles[0].title[0];
		for (size_t j = 0; j < titles.size(); j++) {
			if (titles[j].title[0] != firstLetter) {
				outfile << "\n" << "\\indexspace" << "\n\n";
				firstLetter = titles[j].title[0];
			}
			outfile << "\\item ";
			if (titles[j].startsThe) {
				outfile << "The ";
			} 
			if (titles[j].startsA) {
				outfile << "A ";
			}	
			outfile <<  titles[j].title << ", \\textbf{" << titles[j].number << '}' << "\n";

		}

	outfile << "\n\\end{theindex}";
    myfile.close();
	outfile.close();
  }

  else cout  << "Unable to open file"; 

  return 0;
}
