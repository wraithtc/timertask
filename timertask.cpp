#include <iostream>
#include "timertask.h"

int timertask::AddTask(int day, TASK_DURATION_INFO &taskDurationInfo, string taskType)
{
    int i = 0;
    TIMER_TASK_INFO::iterator it1 = taskInfo.find(taskType);

    if (timeCompare(taskDurationInfo.duration.first, taskDurationInfo.duration.second) == 0)
    {
        return -1;
    }

    if (it1 == taskInfo.end())
    {
        TIME_DURATION_LIST taskList;
        taskInfo[taskType] = taskList;
    }
    for (i = 0; i < 7; i++)
    {
        if (day & 1 << i)
        {
            if (timeCompare(taskDurationInfo.duration.first, taskDurationInfo.duration.second) == 1)
            {
                TASK_DURATION_INFO t1,t2;
                
                t1.enable = taskDurationInfo.enable;
                t1.taskId = taskDurationInfo.taskId;
                t1.day = i;
                t1.duration.first = taskDurationInfo.duration.first;
                t1.duration.second = pair<int, int> (23, 59);
                t2.enable = taskDurationInfo.enable;
                t2.taskId = taskDurationInfo.taskId;
                t2.day = i+1;
                t2.duration.first = pair<int, int> (0, 0);
                t2.duration.second = taskDurationInfo.duration.second;
                taskInfo[taskType].push_back(t1);
                taskInfo[taskType].push_back(t2);
            }
            else
            {
                TASK_DURATION_INFO t1;
                t1.enable = taskDurationInfo.enable;
                t1.taskId = taskDurationInfo.taskId;
                t1.day = i;
                t1.duration.first = taskDurationInfo.duration.first;
                t1.duration.second = taskDurationInfo.duration.second;
                taskInfo[taskType].push_back(t1);
            }
        }
    }

    return 0;
}

int timertask::timeCompare(TIME_INFO t1, TIME_INFO t2)
{
    if (t1.first > t2.first)
    {
        return 1;
    }
    else if (t1.first < t2.first)
    {
        return -1;
    }
    else
    {
        if (t1.second > t2.second)
        {
            return 1;
        }
        else if (t1.second < t2.second)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}

void timertask::printTask()
{
    TIMER_TASK_INFO::iterator mapIt;

    cout << "Day\tStart\tEnd" << endl;

    for (mapIt = taskInfo.begin(); mapIt != taskInfo.end(); ++mapIt)
    {
        TIME_DURATION_LIST::iterator listIt;
        for (listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt)
        {
            cout << listIt->day<<"\t"<<listIt->duration.first.first<<":"<<listIt->duration.first.second<<"\t"\
            <<listIt->duration.second.first<<":"<<listIt->duration.second.second<<endl;
        }
    }
}
