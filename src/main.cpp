#include "Application.h"
#include "spdlog/sinks/basic_file_sink.h"

const std::string timeFormat = "%H:%M:%S";
const std::string dateFormat = ":%Y-%m-%d";

int main(int argc, char* argv[]) {
	spdlog::set_pattern(fmt::format("[{}] %^[%l]%$: %v", timeFormat));

	int logNumber = 1;
	auto logger = spdlog::basic_logger_mt("logger", fmt::format("logs/{}-{}.txt", fmt::format(dateFormat, std::chrono::system_clock::now()), logNumber));
	spdlog::set_default_logger(logger);

	try {
		Application app;
		return app.Start();
	}
	catch (const std::exception& e) {
		spdlog::critical("A fatal exception occurred and caused the application to abort: {}", e.what());
	}
	catch (...){
		spdlog::critical("A unknown fatal exception occurred and caused the application to abort");
	}
}
