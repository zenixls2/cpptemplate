#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <build.hpp>
#include <exception>
#include <csignal>
#include <iostream>
#include <cstdlib>

std::shared_ptr<spdlog::logger> logger;

void signal_handler([[gnu::unused]] int signal) {
    if (logger) logger->flush();
}

int main(int argc, char* argv[]) {
    try {
        int c;
        while((c=getopt(argc, argv, "hv")) != -1) {
            switch(c) {
                case 'h':
                    std::cout << build::project_name() << "version "
                        << build::project_version() << "\n"
                        << "build time: " << build::build_time() << "\n"
                        << "Usage: " << std::endl
                        << "-h show this help" << std::endl
                        << "-v show version" << std::endl;
                    return 0;
                case 'v':
                    std::cout << build::project_version() << std::endl;
                    return 0;
                default:
                    break;
            }
        }
        auto console = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_st>();
        console->set_level(spdlog::level::info);
        logger = std::make_shared<spdlog::logger>(build::project_name(), console);
        logger->info("Application name: {}", build::project_name());
        logger->info("Application version: {}", build::project_version());
        logger->info("Build type: {}", build::cmake_build_type());
        logger->info("Build time: {}", build::build_time());
        logger->info("Build platform: {}", build::build_platform());
        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);
    } catch(const spdlog::spdlog_ex& e) {
        std::cerr << "log init failed: " << e.what() << std::endl;
    } catch(const std::exception& e) {
        std::cerr << "init failed: " << e.what() << std::endl;
    }
    return 0;
}
