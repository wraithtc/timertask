#include <iostream>
#include "timertask.h"

using namespace std;

map<int, string> g_testMap;

void wifi_handler(int isIn)
{
    if (isIn)
        cout << "wifi down" << endl;
    else
    {
        cout << "wifi up" << endl;
    }
}

int main()
{
    timertask t;
    TASK_DURATION_INFO di = {TASK_DURATION (TIME_INFO (22,23), TIME_INFO (4, 22)),1, 0,0};
    TASK_DURATION_INFO di2 = {TASK_DURATION (TIME_INFO (11,22), TIME_INFO (22, 33)),1, 0,0};
    t.AddTask(1 << 2 | 1 << 3 | 1 << 4, di, "wifi", wifi_handler);
    t.AddTask(1 << 0 | 1 << 3 | 1 << 5, di2, "wifi", wifi_handler);
    t.printTask();
    t.taskRun();
    system("pause");
    return 0;
}