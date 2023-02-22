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
#include <thread>

#include <stdio.h>
#include <myo/myo.hpp>


//code for WX
#define WXUSINGDLL
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//Global variables:
wxString test_string = "a";
const int data_point_amount = 500;
const int margin = 100;
int graph_counter = 0;
std::array<int8_t, data_point_amount> graph_emg_1 = { 0 };
std::array<int8_t, data_point_amount> graph_emg_2 = { 0 };
std::array<int8_t, data_point_amount> graph_emg_3 = { 0 };
std::array<int8_t, data_point_amount> graph_emg_4 = { 0 };
std::array<int8_t, data_point_amount> graph_emg_5 = { 0 };
std::array<int8_t, data_point_amount> graph_emg_6 = { 0 };
std::array<int8_t, data_point_amount> graph_emg_7 = { 0 };
std::array<int8_t, data_point_amount> graph_emg_8 = { 0 };

//Global functions:
void stepGraphCounter(){
    if (graph_counter < data_point_amount - 1) {
        graph_counter += 1;
    }
    else {
        graph_counter = 0;
    }
}

void setGraphEmg(std::array<int8_t, 8> value) {
        graph_emg_1[graph_counter] = value[0];
        graph_emg_2[graph_counter] = value[1];
        graph_emg_3[graph_counter] = value[2];
        graph_emg_4[graph_counter] = value[3];
        graph_emg_5[graph_counter] = value[4];
        graph_emg_6[graph_counter] = value[5];
        graph_emg_7[graph_counter] = value[6];
        graph_emg_8[graph_counter] = value[7];
}


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    void setString(wxString input);
};

class MyFrame : public wxFrame
{
    wxTimer* m_timer;
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, const wxString& statusText);
private:
    void OnTimer(wxTimerEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_PAINT(MyFrame::OnPaint)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP_NO_MAIN(MyApp);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("EMG Graph", wxPoint(50, 50), wxSize(450, 340), "graphing");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, const wxString& statusText)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText(statusText);

    m_timer = new wxTimer(this, wxID_ANY);
    m_timer->Start(20); 
    Bind(wxEVT_TIMER, &MyFrame::OnTimer, this, m_timer->GetId());
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets' Hello world sample",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnPaint(wxPaintEvent& event) {
    wxPen emg1(wxColour(255, 0, 0));
    wxPen emg2(wxColour(0, 150, 0));
    wxPen emg3(wxColour(0, 0, 150));
    wxPen emg4(wxColour(255, 150, 0));
    wxPen emg5(wxColour(0, 150, 150));
    wxPen emg6(wxColour(255, 0, 150));
    wxPen emg7(wxColour(100, 150, 0));
    wxPen emg8(wxColour(0, 150, 50));
    wxPaintDC dc(this);

    dc.SetPen(emg1);

    for (int i = 0; i < 15; i++) {
        if (graph_counter - i > 0) {
            dc.DrawLine(margin + (graph_counter - i) * 2, -(graph_emg_1[graph_counter - i]) + 256, margin + (graph_counter - i) * 2 - 1, -(graph_emg_1[graph_counter - i - 1]) + 256);
        }
    }

    dc.SetPen(emg2);

    for (int i = 0; i < 15; i++) {
        if (graph_counter - i > 0) {
            dc.DrawLine(margin + (graph_counter - i) * 2, -(graph_emg_2[graph_counter - i]) + 256, margin + (graph_counter - i) * 2 - 1, -(graph_emg_2[graph_counter - i - 1]) + 256);
        }
    }

    dc.SetPen(emg3);

    for (int i = 0; i < 15; i++) {
        if (graph_counter - i > 0) {
            dc.DrawLine(margin + (graph_counter - i) * 2, -(graph_emg_3[graph_counter - i]) + 256, margin + (graph_counter - i) * 2 - 1, -(graph_emg_3[graph_counter - i - 1]) + 256);
        }
    }

    dc.SetPen(emg4);

    for (int i = 0; i < 15; i++) {
        if (graph_counter - i > 0) {
            dc.DrawLine(margin + (graph_counter - i) * 2, -(graph_emg_4[graph_counter - i]) + 256, margin + (graph_counter - i) * 2 - 1, -(graph_emg_4[graph_counter - i - 1]) + 256);
        }
    }

    dc.SetPen(emg5);

    for (int i = 0; i < 15; i++) {
        if (graph_counter - i > 0) {
            dc.DrawLine(margin + (graph_counter - i) * 2, -(graph_emg_5[graph_counter - i]) + 256, margin + (graph_counter - i) * 2 - 1, -(graph_emg_5[graph_counter - i - 1]) + 256);
        }
    }
    
    dc.SetPen(emg6);

    for (int i = 0; i < 15; i++) {
        if (graph_counter - i > 0) {
            dc.DrawLine(margin + (graph_counter - i) * 2, -(graph_emg_6[graph_counter - i]) + 256, margin + (graph_counter - i) * 2 - 1, -(graph_emg_6[graph_counter - i - 1]) + 256);
        }
    }

    dc.SetPen(emg7);

    for (int i = 0; i < 15; i++) {
        if (graph_counter - i > 0) {
            dc.DrawLine(margin + (graph_counter - i) * 2, -(graph_emg_7[graph_counter - i]) + 256, margin + (graph_counter - i) * 2 - 1, -(graph_emg_7[graph_counter - i - 1]) + 256);
        }
    }

    dc.SetPen(emg8);

    for (int i = 0; i < 15; i++) {
        if (graph_counter - i > 0) {
            dc.DrawLine(margin + (graph_counter - i) * 2, -(graph_emg_8[graph_counter - i]) + 256, margin + (graph_counter - i) * 2 - 1, -(graph_emg_8[graph_counter - i - 1]) + 256);
        }
    }
    
}

void MyFrame::OnTimer(wxTimerEvent& event) {
    const wxRect rect1 = wxRect(margin + ((graph_counter - 10) * 2), 128, 42 * 2, 256);
    const wxRect* pRect1 = &rect1;
    Refresh(true, pRect1);
}

//myo code starts here
class DataCollector : public myo::DeviceListener {
public:

    void addMarker(int type) {
        if (type == 1) {
            marker_amount[0] += 1;
        }
        if (type == 2) {
            marker_amount[1] += 1;
        }
    }

    void createCsvAcc(std::string filename)
    {
        //Tells DataCollector to create csv file with filename 
        //and remember filename as save location for accelerometer data.
        //Note filename also inclues reletive path to file
        ACCfilename = filename;
        std::fstream ACCfile;
        ACCfile.open(ACCfilename, std::ios_base::out);
        if (!ACCfile.is_open()) {
            std::cout << "failed to create " << ACCfilename << '\n';
            ACC_saving = false;
        }
        else {
            ACCfile << "Timestamp, Acceleration x, Acceleration y, Acceleration z, Marker" << std::endl;
            std::cout << ACCfilename << " created" << std::endl;
        }
    }

    void createCsvEmg(std::string filename)
    {
        //Tells DataCollector to create csv file with filename 
        //and remember filename as save location for emg data.
        //Note filename also inclues reletive path to file
        EMGfilename = filename;
        std::fstream EMGfile;
        EMGfile.open(EMGfilename, std::ios_base::out);
        if (!EMGfile.is_open()) {
            std::cout << "failed to create " << EMGfilename << '\n';
            EMG_saving = false;
        }
        else {
            EMGfile << "Timestamp, Electrode 1, Electrode 2, Electrode 3, Electrode 4, Electrode 5, Electrode 6, Electrode 7, Electrode 8, Marker" << std::endl;
            std::cout << EMGfilename << " created" << std::endl;
        }
    }

    void createCsvGyro(std::string filename)
    {
        //Tells DataCollector to create csv file with filename 
        //and remember filename as save location for gyroscope data.
        //Note filename also inclues reletive path to file
        Gyrofilename = filename;
        std::fstream Gyrofile;
        Gyrofile.open(Gyrofilename, std::ios_base::out);
        if (!Gyrofile.is_open()) {
            std::cout << "failed to create " << Gyrofilename << '\n';
            gyro_saving = false;
        }
        else {
            Gyrofile << "Timestamp, Rotation x, Rotation y, Rotation z, Marker" << std::endl;
            std::cout << Gyrofilename << " created" << std::endl;
        }
    }

    void createCsvOrient(std::string filename)
    {
        //Tells DataCollector to create csv file with filename 
        //and remember filename as save location for orientation data.
        //Note filename also inclues reletive path to file
        Orientfilename = filename;
        std::fstream Orientfile;
        Orientfile.open(Orientfilename, std::ios_base::out);
        if (!Orientfile.is_open()) {
            std::cout << "failed to create " << Orientfilename << '\n';
            orient_saving = false;
        }
        else {
            Orientfile << "Timestamp, Angle x, Angle y, Angle z, Marker" << std::endl;
            std::cout << Orientfilename << " created" << std::endl;
        }
    }

    //onConnect() is called each time a pair myo is connected via Myo Connect
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
        std::cout << "Myo Disconnected!";
    }

    // onAccelerometerData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
    void onAccelerometerData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& accel)
    {
        //Prevents function from recording data before EMG data is recieved.
        //As timestamp is calculated using onEmgData(), this prevents multiple 0 timestamps at start.
        if (collection_start == false) {
            return;
        }

        //Adds the data point timestamp as caluclated by onEmgData() to the ACC_data container for accelerometor data
        ACC_data.append(std::to_string(timestamp_calculated) + ",");

        //Notes how many data points had been recored, this informs program of when to save data
        ACC_recorded += 1;

        //Converts the pointers to data provided by SDK into an array for easier manipulation
        accelSamples[0] = accel.x();
        accelSamples[1] = accel.y();
        accelSamples[2] = accel.z();

        //Adds marker if number of marker required larger than number of markers added
        for (size_t i = 0; i < accelSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(accelSamples[i]);
            std::string accString = oss.str();
            ACC_data.append(accString + ",");
        }
        if (ACC_marker[0] != marker_amount[0]) {
            ACC_data.append("1");
            ACC_marker[0] += 1;
        }
        else {
            if (ACC_marker[1] != marker_amount[1]) {
                ACC_data.append("2");
                ACC_marker[1] += 1;
            }
            else {
                ACC_data.append("0");
            }
        }
        ACC_data.append("\n");

        //Saves the data in ACC_data into the selected CSV file
        //Saving only occures every 50 data points for performance reasons
        if (ACC_recorded > 50) {
            std::fstream ACC_out;
            ACC_out.open(ACCfilename, std::ios_base::app);
            if (!ACC_out.is_open()) {
                ACC_saving = false;
            }
            else {
                ACC_out << ACC_data;
            }
            //Resets the counter and emties the temporary container for accelerometer data
            ACC_recorded = 0;
            ACC_data = "";
        }

    }

    // onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enable
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
    {
        //Allows data collection to start onece emg data is recieved
        if (collection_start == false) {
            collection_start = true;
        }

        //Data correction mechenism - functionally similar as the one used in MyoMex
        if (EMG_timestamp_repeat == true) {
            //A quirk of myo SDK is it sends pairs of data with same system timestamps
            //If a data point does not come with it's pair, them we know a data point is missing
            if (EMG_last_timestamp != timestamp) {
                //Duplicates the known data point in the pair as placeholder for the unknown datapoint
                EMG_data.append(std::to_string(timestamp_calculated) + ",");
                timestamp_calculated += 5;
                EMG_data.append(EMG_tmp);
                //Records that above duplication had occured, this info will be made known to user in print() 
                lines_duplicated += 1;
            }
            //Once the system timestamp had repeated once, we expect next data point to have different timestamp
            EMG_timestamp_repeat = false;
        }
        else {
            //If last timestamp is not expected to repeat, then we expect next timestamp to repeat
            EMG_timestamp_repeat = true;

            //Records current system timestamp so we can compare the next system timestamp with it
            EMG_last_timestamp = timestamp;
        }

        //The recorded timestamp is calculated, we assume emg data is actually recorded in perfect 5 ms intervals
        //and all inperfections in system timestamp is due to how system records time
        //The same method is also used in MyoMex
        EMG_data.append(std::to_string(timestamp_calculated) + ",");
        timestamp_calculated += 5;

        //Notes how many emg data points had been recored, this informs program of when to save data
        EMG_recorded += 1;

        //EMG_tmp holds emg values from last data point for data correction mechenism
        //Data from last time onEmgData() was called is emptied here to recieve current data for next cycle
        EMG_tmp = "";

        //Converts the pointers to emg data provided by SDK into an array for easier manipulation
        for (int i = 0; i < 8; i++) {
            emgSamples[i] = emg[i];
        }

        stepGraphCounter();
        setGraphEmg(emgSamples);

        //Converts emgSamples array into a string with CSV compatible formatting stored in EMG_tmp
        for (size_t i = 0; i < emgSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(emgSamples[i]);
            std::string emgString = oss.str();
            EMG_tmp.append(emgString + ',');
        }

        //Adds marker if number of marker required larger than number of markers added
        if (EMG_marker[0] != marker_amount[0]) {
            EMG_tmp.append("1");
            EMG_marker[0] += 1;
        }
        else {
            if (EMG_marker[1] != marker_amount[1]) {
                EMG_tmp.append("2");
                EMG_marker[1] += 1;
            }
            else {
                EMG_tmp.append("0");
            }
        }
        EMG_tmp.append("\n");

        //Adds this data point as a new line to EMG_data, which records all string data awaiting output to CSV
        EMG_data.append(EMG_tmp);

        //Saves the data in EMG_data into the selected CSV file
        //Saving only occures every 200 data points for performance reasons
        if (EMG_recorded > 200) {
            std::fstream EMG_out;
            EMG_out.open(EMGfilename, std::ios_base::app);
            if (!EMG_out.is_open()) {
                EMG_saving = false;
            }
            else {
                EMG_out << EMG_data;
            }
            //Resets the counter and emties the temporary container for emg data
            EMG_recorded = 0;
            EMG_data = "";
        }
    }

    void onGyroscopeData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& gyro)
    {
        //Prevents function from recording data before EMG data is recieved.
        //As timestamp is calculated using onEmgData(), this prevents multiple 0 timestamps at start.
        if (collection_start == false) {
            return;
        }

        //Adds the data point timestamp as caluclated by onEmgData() to the ACC_data container for gyroscope data
        gyro_data.append(std::to_string(timestamp_calculated) + ",");

        //Notes how many data points had been recored, this informs program of when to save data
        gyro_recorded += 1;

        //Converts the pointers to data provided by SDK into an array for easier manipulation
        gyroSamples[0] = gyro.x();
        gyroSamples[1] = gyro.y();
        gyroSamples[2] = gyro.z();

        //Converts gyroSamples array into a string with CSV compatible formatting stored in gyro_data container
        for (size_t i = 0; i < gyroSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(gyroSamples[i]);
            std::string gyroString = oss.str();
            gyro_data.append(gyroString + ",");
        }
        //Adds marker if number of marker required larger than number of markers added
        if (gyro_marker[0] != marker_amount[0]) {
            gyro_data.append("1");
            gyro_marker[0] += 1;
        }
        else {
            if (gyro_marker[1] != marker_amount[1]) {
                gyro_data.append("2");
                gyro_marker[1] += 1;
            }
            else {
                gyro_data.append("0");
            }
        }
        gyro_data.append("\n");

        //Saves the data in gyro_data into the selected CSV file
        //Saving only occures every 50 data points recored for performance reasons
        if (gyro_recorded > 50) {
            std::fstream gyro_out;
            gyro_out.open(Gyrofilename, std::ios_base::app);

            if (!gyro_out.is_open()) {
                gyro_saving = false;
            }
            else {
                gyro_out << gyro_data;
            }
            //Resets the counter and emties the temporary container for gyroscope data
            gyro_recorded = 0;
            gyro_data = "";
        }
    }

    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
    {
        //Namespaces for math functions
        using std::atan2;
        using std::asin;
        using std::sqrt;
        using std::max;
        using std::min;

        //Prevents function from recording data before EMG data is recieved.
        //As timestamp is calculated using onEmgData(), this prevents multiple 0 timestamps at start.
        if (collection_start == false) {
            return;
        }

        //Adds the data point timestamp as caluclated by onEmgData() to the ACC_data container for gyroscope data
        orient_data.append(std::to_string(timestamp_calculated) + ",");

        //Notes how many data points had been recored, this informs program of when to save data
        orient_recorded += 1;

        // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
        orientSamples[0] = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
            1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));

        orientSamples[1] = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));

        orientSamples[2] = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
            1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));

        //Converts orientSamples array into a string with CSV compatible formatting stored in orient_data container
        for (size_t i = 0; i < orientSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<float>(orientSamples[i]);
            std::string orientString = oss.str();
            orient_data.append(orientString + ",");
        }
        //Adds marker if number of marker required larger than number of markers added
        if (orient_marker[0] != marker_amount[0]) {
            orient_data.append("1");
            orient_marker[0] += 1;
        }
        else {
            if (orient_marker[1] != marker_amount[1]) {
                orient_data.append("2");
                orient_marker[1] += 1;
            }
            else {
                orient_data.append("0");
            }
        }
        orient_data.append("\n");

        //Saves the data in orient_data into the selected CSV file
        //Saving only occures every 50 data points recored for performance reasons
        if (orient_recorded > 50) {
            std::fstream orient_out;
            orient_out.open(Orientfilename, std::ios_base::app);
            if (!orient_out.is_open()) {
                orient_saving = false;
            }
            else {
                orient_out << orient_data;
            }
            //Resets the counter and emties the temporary container for orientation data
            orient_recorded = 0;
            orient_data = "";
        }
    }

    void print() {
        //Inhibits outputing meaningless data when collection had not started
        if (collection_start == false) {
            return;
        }

        //Deletes last 5 lines of output so data output is not a mess
        for (int i = 0; i < 5; i++) {
            std::cout << "\x1b[1A" << "\x1b[2K";
        }

        //Line for emg data output
        std::cout << "          EMG data:";
        for (size_t i = 0; i < emgSamples.size(); i++) {
            //Outputs data from last time onEmgData() was called
            //Note console output is a snapshot of one particular time point rather than some average over time
            std::ostringstream oss;
            oss << static_cast<float>(emgSamples[i]);
            std::string emgString = oss.str();
            std::cout << '[' << emgString << std::string(4 - emgString.size(), ' ') << ']';
        }

        std::ostringstream oss;
        oss << static_cast<float>(graph_emg_1[1]);
        std::string emgString = oss.str();
        std::cout << emgString;
        std::cout << std::to_string(graph_counter);

        //Informs the user if data saving is occuring correctly
        if (EMG_saving == true) {
            //When data saving is normal, informs the user if data had been modified by correction mechenism
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

        //Adds new line for next row of output
        std::cout << "\n";

        //Line for Accelerometer data output
        std::cout << "Accelerometer data:";
        //Outputs data from last time onAccelerometerData() was called
        for (size_t i = 0; i < accelSamples.size(); i++) {
            //Rounding to provide a neat console output
            float tmp;
            tmp = accelSamples[i] * 1000;
            tmp = round(tmp);
            tmp = tmp / 1000;
            std::string accelString = std::to_string(tmp);
            accelString = accelString.substr(0, accelString.size() - 3);
            std::cout << '[' << accelString << std::string(10 - accelString.size(), ' ') << ']';
        }
        //Informs the user if data saving is occuring correctly
        if (ACC_saving == true) {
            std::cout << "             data saving normal";
        }
        else {
            std::cout << "             ***data saving failed!***";
        }
        //Adds new line for next row of output
        std::cout << "\n";

        //Line for Gyroscope data output
        std::cout << "    Gyroscope data:";
        //Outputs data from last time onGyroscopeData() was called
        for (size_t i = 0; i < gyroSamples.size(); i++) {
            //Rounding to provide a neat console output
            float tmp;
            tmp = gyroSamples[i] * 1000;
            tmp = round(tmp);
            tmp = tmp / 1000;
            std::string gyroString = std::to_string(tmp);
            gyroString = gyroString.substr(0, gyroString.size() - 3);
            std::cout << '[' << gyroString << std::string(10 - gyroString.size(), ' ') << ']';
        }
        //Informs the user if data saving is occuring correctly
        if (gyro_saving == true) {
            std::cout << "             data saving normal";
        }
        else {
            std::cout << "             ***data saving failed!***";
        }
        //Adds new line for next row of output
        std::cout << "\n";

        //Line for Orientation data output
        std::cout << "  Orientation data:";
        for (size_t i = 0; i < orientSamples.size(); i++) {
            //Rounding to provide a neat console output
            float tmp;
            tmp = orientSamples[i] * 1000;
            tmp = round(tmp);
            tmp = tmp / 1000;
            std::string orientString = std::to_string(tmp);
            orientString = orientString.substr(0, orientString.size() - 3);
            std::cout << '[' << orientString << std::string(10 - orientString.size(), ' ') << ']';
        }
        //Informs the user if data saving is occuring correctly
        if (orient_saving == true) {
            std::cout << "             data saving normal";
        }
        else {
            std::cout << "             ***data saving failed!***";
        }
        //Adds new line for next row of output
        std::cout << "\n";

        //Output for time counter
        float output_time;
        float float_time = timestamp_calculated;

        //Converts miliseconds into seconds
        output_time = float_time / 1000;
        std::string output_string = std::to_string(output_time);

        //Outputs the timestamp in seconds with trailing zeros removed
        std::cout << "      Elapsed time:" << output_string.substr(0, output_string.size() - 3) << "\n";

    }

    // Initializing variables
    bool collection_start = false;
    int timestamp_calculated = 0;
    std::array<int, 2> marker_amount = { 0, 0 };

    //Recording accelerometor data
    std::array<float, 3> accelSamples = { 0, 0, 0 };
    std::string ACC_data;
    bool ACC_saving = true;
    int ACC_recorded = 0;
    std::array<int, 2> ACC_marker = { 0, 0 };

    //Recording EMG data
    std::array<int8_t, 8> emgSamples = { 0, 0, 0, 0, 0, 0, 0, 0 };
    std::string EMG_data;
    std::string EMG_tmp;
    uint64_t EMG_last_timestamp = 0;
    bool EMG_saving = true;
    bool EMG_timestamp_repeat = false;
    int EMG_recorded = 0;
    int lines_duplicated = 0;
    std::array<int, 2> EMG_marker = { 0, 0 };

    //Recording gyroscope data
    std::array<float, 3> gyroSamples = { 0, 0, 0 };
    std::string gyro_data;
    bool gyro_saving = true;
    int gyro_recorded = 0;
    std::array<int, 2> gyro_marker = { 0, 0 };

    //Recording orientation data
    std::array<float, 3> orientSamples = { 0, 0, 0 };
    std::string orient_data;
    bool orient_saving = true;
    int orient_recorded = 0;
    std::array<int, 2> orient_marker = { 0, 0 };

    //File names
    std::string ACCfilename;
    std::string EMGfilename;
    std::string Gyrofilename;
    std::string Orientfilename;
};

int main(int argc, char** argv)
{
    std::thread graphThread([&]() {
        wxEntry();
    });
    graphThread.detach();

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

        // Creates the CSV files for data saving, this will overide any existing files
        collector.createCsvAcc("Output/Accelerometer.csv");
        collector.createCsvEmg("Output/EMG.csv");
        collector.createCsvGyro("Output/Gyroscope.csv");
        collector.createCsvOrient("Output/Orientation.csv");

        // Quick and dirty way of preventing previous consol output from deleted by print()
        std::cout << "\n\n\n\n\n";

        // Initializes couter for console output
        int counter = 0;

        // Finally we enter our main loop.
        while (1) {

            test_string = std::to_string(counter);

            // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
            // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
            hub.runOnce(10);

            // Updates the console output using data recieved at this moment 
            // This is only done every 30 cycles of the main loop to improve legibility
            if (counter > 30) {
                collector.print();
                counter = 0;
            }
            counter += 1;
        }


        // If a standard exception occurred, we print out its message and exit.
    }
    catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
}
