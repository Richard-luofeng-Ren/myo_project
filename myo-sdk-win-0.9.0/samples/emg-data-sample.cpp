// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.

// This sample illustrates how to use EMG data. EMG streaming is only supported for one Myo at a time.

#include <array>
#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <string>

#include <stdio.h>
#include <myo/myo.hpp>

class DataCollector : public myo::DeviceListener {
public:
    // DataCollector()
     //: emgSamples()
     //{
    // }

    void createCsvAcc(std::string filename)
    {
        ACCfilename = filename;
        std::fstream ACCfile;
        ACCfile.open(ACCfilename, std::ios_base::out);
        if (!ACCfile.is_open()) {
            std::cout << "failed to create " << ACCfilename << '\n';
            ACC_saving = false;
        }
        else {
            ACCfile << "Timestamp, Acceleration x, Acceleration y, Acceleration z" << std::endl;
            std::cout << ACCfilename << " created" << std::endl;
        }
    }

    void createCsvEmg(std::string filename)
    {
        EMGfilename = filename;
        std::fstream EMGfile;
        EMGfile.open(EMGfilename, std::ios_base::out);
        if (!EMGfile.is_open()) {
            std::cout << "failed to create " << EMGfilename << '\n';
            EMG_saving = false;
        }
        else {
            EMGfile << "Timestamp, Electrode 1, Electrode 2, Electrode 3, Electrode 4, Electrode 5, Electrode 6, Electrode 7, Electrode 8" << std::endl;
            std::cout << EMGfilename << " created" << std::endl;
        }
    }

    void createCsvGyro(std::string filename)
    {
        Gyrofilename = filename;
        std::fstream Gyrofile;
        Gyrofile.open(Gyrofilename, std::ios_base::out);
        if (!Gyrofile.is_open()) {
            std::cout << "failed to create " << Gyrofilename << '\n';
            gyro_saving = false;
        }
        else {
            Gyrofile << "Timestamp, Rotation x, Rotation y, Rotation z" << std::endl;
            std::cout << Gyrofilename << " created" << std::endl;
        }
    }

    void createCsvOrient(std::string filename)
    {
        Orientfilename = filename;
        std::fstream Orientfile;
        Orientfile.open(Orientfilename, std::ios_base::out);
        if (!Orientfile.is_open()) {
            std::cout << "failed to create " << Orientfilename << '\n';
            orient_saving = false;
        }
        else {
            Orientfile << "Timestamp, Angle x, Angle y, Angle z" << std::endl;
            std::cout << Orientfilename << " created" << std::endl;
        }
    }

    void onConnect(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
    {
        std::cout << "Myo Connection Successful" << '\n';
    }

    // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    void onUnpair(myo::Myo* myo, uint64_t timestamp)
    {
        // We've lost a Myo.
        // Let's clean up some leftover state.
        emgSamples.fill(0);
        accelSamples.fill(0);
    }

    // onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
    void onAccelerometerData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& accel)
    {
        
        if (collection_start == false){
            return;
        }

        ACC_data.append(std::to_string(timestamp_calculated) + ",");

        ACC_recorded += 1;

        accelSamples[0] = accel.x();
        accelSamples[1] = accel.y();
        accelSamples[2] = accel.z();

        for (size_t i = 0; i < accelSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(accelSamples[i]);
            std::string accString = oss.str();
            ACC_data.append(accString + ",");
        }
        ACC_data.pop_back();
        ACC_data.append("\n");

        if (ACC_recorded > 50) {
            std::fstream ACC_out;
            ACC_out.open(ACCfilename, std::ios_base::app);
            if (!ACC_out.is_open()) {
                ACC_saving = false;
            }
            else {
                ACC_out << ACC_data;
            }
            ACC_recorded = 0;
            ACC_data = "";
        }

    }

    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
    {

        if (collection_start == false){
            collection_start = true;
        }

        //Adds timestamps
        if (EMG_timestamp_repeat == true) {
            if (EMG_last_timestamp != timestamp) {
                EMG_data.append(std::to_string(timestamp_calculated) + ",");
                timestamp_calculated += 5;
                EMG_data.append(EMG_tmp);
                lines_duplicated += 1;
            }
            EMG_timestamp_repeat = false;
        }
        else {
            EMG_timestamp_repeat = true;
        }
        EMG_data.append(std::to_string(timestamp_calculated) + ",");
        timestamp_calculated += 5;

        EMG_last_timestamp = timestamp;
        EMG_recorded += 1;

        EMG_tmp = "";

        for (int i = 0; i < 8; i++) {
            emgSamples[i] = emg[i];
        }

        for (size_t i = 0; i < emgSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(emgSamples[i]);
            std::string emgString = oss.str();
            EMG_tmp.append(emgString + ',');
        }
        EMG_tmp.pop_back();
        EMG_tmp.append("\n");
        EMG_data.append(EMG_tmp);


        if (EMG_recorded > 200) {
            std::fstream EMG_out;
            EMG_out.open(EMGfilename, std::ios_base::app);
            if (!EMG_out.is_open()) {
                EMG_saving = false;
            }
            else {
                EMG_out << EMG_data;
                //std::cout << "EMG file saved" << "\n";
            }
            EMG_recorded = 0;
            EMG_data = "";
        }
    }

    void onGyroscopeData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& gyro)
    {

        if (collection_start == false) {
            return;
        }

        gyro_data.append(std::to_string(timestamp_calculated) + ",");

        gyro_recorded += 1;

        gyroSamples[0] = gyro.x();
        gyroSamples[1] = gyro.y();
        gyroSamples[2] = gyro.z();

        for (size_t i = 0; i < gyroSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(gyroSamples[i]);
            std::string gyroString = oss.str();
            gyro_data.append(gyroString + ",");
        }
        gyro_data.pop_back();
        gyro_data.append("\n");

        if (gyro_recorded > 50) {
            std::fstream gyro_out;
            gyro_out.open(Gyrofilename, std::ios_base::app);

            if (!gyro_out.is_open()) {
                gyro_saving = false;
            }
            else {
                gyro_out << gyro_data;
                //std::cout << "Gyroscope file saved" << "\n";
            }

            gyro_recorded = 0;
            gyro_data = "";
        }
    }

    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
    {
        using std::atan2;
        using std::asin;
        using std::sqrt;
        using std::max;
        using std::min;

        if (collection_start == false) {
            return;
        }

        orient_data.append(std::to_string(timestamp_calculated) + ",");

        orient_recorded += 1;

        // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
        orientSamples[0] = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
            1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));

        orientSamples[1] = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));

        orientSamples[2] = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
            1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));

        for (size_t i = 0; i < orientSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(orientSamples[i]);
            std::string orientString = oss.str();
            orient_data.append(orientString + ",");
        }
        orient_data.pop_back();
        orient_data.append("\n");

        if (orient_recorded > 50) {
            std::fstream orient_out;
            orient_out.open(Orientfilename, std::ios_base::app);
            if (!orient_out.is_open()) {
                orient_saving = false;
            }
            else {
                orient_out << orient_data;
            }
            orient_recorded = 0;
            orient_data = "";
        }
    }

    void print() {
        if (collection_start == false) {
            return;
        }
        
        for (int i = 0; i < 5; i++) {
            std::cout << "\x1b[1A" << "\x1b[2K";
        }
        std::cout << "          EMG data:";
        for (size_t i = 0; i < emgSamples.size(); i++) {

            std::ostringstream oss;
            oss << static_cast<float>(emgSamples[i]);
            std::string emgString = oss.str();
            std::cout << '[' << emgString << std::string(4 - emgString.size(), ' ') << ']';
        }
        if (EMG_saving == true) {
            if (lines_duplicated > 0 && EMG_saving == true) {
                std::cout << " " << lines_duplicated << " line(s) of problematic data!";
            }
            else {
                std::cout << " data saving normal";
            }
        }
        else {
            std::cout << " ***data saving failed!***";
        }
        
        std::cout << "\n";

        std::cout << "Accelerometer data:";
        for (size_t i = 0; i < accelSamples.size(); i++) {
            float tmp;
            tmp = accelSamples[i] * 1000;
            tmp = round(tmp);
            tmp = tmp / 1000;
            std::string accelString = std::to_string(tmp);
            accelString = accelString.substr(0, accelString.size() - 3);
            std::cout << '[' << accelString << std::string(10 - accelString.size(), ' ') << ']';
        }
        if (ACC_saving == true) {
            std::cout << "             data saving normal";
        }
        else {
            std::cout << "             ***data saving failed!***";
        }
        std::cout << "\n";

        std::cout << "    Gyroscope data:";
        for (size_t i = 0; i < gyroSamples.size(); i++) {
            float tmp;
            tmp = gyroSamples[i] * 1000;
            tmp = round(tmp);
            tmp = tmp / 1000;
            std::string gyroString = std::to_string(tmp);
            gyroString = gyroString.substr(0, gyroString.size() - 3);
            std::cout << '[' << gyroString << std::string(10 - gyroString.size(), ' ') << ']';
        }
        if (gyro_saving == true) {
            std::cout << "             data saving normal";
        }
        else {
            std::cout << "             ***data saving failed!***";
        }
        std::cout << "\n";

        std::cout << "  Orientation data:";
        for (size_t i = 0; i < orientSamples.size(); i++) {
            float tmp;
            tmp = orientSamples[i] * 1000;
            tmp = round(tmp);
            tmp = tmp / 1000;
            std::string orientString = std::to_string(tmp);
            orientString = orientString.substr(0, orientString.size() - 3);
            std::cout << '[' << orientString << std::string(10 - orientString.size(), ' ') << ']';
        }
        if (orient_saving == true) {
            std::cout << "             data saving normal";
        }
        else {
            std::cout << "             ***data saving failed!***";
        }
        std::cout << "\n";

        float output_time;
        float float_time = timestamp_calculated;

        output_time = float_time / 1000;
        std::string output_string = std::to_string(output_time);

        std::cout << "      Elapsed time:" << output_string.substr(0, output_string.size() - 3) << "\n";
 
    }

    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.

    // Initializing variables

    bool collection_start = false;
    int timestamp_calculated = 0;

    //Recording accelerometor data
    std::array<float, 3> accelSamples = {0, 0, 0};
    std::string ACC_data;
    bool ACC_saving = true;
    int ACC_recorded = 0;

    //Recording EMG data
    std::array<int8_t, 8> emgSamples = {0, 0, 0, 0, 0, 0, 0, 0};
    std::string EMG_data;
    std::string EMG_tmp;
    uint64_t EMG_last_timestamp = 0;
    bool EMG_saving = true;
    bool EMG_timestamp_repeat = false;
    int EMG_recorded = 0;
    int lines_duplicated = 0;

    //Recording gyroscope data
    std::array<float, 3> gyroSamples = { 0, 0, 0 };
    std::string gyro_data;
    bool gyro_saving = true;
    int gyro_recorded = 0;

    //Recording orientation data
    std::array<float, 3> orientSamples = { 0, 0, 0 };
    std::string orient_data;
    bool orient_saving = true;
    int orient_recorded = 0;

    //File names
    std::string ACCfilename;
    std::string EMGfilename;
    std::string Gyrofilename;
    std::string Orientfilename;
};

int main(int argc, char** argv)
{
    // We catch any exceptions that might occur below -- see the catch statement for more details.
    try {

    // First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
    // publishing your application. The Hub provides access to one or more Myos.
    myo::Hub hub("com.example.emg-data-sample");
    
    std::cout << "Attempting to find a Myo..." << std::endl;

    // Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
    // immediately.
    // waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
    // if that fails, the function will return a null pointer.
    myo::Myo* myo = hub.waitForMyo(10000);

    // If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
    if (!myo) {
        throw std::runtime_error("Unable to find a Myo!");
    }

    // We've found a Myo.
    std::cout << "Connected to a Myo armband!" << std::endl << std::endl;

    // Next we enable EMG streaming on the found Myo.
    myo->setStreamEmg(myo::Myo::streamEmgEnabled);

    // Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
    DataCollector collector;

    // Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
    // Hub::run() to send events to all registered device listeners.
    hub.addListener(&collector);

    std::string EMGfilename("EMG.csv");
    std:: fstream file_out;

    collector.createCsvAcc("Output/Accelerometer.csv");
    collector.createCsvEmg("Output/EMG.csv");
    collector.createCsvGyro("Output/Gyroscope.csv");
    collector.createCsvOrient("Output/Orientation.csv");

    std::cout << "\n\n\n\n";

    int counter = 0;

    // Finally we enter our main loop.
    while (1) {

        // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
        // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
        hub.runOnce(10);

        // After processing events, we call the print() member function we defined above to print out the values we've
        // obtained from any events that have occurred.
        if (counter > 30) {
            collector.print();
            counter = 0;
        }

        counter += 1;
     }
  

    // If a standard exception occurred, we print out its message and exit.
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
}
