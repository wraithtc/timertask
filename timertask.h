#include <map>
#include <list>

using namespace std;

typedef enum {
    TASK_TYPE_WIFI_UP = 0,
    TASK_TYPE_WIFI_DOWN,
    TASK_TYPE_REBOOT
} TASK_TYPE_E;

typedef pair<int, int> TIME_INFO;
typedef pair<TIME_INFO, TIME_INFO> TASK_DURATION;
typedef struct{
    TASK_DURATION duration;
    int enable;
    int taskId;
    int day;
} TASK_DURATION_INFO;

typedef list<TASK_DURATION_INFO> TIME_DURATION_LIST;
typedef map<string, TIME_DURATION_LIST> TIMER_TASK_INFO;




class timertask
{
    private:
      TIMER_TASK_INFO taskInfo;
      int addToUci();
      int timeCompare(TIME_INFO t1, TIME_INFO t2);

    public:
      int AddTask(int day, TASK_DURATION_INFO &taskDurationInfo, string taskType);
      int DelTask(int day, TIME_INFO timeInfo, TASK_TYPE_E taskType);
      int EditTask(int day, TIME_INFO timeInfo, TASK_TYPE_E taskType);
      void printTask();

};