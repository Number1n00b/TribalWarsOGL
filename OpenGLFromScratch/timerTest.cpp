#pragma comment(lib, "winmm.lib")

#include <time.h>
#include <iostream>
#include <windows.h>

using std::cout;
using std::endl;
using std::cin;

const int TARGET_FPS = 60;
const double ms_per_frame = 1000.0 / TARGET_FPS;

int main(void) {
    cout << "====== Starting Program ======" << endl;

    double curr_time = 0;
    double prev_time = timeGetTime();
    double dt = 0;
    
    double time_since_last_frame = 0;

    int num_frames = 0;
    while (num_frames < 10) {
        curr_time = timeGetTime();

        //dt here is time per loop
        dt = curr_time - prev_time; 
        prev_time = curr_time;

        cout << "dt: " << dt << " | ";

        time_since_last_frame += dt;

        //Cap FPS and render only when needed.
        if (time_since_last_frame >= ms_per_frame) {
            //Update Physics here.
            cout << "\nFRAME NUM: " << num_frames << endl;

            cout << "time since frame: " << time_since_last_frame << endl;
            cout << "time per frame: " << ms_per_frame << endl;

            //Render here.
            cout << "Rendering." << endl;

            cout << "FPS: " << (double)(1000.0 / time_since_last_frame) << endl;

            time_since_last_frame = 0.0;
            num_frames++;
        }
    }


    cout << "====== Ending Program... ======" << endl;
    cin.get();
    return 0;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}