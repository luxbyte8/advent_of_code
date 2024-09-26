#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Signal {
    uint16_t signal;
    bool live;
    Signal(uint16_t s = 0, bool l = false) : signal(s), live(l) {};
};

typedef unordered_map<string, function<Signal()>> WireMapping;
typedef unordered_map<string, Signal> WireCache;
typedef unordered_map<string, bool> WireVisited;

WireMapping Wires;
WireCache Cache;
WireVisited Visited;

void part1(const string&);
void part2(const string&);

// utility
void parse_input(const string&);
Signal get_signal(const string&);
bool is_number(const string&);

int main()
{
    part1("input.txt");
    part1("puzzle.txt");
    part2("puzzle.txt");
    return EXIT_SUCCESS;
}

void part1(const string &filename)
{
    Wires.clear();
    Cache.clear();
    Visited.clear();
    parse_input(filename);

    for(const auto &wire : Wires) {
        int signal = ((wire.second)().live) ? (wire.second)().signal : -1;
        cout << "w: " << wire.first << ", val: " << signal << endl;
    }
}

void part2(const string &filename)
{
    Wires.clear();
    Cache.clear();
    Visited.clear();
    parse_input(filename);

    // override signal b with signal from a
    Signal s = get_signal("a");
    Wires["b"] = [=]() {
        return s;
    };
    // clear cache so new values are computed
    Cache.clear();
    Visited.clear();
    
    for(const auto &wire : Wires) {
        int signal = ((wire.second)().live) ? (wire.second)().signal : -1;
        cout << "w: " << wire.first << ", val: " << signal << endl;
    }

} // part1

void parse_input(const string &filename)
{
    fstream ifs(filename, ios::in);
    if(!ifs.is_open()) {
        cerr << "[+] ERROR: Unable to open file: " << filename << endl;
        exit(1);
    }

    string line;
    while(getline(ifs, line))
    {
        istringstream iss(line);
        string src1, src2, op, arrow, dst;
        if(line.find("AND") != string::npos || line.find("OR") != string::npos || line.find("LSHIFT") != string::npos || line.find("RSHIFT") != string::npos) {
            
            // parse
            iss >> src1 >> op >> src2 >> arrow >> dst;
            // cout << "Processing: " << dst << " <- " << src1 << " " << op << " " << src2 << endl;

            if(op == "AND") {
                Wires[dst] = [=]() {
                    Signal lhs = is_number(src1) ? Signal(stoi(src1), true) : get_signal(src1);
                    Signal rhs = is_number(src2) ? Signal(stoi(src2), true) : get_signal(src2);
                    return (!lhs.live || !rhs.live) ? Signal(0, false) : Signal(lhs.signal & rhs.signal, true);
                };
            }
            else if(op == "OR") {
                Wires[dst] = [=]() {
                    Signal lhs = is_number(src1) ? Signal(stoi(src1), true) : get_signal(src1);
                    Signal rhs = is_number(src2) ? Signal(stoi(src2), true) : get_signal(src2);
                    return (!lhs.live || !rhs.live) ? Signal(0, false) : Signal(lhs.signal | rhs.signal, true);
                };
            }
            else if(op == "LSHIFT") {
                Wires[dst] = [=]() {
                    Signal lhs = is_number(src1) ? Signal(stoi(src1), true) : get_signal(src1);
                    Signal rhs = is_number(src2) ? Signal(stoi(src2), true) : get_signal(src2);
                    return (!lhs.live || !rhs.live) ? Signal(0, false) : Signal(lhs.signal << rhs.signal, true);
                };
            }
            else if(op == "RSHIFT") {
                Wires[dst] = [=]() {
                    Signal lhs = is_number(src1) ? Signal(stoi(src1), true) : get_signal(src1);
                    Signal rhs = is_number(src2) ? Signal(stoi(src2), true) : get_signal(src2);
                    return (!lhs.live || !rhs.live) ? Signal(0, false) : Signal(lhs.signal >> rhs.signal, true);
                };
            }
        }
        else if(line.find("NOT") != string::npos) {
            iss >> op >> src1 >> arrow >> dst;
            // cout << "Proccesing: " << dst << " <- " << op << " " << src1 << endl;
            Wires[dst] = [=]() {
                Signal lhs = is_number(src1) ? Signal(stoi(src1), true) : get_signal(src1);
                return (!lhs.live) ? Signal(0, false) : Signal(~lhs.signal, true);
            };
        }
        else {
            iss >> src1 >> arrow >> dst;
            // cout << "Processing: " << dst << " <- " << src1 << endl;
            Wires[dst] = [=]() {
                Signal lhs = is_number(src1) ? Signal(stoi(src1), true) : get_signal(src1);
                return (!lhs.live) ? Signal(0, false) : Signal(lhs.signal, true);
            };
        }
    } // while(getline)
} // parse_input

Signal get_signal(const string &src)
{
    if(Visited[src]) {
        cerr << "[+] ERROR: Cyclic depending on: " << src << endl;
        exit(1);
    }
    if(Cache.find(src) != Cache.end()) return Cache[src];
    Visited[src] = true;
    Signal result = Wires[src]();
    Cache[src] = result;
    Visited[src] = false;
    return result;
} // get_signal

bool is_number(const string &token)
{
    for(char ch : token)
        if(!isdigit(ch)) return false;
    return true;
} // is_number

// EOF