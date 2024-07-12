#include "ViewVault.h"

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

std::vector<CapturedView> ViewVault::m_CapturedViews;
std::vector<CapturedCamera> ViewVault::m_CapturedCameras;

MStatus ViewVault::initPlugin(MObject obj)
{
	MFnPlugin viewVault(obj, "Saeb K. H. Naser", "1.0", "Any");

	viewVault.registerCommand("captureViewport", CaptureViewCmd::creator);
	viewVault.registerCommand("recallViewport", RecallViewCmd::creator);
	viewVault.registerCommand("newCameraToView", NewCameraToViewCmd::creator);

	createUI();

	MGlobal::displayInfo("ViewVault plugin loaded!");
	return MS::kSuccess;
}


MStatus ViewVault::uninitPlugin(MObject obj)
{
	MFnPlugin viewVault(obj);

	viewVault.deregisterCommand("captureViewport");
	viewVault.deregisterCommand("recallViewport");

	deleteUI();

	MGlobal::displayInfo("ViewVault plugin unloaded!");
	return MS::kSuccess;
}