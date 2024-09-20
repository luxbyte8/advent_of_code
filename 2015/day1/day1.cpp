#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void part1(const string&);
void part2(const string&);

int main()
{
    // ( -> move up 1
    // ) -> move down 1
    part1("input.txt");
    part1("puzzle.txt");
    part2("input.txt");
    part2("puzzle.txt");
    return EXIT_SUCCESS;
}

void part1(const string &filename)
{
    fstream ifs(filename, ios::in);
    if(ifs.is_open()) {
        char c;
        int floor = 0;
        while(ifs.get(c)) {
            if(c == '(') floor += 1;
            if(c == ')') floor -= 1;
        } 
        cout << "floor: " << floor << endl;
    }
    else {
        cout << "unable to open file" << endl;
    }
    ifs.close();
}

void part2(const string &filename)
{
    fstream ifs(filename, ios::in);
    if(ifs.is_open()) {
        char c;
        int floor = 0;
        int pos = 0;
        while(ifs.get(c)) {
            if(c == '(') floor += 1;
            if(c == ')') floor -= 1;
            pos += 1;
            if(floor == -1) break;
        }
        cout << "floor: " << floor << " at: " << pos << endl;
    }
}
