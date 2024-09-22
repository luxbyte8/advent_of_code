#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

void part1(const string&);
void part2(const string&);

int main()
{
    part1("input1.txt");
    part1("puzzle.txt");
    part2("input2.txt");
    part2("puzzle.txt");
    return EXIT_SUCCESS;
} // main

void part1(const string &filename)
{
    fstream ifs(filename, ios::in);
    if(!ifs.is_open()) {
        cerr << "unable to open file: " << filename << endl;
        exit(1);
    }

    string line;
    size_t nice_strings = 0;
    while(getline(ifs, line)) {
        bool found_vowel = false;
        bool found_dup = false;
        bool found_exclude = false;
        int vowel_count = 0;
        set<char> st = {'a', 'e', 'i', 'o', 'u'};
        for(size_t i = 0; i < line.size() - 1; ++i) {
            // contains at least 3 vowels
            if(!found_vowel && st.find(line[i]) != st.end()) {
                vowel_count += 1;
                if(vowel_count == 3) found_vowel = true;
            }
            // at least one letter appears twice in a row
            // and does not contain: ab, cd, pq, or xy
            if(!found_dup && line[i] == line[i + 1]) found_dup = true;
            else if(!found_exclude) {
                if(line[i] == 'a' && line[i + 1] == 'b') found_exclude = true;
                else if(line[i] == 'c' && line[i + 1] == 'd') found_exclude = true;
                else if(line[i] == 'p' && line[i + 1] == 'q') found_exclude = true;
                else if(line[i] == 'x' && line[i + 1] == 'y') found_exclude = true;
                if(found_exclude) break;
            }
        }
        // check last elem for vowel
        if(st.find(line[line.size() - 1]) != st.end()) {
            vowel_count += 1;
            if(vowel_count == 3) found_vowel = true;
        }
        nice_strings += (found_vowel && found_dup && !found_exclude) ? 1 : 0;
    }
    cout << "nice strings: " << nice_strings << endl;
}

void part2(const string &filename)
{
    // ans: 51
    fstream ifs(filename, ios::in);
    if(!ifs.is_open()) {
        cerr << "unable to open file" << endl;
        exit(1);
    }
    string line;
    size_t nice_strings = 0;
    while(getline(ifs, line)) {
        // super ambiguous question
        // containing an overlap is okay as long as there
        // exists another matching pair at least 2 indices away
        // i.e. aaaa would be a nice string
        bool found_pair = false;
        bool found_rep = false;
        unordered_map<string, set<size_t>> mp;  // store pair and its starting index
        for(size_t i = 0; i < line.size(); ++i) {
            stringstream pair;
            pair << line[i] << line[i + 1];
            if(mp.find(pair.str()) != mp.end()) {
                for(const auto idx : mp[pair.str()]) {
                    size_t diff = (i < idx) ? idx - i : i - idx;
                    // is there a matching pair that is at least 2 indices away
                    if(diff >= 2) {
                        found_pair = true;
                        break;
                    }
                }
            }
            mp[pair.str()].insert(i);
        }
        if(!found_pair) continue;
        for(size_t i = 0; i < line.size() - 2; ++i) {
            char c1 = line[i];
            char c2 = line[i + 2];
            if(c1 == c2) {
                found_rep = true;
                break;
            }
        }
        if(!found_rep) continue;
        nice_strings += 1;
    }
    cout << "nice strings: " << nice_strings << endl;
}
// EOF