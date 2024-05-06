#include <endian.h>
#include <iostream>
#include <fstream>

#include <thread>
#include <chrono>


int write() {
    std::ofstream cap1188_in("/dev/CAP1188");
    if (!cap1188_in.is_open()) {
        std::cerr << "Could not open /dev/CAP1188" << std::endl;
        return -1;
    }

    char wow[] = {0x74, 0x01};
    //char* buf = char[2];

   // buf[0] = 0x74;
    //buf[1] = 0xfe;
    //uint32_t data = 2;
    char* buf = wow;
    if (cap1188_in.write(buf, sizeof(buf))) {
        //return data;
        std::cout << "WROTE DATA SUCCESSFLLYY" << std::endl;
    }
    else {
        //std::cerr << "Read failed" << std::endl;
        std::cout << "failed to write data" << std::endl;
    }

    return -1;
}

int read() {
    std::ifstream cap1188_in("/dev/CAP1188");
    if (!cap1188_in.is_open()) {
        std::cerr << "Could not open /dev/CAP1188" << std::endl;
        return -1;
    }

    //uint32_t data;
    char data = {0};
    char* wow = &data;
    if (cap1188_in.read(wow, sizeof(wow))) {
        std::cout << "Read Success!!!" << std::endl;
        //return data;
        return 0;
    }
    else {
        std::cout << "Read failed" << std::endl;
    }

    return -1;
}

int main() {

    //write();

    //auto range_mm = read();
    read();
    //std::cout << "will this work??" << range_mm << std::endl;
    //if (range_mm != -1) {
        //std::cout << "Measured range in mm: " << range_mm << std::endl;
    //}

    /*while (true) {
        auto range_mm = read();
        if (range_mm != -1) {
            std::cout << "Measured range in mm: " << range_mm << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }*/

    return 0;
}