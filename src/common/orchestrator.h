#pragma once
#include <string>
#include <memory>
#include "output_stream.h"
#include "ping.h"

class Orchestrator {
    OutputStream &output_stream;
    std::shared_ptr<Ping> ping;
public:
    Orchestrator(OutputStream &stream);
    int start(std::string &address_and_mask);
    void stop();
    int get_progress();     // returns the % of finalized hosts
};