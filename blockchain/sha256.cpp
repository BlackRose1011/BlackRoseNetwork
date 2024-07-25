// NO COMMENTS, JUST SHA-256 FUNC
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

const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

SHA256::SHA256() {
    bit_count = 0;
    state[0] = 0x6a09e667;
    state[1] = 0xbb67ae85;
    state[2] = 0x3c6ef372;
    state[3] = 0xa54ff53a;
    state[4] = 0x510e527f;
    state[5] = 0x9b05688c;
    state[6] = 0x1f83d9ab;
    state[7] = 0x5be0cd19;
}

void SHA256::update(const uint8_t* data, size_t length) {
    size_t buffer_filled = bit_count / 8 % block_size;
    bit_count += length * 8;

    size_t i = 0;
    if (buffer_filled + length >= block_size) {
        std::memcpy(buffer + buffer_filled, data, block_size - buffer_filled);
        transform(buffer);
        i = block_size - buffer_filled;
        for (; i + block_size <= length; i += block_size) {
            transform(data + i);
        }
        buffer_filled = 0;
    }
    std::memcpy(buffer + buffer_filled, data + i, length - i);
}

void SHA256::final(uint8_t* hash) {
    size_t buffer_filled = bit_count / 8 % block_size;
    buffer[buffer_filled++] = 0x80;

    if (buffer_filled > block_size - 8) {
        std::memset(buffer + buffer_filled, 0, block_size - buffer_filled);
        transform(buffer);
        buffer_filled = 0;
    }
    std::memset(buffer + buffer_filled, 0, block_size - 8 - buffer_filled);

    uint64_t bit_count_be = __builtin_bswap64(bit_count);
    std::memcpy(buffer + block_size - 8, &bit_count_be, 8);
    transform(buffer);

    for (size_t i = 0; i < state_size; i++) {
        uint32_t state_be = __builtin_bswap32(state[i]);
        std::memcpy(hash + i * 4, &state_be, 4);
    }
}

void SHA256::transform(const uint8_t* chunk) {
    uint32_t w[64];
    for (size_t i = 0; i < 16; i++) {
        w[i] = (chunk[i * 4] << 24) | (chunk[i * 4 + 1] << 16) | (chunk[i * 4 + 2] << 8) | chunk[i * 4 + 3];
    }
    for (size_t i = 16; i < 64; i++) {
        w[i] = delta1(w[i - 2]) + w[i - 7] + delta0(w[i - 15]) + w[i - 16];
    }

    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];
    uint32_t e = state[4];
    uint32_t f = state[5];
    uint32_t g = state[6];
    uint32_t h = state[7];

    for (size_t i = 0; i < 64; i++) {
        uint32_t t1 = h + sigma1(e) + choose(e, f, g) + K[i] + w[i];
        uint32_t t2 = sigma0(a) + majority(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

uint32_t SHA256::rotr(uint32_t value, uint32_t count) {
    return (value >> count) | (value << (32 - count));
}

uint32_t SHA256::choose(uint32_t e, uint32_t f, uint32_t g) {
    return (e & f) ^ (~e & g);
}

uint32_t SHA256::majority(uint32_t a, uint32_t b, uint32_t c) {
    return (a & b) ^ (a & c) ^ (b & c);
}

uint32_t SHA256::sigma0(uint32_t x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

uint32_t SHA256::sigma1(uint32_t x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

uint32_t SHA256::delta0(uint32_t x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

uint32_t SHA256::delta1(uint32_t x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

std::string SHA256::toString(const uint8_t* hash) {
    std::ostringstream result;
    for (size_t i = 0; i < SHA256::hash_size; i++) {
        result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return result.str();
}
