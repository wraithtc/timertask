#include <iostream>
#include "timertask.h"

using namespace std;

map<int, string> g_testMap;

int main()
{
    timertask t;
    TASK_DURATION_INFO di = {TASK_DURATION (TIME_INFO (14,23), TIME_INFO (11, 22)),1, 0,0};
    t.AddTask(1 << 2 | 1 << 3 | 1 << 4, di, "wifi");
    t.printTask();
    system("pause");
    return 0;
}