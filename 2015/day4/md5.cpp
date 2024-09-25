#include "md5.h"

const uint32_t MD5::S[64] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,   // Round 0..15
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,   // Round 16..31
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,   // Round 32..47
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21    // Round 48..63
};

MD5::MD5()
{
    init();
}

MD5::~MD5()
{

}

void MD5::update(const uint8_t *input, size_t len)
{
    buffer.insert(buffer.end(), input, input + len);
    bit_len += len * 8; // len is in bytes so convert to bits

    // process in 64 bytes chunks
    while(buffer.size() >= 64) {
        process(buffer.data());
        buffer.erase(buffer.begin(), buffer.begin() + 64);
    }
}

void MD5::finalize(vector<uint8_t> &digest)
{
    // append 1 then pad 0 up to congruent 448 mod 512
    // 512 - 64     = 448 = 56 bytes; buffer < 56 bytes, pad up to 56 bytes
    // 512 * 2 - 64 = 960 = 120 bytes; buffer > 56 bytes, pad up to 120 bytes
    size_t pad_len = (buffer.size() < 56) ? (56 - buffer.size()) : (120 - buffer.size());
    vector<uint8_t> padding(pad_len, 0); // padding of zeros
    padding[0] = 0x80;  // insert 1 at the beginning since we have to append 1 then the zeros 
    buffer.insert(buffer.end(), padding.begin(), padding.end());
    uint64_t bit_len_LE = bit_len; // bit length; little endian
    buffer.insert(buffer.end(),
                  reinterpret_cast<uint8_t*>(&bit_len_LE),
                  reinterpret_cast<uint8_t*>(&bit_len_LE) + 8); // bit_len_LE is 64 bits: 8 bytes
    while(buffer.size() >= 64) {
        process(buffer.data());
        buffer.erase(buffer.begin(), buffer.begin() + 64);
    }
    digest.resize(16);
    memcpy(digest.data(), &A, 4);
    memcpy(digest.data() + 4, &B, 4);
    memcpy(digest.data() + 8, &C, 4);
    memcpy(digest.data() + 12, &D, 4);
}

void MD5::init()
{
    // compute constants
    for(size_t i = 0; i < 64; ++i)
        K[i] = floor((1ULL << 32) * abs(sin(i + 1)));
    A = 0x67452301;
    B = 0xefcdab89;
    C = 0x98badcfe;
    D = 0x10325476;
    bit_len = 0;
    buffer.clear();
}

void MD5::process(const uint8_t *block)
{
    // process 64 BYTE block
    uint32_t M[16]; // 32-bit => 4 bytes; 4 * 16 = 64 bytes
    memcpy(M, block, 64);
    
    uint32_t AA = A;
    uint32_t BB = B;
    uint32_t CC = C;
    uint32_t DD = D;
    
    for(int i = 0; i < 64; ++i) {
        uint32_t F_val, g;
        if(i < 16) {
            F_val = F(BB, CC, DD);
            g = i;
        }
        else if(i < 32) {
            F_val = G(BB, CC, DD);
            g = (5 * i + 1) % 16;
        }
        else if(i < 48) {
            F_val = H(BB, CC, DD);
            g = (3 * i + 5) % 16;
        }
        else {
            F_val = I(BB, CC, DD);
            g = (7 * i) % 16;
        }
        F_val += AA + K[i] + M[g];
        AA = DD;
        DD = CC;
        CC = BB;
        BB += left_rotate(F_val, S[i]);
    } // for
    A += AA;
    B += BB;
    C += CC;
    D += DD;
}

uint32_t MD5::F(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y ) | (~x & z);
}

uint32_t MD5::G(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & z) | (y & ~z);
}

uint32_t MD5::H(uint32_t x, uint32_t y, uint32_t z)
{
    return x ^ y ^ z;
}

uint32_t MD5::I(uint32_t x, uint32_t y, uint32_t z)
{
    return y ^ (x | ~z);
}

uint32_t MD5::left_rotate(uint32_t x, uint32_t n)
{
    return (x << n) | (x >> (32 - n));
}
// EOF