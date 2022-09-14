namespace myGitStatus {

#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

using namespace std;

int status();
string get_cwd();
vector<string> get_files(string);
string get_sha(string);
map<string, string> get_map(string);

string get_cwd() {
    char cwd_path[PATH_MAX];
    string current_path;
    
    if (getcwd(cwd_path, sizeof(cwd_path)) != NULL) {
        current_path = cwd_path; 
    } else {
        perror("Unable to get current working directory");
        exit(1);
    }

    return current_path;
}

vector<string> get_files(string path) {
    struct dirent *pointerp;
    DIR *dir = opendir(path.c_str());  // pointer to the directory whose files we wish to copy.
    if (dir == NULL) {
        cout << "Failed to open Directory.";
        exit(EXIT_FAILURE);
    }

    vector<string> v;
    while ((pointerp = readdir(dir)) != NULL) {  // readdir(dir) will point to the files one by one.
        // cout << pointerp->d_name << endl;
        string file = pointerp->d_name;
        if (file != "." and file != ".." and file != ".mygit" and file != "a.out" and file != ".vscode" and file != "mygit" and file != "status.hpp" and file != "add.hpp" and file != "commit.hpp" and file != "mygit.cpp" and file != "log.hpp" and file != "pull.hpp" and file != "push.hpp" and file != "merge.hpp" and file != "rollback.hpp" and file != "pull" and file != "push") {
            v.push_back(file);  // push the file in vector.
        }
    }
    closedir(dir);
    return v;
    
}

int status() {
    string cwd_path = get_cwd();
    string mygit_path = cwd_path + "./mygit/";

    vector<string> files = get_files(cwd_path); // store all files of cwd.
    int n = files.size();

    string version_file_path = mygit_path;
    version_file_path += "version_no.txt";  // goto version_no.txt file.

    fstream version_no_file(version_file_path, std::ios_base::in);
    string version_no;
    version_no_file >> version_no; // store the version no from version_no.txt.
    version_no_file.close();

    string index_path = mygit_path + version_no; // goto current version folder.
    index_path = index_path + "/index.txt"; // goto index.txt file.

    map<string, string> map_index = get_map(index_path); // store the content of index file to map.

    vector<string> newFiles, deletedFiles, modifiedFiles;

    map<string, string> map_cwd; // create a map for cwd files.

    for (int i = 0; i < n; i++) {
        string sha = get_sha(files[i]);
        map_cwd[files[i]] = sha;
    }

    for (int i = 0; i < n; i++) {
        string sha = get_sha(files[i]);
        if (map_index.find(files[i]) == map_index.end()) { // file exist in cwd_map but not in index_map so it is new file.
            newFiles.push_back(files[i]);
        } else if (map_index[files[i]] != sha) { // sha of same file name doesn't match, means modified.
            modifiedFiles.push_back(files[i]);
        }
    }

    sort(files.begin(), files.end());
    for (auto f : map_index) // file exist in map but not in vector, means those file were deleted.
    {
        if (find(files.begin(), files.end(), f.first) == files.end()) {
            deletedFiles.push_back(f.first);
        }
    }

    cout << "No. of modified files - " << modifiedFiles.size() << endl;
    cout << "No. of new files - " << newFiles.size() << endl;
    cout << "No. of deleted files - " << deletedFiles.size() << endl;

    return 1;

}

string get_sha(string file_name) {
    string s = "sha1sum " + file_name + " > temp.txt";

    char arr[255];
    strcpy(arr, s.c_str()); // store string s in array arr.
    system(arr); // sha calculation.

    FILE *filepointer = fopen("temp.txt", "r+"); // open temporary file to read the sha.
    char aux[100];
    fread(aux, sizeof(char), 100, filepointer); // reading in sha in aux array.
    string input = aux;
    stringstream ss(input);
    string sha;
    ss >> sha;
    fclose(filepointer);

    remove("temp.txt"); // delete temp.txt file

    return sha;
}

map<string, string> get_map(string path) {
    map<string, string> index_map;
    fstream f(path, std::ios_base::in);
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            stringstream ss(line);
            string filename = "";
            string sha = "";
            ss >> filename;
            ss >> sha;
            index_map[filename] = sha; // filename : sha
        }
    } else {
        perror("Unable to open file in get_map function");
        exit(1);
    }

    return index_map;
}

}