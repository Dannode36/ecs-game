#include "Application.h"

#define DEBUG_CRTICAL 0
#define DEBUG_ERROR 1
#define DEBUG_WARNING 2
#define DEBUG_INFO 3
#define DEBUG_VERBOSE 4

#define DEBUG_LEVEL DEBUG_VERBOSE

int main()
{
    Application app;
    return app.Start();
}
