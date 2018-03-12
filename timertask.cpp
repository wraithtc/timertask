#include <map>

using namespace std;

typedef enum {
    TASK_TYPE_WIFI_UP = 0,
    TASK_TYPE_WIFI_DOWN,
    TASK_TYPE_REBOOT
} TASK_TYPE_E;

typedef struct{
    int startHour;
    int startMin;
    int endHour;
    int endMin;
    int weedDay;
    TASK_TYPE_E taskType;
    int enable;
} TASK_INFO;

class timertask
{
    private:
        TASK_INFO taskInfo;
        int addToUci();

    public:
      int AddTask(int day, TIME_INFO timeInfo, TASK_TYPE_E taskType);
      int DelTask(int day, TIME_INFO timeInfo, TASK_TYPE_E taskType);
      int EditTask(int day, TIME_INFO timeInfo, TASK_TYPE_E taskType);
}