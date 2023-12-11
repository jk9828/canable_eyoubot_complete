#include "can_api.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <atomic>

#ifndef PER
#define GREAT 1
#define PER GREAT
#endif

std::atomic<bool> stopCan = false;

std::stringstream strstr_rd;

void canReadProc(CanInterface* device)
{
    int i = 0;
    while (!stopCan)
    {
        CanFrame frame = device->readCanData(2);
        if (frame.can_dlc != 0)
            std::cout << frame; //순차적으로 출력
            //strstr_rd << std::dec << i++ << " " << frame; //한번에 출력
    }
}

#if 1 //for eyoubot planatery motor

int eyoubot_speed_cotrol()
{
    // for windows you can specify the baudrate to the NewCanDevice function

    std::stringstream strstr;

    CanInterface* device = NewCanDevice();
    device->Open(0, 1000000);

    // start the read thread
    std::thread readProc(canReadProc, device);

    std::cout << "Writing CAN data.\n";

    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };


    // motor open
    for (uint32_t j = 11; j <= 15; j++)
    {
        uint8_t id = j & 0xFF;
        // set speed mode
        if (device->writeCanData(id, 6, motor_enable) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "motor opened.\n";

    getchar();

    param32 = 3;

    data[0] = 0x01;
    data[1] = 0x0F; // speed mode
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    for (int j = 11; j <= 15; j++)
    {
        uint8_t id = j & 0xFF;

        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    strstr << "Speed = " << std::dec << param32 << std::endl;

    getchar();

    param32 = 10000; // speed

    data[0] = 0x01; // write mode
    data[1] = 0x09; // speed mode
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    for (int j = 11; j <= 15; j++)
    {
        uint8_t id = j & 0xFF;

        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    strstr << "Speed = " << std::dec << param32 << std::endl;

    getchar();

    for (uint32_t j = 11; j <= 15; j++)
    {
        uint8_t id = j & 0xFF;
        if (device->writeCanData(id, 6, motor_disable) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor closed.\n";


    stopCan = true;
    readProc.join();

    device->Close();
    delete device;

    return 0;
}

#endif
