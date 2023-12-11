
#include "can_api.h"
#include "eyoubot_function.h"
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
    }
}

#if 1



//for eyoubot planatery motor

int main()
{ // for windows you can specify the baudrate to the NewCanDevice function

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
    for (uint32_t j = 11; j <= 15 ; j++)
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


    param32 = 0; // position limit enable

    data[0] = 0x01; // write mode
    data[1] = 0x38; // position limit enable
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    for (int id = 11; id <= 15; id++)
    {
        if (device->writeCanData( id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }


    getchar();
    std::cout << "\nnext\n";

    for (uint8_t id = 11; id <= 15; id++) {
        eyoubot_position_control(device, id, 0, 3000);
    }

    

    getchar();
    std::cout << "\nnext\n";
    for (uint8_t id = 11; id <= 11; id++) {
        eyoubot_position_control(device, id, -65536/4, 3000);
        //eyoubot_get_position(device, id);
    }

    std::cout << "\nnext\n";



    for (uint8_t id = 12; id <= 12; id++) {
       eyoubot_position_control(device, id, 65536 / 8, 3000);
        //eyoubot_get_position(device, id);
    }

    std::cout << "\nnext\n";
    for (uint8_t id = 13; id <= 13; id++) {
        eyoubot_position_control(device, id, 65536 / 24, 2000);
       // eyoubot_get_position(device, id);
    }

    std::cout << "\nnext\n";
    for (uint8_t id = 14; id <= 14; id++) {
        eyoubot_position_control(device, id, 65536 / 12, 2000);
        //eyoubot_get_position(device, id);

    }
    std::cout << "\nnext\n";
    for (uint8_t id = 15; id <= 15; id++) {
        eyoubot_position_control(device, id, 0, 2000);
       // eyoubot_get_position(device, id);
    }
    std::cout << "\nnext\n";
    getchar();


    for (uint8_t id = 11; id <= 11; id++) {
        eyoubot_position_control(device, id, +65536 / 4, 3000);
        //eyoubot_get_position(device, id);

    }

    getchar();

    for (uint8_t id = 15; id <= 15; id++) {
        eyoubot_position_control(device, id, -65536 / 3, 3000);
        // eyoubot_get_position(device, id);
    }

    getchar();

    for (uint8_t id = 11; id <= 11; id++) {
        eyoubot_position_control(device, id, -65536 / 4, 3000);
        //eyoubot_get_position(device, id);

    }

    for (uint8_t id = 15; id <= 15; id++) {
        eyoubot_position_control(device, id, 0, 3000);
        // eyoubot_get_position(device, id);
    }



    getchar();
    std::cout << "\nwarning motor stop!!\n";

    for (uint8_t id = 11; id <= 15; id++) {
        eyoubot_position_control(device, id, 0, 3000);
    }


    getchar();
    std::cout << "\nwarning motor stop!!\n";
    getchar();
    std::cout << "\nwarning motor stop!!\n";
    getchar();
    std::cout << "\nwarning motor stop!!\n";
    getchar();
    std::cout << "\nwarning motor stop!!\n";
    getchar();
    std::cout << "\nwarning motor stop!!\n";
    getchar();
    std::cout << "\nwarning motor stop!!\n";
    getchar();
    std::cout << "\nwarning motor stop!!\n";
    getchar();
    std::cout << "\nwarning motor stop!!\n";
    getchar();
    std::cout << "\nwarning motor stop!!\n";
    getchar();
    std::cout << "\nwarning motor stop!!\n";

    for (uint32_t j = 11; j <= 15; j++)
    {
        uint8_t id = j & 0xFF;
        if (device->writeCanData(id, 6, motor_disable) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }


    std::cout << "motor closed.\n";




    stopCan = true;
    readProc.join();

    device->Close();
    delete device;
}

#endif






















#if 0


//for eyoubot planatery motor

int main()
{ // for windows you can specify the baudrate to the NewCanDevice function

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
    int motor_pos[16];


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
    std::cout << "\nnext\n";

    for (uint8_t id = 11; id <= 15; id++) {

        eyoubot_limit_lower_position(device, id, 0xFA0A1F00);
    }

    getchar();
    std::cout << "\nnext\n";
    for (uint8_t id = 11; id <= 15; id++) {
        eyoubot_limit_upper_position(device, id, 0x05F5E100);
    }

    getchar();
    std::cout << "\nnext\n";
    for (uint8_t id = 11; id <= 15; id++) {
        eyoubot_limit_current(device, id,800);
    }

    getchar();
    std::cout << "\nnext\n";
    for (uint8_t id = 11; id <= 15; id++) {
        eyoubot_limit_speed(device, id, 3000);
    }

    getchar();
    std::cout << "\nnext\n";

    for (uint32_t j = 11; j <= 15; j++)
    {
        uint8_t id = j & 0xFF;
        if (device->writeCanData(id, 6, motor_disable) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }


    std::cout << "motor closed.\n";




    stopCan = true;
    readProc.join();

    device->Close();
    delete device;
}

#endif




















#if 0


//for eyoubot planatery motor

int main()
{ // for windows you can specify the baudrate to the NewCanDevice function

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
    int motor_pos[16];

    motor_pos[11] = 0xde6;
    motor_pos[12] = 0x3e65;
    motor_pos[13] = 0x9d7e;
    motor_pos[14] = 0x3187;
    motor_pos[15] = 0xf661;


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
    std::cout << "\nnext\n";

    for (uint8_t id = 11; id <= 15; id++) {
        eyoubot_get_position(device, id);
    }

    getchar();
    std::cout << "\nnext\n";


    for (uint32_t j = 11; j <= 15; j++)
    {
        uint8_t id = j & 0xFF;
        if (device->writeCanData(id, 6, motor_disable) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }


    std::cout << "motor closed.\n";




    stopCan = true;
    readProc.join();

    device->Close();
    delete device;
}

#endif