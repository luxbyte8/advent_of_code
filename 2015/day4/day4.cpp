#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// All variables are unsinged 32-bit and mod 2^32

// per-round shift amounts
const vector<uint32_t> MD5_SHIFT {
    7, 12, 17, 22, // Round 1
    5, 9,  14, 20, // Round 2
    4, 11, 16, 23, // Round 3
    6, 10, 15, 21, // Round 4
    7, 12, 17, 22, // Round 5
    5, 9,  14, 20, // Round 6
    4, 11, 16, 23, // Round 7
    6, 10, 15, 21, // Round 8
    7, 12, 17, 22, // Round 9
    5, 9,  14, 20, // Round 10
    4, 11, 16, 23, // Round 11
    6, 10, 15, 21, // Round 12
    7, 12, 17, 22, // Round 13
    5, 9,  14, 20, // Round 14
    4, 11, 16, 23, // Round 15
    6, 10, 15, 21  // Round 16
};

vector<uint32_t> compute_md5_k();
const vector<uint32_t> MD5_K = compute_md5_k();

uint32_t A = 0x67452301;
uint32_t B = 0xefcdab89;
uint32_t C = 0x98badcfe;
uint32_t D = 0x10325476;

int main()
{
    for(const auto &x : MD5_K) {
        cout << hex << x << " " << endl;
    }
    return EXIT_SUCCESS;
}

vector<uint32_t> compute_md5_k()
{
    vector<uint32_t> md5_k(64);
    for(size_t i = 0; i < 64; ++i)
        md5_k[i] = static_cast<uint32_t>(floor((1ULL << 32) * abs(sin(i + 1))));
    return md5_k;
}