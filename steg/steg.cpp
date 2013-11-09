#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <cstdlib>
#include "steg.hpp"

int main(int argc, char** argv){
    using namespace std;
    if (argc == 2){
        string s = decode(argv[1]);
        cout << s << endl;
    }else if (argc == 3){
        vector<char> input((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
        encode(argv[1], argv[2], &input[0]);
    }else if (argc == 4){
        encode(argv[1], argv[2], argv[3]);
    }else{
        cerr << "<USAGE>" << endl;
        exit(EXIT_FAILURE);
    }
}

