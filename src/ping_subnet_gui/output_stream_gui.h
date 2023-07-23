#pragma once

#include <string>
#include <iostream>
#include "output_stream.h"

// This class is redirecting output to our GUI main form.
// Used by GUI version of the app aka ping_subnet_gui.
struct OutputStreamGUI : public OutputStream {
    OutputStreamGUI(std::ostream &stream) : OutputStream(stream) {};
    virtual OutputStream& operator<<(std::string arg);
    virtual OutputStream& operator<<(std::ostream& (*arg)(std::ostream&));  // handle std::endl
};