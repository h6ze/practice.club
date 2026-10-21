#pragma once
#include <Windows.h>
#include <client/diag/crash/report/writer.hh>

namespace crash {

    void write_registers(writer& out, const CONTEXT& context);

}
