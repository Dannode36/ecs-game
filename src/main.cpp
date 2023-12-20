#include <iostream>
#include <thread>
#include "Application.h"

int main()
{
    Application app;

    ////Loading Animation
    //for (size_t i = 0; i < 3; i++)
    //{
    //    std::cout << "2D Game Engine is starting   \r" << std::flush;
    //    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    //    std::cout << "2D Game Engine is starting.\r" << std::flush;
    //    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    //    std::cout << "2D Game Engine is starting..\r" << std::flush;
    //    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    //    std::cout << "2D Game Engine is starting...\r" << std::flush;
    //    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    //}
    //std::cout << std::endl;

    app.Start();
}
