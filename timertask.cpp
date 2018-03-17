#include <iostream>
#include <time.h>
#include "timertask.h"

int timertask::AddTask(int day, TASK_DURATION_INFO &taskDurationInfo, string taskType, task_handler handler)
{
    int i = 0;
    TIMER_TASK_INFO::iterator it1 = taskInfo.find(taskType);

    if (timeCompare(taskDurationInfo.duration.first, taskDurationInfo.duration.second) == 0)
    {
        return -1;
    }

    taskToDo[taskType] = handler;

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

int weekDayStrToInt(string weekday)
{
    if (weekday == "Sun")
    {
        return 6;
    }
    else if (weekday == "Sat")
    {
        return 5;
    }
    else if (weekday == "Fri")
    {
        return 4;
    }
    else if (weekday == "Thu")
    {
        return 3;
    }
    else if (weekday == "Wed")
    {
        return 2;
    }
    else if (weekday == "Tue")
    {
        return 1;
    }
    else if (weekday == "Mon")
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void timertask::taskRun()
{
    time_t t = time(0); 
    char tmp[64]; 
    TIMER_TASK_INFO::iterator mapIt;
    int nowHour, nowMin, nowDay;
    char nowDayStr[16];
    int found;
    strftime( tmp, sizeof(tmp), "%H %M %a",localtime(&t) );
    cout << tmp << endl;
    sscanf(tmp, "%d %d %s", &nowHour, &nowMin, nowDayStr);
    nowDay = weekDayStrToInt(nowDayStr);

    for (mapIt = taskInfo.begin(); mapIt != taskInfo.end(); ++mapIt)
    {
        TIME_DURATION_LIST::iterator listIt;
        found = 0;
        for (listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt)
        {
            cout << listIt->day<<"\t"<<listIt->duration.first.first<<":"<<listIt->duration.first.second<<"\t"\
            <<listIt->duration.second.first<<":"<<listIt->duration.second.second<<endl;
            
            if (nowDay == listIt->day)
            {
                int startCompareRet = timeCompare(TIME_INFO(nowHour, nowMin), listIt->duration.first);
                int endCompareRet = timeCompare(TIME_INFO(nowHour, nowMin), listIt->duration.second);

                if (startCompareRet >= 0 && endCompareRet <= 0)
                {
                    taskToDo[mapIt->first](1); //若当前时间在定时任务时间段内，直接执行所需任务，后面时间也不用继续查找
                    found = 1;
                    break;
                }
            }
        }
        //当前时间不在所有时间段内，执行定时任务超时时的动作
        if (!found)
        {
            taskToDo[mapIt->first](0);
        }
        
    }
}
