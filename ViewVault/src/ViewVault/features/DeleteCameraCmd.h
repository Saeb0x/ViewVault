#pragma once

#include <maya/MPxCommand.h>
#include <maya/MArgList.h>

class DeleteCameraCmd : public MPxCommand
{
public:
	static void* creator() { return new DeleteCameraCmd; }
	MStatus doIt(const MArgList& args) override;
	static MStatus deleteCamera(const std::string& cameraName);
};

