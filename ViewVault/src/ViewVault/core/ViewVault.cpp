#include "ViewVault.h"

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

std::vector<CapturedView> ViewVault::m_CapturedViews;
std::vector<CapturedCamera> ViewVault::m_CapturedCameras;

MStatus ViewVault::initPlugin(MObject obj)
{
	MFnPlugin viewVault(obj, "Saeb K. H. Naser", "1.0", "Any");

	viewVault.registerCommand("captureView", CaptureViewCmd::creator);
	viewVault.registerCommand("recallView", RecallViewCmd::creator);
	viewVault.registerCommand("newCameraToView", NewCameraToViewCmd::creator);
	viewVault.registerCommand("deleteView", DeleteViewCmd::creator);
	viewVault.registerCommand("deleteCamera", DeleteCameraCmd::creator);

	createUI();

	MGlobal::displayInfo("ViewVault plugin loaded!");
	return MS::kSuccess;
}


MStatus ViewVault::uninitPlugin(MObject obj)
{
	MFnPlugin viewVault(obj);

	viewVault.deregisterCommand("captureView");
	viewVault.deregisterCommand("recallView");
	viewVault.deregisterCommand("newCameraToView");
	viewVault.deregisterCommand("deleteView");

	deleteUI();

	MGlobal::displayInfo("ViewVault plugin unloaded!");
	return MS::kSuccess;
}