#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct hash_pair {
    size_t operator()(const pair<int, int> &p) const {
        auto hash1 = hash<int>{}(p.first);
        auto hash2 = hash<int>{}(p.second);
        return hash1 ^ (hash2 << 1);    // try to reduce collision
        // size_t prime1 = 1000003;
        // size_t prime2 = 10000019;
        // return (hash1 * prime1) ^ (hash2 * prime2)); // another way to reduce collision
    }
};

void part1(const string&);
void part2(const string&);

int main()
{
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
        char dir;
        // using pair as key requires custom hash function
        unordered_map<pair<int, int>, int, hash_pair> mp;
        pair<int, int> curr_coord = {0, 0}; // x, y
        while(ifs.get(dir)) {
            switch(dir) {
                case '>':
                    curr_coord.first += 1;
                    break;
                case '<':
                    curr_coord.first -= 1;
                    break;
                case '^':
                    curr_coord.second += 1;
                    break;
                case 'v':
                case 'V':
                    curr_coord.second -= 1;
                    break;
                default:
                    cerr << "[-] unreachable: " << dir  << endl;
                    break;
            } // switch
            if(mp.find(curr_coord) == mp.end()) {
                mp[curr_coord] = 1;
            }
            else {
                mp[curr_coord] += 1;
            }
        } // while(ifs.get)
        cout << "visited: " << mp.size() << endl;
    } // if(ifs.is_open)
} // part1

void part2(const string &filename)
{
    fstream ifs(filename, ios::in);
    if(ifs.is_open()) {
        char dir;
        set<pair<int, int>> st;
        pair<int, int> santa = {0, 0};
        pair<int, int> robot = {0, 0}; 
        int turn = 0;
        while(ifs.get(dir)) {
            switch(dir) {
                case '>':
                    if(turn % 2 == 0) santa.first += 1;
                    else robot.first += 1;
                    break;
                case '<':
                    if(turn % 2 == 0) santa.first -= 1;
                    else robot.first -= 1;
                    break;
                case '^':
                    if(turn % 2 == 0) santa.second += 1;
                    else robot.second += 1;
                    break;
                case 'v':
                case 'V':
                    if(turn % 2 == 0) santa.second -= 1;
                    else robot.second -= 1;
                    break;
                default:
                    break;
            }
            if(turn % 2 == 0) {
                if(st.find(santa) == st.end()) st.insert(santa);
            }
            else {
                if(st.find(robot) == st.end()) st.insert(robot);
            }
            turn += 1;
        } // while(ifs.get)
        cout << "visited: " << st.size() << endl;
    } // if(ifs.is_open)
}