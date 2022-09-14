namespace myGitLog {

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <cstring>
#include <ctime>

#include "status.hpp"


using namespace std;
using namespace myGitStatus;

string log_path;

void log_print();
void log_write(string);
string currenttime();


void log_print() {
    log_path = myGitStatus::get_cwd();
    log_path += "/.mygit/log.txt";  //goto log.txt file which resides in .mygit folder.

    string s;
    ifstream fin;
    fin.open(log_path, ios::in); // open log file by providing its path.
    while (fin) {
        getline(fin, s); // read it line by line.
        cout << s << endl;
    }
    fin.close();
    
}

void log_write(string str) {
    log_path = myGitStatus::get_cwd();
    log_path += "/.mygit/log.txt";

    ofstream fout;
    fout.open(log_path, ios::app);
    string s = currenttime(); // take curent time.
    fout << s << " : " << str << endl; // store in the log file.
    fout.close();
}

string currenttime() {
    time_t current_time;
    current_time = time(NULL);
    tm *tm_local = localtime(&current_time);
    string time = "";
    string timehour = to_string(tm_local->tm_hour);
    string timemin = to_string(tm_local->tm_min);
    string timesec = to_string(tm_local->tm_sec);

    time += timehour + ":" + timemin + ":" + timesec;
    return time;
}

}