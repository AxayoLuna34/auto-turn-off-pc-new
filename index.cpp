#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <fstream>

using namespace std;

void shutdownPC() {
    system("shutdown /s /t 1");
}

void notifyPC() {
    string vbsFileName = "shutdown_notification.vbs";

    ifstream fileCheck(vbsFileName);
    if (!fileCheck.good()) {
        ofstream vbsFile(vbsFileName);
        vbsFile << "Set objShell = CreateObject(\"WScript.Shell\")\n";
        vbsFile << "objShell.Popup \"It is time to shutdown your PC\", 10, \"Notification\", 64";
        vbsFile.close();
        cout << "Plik " << vbsFileName << " was created." << endl;
    } else {
        cout << "Plik " << vbsFileName << " already exists." << endl;
    }
    fileCheck.close();

    system(("start " + vbsFileName).c_str());
}


int main() {
    int option, shutdown_hour, shutdown_minute, notify_hour, notify_minute;

    cout << "Automatic Turn Off PC by AxayoLuna34" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "1 - Turning off the PC at given time" << endl;
    cout << "2 - Displaying message at a set time" << endl;

    cout << "Select Options (1/2): ";
    cin >> option;

    if (option == 1) {
        cout << "Enter Shutdown Time (0-23): ";
        cin >> shutdown_hour;
        cout << "Enter Shutdown Minute (0-59): ";
        cin >> shutdown_minute;

        cout << "System will be shutdown in " 
             << shutdown_hour << ":" << (shutdown_minute < 10 ? "0" : "") << shutdown_minute << endl;

        while (true) {
            time_t now = time(0);
            tm *ltm = localtime(&now);

            if (ltm->tm_hour == shutdown_hour && ltm->tm_min == shutdown_minute) {
                cout << "The computer is shutting down..." << endl;
                shutdownPC();
                break;
            }

            this_thread::sleep_for(chrono::seconds(1));
        }
    } 
    else if (option == 2) {
        cout << "Enter Notify Time (0-23): ";
        cin >> notify_hour;
        cout << "Enter Notify Minute (0-59): ";
        cin >> notify_minute;

        cout << "The notify will be showed in " 
             << notify_hour << ":" << (notify_minute < 10 ? "0" : "") << notify_minute << endl;

        while (true) {
            time_t now = time(0);
            tm *ltm = localtime(&now);

            if (ltm->tm_hour == notify_hour && ltm->tm_min == notify_minute) {
                notifyPC();
                break;
            }

            this_thread::sleep_for(chrono::seconds(1));
        }
    } 
    else {
        cout << "There is no such option, please type 1 or 2" << endl;
    }
    return 0;
}