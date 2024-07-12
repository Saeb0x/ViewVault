#include "NewCameraToViewCmd.h"

#include <maya/MFnTransform.h>
#include <maya/MFnCamera.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>
#include <maya/MGlobal.h>

#include "../core/ViewVault.h"

MStatus NewCameraToViewCmd::doIt(const MArgList& args) {
    // Check if the command was provided with the viewName argument
    if (args.length() < 1) {
        MGlobal::displayError("Usage: newCameraToView <viewName>");
        return MS::kFailure;
    }
    
    addCamera(args.asString(0).asChar());

    return MS::kSuccess;
}

void NewCameraToViewCmd::addCamera(const std::string& viewName) {
    // Find the captured view with the specified name in ViewVault
    CapturedView selectedView;
    bool viewFound = false;
    for (const auto& view : ViewVault::m_CapturedViews) {
        if (view.m_Name == viewName.c_str()) {
            selectedView = view;
            viewFound = true;
            break;
        }
    }

    // If the view with the specified name is not found, display an error
    if (!viewFound) {
        MGlobal::displayError(MString("View '") + viewName.c_str() + "' not found in captured views.");
        return;
    }

    // Create a new camera
    MFnCamera newCamera;
    MObject cameraObj = newCamera.create();
    if (cameraObj.isNull()) {
        MGlobal::displayError("Failed to create a new camera.");
        return;
    }

    // Set the camera's translation and rotation to match the stored view
    MFnTransform cameraTransform(cameraObj);
    MStatus status;

    cameraTransform.setTranslation(selectedView.m_Translation, MSpace::kTransform);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Failed to set camera translation.");
        return;
    }

    cameraTransform.setRotation(selectedView.m_Rotation);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Failed to set camera rotation.");
        return;
    }

    // Get the DAG path of the new camera
    MDagPath cameraPath;
    status = MFnDagNode(cameraObj).getPath(cameraPath);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Failed to get DAG path for new camera.");
        return;
    }

    // Set the new camera as the active camera in the active 3D view
    M3dView activeView = M3dView::active3dView();
    status = activeView.setCamera(cameraPath);
    if (status != MS::kSuccess) {
        MGlobal::displayError("Failed to set new camera as active camera.");
        return;
    }

    // Refresh the active 3D view to reflect changes
    activeView.refresh();

    MString cameraName = (viewName + " Cam").c_str();

    // Add the new camera to the camera list in the UI
    MString script = "import maya.cmds as cmds;\n";
    script += "cmds.textScrollList('cameraList', edit=True, append='" + cameraName + "')\n";
    script += "cmds.frameLayout('cameraListFrame', edit=True, collapse=False)\n";  // Expand the frame layout
    MGlobal::executePythonCommand(script);

    // Display success message
    MGlobal::displayInfo(MString("Camera '") + viewName.c_str() + "' added to view '" + selectedView.m_Name + "'.");
}