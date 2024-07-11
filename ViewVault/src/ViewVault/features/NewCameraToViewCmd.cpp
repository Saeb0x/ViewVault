#include "NewCameraToViewCmd.h"

#include <maya/MFnTransform.h>
#include <maya/MFnCamera.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>

#include "../core/ViewVault.h"

MStatus NewCameraToViewCmd::doIt(const MArgList& args) {
    // Check if the command was provided with the viewName argument
    if (args.length() < 1) {
        MGlobal::displayError("Usage: newCameraToView <viewName>");
        return MS::kFailure;
    }

    // Get the viewName argument from the command arguments
    MString viewName = args.asString(0);

    // Find the captured view with the specified name in ViewVault
    CapturedView selectedView;
    bool viewFound = false;
    for (const auto& view : ViewVault::m_CapturedViews) {
        if (view.m_Name == viewName.asChar()) {
            selectedView = view;
            viewFound = true;
            break;
        }
    }

    // If the view with the specified name is not found, display an error
    if (!viewFound) {
        MGlobal::displayError("View '" + viewName + "' not found in captured views.");
        return MS::kFailure;
    }

    // Get the active 3D view in Maya
    M3dView activeView = M3dView::active3dView();

    // Create a new camera
    MFnCamera newCamera;
    MObject cameraObj = newCamera.create();
    if (cameraObj.isNull()) {
        MGlobal::displayError("Failed to create a new camera.");
        return MS::kFailure;
    }

    // Set camera attributes from the existing camera (optional, adjust as needed)
    double focalLength = newCamera.focalLength();
    double horizontalFilmAperture = newCamera.horizontalFilmAperture();
    double verticalFilmAperture = newCamera.verticalFilmAperture();
    double nearClipping = newCamera.nearClippingPlane();
    double farClipping = newCamera.farClippingPlane();

    // Set new camera attributes (optional, adjust as needed)
    newCamera.setFocalLength(focalLength);
    newCamera.setHorizontalFilmAperture(horizontalFilmAperture);
    newCamera.setVerticalFilmAperture(verticalFilmAperture);
    newCamera.setNearClippingPlane(nearClipping);
    newCamera.setFarClippingPlane(farClipping);

    // Set the camera's translation and rotation
    MFnTransform cameraTransform(cameraObj);
    cameraTransform.setTranslation(selectedView.m_Translation, MSpace::kTransform);
    cameraTransform.setRotation(selectedView.m_Rotation);

    // Get the DAG path of the new camera
    MDagPath cameraPath;
    MStatus status = MFnDagNode(cameraObj).getPath(cameraPath);
    if (!status) {
        MGlobal::displayError("Failed to get DAG path for new camera.");
        return MS::kFailure;
    }

    // Set the new camera as the active camera in the active 3D view
    status = activeView.setCamera(cameraPath);
    if (!status) {
        MGlobal::displayError("Failed to set new camera as active camera.");
        return MS::kFailure;
    }

    // Refresh the active 3D view to reflect changes
    activeView.refresh();

    return MS::kSuccess;
}