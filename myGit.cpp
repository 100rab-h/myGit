#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) { 
    string str;
    char *p = argv[1];
    str = p;

    if (str == "init") {

    }
    else if (str == "status") {

    }
    else if (str == "add") {

    }
    else if (str == "commit") {

    }
    else if (str == "rollback") {

    }
    else if (str == "log") {

    }
    else if (str == "push") {

    }
    else if (str == "merge") {

    }
    else if (str == "retrieve_version_no") {

    }
    else if (str == "retrieve_sha") {

    }
    else if (str == "retrieve_filename") {

    } 
    else {
        cout << str << " is not a Git command. " << endl;
        cout << "These are common Git commands :" << endl;
        cout << "1 - ./mygit init \n2 - ./mygit status\n3 - mygit add \n4 - ./mygit commit\n5 - ./mygit log\n6 - ./mygit rollback\n7 - ./mygit pull\n8 - ./mygit push\n9 - ./mygit merge\n10 - ./mygit retrieve_version_no\n11 - ./mygit retrieve_sha filename version_no\n12 - ./mygit retrieve_filename sha version_no\n" << endl;
    }

    return 0;
}