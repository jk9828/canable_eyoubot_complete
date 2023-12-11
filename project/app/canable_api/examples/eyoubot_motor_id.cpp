// the setting is applied after turn-off and turn-on the motor (not open and close)


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

int main()
{
    // for windows you can specify the baudrate to the NewCanDevice function

    std::stringstream strstr;

    CanInterface* device = NewCanDevice();
    device->Open(0, 1000000);

    // start the read thread
    std::thread readProc(canReadProc, device);

    std::cout << "\nWriting CAN data.\n";

    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };


    // motor open
    for (uint32_t j = 1; j <= 1; j++)
    {
        uint8_t id = 0x00;
        if (device->writeCanData(id, 6, motor_enable) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }

    getchar();

    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        uint8_t id = 0x00;
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    getchar();


    param32 = 10;

    data[0] = 0x01; // write mode
    data[1] = 0x4C; // motor id mode
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    //write motor id
    for (uint32_t j = 1; j <= 1; j++)
    {
        uint8_t id = 0x00;
        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }

    strstr << "Speed = " << std::dec << param32 << std::endl;


    getchar();


    param32 = 1;

    data[0] = 0x01; // write mode
    data[1] = 0x4D; // setting save
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    for (uint32_t j = 1; j <= 1; j++)
    {
        uint8_t id = 0x00;
        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }

    std::cout << "\nsetting saved.\n";


    getchar();

    for (uint32_t j = 1; j <= 1; j++)
    {
        uint8_t id = 0x00;
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

}

#endif
