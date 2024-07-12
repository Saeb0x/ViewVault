#pragma once

#include <maya/MPxCommand.h>
#include <maya/MArgList.h>


class DeleteViewCmd : public MPxCommand
{
public:
	static void* creator() { return new DeleteViewCmd; }
	MStatus doIt(const MArgList& args) override;
	static MStatus deleteCapturedView(const std::string& viewName);
};

