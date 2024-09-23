#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric> // std::accumulate
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum {OFF, ON, TOGGLE};

void part1(const string&);
void part2(const string&);
void tokenize(const string&, vector<string>&);

int main()
{
    part1("input.txt");
    part1("puzzle.txt");
    part2("input.txt");
    part2("puzzle.txt");
    return EXIT_SUCCESS;
} // main

void part1(const string &filename) 
{
    vector<vector<int>> lights(1000, vector<int>(1000, 0));

    fstream ifs(filename, ios::in);
    if(!ifs.is_open()) {
        cerr << "unable to open file: " << filename << endl;
        exit(1);
    }

    size_t lights_on = 0;
    string line;
    while(getline(ifs, line)) {
        vector<string> tokens;
        tokenize(line, tokens);
        
        int set_light = -1;
        if(tokens[0] == "turn" && tokens[1] == "on") set_light = ON;
        else if(tokens[0] == "turn" && tokens[1] == "off") set_light = OFF;
        else if(tokens[0] == "toggle") set_light = TOGGLE;
        if(set_light == -1) {
            cerr << "unable to set light" << endl;
            exit(1);
        }

        size_t x1, y1, x2, y2;
        size_t c = (set_light == TOGGLE) ? 0 : 1;
        x1 = stoull(tokens[1 + c]);
        y1 = stoull(tokens[2 + c]);
        x2 = stoull(tokens[4 + c]);
        y2 = stoull(tokens[5 + c]);

        for(size_t x = x1; x <= x2; ++x) {
            for(size_t y = y1; y <= y2; ++y) {
                if(set_light == ON) lights[x][y] = ON;
                else if(set_light == OFF) lights[x][y] = OFF;
                else if(set_light == TOGGLE) {
                    lights[x][y] = (lights[x][y] == ON) ? OFF : ON;
                }
            }
        }
    } // while(getline)
    
    for(const auto &row : lights) {
        for(const auto &light : row) {
            lights_on += light;
        }
    }
    cout << "lights on: " << lights_on << endl;
} // part1

void part2(const string &filename)
{
    vector<vector<int>> lights(1000, vector<int>(1000, 0));

    fstream ifs(filename, ios::in);
    if(!ifs.is_open()) {
        cerr << "unable to open file: " << filename << endl;
        exit(1);
    }

    size_t lights_brightness = 0;
    string line;
    while(getline(ifs, line)) {
        vector<string> tokens;
        tokenize(line, tokens);
        
        int set_light = -1;
        if(tokens[0] == "turn" && tokens[1] == "on") set_light = ON;
        else if(tokens[0] == "turn" && tokens[1] == "off") set_light = OFF;
        else if(tokens[0] == "toggle") set_light = TOGGLE;
        if(set_light == -1) {
            cerr << "unable to set light" << endl;
            exit(1);
        }

        size_t x1, y1, x2, y2;
        size_t c = (set_light == TOGGLE) ? 0 : 1;
        x1 = stoull(tokens[1 + c]);
        y1 = stoull(tokens[2 + c]);
        x2 = stoull(tokens[4 + c]);
        y2 = stoull(tokens[5 + c]);

        for(size_t x = x1; x <= x2; ++x) {
            for(size_t y = y1; y <= y2; ++y) {
                if(set_light == ON) lights[x][y] += 1;
                else if(set_light == OFF) lights[x][y] -= (lights[x][y] == 0) ? 0 : 1;
                else if(set_light == TOGGLE) lights[x][y] += 2;
            }
        }
    } // while(getline)
    
    for(const auto &row : lights) {
        for(const auto &light : row) {
            lights_brightness += light;
        }
    }
    cout << "lights brightness: " << lights_brightness << endl;
} // part2

void tokenize(const string &line, vector<string> &tokens)
{
    stringstream ss(line);
    string token;
    char ch;
    while(ss.get(ch)) {
        if(ch == ' ' || ch == ',') {
            tokens.push_back(token);
            token.clear();
        }
        else token += ch;
    }
    if(token.size() > 0) tokens.push_back(token);
}
// EOF