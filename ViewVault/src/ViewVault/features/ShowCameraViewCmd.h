#pragma once

#include <maya/MPxCommand.h>
#include <maya/MArgList.h>

class ShowCameraViewCmd : public MPxCommand
{
public:
	static void* creator() { return new ShowCameraViewCmd; }
	MStatus doIt(const MArgList& args) override;
	static MStatus showCameraView(const std::string& cameraName);
};

