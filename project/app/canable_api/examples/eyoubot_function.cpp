
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

static std::atomic<bool> stopCan = false;

static std::stringstream strstr_rd;

static void canReadProc(CanInterface* device)
{
    int i = 0;
    while (!stopCan)
    {
        CanFrame frame = device->readCanData(2);
        if (frame.can_dlc != 0)
            std::cout << frame; //순차적으로 출력
    }
}


int eyoubot_baudrate(CanInterface* device, int baudrate) // connected all motor 
{

    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

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


    param32 = baudrate;

    data[0] = 0x01; // write mode
    data[1] = 0x4B; // set bauderate
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    // write bauderate
    for (int j = 1; j <= 1; j++)
    {
        uint8_t id = 0x00;

        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::cout << "\nwrite bauderate.\n";

    getchar();


    param32 = 1;

    data[0] = 0x03; // read mode
    data[1] = 0x4B; // set bauderate
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    // read bauderate
    for (int j = 1; j <= 1; j++)
    {
        uint8_t id = 0x00;

        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "\nread bauderate.\n";

    getchar();


    param32 = 1;

    data[0] = 0x01; // write mode
    data[1] = 0x4D; // setting save
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    // write setting
    for (int j = 1; j <= 1; j++)
    {
        uint8_t id = 0x00;


        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nsetting saved.\n";

    return 0;
}


int eyoubot_cease(CanInterface* device)
{

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    // motor stand-by
    for (uint32_t j = 11; j <= 15; j++)
    {
        uint8_t id = j & 0xFF;
        // set speed mode
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    return 0;
}



int eyoubot_current_control(CanInterface* device, uint8_t id, int current)
{
    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };


    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    getchar();

    param32 = 4;

    data[0] = 0x01;
    data[1] = 0x0F; // current mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\ncurrent mode.\n";

    getchar();

    param32 = current; // current

    data[0] = 0x01;
    data[1] = 0x08; // current control mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "current = " << std::dec << param32 << std::endl;

    getchar();

    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_disable) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor closed.\n";
    return 0;
}



int eyoubot_get_current(CanInterface* device, uint8_t id)
{
    // for windows you can specify the baudrate to the NewCanDevice function

    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    getchar();

    param32 = 1;

    data[0] = 0x03; // read mode
    data[1] = 0x05; // current mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::cout << "\ncurrent : \n";

    getchar();

    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_disable) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    return 0;
}



int eyoubot_get_position(CanInterface* device, uint8_t id)
{
    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    getchar();


    param32 = 1;

    data[0] = 0x03; // read mode
    data[1] = 0x07; // position mode
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    for (int j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "\nmotor position : \n";

    return 0;
}



int eyoubot_get_temperature(CanInterface* device, uint8_t id)
{
    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {

        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    getchar();


    param32 = 1;

    data[0] = 0x03; // read mode
    data[1] = 0x1D; // temperature mode
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    // get temperature
    for (int j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));


    std::cout << "\ntemperature : \n";

    return 0;

}



int eyoubot_get_voltage(CanInterface* device, uint8_t id)
{

    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };


    // motor stand-by
    for (uint32_t j = 11; j <= 15; j++)
    {
        uint8_t id = j & 0xFF;
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    getchar();

    param32 = 1;

    data[0] = 0x03; // read mode
    data[1] = 0x1B; // voltage mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return 0;

}



int eyoubot_id(CanInterface* device, int new_id)
{

    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };


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


    param32 = new_id;

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

    return 0;

}



int eyoubot_limit_current(CanInterface* device, uint8_t id, int current)
{

    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    getchar();

    param32 = 4; // current mode

    data[0] = 0x01; // write mode
    data[1] = 0x0F; //  
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }

    getchar();

    param32 = current; // current limit

    data[0] = 0x01; // write mode
    data[1] = 0x30; // current limit mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::cout << "\ncurrent limit : " << std::dec << param32 << "\n" << std::endl;

    getchar();

    param32 = 1;

    data[0] = 0x03; // read mode
    data[1] = 0x30; // current limit
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    getchar();


    param32 = 1;

    data[0] = 0x01;
    data[1] = 0x4D; // setting save mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::cout << "\nsetting saved.\n";

    return 0;
}




int eyoubot_limit_lower_position(CanInterface* device, uint8_t id, int lower_limit)
{
    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        uint8_t id = j & 0xFF;
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    param32 = 1; // position limit enable

    data[0] = 0x01; // write mode
    data[1] = 0x38; // position limit enable
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::cout << "\nposition limit enable.\n";




    param32 = lower_limit;

    data[0] = 0x01; // write mode
    data[1] = 0x31; // postion lower limit
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::cout << "\nposition lower limit : " << std::dec << param32 / 65536 * 360 << "\n" << std::endl;


    param32 = 1;

    data[0] = 0x03; // read mode
    data[1] = 0x31; // postion lower limit
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return 0;

}




int eyoubot_limit_speed(CanInterface* device, uint8_t id, int speed_limit)
{
    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    param32 = 3; // speed mode

    data[0] = 0x01;
    data[1] = 0x0F; //
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    param32 = speed_limit; // speed limit

    data[0] = 0x01; // write mode
    data[1] = 0x31; // speed limit mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::cout << "\nspeed limit : " << std::dec << param32 << "\n" << std::endl;

    param32 = 1;

    data[0] = 0x03; // read mode
    data[1] = 0x31; // speed limit
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3));

    return 0;
}




int eyoubot_limit_upper_position(CanInterface* device, uint8_t id, int upper_limit)
{

    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    param32 = 1; // position limit enable

    data[0] = 0x01;
    data[1] = 0x38;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "\nposition limit enable.\n";

    param32 = upper_limit;

    data[0] = 0x01;
    data[1] = 0x31; // postion upper limit
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "\nposition upper limit : " << std::dec << param32 / 65536 * 360 << "\n" << std::endl;

    param32 = 1;

    data[0] = 0x03;
    data[1] = 0x31; // postion upper limit
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return 0;

}





int eyoubot_position_control(CanInterface* device, uint8_t id, int position, int speed = 5000)
{
    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };


    int motor_pos[16];

    motor_pos[11] = 0x35c1;

    motor_pos[12] = 0xb30d+ 65536 / 30;
    motor_pos[13] = 0x194f;
    motor_pos[14] = 0x9385;
    motor_pos[15] = 0xdf1c;



    int origin_pos=0;

    switch (id) {
    case 11:
        origin_pos = motor_pos[11];
        std::cout << "11.\n";
        break;
    case 12:
        origin_pos = motor_pos[12];
        std::cout << "12.\n";
        break;
    case 13:
        origin_pos = motor_pos[13];
        std::cout << "13.\n";
        break;
    case 14:
        origin_pos = motor_pos[14];
        std::cout << "14.\n";
        break;
    case 15:
        origin_pos = motor_pos[15];
        std::cout << "15.\n";
        break;
    default:
        origin_pos = 0;
        std::cout << "15.\n";
        break;
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







    std::cout << "movet to" << param32 << "\n";



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


    data[0] = 0x03;
    data[1] = 0x0A; // position control mode
    data[2] = (param32 >> 24) & 0xFF;
    data[3] = (param32 >> 16) & 0xFF;
    data[4] = (param32 >> 8) & 0xFF;
    data[5] = param32 & 0xFF;

    std::cout << int(data[0]) << int(data[1]) << int(data[2]) << int(data[3]) << int(data[4]) << int(data[5]) << std::endl;

    for (int j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, data) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "position = " << std::dec << position << std::endl;







    if (position < 0) {
        param32 = speed;
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


    data[0] = 0x03;
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



    return 0;
}





int eyoubot_speed_control(CanInterface* device, uint8_t id, int speed)
{

    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    param32 = 3;

    data[0] = 0x01;
    data[1] = 0x0F; // speed mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Speed = " << std::dec << param32 << std::endl;

    getchar();

    param32 = speed; // speed

    data[0] = 0x01; // write mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Speed = " << std::dec << param32 << std::endl;

    return 0;
}




int eyoubot_get_speed(CanInterface* device, uint8_t id)
{
    uint8_t data[8];

    int param32 = 0;

    uint8_t motor_enable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_standby[6] = { 0x01, 0x11, 0x00, 0x00, 0x00, 0x01 };
    uint8_t motor_disable[6] = { 0x01, 0x10, 0x00, 0x00, 0x00, 0x00 };

    // motor stand-by
    for (uint32_t j = 1; j <= 1; j++)
    {
        if (device->writeCanData(id, 6, motor_standby) < 0)
        {
            std::cerr << "Error writing to CAN bus.\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    std::cout << "\nmotor stand-by.\n";

    getchar();


    param32 = 1;

    data[0] = 0x03; // read mode
    data[1] = 0x06; // speed mode
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::cout << "\ncurrent : \n";

    return 0;
}