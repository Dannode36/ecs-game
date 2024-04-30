#include "Application.h"
#include <util/Logging.h>

int main()
{
	try {
		Application app;
		return app.Start();
	}
	catch (const std::exception& e) {
		LOG_CRITICAL(std::string("A fatal exception occurred: ") + e.what());
	}
	catch (...){
		LOG_CRITICAL("A fatal exception occurred");
	}
}
