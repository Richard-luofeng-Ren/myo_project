project made with Visual Studio 2022, not tested on any other platform.
Myo Connect is required to run this project, because Myo Connect is not actively maintained, it can often get stuck or otherwise fail for no apparent reason.
  - Always check Myo Connect if some weird error occurs
All necessary packages should be included - no building or installation required.

How does data saving occur:
  - Data is always saved as 4 CSV files (EMG, Accelerometer, Gyroscope and Orientation) whenever emg-data.cpp is working
  - Data is saved in the output folder
  - Data from last time emg-data.cpp was run is overwritten when emg-data.cpp runs
      - Change the CSV file names if you want to preserve these files
  - Make sure you close all CSV files before running emg-data.cpp

How to use the real time graphing function:
  - A window displaying the data graph should appear upon running emg-data.cpp 
      - If the window contains no data, make sure the armand is worn on arm before running emg-data.cpp
  - Use 1 - 8 keys on keyboard to toggle which EMG channel you want to see
      - Each channel is represented by a specific colour
      - The display status of each channel is on the top right
      - Note that data from all channels are still recorded even if they are not displayed
  - Use 0 key to clear all channel displays
  - Alternatively the Graph tab on the top left corner can also be used to toggle channel displays

