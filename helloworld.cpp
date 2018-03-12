#include <iostream>
#include <stdio.h>
#include <map>

using namespace std;

map<int, string> g_testMap;

int main()
{
    g_testMap[1] = "hello";
    g_testMap[2] = "world";
    cout << g_testMap[1] << " " << g_testMap[2] << endl;
    system("pause");
    return 0;
}