namespace myGitAdd {

#include <iostream>
#include <bits/stdc++.h>
#include <cstring>

#include "status.hpp"

using namespace std;
using namespace myGitStatus;

char cwd[PATH_MAX];
string mygit_path;
string version_no_file_path;
string version_no;
string index_path;
string base_path;
itn n;

vector<string> files;
map<string, string> map_index;
vector<string> new_files;
vector<string> modified_files;
vector<string> deleted_files;



int add();
int add_new(vector<string>);
int add_modified(vector<string>);
int add_deleted(vector<string>);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

int add() {
    mygit_path = "";
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        mygit_path = cwd;
        mygit_path += "/.mygit/"; // mygit path is the path to .mygit folder.
    } else {
        perror("Unable to get current working directory.\n");
        exit(1);
    }
}

// get files into a vector from the cwd.
files = myGitStatus::get_files(cwd);
n = files.size();

// goto the current version and read the version no.
version_no_file_path = mygit_path + "version_no.txt";

}

