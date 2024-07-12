#include "CaptureViewCmd.h"

#include <maya/MFnTransform.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>

#include "../core/ViewVault.h"

MStatus CaptureViewCmd::doIt(const MArgList& args) 
{
    if (args.length() < 1) {
        MGlobal::displayError("Usage: captureView <name>");
        return MS::kFailure;
    }

    captureView(args.asString(0).asChar());

    return MS::kSuccess;
}

void CaptureViewCmd::captureView(const std::string& viewName) 
{
    // To check if a view with a similar name exists
    for (const auto& view : ViewVault::m_CapturedViews)
    {
        if (view.m_Name == MString(viewName.c_str()))
        {
            MGlobal::displayError("View '" + MString(viewName.c_str()) + "' already exists.");
            return;
        }
    }

    CapturedView capView;
    capView.m_Name = MString(viewName.c_str());
    capView.m_View = M3dView::active3dView();

    // Get the active camera and its path
    capView.m_View.getCamera(capView.m_CameraPath);

    // Get the transform node of the camera
    MFnTransform camTransform(capView.m_CameraPath.transform());

    // Get the inclusive matrix of the camera
    capView.m_TransformMatrix = capView.m_CameraPath.inclusiveMatrix();

    // Decompose the matrix to get translation, rotation, scale, and shear
    MTransformationMatrix transformMatrix(capView.m_TransformMatrix);
    capView.m_Translation = transformMatrix.getTranslation(MSpace::kTransform);
    capView.m_Rotation = transformMatrix.rotation();
    transformMatrix.getScale(capView.m_Scale, MSpace::kTransform);
    transformMatrix.getShear(capView.m_Shear, MSpace::kTransform);

    // Add the captured view to the vector
    ViewVault::m_CapturedViews.push_back(capView);

    // Update UI
    MString script = "import maya.cmds as cmds;\n";
    script += "cmds.textScrollList('viewList', edit=True, append='" + MString(viewName.c_str()) + "')\n";
    script += "cmds.frameLayout('viewListFrame', edit=True, collapse=False)\n";  // Expand the frame layout
    MGlobal::executePythonCommand(script);

    MGlobal::displayInfo("Viewport '" + MString(viewName.c_str()) + "' captured.");
}