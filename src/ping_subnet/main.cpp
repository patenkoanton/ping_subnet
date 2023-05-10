#include <iostream>
#include <string>
#include <set>
#include "main.h"
#include "orchestrator.h"
#include "factory.h"
#include "output_stream.h"


int main(int argc, char *argv[])
{
    if (Main::argc_is_incorrect(argc)) {
        Main::show_help();
        return 0;
    }

    if (Main::help_message_requested(argc, argv)) {
        Main::show_help();
        return 0;
    }

    OutputStream stream_to_console(std::cout);
    const std::string address_and_mask = argv[1];

    // TODO: handle error codes returned from start() method.
    return Factory::make_unique<Orchestrator, OutputStream&>(stream_to_console)->start(address_and_mask);
}


bool Main::argc_is_incorrect(int argc)
{
    return argc < Main::min_argc;
}


/* Check if either --help or -help was passed. */
bool Main::help_message_requested(int argc, char **argv)
{
    std::set<std::string> args(argv, argv + argc);
    return args.count("--help") || args.count("-h");
}


/* Show info message for user. */
void Main::show_help()
{
    std::cout << std::endl;
    std::cout << "Usage: ./ping_subnet [subnet_ip_address]/[mask]" << std::endl;
}
