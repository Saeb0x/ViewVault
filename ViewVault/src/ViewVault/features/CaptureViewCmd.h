#pragma once

#include <maya/MPxCommand.h>
#include <maya/MArgList.h>

class CaptureViewCmd : public MPxCommand
{
public:
	static void* creator() { return new CaptureViewCmd; }
	MStatus doIt(const MArgList& args) override;
	static void captureView(const std::string& viewName);
};

