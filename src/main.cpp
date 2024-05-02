#include "Application.h"


int main(int argc, char* argv[]) {
	spdlog::set_pattern("[%T] %^[%l]%$: %v");

	try {
		Application app;
		return app.Start();
	}
	catch (const std::exception& e) {
		spdlog::critical("A fatal exception occurred and caused the application to abort: {}", e.what());
	}
	catch (...){
		spdlog::critical("A fatal exception occurred and caused the application to abort");
	}
}
