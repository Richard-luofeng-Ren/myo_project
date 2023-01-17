// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.

// This sample illustrates how to use EMG data. EMG streaming is only supported for one Myo at a time.

#include <array>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <Windows.h>  //<-- disable on linux system
//#include <unistd.h> //<-- enable on linux system


#include <myo/myo.hpp>

class DataCollector : public myo::DeviceListener {
public:
    DataCollector()
    : emgSamples()
    {
    }

    // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    void onUnpair(myo::Myo* myo, uint64_t timestamp)
    {
        // We've lost a Myo.
        // Let's clean up some leftover state.
        emgSamples.fill(0);
    }

    // onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
    {
        for (int i = 0; i < 8; i++) {
            emgSamples[i] = emg[i];
        }
    }

    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.

    // We define this function to print the current values that were updated by the on...() functions above.
    std::string print()
    {
        // Variable for data saving system
        std::string emg_data;

        // Clear the current line on console
        //std::cout << '\r';

        // Print out the EMG data and loads data into emg_data for saving
        for (size_t i = 0; i < emgSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<int>(emgSamples[i]);
            std::string emgString = oss.str();

            emg_data.append(emgString + ',');

            std::cout << '[' << emgString << std::string(4 - emgString.size(), ' ') << ']';
        }

        emg_data.append("\n");

        std::cout << std::flush << '\n';

        return emg_data;
    }

    // The values of this array is set by onEmgData() above.
    std::array<int8_t, 8> emgSamples;
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

    std:: string filename("tmp.csv");
    std:: fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if (!file_out.is_open()) {
        std::cout << "failed to create file" << filename << '\n';
    }
    else { 
        file_out << "EMG Data,\n Timestamp, Electrode 1, Electrode 2, Electrode 3, Electrode 4, Electrode 5, Electrode 6, Electrode 7, Electrode 8" << std::endl;
        std::cout << "tmp.csv created" << std::endl;
    }

    double start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    double timestamp;
    double last_save_time = 0;

    std::string saved_output;

    std::cout << start_time << std::endl;

    // Finally we enter our main loop.
    while (1) {
        std::string temp_output;
        double frame_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - start_time;

        if (frame_time < start_time + 5) {
            std::Sleep();
        }

        // Save file timestamp calculations
        timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - start_time;
        std::cout << timestamp;

        temp_output = std::to_string(timestamp) + ",";
        // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
        // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
        hub.runOnce(1);


        // After processing events, we call the print() member function we defined above to print out the values we've
        // obtained from any events that have occurred.
        temp_output.append(collector.print());

        saved_output.append(temp_output);

        // Save EMG data to specified CSV file
        if (timestamp - last_save_time > 1000) {

            saved_output.pop_back();

            std::fstream file_out;
            file_out.open(filename, std::ios_base::app);
            if (!file_out.is_open()) {
                std::cout << "failed to write" << filename << "\n";
            }
            else {
                file_out << saved_output << std::endl;
                std::cout << "file saved" << "\n";
            }
            last_save_time = timestamp;
            saved_output = "";
        }
    }

    // If a standard exception occurred, we print out its message and exit.
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
}
