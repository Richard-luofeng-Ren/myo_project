// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.

// This sample illustrates how to use EMG data. EMG streaming is only supported for one Myo at a time.

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string>

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
            std::cout << "failed to create" << ACCfilename << '\n';
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
            std::cout << "failed to create" << EMGfilename << '\n';
        }
        else {
            EMGfile << "Timestamp, Electrode 1, Electrode 2, Electrode 3, Electrode 4, Electrode 5, Electrode 6, Electrode 7, Electrode 8" << std::endl;
            std::cout << EMGfilename << "created" << std::endl;
        }
    }

    void createCsvGyro(std::string filename) 
    {
        Gyrofilename = filename;
        std::fstream Gyrofile;
        Gyrofile.open(Gyrofilename, std::ios_base::out);
        if (!Gyrofile.is_open()) {
            std::cout << "failed to create" << Gyrofilename << '\n';
        }
        else {
            Gyrofile << "Timestamp, Rotation x, Rotation y, Rotation z" << std::endl;
            std::cout << Gyrofilename << "created" << std::endl;
        }
    }

    void createCsvOrient(std::string filename)
    {
        Orientfilename = filename;
        std::fstream Orientfile;
        Orientfile.open(Orientfilename, std::ios_base::out);
        if (!Orientfile.is_open()) {
            std::cout << "failed to create" << Orientfilename << '\n';
        }
        else {
            Orientfile << "Timestamp, Angle x, Angle y, Angle z" << std::endl;
            std::cout << Orientfilename << "created" << std::endl;
        }
    }

    void onConnect(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
    {
        start_time = timestamp;
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
    void onAccelerometerData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float> & accel)
    {
        std::ostringstream oss;
        oss << static_cast<float>((timestamp - start_time)/1000);
        std::string time_string = oss.str();
        ACC_data.append(time_string + ",");

        ACC_recorded += 1;

        std::cout << ACC_recorded << "\n";

        accelSamples[0] = accel.x();
        accelSamples[1] = accel.y();
        accelSamples[2] = accel.z();

        for (size_t i = 0; i < accelSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(accelSamples[i]);
            std::string accString = oss.str();
            ACC_data.append(accString + ",");
        }

        ACC_data.append("\n");

        if (ACC_recorded > 50) {
            std::fstream ACC_out;
            ACC_out.open(ACCfilename, std::ios_base::app);
            if (!ACC_out.is_open()) {
                std::cout << "failed to write" << ACCfilename << "\n";
            }
            else {
                ACC_out << ACC_data;
                std::cout << "Accelerometer file saved" << "\n";
            }
            ACC_recorded = 0;
            ACC_data = "";
            std::cout << ACCfilename << time_string << '\n';
        }

    }

    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t * emg)
    {

        std::ostringstream oss;
        oss << static_cast<float>((timestamp - start_time) / 1000);
        //oss << static_cast<double>(timestamp);
        //std::cout << timestamp;
        std::string time_string = oss.str();
        EMG_data.append(time_string + ",");

        EMG_recorded += 1;

        for (int i = 0; i < 8; i++) {
            emgSamples[i] = emg[i];
        }

        for (size_t i = 0; i < emgSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(emgSamples[i]);
            std::string emgString = oss.str();

            EMG_data.append(emgString + ',');
        }

        EMG_data.append("\n");

        if (EMG_recorded > 200) {
            std::fstream EMG_out;
            EMG_out.open(EMGfilename, std::ios_base::app);
            if (!EMG_out.is_open()) {
                std::cout << "failed to write" << EMGfilename << "\n";
            }
            else {
                EMG_out << EMG_data;
                std::cout << "EMG file saved" << "\n";
            }
            EMG_recorded = 0;
            EMG_data = "";
        }

    }

    void onGyroscopeData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& gyro)
    {
        std::ostringstream oss;
        oss << static_cast<float>((timestamp - start_time) / 1000);
        std::string time_string = oss.str();
        gyro_data.append(time_string + ",");

        gyro_recorded += 1;

        std::cout << gyro_recorded << "\n";

        gyroSamples[0] = gyro.x();
        gyroSamples[1] = gyro.y();
        gyroSamples[2] = gyro.z();

        for (size_t i = 0; i < gyroSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(gyroSamples[i]);
            std::string gyroString = oss.str();
            gyro_data.append(gyroString + ",");
        }

        gyro_data.append("\n");

        if (gyro_recorded > 50) {
            std::fstream gyro_out;
            gyro_out.open(Gyrofilename, std::ios_base::app);

            if (!gyro_out.is_open()) {
                std::cout << "failed to write" << Gyrofilename << "\n";
            }
            else {
                gyro_out << gyro_data;
                std::cout << "Gyroscope file saved" << "\n";
            }

            gyro_recorded = 0;
            gyro_data = "";
            std::cout << "gyro data:" << time_string << '\n';
        }
    }

    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
    {   
        using std::atan2;
        using std::asin;
        using std::sqrt;
        using std::max;
        using std::min;

        std::ostringstream oss;
        oss << static_cast<float>((timestamp - start_time) / 1000);
        std::string time_string = oss.str();
        orient_data.append(time_string + ",");

        orient_recorded += 1;

        std::cout << orient_recorded << "\n";

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

        orient_data.append("\n");

        if (orient_recorded > 50) {
            std::fstream orient_out;
            orient_out.open(Orientfilename, std::ios_base::app);
            if (!orient_out.is_open()) {
                std::cout << "failed to write" << Orientfilename << "\n";
            }
            else {
                orient_out << orient_data;
                std::cout << "Orientation file saved" << "\n";
            }
            orient_recorded = 0;
            orient_data = "";
            std::cout << "orientation data:" << time_string << '\n';
        }
    }

    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.

    // We define this function to print the current values that were updated by the on...() functions above.
    void print()
    {
        // Clear the current line on console
        //std::cout << '\r';

        // Print out the EMG data and loads data into emg_data for saving
        for (size_t i = 0; i < emgSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(emgSamples[i]);
            std::string emgString = oss.str();

            std::cout << '[' << emgString << std::string(4 - emgString.size(), ' ') << ']';
        }

        std::cout << std::flush << '\n';
    }

    // Initializing variables

    //time calcs
    std::uint64_t start_time;

    //Recording accelerometor data
    std::array<float, 3> accelSamples;
    std::string ACC_data;
    int ACC_recorded = 0;

    //Recording EMG data
    std::array<int8_t, 8> emgSamples;
    std::string EMG_data;
    int EMG_recorded = 0;

    //Recording gyroscope data
    std::array<float, 3> gyroSamples;
    std::string gyro_data;
    int gyro_recorded = 0;

    //Recording orientation data
    std::array<float, 3> orientSamples;
    std::string orient_data;
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

    // Finally we enter our main loop.
    while (1) { 

        // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
        // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
        hub.runOnce(10);


        // After processing events, we call the print() member function we defined above to print out the values we've
        // obtained from any events that have occurred.
        collector.print();

     }
  

    // If a standard exception occurred, we print out its message and exit.
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
}
