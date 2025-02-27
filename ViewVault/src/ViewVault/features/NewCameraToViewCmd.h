#pragma once

#include <maya/MPxCommand.h>
#include <maya/MArgList.h>

class NewCameraToViewCmd : public MPxCommand
{
public:
    static void* creator() { return new NewCameraToViewCmd; }
    MStatus doIt(const MArgList& args) override;
    static void addCamera(const std::string& viewName, const std::string& cameraName);
};

