#ifndef MD5_H_
#define MD5_H_

#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <vector>

using namespace std;

class MD5 {
    public:
        MD5();
        ~MD5();
        void update(const uint8_t*, size_t);
        void finalize(vector<uint8_t>&);
    protected:
        void process(const uint8_t *block);
        void init();
        uint32_t F(uint32_t, uint32_t, uint32_t);
        uint32_t G(uint32_t, uint32_t, uint32_t);
        uint32_t H(uint32_t, uint32_t, uint32_t);
        uint32_t I(uint32_t, uint32_t, uint32_t);
        uint32_t left_rotate(uint32_t, uint32_t);
    private:
        // per-round shifts
        static const uint32_t S[64]; 
        uint32_t K[64];         // MD5 constants
        uint32_t A, B, C, D;
        uint64_t bit_len;       // we need length as 64-bit int
        vector<uint8_t> buffer; // we work at byte level

}; // MD5

#endif