namespace myGitPush {

#include <iostream>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <error.h>
#include <fstream>
#include <unistd.h>
#include <dirent.h>

using namespace std;

string get_cwd();
vector<string> get_files(string);

int push() {
    string cwd = get_cwd();

    // creating push folder
    string path_push = cwd + "/push";
    int t = mkdir(path_push.c_str(), 0777);
    if (t != 0 and errno != EEXIST) {
        cerr << "Unable to make push directory " << strerror(errno) << endl;
        return 0;
    }

    // copy files from pull to push folder.
    string path_pull = cwd + "/pull";
    vector<string> files = get_files(path_pull);
    for (auto it : files) {
        string src = path_pull + "/" + it;
        string des = path_push + "/" + it;
        ifstream fin;
        ofstream fout;
        fin.open(src, ios::in);
        fout.open(src, ios::out);

        string line;
        while (fin) {
            getline(fin, line);
            fout << line << endl;
        }
        fin.close();
        fout.close();
    }

    cout << "Successfully pushed files to: " << path_push << endl;
    return 0;

}

string get_cwd() {
    char cwd_path[PATH_MAX];
    string current_path;
    if (getcwd(cwd_path, sizeof(cwd_path)) != NULL) {
        current_path = cwd_path;
    } else {
        perror("unable to get current working directory.");
        exit(1);
    }

    return current_path;
}

vector<string> get_files(string path) {
    struct dirent *pointerp;
    DIR *dir = opendir(path.c_str());

    if (dir == NULL) {
        cout << "Error in opening Directory.";
        exit(EXIT_FAILURE);
    }

    vector<string> v;
    while ((pointerp = readdir(dir)) != NULL)
    {
        string filename = pointerp->d_name;
        if (filename == "." || filename == ".." || filename == ".mygit" || filename == "a.out" || filename == ".vscode" || filename == "mygit" || filename=="status.hpp" || filename=="add.hpp" || filename=="commit.hpp" || filename=="mygit.cpp" || filename=="log.hpp" || filename=="pull.hpp" || filename=="push.hpp" || filename=="merge.hpp" || filename=="rollback.hpp" || filename=="mygit" || filename=="pull" || filename=="push" )
        {
            continue;
        }
        else
        {
            v.push_back(filename);
        }
    }
    closedir(dir);
    return v;
    
}

}