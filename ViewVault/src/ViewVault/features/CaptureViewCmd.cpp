#include "CaptureViewCmd.h"

#include <maya/MFnTransform.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>

#include "../core/ViewVault.h"

MStatus CaptureViewCmd::doIt(const MArgList& args) {
    if (args.length() < 1) {
        MGlobal::displayError("Usage: captureViewport <name>");
        return MS::kFailure;
    }
    captureViewport(args.asString(0).asChar());
    return MS::kSuccess;
}

void CaptureViewCmd::captureViewport(const std::string& viewName) {
    CapturedView capturedView;
    capturedView.m_Name = viewName;
    capturedView.m_View = M3dView::active3dView();

    // Get the active camera and its path
    capturedView.m_View.getCamera(capturedView.m_CameraPath);

    // Get the transform node of the camera
    MFnTransform camTransform(capturedView.m_CameraPath.transform());

    // Get the inclusive matrix of the camera
    capturedView.m_TransformMatrix = capturedView.m_CameraPath.inclusiveMatrix();

    // Decompose the matrix to get translation, rotation, scale, and shear
    MTransformationMatrix transformMatrix(capturedView.m_TransformMatrix);
    capturedView.m_Translation = transformMatrix.getTranslation(MSpace::kTransform);
    capturedView.m_Rotation = transformMatrix.rotation();
    transformMatrix.getScale(capturedView.m_Scale, MSpace::kTransform);
    transformMatrix.getShear(capturedView.m_Shear, MSpace::kTransform);

    // Add the captured view to the vector
    ViewVault::m_CapturedViews.push_back(capturedView);

    // Update UI or perform other actions as needed
    MString script = "import maya.cmds as cmds;\n";
    script += "cmds.textScrollList('viewList', edit=True, append='" + MString(viewName.c_str()) + "')\n";
    MGlobal::executePythonCommand(script);

    MGlobal::displayInfo("Viewport '" + MString(viewName.c_str()) + "' captured.");
}