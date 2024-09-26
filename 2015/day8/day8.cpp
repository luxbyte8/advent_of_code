#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>

using namespace std;

void solution(const string&);

int main()
{
    solution("input.txt");
    solution("puzzle.txt");
    return EXIT_SUCCESS;
}

void solution(const string &filename)
{
    fstream ifs(filename, ios::in);
    if(!ifs.is_open()) {
        cerr << "[+] ERROR: Unable to open file: " << filename << endl;
        exit(1);
    }

    string line;
    size_t total_char1 = 0; // for part1
    size_t total_char2 = 0; // for part2
    size_t total_tok = 0;
    while(getline(ifs, line)) {
        size_t idx = 0;
        while(idx < line.size()) {
            char ch = line[idx];
            total_char1 += 1;
            total_char2 += 1;
            if(ch == '\\') {
                if(idx + 1 < line.size()) {
                    if(line[idx + 1] == '"') {
                        // escaped double quote
                        idx += 2;
                        total_char1 += 1;
                        total_char2 += 3;
                        total_tok += 1;
                    }
                    else if(line[idx + 1] == '\\') {
                        // escaped backslash
                        idx += 2;
                        total_char1 += 1;
                        total_char2 += 3;
                        total_tok += 1;
                    }
                    else if(line[idx + 1] == 'x') {
                        // escaped hex value
                        if(idx + 2 < line.size() && idx + 3 < line.size()) {
                            idx += 4;
                            total_char1 += 3;
                            total_char2 += 4;
                            total_tok += 1;
                        }
                    }
                }
            }
            else if(ch == '"') {
                total_char2 += 2;
                idx += 1;
            }
            else if(isalpha(ch)) {
                total_tok += 1;
                idx += 1;
            }
        } // parse token
    } // while(getline)
    cout << "part1: " << total_char1 << " - " << total_tok << " = " << total_char1 - total_tok << endl;
    cout << "part2: " << total_char2 << " - " << total_char1 << " = " << total_char2 - total_char1 << endl;
}
