#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <fstream>

#include "log.hpp"
#include "status.hpp"
#include "add.hpp"
#include "commit.hpp"
#include "pull.hpp"
#include "push.hpp"
#include "merge.hpp"
#include "rollback.hpp"

using namespace std;
using namespace myGitLog;
using namespace myGitStatus;
using namespace myGitAdd;
using namespace myGitCommit;
using namespace myGitPull;
using namespace myGitPush;
using namespace myGitMerge;
using namespace myGitRollback;

int init();
string retrieve_version_no();
void retrieve_sha(string, string);
void retrieve_filename(string, string);

int main(int argc, char** argv) { 
    // char * p = argv[1];
    string str;
    str = argv[1];

    if (str == "init") {
        if (init()) {
            string s = "Mygit successfully initialised.";
            myGitLog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        } else {
            string s = "Error in initialisation.";
            myGitLog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
        cout << str << endl;
    }

    else if (str == "status") {
        if (myGitStatus::status()) {
            string s = "Mygit status executed.";
            myGitLog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        } else {
            string s = "Error in Status.";
            myGitLog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }
    else if (str == "add") {
        if (myGitAdd::add()) {
            string s = "Mygit add executed.";
            myGitLog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }
    else if (str == "commit") {
        if (myGitCommit::commit()) {
            string s = "Mygit commit executed";
            myGitLog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }
    else if (str == "rollback") {
        int n = myGitRollback::rollback();
        if (n == 1) {
            cout << "Rollback successfully to the previous version." << endl;
        }
        string s = "Mygit rollback executed";
        myGitLog::log_write(s);
        cout << s << endl;
        exit(EXIT_SUCCESS);
    }
    else if (str == "log") {
        myGitLog::log_print();
        string s = "Mygit log print Executed.";
        myGitLog::log_write(s);
        cout << s << endl;
        exit(EXIT_SUCCESS);
    }
    else if (str == "pull") {
        myGitPull::pull();
        string s = "Mygit pull executed.";
        myGitLog::log_write(s);
        cout << s << endl;
        exit(EXIT_SUCCESS);
    }
    else if (str == "push") {
        myGitPush::push();
        string s = "Mygit push Executed.";
        myGitLog::log_write(s);
        cout << s << endl;
        exit(EXIT_SUCCESS);
    }
    else if (str == "merge") {
        myGitMerge::merge();
        string s = "Mygit Merge executed.";
        myGitLog::log_write(s);
        cout << s << endl;
        exit(EXIT_SUCCESS);
    }
    else if (str == "retrieve_version_no") {
        string version_no = retrieve_version_no();
        cout << "version no : " << version_no << endl;
        string s = "Mygit version retrieve executed";
        myGitLog::log_write(s);
        cout << s << endl;
        exit(EXIT_SUCCESS);
    }
    else if (str == "retrieve_sha") {
         
        retrieve_sha(argv[2],argv[3]);
        string s = "Mygit retrieve sha executed";
        myGitLog::log_write(s);
        cout << s << endl;
        exit(EXIT_SUCCESS);
    }
    else if (str == "retrieve_filename") {
        retrieve_filename(argv[2],argv[3]);
        string s = "Mygit retrieve filename executed";
        myGitLog::log_write(s);
        cout << s << endl;
        exit(EXIT_SUCCESS);
    } 
    else {
        cout << str << " is not a Git command. " << endl;
        cout << "These are common Git commands :" << endl;
        cout << "1 - ./mygit init \n2 - ./mygit status\n3 - mygit add \n4 - ./mygit commit\n5 - ./mygit log\n6 - ./mygit rollback\n7 - ./mygit pull\n8 - ./mygit push\n9 - ./mygit merge\n10 - ./mygit retrieve_version_no\n11 - ./mygit retrieve_sha filename version_no\n12 - ./mygit retrieve_filename sha version_no\n" << endl;
    }

    return 0;
}

int init() {
    bool createmygitdir = false;
    bool chdirmygit = false;
    bool createversion0dir = false;
    bool chdirversion0 = false;
    bool createIndexVersion0 = false;

    // getting current version directory
    string current_path = myGitStatus::get_cwd();
    
    // create .mygit folder
    if (mkdir(".mygit", 0777) == -1) {
        cerr << strerror(errno) << endl; // diplays error in making .mygit folder.
        return 0;
    } else {
        createmygitdir = true; // .mygit directory created.
    }

    if (chdir(".mygit") == -1) {
        cerr << strerror(errno) << endl; // display error in changing directory to .mygit.
        return 0;
    } else {
        chdirmygit = true;    // moved to .mygit folder.
    }

    // make version_no.txt file.

    ofstream fout;
    fout.open("version_no.txt", ios::out);
    if (fout) {
        string num = "0";  // initailly version no is 0;
        fout << num << endl;
    }

    fout.close();

    // make log.txt file.
    ofstream fout2;
    fout2.open("log.txt", ios::out);
    fout.close();

    if (mkdir("0", 0777) == -1) {
        cerr << strerror(errno) << endl;  // diplays error in making 0 version directory.
        return 0;
    } else {
        createversion0dir = true;   // 0 version folder created.
    }

    if (chdir("0") == -1) {
        cerr << strerror(errno) << endl;   // displays error in changing directory to 0 version directory.
        return 0;
    } else {
        chdirversion0 = true;
    }

    // create 0 version index file.
    ofstream fout3;
    fout3.open("index.txt");
    createIndexVersion0 = true;
    fout3.close();

    // returning to .mygit folder.
    string path = current_path + "./mygit";
    if (chdir(path.c_str()) == -1) {
        cerr << strerror(errno) << endl;
        return 0;
    }

    // create base folder.
    if (mkdir("base", 0777) == -1) {
        cerr << strerror(errno) << endl;
        return 0;
    }

    if (chdir("base") == -1) {
        cerr << strerror(errno) << endl;
        return 0;
    }

    // now transfer all the file from current path to this base folder.
    vector<string> v = myGitStatus::get_files(current_path);
    for (int i = 0; i < v.size(); i++) {
        string file = v[i];
        string s = current_path + "/" + file;

        // getting current working directory.
        string base_path = myGitStatus::get_cwd();
        string path = base_path + "/" + file;

        // copy files from cwd_path to base.
        ifstream fin;
        ofstream fout;

        fin.open(s, ios::in); // open that file in current path to read.
        fout.open(path, ios::out); // open that file in base to write.

        string line;
        while (fin) {
            getline(fin, line); // reading line by line.
            fout << line << endl; // writting line by line.
        }
        fin.close();
        fout.close();
        // file copied.
    }

    path = current_path + "./mygit";
    if (chdir(path.c_str()) == -1) {
        cerr << strerror(errno) << endl;
        return 0;
    }

    // if everything is done then init is successfull
    if (createmygitdir and chdirmygit and createversion0dir and chdirversion0 and createIndexVersion0) return 1;
    else return 0;

}

string retrieve_version_no() {
    string cwd_path = myGitStatus::get_cwd();
    string mygit_path = cwd_path + "/.mygit/";

    //reading version_no file to get current version number
    string version_no_file_path = mygit_path + "version_no.txt";
    fstream version_no_file(version_no_file_path, std::ios_base::in);
    string version_no;
    version_no_file >> version_no;
    version_no_file.close();

    return (version_no);
}

void retrieve_sha(string filename, string version_no)
{   
    //getting current working directory
    string cwd_path = myGitStatus::get_cwd();
    string mygit_path = cwd_path + "/.mygit/";
    
    string version_no_file_path = mygit_path + version_no + "/index.txt";
    
    map<string, string> files = myGitStatus::get_map(version_no_file_path);

    string sha = "";
    //retrieving sha of given file
    for (auto it : files)
    {
        if (it.first == filename)
        {
            sha = it.second;
            break;
        }
    }
    if (sha == "")
    {
        cout << "file with given filename not found in the given version...unable to retrieve sha" << endl;
    }
    else
    {
        cout <<"sha : "<< sha << endl;
    }
}

void retrieve_filename(string sha, string version_no)
{   
    //getting current working directory
    string cwd_path = myGitStatus::get_cwd();
    string mygit_path = cwd_path + "/.mygit/";
    
    string version_no_file_path = mygit_path + version_no + "/index.txt";
    
    map<string, string> files = myGitStatus::get_map(version_no_file_path);


    string filename = "";
    //retrieving filename of given file
    for (auto it : files)
    {
        if (it.second == sha)
        {
            filename = it.first;
            break;
        }
    }
    if (filename == "")
    {
        cout << "file with given sha not found in the given version...unable to retrieve filename" << endl;
    }
    else
    {
        cout << "filename : "<< filename << endl;
    }
}