// #include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
    if(ifs.is_open()) {
        string line;
        unsigned long total_paper = 0;  // part 1
        unsigned long total_ribbon = 0; // part 2
        while(getline(ifs, line)) {
            vector<int> dimensions;
            stringstream ss(line);
            string dim;
            int number;
            while(getline(ss, dim, 'x')) {
                stringstream num(dim);
                num >> number;
                dimensions.push_back(number); 
            }
            sort(dimensions.begin(), dimensions.end());
            int l = dimensions[0];
            int w = dimensions[1];
            int h = dimensions[2];
            total_paper += 2*l*h + 2*l*w + 2*w*h + dimensions[0]*dimensions[1];
            total_ribbon += 2*dimensions[0] + 2*dimensions[1] + (l*w*h);
        }
        cout << "paper: " << total_paper << endl;
        cout << "ribbon: " << total_ribbon << endl;
    }
}