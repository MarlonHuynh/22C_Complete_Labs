#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>

using namespace std;

// Custom leak reporting function
int CustomLeakReportHook(int reportType, char* message, int* returnValue) {
    if (reportType == _CRTDBG_LEAK_CHECK_DF && message != nullptr) {
        cout << "Memory leak detected:\n" << message << endl;
    }
    return 0;
}

class MyClass {
public:
    MyClass() {
        data = new int[100];
    }
    ~MyClass() {
        delete[] data;
    }
private:
    int* data;
};

int main() {
    // Enable memory leak detection
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Set custom leak reporting function
    _CrtSetReportHook2(_CRT_RPTHOOK_INSTALL, CustomLeakReportHook);

    // Allocate memory (simulate memory leak)
    MyClass* obj = new MyClass;

#ifdef _MSC_VER
    printf(_CrtDumpMemoryLeaks() ? "Memory Leak using _CrtDumpMemoryLeaks\n" : "No Memory Leak using _CrtDumpMemoryLeaks\n");
#endif

    return 0;
}