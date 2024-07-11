#pragma once

#include <maya/MPxCommand.h>
#include <maya/MArgList.h>

class RecallViewCmd : public MPxCommand {
public:
    static void* creator() { return new RecallViewCmd; }
    MStatus doIt(const MArgList& args) override;
    static void recallViewport(const std::string& viewName);
};

