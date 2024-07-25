// файл для передачі коду в інчий файл
#ifndef SHA256_H
#define SHA256_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstdint>

class SHA256 {
public:
    SHA256();
    void update(const uint8_t* data, size_t length);
    void final(uint8_t* hash);
    static std::string toString(const uint8_t* hash);
    static const size_t hash_size = 32;

private:
    void transform(const uint8_t* chunk);
    static uint32_t rotr(uint32_t value, uint32_t count);
    static uint32_t choose(uint32_t e, uint32_t f, uint32_t g);
    static uint32_t majority(uint32_t a, uint32_t b, uint32_t c);
    static uint32_t sigma0(uint32_t x);
    static uint32_t sigma1(uint32_t x);
    static uint32_t delta0(uint32_t x);
    static uint32_t delta1(uint32_t x);

    static const size_t block_size = 64;
    static const size_t state_size = 8;

    uint32_t state[state_size];
    uint64_t bit_count;
    uint8_t buffer[block_size];
};

#endif
