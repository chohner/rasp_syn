#include <iostream>
#include <thread>      // std::thread
#include <sys/types.h> // open
#include <sys/stat.h>  // open
#include <fcntl.h>     // open
#include <sys/ioctl.h> // control
#include <unistd.h>    // read/write usleep
#include <chrono>      // timer
#include <stdlib.h>    // exit
#include <inttypes.h>  // uint8_t, etc
#include <linux/i2c-dev.h> // I2C bus definitions
#include <cmath>

//Global Potis
#include "potis.h"
Potis potis;

using namespace std;

int fd;
// adress with addr=GND : 0x48
int ads_address = 0x48;
float VPS;
int16_t val;
uint8_t writeBuf[3];
uint8_t readBuf[2];

void setup_ads(){
        //open device on /dev/i2c-1
        if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) {
                cout << "Error: Couldn't open device! " << fd << endl;
                exit (1);
        }

        // connect to ads1115 as i2c slave
        if (ioctl(fd, I2C_SLAVE, ads_address) < 0) {
                cout << "Error: Couldn't find device on address!" << endl;
                exit (1);
        }

        bool continuousMode = true;

        // setup ADS1115
        writeBuf[0] = 0b00000001; // (points to Config register)
        writeBuf[1] = 0b11000101; // bit 15-8 0xD3
        writeBuf[2] = 0b10000011; // bits 7-0  0x85
        if (continuousMode)
                writeBuf[1] = 0b11000100;

        VPS = 2.048 / 32768.0; // volts per step

        // begin conversation
        // track setup time
        std::chrono::high_resolution_clock::time_point start, end;
        start = std::chrono::high_resolution_clock::now();

        if (write(fd, writeBuf, 3) != 3) {
                perror("Write to register 1");
                exit(-1);
        }

        if (!continuousMode) {
                // wait for bit 15 (1 : ready)
                while ((writeBuf[0] & 0x80) == 0) {
                        if (read(fd, writeBuf, 2) != 2) {
                                perror("Read conversion");
                                exit(-1);
                        }
                }
        } else {
                sleep(1);
        }

        // set pointer to 0
        readBuf[0] = 0;
        if (write(fd, readBuf, 1) != 1) {
                perror("Write register select");
                exit(-1);
        }

        cout << "ADS1115 Setup complete" << endl;
        end = std::chrono::high_resolution_clock::now();
        double time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
        cout << "Setup took " << time_elapsed << " miliseconds to execute\n"<< endl;
}

void powerdown_ads(){
        // power down ASD1115
        writeBuf[0] = 1; // config register is 1
        writeBuf[1] = 0b11000101; // bit 15-8 0xC3 single shot on
        writeBuf[2] = 0b10000011; // bits 7-0  0x85
        if (write(fd, writeBuf, 3) != 3) {
                perror("Write to register 1");
                exit (1);
        }
        close(fd);
        cout << "ADS1115 Powerdown complete\n";
}

float read_ads(){
        // read conversion register
        if (read(fd, readBuf, 2) != 2) {
                perror("Read conversion");
                exit(-1);
        }

        float potVal = 0;
        // multiply by 256 then add readBuf[1]
        val = readBuf[0] << 8 | readBuf[1];
        if (val < 0) val = 0;  // LSB sometimes generates very low neg number.

        potVal = val * VPS;
        return potVal;
}

void read_n_values(int n){
        float maxVolt = 2.0;

        for (int i = 0; i < n; ++i) {
                float curVolt = read_ads();
                curVolt = std::round(curVolt * 100) / 100;
                if (curVolt > maxVolt) maxVolt = curVolt;
                float curValue = curVolt / maxVolt;

                potis.setPoti(0, curValue);
                cout << curVolt << " Volt => " << potis.getPoti(0) << endl;
                usleep(10000); // microseconds
        }
}

void read_cont_values(){
        float maxVolt = 2.0;
        float lastVolt = 0.0;

        for(;;) {
                float curVolt = read_ads();
                curVolt = std::round(curVolt * 100) / 100;

                if (curVolt != lastVolt) {
                        lastVolt = curVolt;
                        if (curVolt > maxVolt) maxVolt = curVolt;
                        float curValue = curVolt / maxVolt;

                        potis.setPoti(0, curValue);
                        cout << curVolt << " Volt => " << potis.getPoti(0) << endl;
                        usleep(10000); // microseconds
                }
        }
}



float Potis::getPoti(int potNo){
        float potVal = 0;
        switch (potNo) {
        case 0: potVal = poti0; break;
        case 1: potVal = poti1; break;
        case 2: potVal = poti2; break;
        case 3: potVal = poti3; break;
        default: std::cout<< "Provide poti ID!" << std::endl;
        }
        return potVal;
}

void Potis::setPoti(int potNo, float potVal){
        switch (potNo) {
        case 0: poti0 = potVal; break;
        case 1: poti1 = potVal; break;
        case 2: poti2 = potVal; break;
        case 3: poti3 = potVal; break;
        default: std::cout<< "Provide poti ID!" << std::endl;
        }
}

