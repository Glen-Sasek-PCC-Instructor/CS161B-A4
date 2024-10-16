//*****************************************************************************
// Author: 
// Assignment:
// Date:
// Description:
// Sources: 
//*****************************************************************************

#include <iostream>
#include <cstring> // for strcpy
#include <limits> //numeric_limits<streamsize>::max()

using namespace std;

const int MAXCHAR = 51;
const int MAX_COURSES = 20;
const int MAX_STUDENTS_PER_COURSE = 25;
const int MIN_STUDENTS_PER_COURSE = 10;

void welcome();
void readInput(char courseNums[][MAXCHAR + 1], int students[], int &count);
void readInt(string prompt, int &num);
void printList(char courseNums[][MAXCHAR + 1], int students[], int count);
void cancelCourses(char courseNums[][MAXCHAR + 1], int students[], int &count);

int main() {
    char courses[MAX_COURSES][MAXCHAR + 1];
    int student_count[MAX_COURSES];
    int course_count = 0;

    welcome();

// b. Call the readInput() function and get the arrays filled. The list must be ordered by the course numbers. 
//    This is important for this grade level.

    cout << "List of courses and students:" << endl; 
    printList(courses, student_count, course_count);

    cancelCourses(courses, student_count, course_count);

    cout << "List after cancellations:" << endl; 
    printList(courses, student_count, course_count);

    cout << "Thank you for checking out my Course Rosters program!" << endl;
}

// - This function prints a welcome message to the user.
void welcome() {
    cout << "Welcome to my Course Rosters program!!" << endl;
}


// a. This function takes an array of c-strings, and an array of ints and reads the
//    course numbers and students enrolled from the user.

// b. Read until the user enters “Quit” or “quit” for the course number. The
//    SampleA04.cpp should help you do this. Read the corresponding number of
//    students enrolled.

// c. Call the readInt function to read the number of students for each course
//    number. You must catch all invalid data such as characters, negative numbers
//    etc.

// d. You must also do validation to make sure that the number is between 0 and 25.
//    The maximum number of students that can be enrolled in a course is less than or
//    equal to 25. Use a while loop to do this.

// e. Insert the course number and the number of students in the right position based
//   on the course number. You must not use any sorting algorithm. Insert the
//   course numbers and its students in the right position, by finding the
//   position and shifting the other courses. Here is an example -
//   insertSorted.cpp. See sample run below.

// f. count will keep track of the number of courses entered.

// g. Test your function with at least 10 courses to make sure that the insertion works
//    correctly.

bool checkQuit(char s[MAXCHAR + 1]) {
    const char QUIT_SENTINEL[]  = "quit";
    if(strlen(s) != strlen(QUIT_SENTINEL)) {
        return false;
    } else {
        for(int i = 0; i < strlen(QUIT_SENTINEL); i++) {
            if(QUIT_SENTINEL[i] != tolower(s[i])) {
                return false;
            }
        }
    }
    return true;
}

void readInput(char courseNums[][MAXCHAR + 1], int students[], int &count) {
    cout << "Enter course number and students enrolled when prompted." << endl;
    cout << "Enter Quit or quit for course number when you are done." << endl;

    char temp[MAXCHAR + 1];
    bool quit = false;

    do {
        cout << "Enter course number: ";
        cin >> temp;
        quit = checkQuit(temp);
        if(!quit) {
            strcpy(courseNums[count], temp);
            int n = 0;
            readInt("Number of students enrolled:", n);
            students[count] = n;
            count++;
        }
    } while (!quit);

}

// a. This function should be used any time you read any integers from the user. Use
//    this function to read the menu option from the user.
// b. It takes a string prompt, outputs it, reads a number from the user, validates and
//    returns the num by reference.
// c. See Samplea01.cpp for the function. You may use the function in the sample.
// d. You must catch all invalid data such as characters, negative numbers etc.
void readInt(string prompt, int &num) {
    bool valid = true;
    do {
        valid = true;
        cout << prompt;
        cin >> num;
        if(!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            valid = false;
        } else if (num < 0 || num > MAX_STUDENTS_PER_COURSE) {
            valid = false;
        }
        if(!valid) {
            cout << "Invalid number!! Please enter a number between 0 and 25" << endl;
        }
    } while (!valid);
}

// a. This function takes the 2 arrays and count, uses a for loop and prints the lists to the user.
// b. Format your list neatly.
void printList(char courseNums[][MAXCHAR + 1], int students[], int count) {
// List of courses and students:
// CS133G 7
// CS160_1 15
// CS160_2 7
// CS161A_1 21
// CS161A_2 25
// CS161B 23
// CS162 25
// CS260 5
    for(int i = 0; i < count; i++) {
        cout << courseNums[i] << ' ' << students[i] << endl;
    }
}

void removeCourse(char courseNums[][MAXCHAR + 1], int students[], int &count, int pos) {
    for(int i = pos; i < count - 1; i++) {
        strcpy(courseNums[i],  courseNums[i + 1]);
        students[i] = students[i + 1];
    }
    count--;
}


// a. This function takes the 2 arrays and the count and removes all courses with less
//    than 10 students in the course.
// b. You must use a for loop, find the index where the number of students is less than 10, 
//    and then remove that number and the corresponding course number from the
//    char array by shifting elements in both the arrays.
// c. Update the count appropriately. If you cancel or remove 3 courses, then count
//    should be subtracted by 3, so the number of courses is updated.
void cancelCourses(char courseNums[][MAXCHAR + 1], int students[], int &count) {
    for(int i = 0; i < count; i++) {
        if(students[i] < MIN_STUDENTS_PER_COURSE) {
            removeCourse(courseNums, students, count, i);
        }
    }
}
