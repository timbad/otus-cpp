
#include "ip_filter.h"

#include <iostream>
#include <string>
#include <vector>


int main(int , char const* [])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // convert to tuple of ints

        ip4_vec_t ip4_vec;
        ip4_vec.reserve(ip_pool.size());
        for (const auto &s_ip: ip_pool) {
            ip4_vec.push_back({std::stoi(s_ip[0]),
                               std::stoi(s_ip[1]),
                               std::stoi(s_ip[2]),
                               std::stoi(s_ip[3])});
        }

//        std::cout << ip4_vec;

        // TODO reverse lexicographically sort
//        std::sort(ip4_vec.begin(), ip4_vec.end(),
//                  [](const ip4_t &ip1, const ip4_t &ip2) {
//                      return to_number(ip1) > to_number(ip2);
//                  });

        sort(ip4_vec);
        std::cout << ip4_vec;

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        auto ip4_vec2 = filter(ip4_vec, 1);
        std::cout << ip4_vec2;
//        for (const auto& ip4 : ip4_vec) {
//            if (ip4[0] == 1) {
//                std::cout << ip4 << std::endl;
//            }
//        }

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        auto ip4_vec3 = filter(ip4_vec, 46,70);
        std::cout << ip4_vec3;
//        for (const auto& ip4 : ip4_vec) {
//            if (ip4[0] == 46 && ip4[1] == 70) {
//                std::cout << ip4 << std::endl;
//            }
//        }

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        auto ip4_vec4 = filter_any(ip4_vec, 46);
        std::cout << ip4_vec4;
//        for (const auto& ip4 : ip4_vec) {
//            for (auto v : ip4) {
//                if (v == 46) {
//                    std::cout << ip4 << std::endl;
//                    break;
//                }
//            }
//        }

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
