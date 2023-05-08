#include <iostream>
#include <vector>
#include <chrono>

std::uint32_t collatz(std::size_t num, std::vector<std::uint32_t>& cache) {
    std::size_t n = num;
    std::uint32_t computed = 0u;

    if (n % 2 == 0) {
        computed = cache[n >> 1] + 1;
        cache.push_back(computed);
        return computed;
    } else {
        while (n != 1) {
            if (n < cache.size() && cache[n] != 0) {
                computed += cache[n];
                break;
            } else {
                computed += 1;
                if (n % 2 == 1) {
                    n = n * 3 + 1;
                } else {
                    n >>= 1;
                }
            }
        }
        cache.push_back(computed);
        return computed;
    }
}

int main() {
    const std::size_t limit = 100'000'000;
    auto now = std::chrono::high_resolution_clock::now();
    std::uint32_t max = 0;
    std::size_t max_num = 0;
    std::vector<std::uint32_t> cache {1u};

    for (std::size_t n = 1; n <= limit; ++n) {
        std::uint32_t c = collatz(n, cache);
        if (c > max) {
            max = c;
            max_num = n;
        }
    }

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now);

    std::cout << "Maximum: collatz(" << max_num << ") " << max << ", Cache Size: " << cache.size() << ". Elapsed: " << elapsed.count() << " ms\n";
    return 0;
}
