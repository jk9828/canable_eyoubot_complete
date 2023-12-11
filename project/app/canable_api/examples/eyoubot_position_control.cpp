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
            std::cout << frame; //���������� ���
            //strstr_rd << std::dec << i++ << " " << frame; //�ѹ��� ���
    }
}

#if 1 //for eyoubot planatery motor


int eyoubot_position_control(CanInterface* device, uint8_t id, int position, int speed = 5000)
{
    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };


    int motor_pos[16];

    motor_pos[11] = 0xc93 -100;
    motor_pos[12] = 0x38fe -100;
    motor_pos[13] = 0x9c9b -100;
    motor_pos[14] = 0x3246 -100;
    motor_pos[15] = 0xf38e -100;

    int origin_pos;

    switch (id) {
    case 11:
        origin_pos = motor_pos[id];
    case 12:
        origin_pos = motor_pos[id];
    case 13:
        origin_pos = motor_pos[id];
    case 14:
        origin_pos = motor_pos[id];
    case 15:
        origin_pos = motor_pos[id];
    }



    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    param32 = 1; // position mode

    data[0] = 0x01;
    data[1] = 0x0F;
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    for (int j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "position control mode.\n";


    getchar();


    param32 = origin_pos + position; // postion

    data[0] = 0x01;
    data[1] = 0x0A; // position control mode
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    for (int j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
    }


    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "position = " << std::dec << param32 << std::endl;

    getchar();


    if (position < 0) {
        param32 = 0x00000000 - speed;
    }
    else {
        param32 = speed; // speed 
    }

    

    
    data[0] = 0x01;
    data[1] = 0x09; // speed mode
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    for (int j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }

    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Speed = " << std::dec << param32 << std::endl;


    getchar();
    return 0;
}
#endif
