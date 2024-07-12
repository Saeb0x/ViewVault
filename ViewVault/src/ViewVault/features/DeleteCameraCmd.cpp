#include "DeleteCameraCmd.h"

#include <maya/MGlobal.h>
#include <maya/MFnDagNode.h>
#include <maya/MDagPath.h>
#include <maya/MSelectionList.h>

#include "../core/ViewVault.h"

MStatus DeleteCameraCmd::doIt(const MArgList& args)
{
    if (args.length() < 1) {
        MGlobal::displayError("Usage: deleteCamera <name>");
        return MS::kFailure;
    }

    deleteCamera(args.asString(0).asChar());

    return MS::kSuccess;
}

MStatus DeleteCameraCmd::deleteCamera(const std::string& cameraName) {
    // Iterate through the captured cameras vector to find and remove the selected camera
    auto& cameras = ViewVault::m_CapturedCameras;

    auto it = std::remove_if(cameras.begin(), cameras.end(), [&](const CapturedCamera& camera) {
        return camera.m_Name == cameraName.c_str();
        });

    if (it != cameras.end()) {
        // Get the camera DAG path
        MSelectionList selectionList;
        MStatus status = selectionList.add(cameraName.c_str());

        if (status != MS::kSuccess) {
            MGlobal::displayError("Failed to add camera name to selection list.");
            return status;
        }

        MDagPath dagPath;
        status = selectionList.getDagPath(0, dagPath);

        if (status != MS::kSuccess) {
            MGlobal::displayError("Failed to get DAG path for camera.");
            return status;
        }

        // Check if the node is a camera
        if (dagPath.hasFn(MFn::kCamera)) {
            // Get the MObject from the dagPath
            MObject cameraObject = dagPath.node();

            // Remove camera from the DAG (delete the node)
            status = MGlobal::deleteNode(cameraObject);
            if (status != MS::kSuccess) {
                MGlobal::displayError("Failed to delete camera node from the outliner.");
                return status;
            }

            // Remove camera from the captured cameras vector
            cameras.erase(it, cameras.end());
            return MS::kSuccess;
        }
        else {
            MGlobal::displayError("Selected node is not a camera.");
            return MS::kFailure;
        }
    }
    else {
        return MS::kFailure;
    }
}