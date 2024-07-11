#include "RecallViewCmd.h"

#include <maya/MFnTransform.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MGlobal.h>

#include "../core/ViewVault.h"

MStatus RecallViewCmd::doIt(const MArgList& args) {
    if (args.length() < 1) {
        MGlobal::displayError("Usage: recallViewport <name>");
        return MS::kFailure;
    }
    recallViewport(args.asString(0).asChar());
    return MS::kSuccess;
}

void RecallViewCmd::recallViewport(const std::string& viewName) {
    bool viewFound = false;

    // Check if there's any captured view with the specified name
    for (const auto& capturedView : ViewVault::m_CapturedViews) {
        if (capturedView.m_Name == viewName) {
            // Check if this is the 'perspShape' camera
            MString cameraName = capturedView.m_CameraPath.partialPathName();
            if (cameraName == "perspShape") {
                // Get the transform node of the camera
                MFnTransform camTransform(capturedView.m_CameraPath.transform());

                // Set translation, rotation, scale, and shear to the transform node
                camTransform.setTranslation(capturedView.m_Translation, MSpace::kTransform);
                camTransform.setRotation(capturedView.m_Rotation);
                camTransform.setScale(capturedView.m_Scale);
                camTransform.setShear(capturedView.m_Shear);

                // Refresh the active view's viewport
                M3dView::active3dView().refresh(true);

                viewFound = true;
                break;
            }
        }
    }

    if (viewFound) {
        MGlobal::displayInfo("Perspective camera updated according to viewport '" + MString(viewName.c_str()) + "'.");
    }
    else {
        MGlobal::displayWarning("Viewport '" + MString(viewName.c_str()) + "' not found or does not affect the 'perspShape' camera.");
    }
}
