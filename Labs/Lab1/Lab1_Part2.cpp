#include <iostream>
#include <list>
#include <string>
using namespace std;

void addCourses( list<string>& courses ){
	courses.push_back("cs 250");
	courses.push_back("cs 210");
	courses.push_back("cs 235");
	courses.push_back("cs 134");
	courses.push_back("cs 211");
}

void sortList( list<string>& courses ){
	courses.sort();
}

void reverseList( list<string>& courses ){
	courses.reverse();
}

void displayCourses( list<string>& courses ){
	int counter = 0;

	for(list<string>::iterator it = courses.begin(); it != courses.end(); it++){
		if (counter != 0){ cout << ", "; }
		cout << counter++ << ". " << (*it);
	}
	cout << endl;
}

int main(){
	list<string> courses;
	addCourses(courses);
	cout << "Normal Order" << endl;
	displayCourses(courses);
	sortList(courses);
	cout << "Sorted Order" << endl;
	displayCourses(courses);
	reverseList(courses);
	cout << "Reverse Order" << endl;
	displayCourses(courses);
	
	cout << endl;
	return 0;
}

