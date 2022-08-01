#ifndef HW02_IP_FILTER_H
#define HW02_IP_FILTER_H

#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, const char d = '.') {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


using ip4_t = std::array<int, 4>;
using ip4_vec_t = std::vector<ip4_t>;

std::ostream &operator<<(std::ostream &oss, const ip4_t &ip4) {
    oss << std::to_string(ip4[0]) << "."
        << std::to_string(ip4[1]) << "."
        << std::to_string(ip4[2]) << "."
        << std::to_string(ip4[3]);
    return oss;
}


std::ostream &operator<<(std::ostream &oss, const ip4_vec_t &ip4_vec) {
    for (const auto &ip4: ip4_vec) {
        oss << ip4 << std::endl;
    }
    return oss;
}

uint32_t to_number(const ip4_t &ip4) {
    uint32_t addr = ip4[0] << 24;
    addr |= ip4[1] << 16;
    addr |= ip4[2] << 8;
    addr |= ip4[3];
    return addr;
}


void sort(ip4_vec_t &ip4_vec, const bool is_reverse = true) {
    std::sort(ip4_vec.begin(), ip4_vec.end(),
              [is_reverse](const ip4_t &ip1, const ip4_t &ip2) {
                  if (is_reverse) {
                      return to_number(ip1) > to_number(ip2);
                  } else {
                      return to_number(ip1) < to_number(ip2);
                  }
              });
}


ip4_vec_t filter(const ip4_vec_t &ip4_vec, int v1 = -1, int v2 = -1, int v3 = -1, int v4 = -1) {
    ip4_vec_t ip4_vec_filtered;
    std::copy_if(ip4_vec.begin(), ip4_vec.end(), std::back_inserter(ip4_vec_filtered),
                 [v1, v2, v3, v4](const ip4_t &ip4) {
                     const bool is_v1 = v1 < 0 || ip4[0] == v1;
                     const bool is_v2 = v2 < 0 || ip4[1] == v2;
                     const bool is_v3 = v3 < 0 || ip4[2] == v3;
                     const bool is_v4 = v4 < 0 || ip4[3] == v4;
                     return is_v1 && is_v2 && is_v3 && is_v4;
                 });
    return ip4_vec_filtered;
}

ip4_vec_t filter_any(const ip4_vec_t &ip4_vec, int v) {
    ip4_vec_t ip4_vec_filtered;
    std::copy_if(ip4_vec.begin(), ip4_vec.end(), std::back_inserter(ip4_vec_filtered),
                 [v](const ip4_t &ip4) {
                     return std::any_of(ip4.begin(), ip4.end(), [v](int v_) { return v == v_; });
                 });
    return ip4_vec_filtered;
}


#endif //HW02_IP_FILTER_H
