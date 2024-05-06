#include <endian.h>
#include <iostream>
#include <fstream>
#include <string>
//#include <ctime>
#include <unistd.h>

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

/*int read() {
    std::ifstream cap1188_in("/dev/CAP1188");
    if (!cap1188_in.is_open()) {
        std::cerr << "Could not open /dev/CAP1188" << std::endl;
        return -1;
    }

    //uint32_t data;
    //char data = {0};
    //char* wow = &data;
    //char * wow = "NOW THAT IS A STRANGE THING";
    char wow[13] = {};
    if (cap1188_in.read(wow, sizeof(wow))) {
        std::cout << "Read Success!!!" << std::endl;
        //return data;
        return 0;
    }
    else {
        std::cout << "Read failed" << std::endl;
    }

    return -1;
}*/

int read() {

    while(1)
    {  
    std::ifstream cap1188_in("/dev/CAP1188");
    if (!cap1188_in.is_open()) {
        std::cerr << "Could not open /dev/CAP1188" << std::endl;
        return -1;
    }

    char wow[2] = {};

    if (!cap1188_in.read(wow, sizeof(wow))) {
        std::cout << "Read Success!!! cahr" << std::endl;
    }
    else {
        std::cout << "Read failed char" << std::endl;
    }

    std::ifstream sensor1_in("/sys/kernel/cap1188/sensor1");
    if (!sensor1_in.is_open()) {
        std::cerr << "Could not open /sys/kernel/cap1188/sensor1" << std::endl;
        return -1;
    }

    std::ifstream sensor2_in("/sys/kernel/cap1188/sensor2");
    if (!sensor1_in.is_open()) {
        std::cerr << "Could not open /sys/kernel/cap1188/sensor2" << std::endl;
        return -1;
    }

    std::ifstream sensor3_in("/sys/kernel/cap1188/sensor3");
    if (!sensor1_in.is_open()) {
        std::cerr << "Could not open /sys/kernel/cap1188/sensor3" << std::endl;
        return -1;
    }

    std::ifstream sensor4_in("/sys/kernel/cap1188/sensor4");
    if (!sensor1_in.is_open()) {
        std::cerr << "Could not open /sys/kernel/cap1188/sensor4" << std::endl;
        return -1;
    }

    std::ifstream sensor5_in("/sys/kernel/cap1188/sensor5");
    if (!sensor1_in.is_open()) {
        std::cerr << "Could not open /sys/kernel/cap1188/sensor5" << std::endl;
        return -1;
    }

    std::ifstream sensor6_in("/sys/kernel/cap1188/sensor6");
    if (!sensor1_in.is_open()) {
        std::cerr << "Could not open /sys/kernel/cap1188/sensor6" << std::endl;
        return -1;
    }

    std::ifstream sensor7_in("/sys/kernel/cap1188/sensor7");
    if (!sensor1_in.is_open()) {
        std::cerr << "Could not open /sys/kernel/cap1188/sensor7" << std::endl;
        return -1;
    }

    std::ifstream sensor8_in("/sys/kernel/cap1188/sensor8");
    if (!sensor1_in.is_open()) {
        std::cerr << "Could not open /sys/kernel/cap1188/sensor8" << std::endl;
        return -1;
    }




        sleep(1);
        std::string value{};
        std::string value2{};
        std::string value3{};
        std::string value4{};
        std::string value5{};
        std::string value6{};
        std::string value7{};
        std::string value8{};
        cap1188_in.read(wow, sizeof(wow));
        std::getline(sensor1_in, value);
        std::cout << "Value read in from sensor 1: " << value << std::endl;
        std::getline(sensor2_in, value3);
        std::cout << "Value read in from sensor 2: " << value2 << std::endl;
        std::getline(sensor3_in, value3);
        std::cout << "Value read in from sensor 3: " << value3 << std::endl;
        std::getline(sensor4_in, value);
        std::cout << "Value read in from sensor 4: " << value4 << std::endl;
        std::getline(sensor5_in, value5);
        std::cout << "Value read in from sensor 5: " << value5 << std::endl;
        std::getline(sensor6_in, value6);
        std::cout << "Value read in from sensor 6: " << value6 << std::endl;
        std::getline(sensor7_in, value7);
        std::cout << "Value read in from sensor 7: " << value7 << std::endl;
        std::getline(sensor8_in, value8);
        std::cout << "Value read in from sensor 8: " << value8 << std::endl;
    

    cap1188_in.close();
    sensor1_in.close();
    sensor2_in.close();
    sensor3_in.close();
    sensor4_in.close();
    sensor5_in.close();
    sensor6_in.close();
    sensor7_in.close();
    sensor8_in.close();
    }
    return 0;
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