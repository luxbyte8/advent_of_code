#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "md5.h"

using namespace std;

void test(const string&);
void solution(const string&);

int main()
{
    test("input.txt");
    solution("input.txt");
    solution("puzzle.txt");
    return EXIT_SUCCESS;
} // main

void test(const string &filename)
{
    MD5 md5{};
    fstream ifs(filename, ios::in | ios::binary);
    // how it could be used:
    // by reading chunks of data or you could read
    // entire data and call update and finalize once
    if(ifs.is_open()) {
        char buffer[512];
        // grab a chunk; in this case chunk of 512 bytes
        while(ifs.read(buffer, sizeof(buffer))) {
            md5.update(reinterpret_cast<uint8_t*>(buffer), ifs.gcount());
        }
        // any leftover data
        if(ifs.gcount() > 0) {
            md5.update(reinterpret_cast<uint8_t*>(buffer), ifs.gcount());
        }
        vector<uint8_t> digest;
        md5.finalize(digest);
        cout << "test: md5: 0x";
        for(uint8_t byte : digest)
            printf("%02x", byte);
        printf("\n");
    }
}

void solution(const string &filename)
{
    fstream ifs(filename, ios::in | ios::binary);
    if(!ifs.is_open()) {
        cerr << "unable to open file: " << filename << endl;
        exit(1);
    }
    char c;
    string msg;
    while(ifs.get(c)) {
        msg += c;
    }
    size_t num = 0;
    stringstream ss(msg); 
    vector<uint8_t> digest;
    bool once = true;
    while(true) {
        MD5 md5{};
        digest.clear();
        md5.update(reinterpret_cast<const uint8_t*>(ss.str().data()), ss.str().size());
        md5.finalize(digest);
        // part 1: starts with 5 zeros
        if(digest[0] == 0x00 && digest[1] == 0x00 && (digest[2] >> 4) == 0x00) {
            if(once) {
                cout << "part 1: " << ss.str() << ", md5: 0x";
                for(uint8_t byte : digest)
                    printf("%02x", byte);
                printf("\n");
            }
            once = false;
            // part 2: starts with 6 zeros
            if(digest[0] == 0x00 && digest[1] == 0x00 && digest[2] == 0x00) {
                cout << "part 2: " << ss.str() << ", md5: 0x";
                for(uint8_t byte : digest)
                    printf("%02x", byte);
                printf("\n");
                break;
            }
        } 
        ss.str(""); // reset content
        ss.clear(); // reset flags
        ss << msg << num;
        num++;
    }
}
// EOF