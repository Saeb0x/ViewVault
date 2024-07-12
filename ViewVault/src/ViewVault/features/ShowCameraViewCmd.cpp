#include "ShowCameraViewCmd.h"

#include <maya/MGlobal.h>
#include <maya/MFnDagNode.h>
#include <maya/MDagPath.h>
#include <maya/MFnCamera.h>
#include <maya/MSelectionList.h>

MStatus ShowCameraViewCmd::doIt(const MArgList& args) {
    if (args.length() != 1) {
        MGlobal::displayError("Please select one camera at a time");
        return MS::kFailure;
    }

    showCameraView(args.asString(0).asChar());

    return MS::kSuccess;
}

MStatus ShowCameraViewCmd::showCameraView(const std::string& cameraName) {
    MStatus status;

    // Find the camera by name
    MSelectionList selectionList;
    status = selectionList.add(cameraName.c_str());
    if (!status) {
        MGlobal::displayError(MString("Failed to add camera '") + cameraName.c_str() + "' to selection list.");
        return status;
    }

    MDagPath dagPath;
    status = selectionList.getDagPath(0, dagPath);
    if (!status) {
        MGlobal::displayError(MString("Failed to get DAG path for camera '") + cameraName.c_str() + "'.");
        return status;
    }

    // Check if the node is a camera
    if (!dagPath.hasFn(MFn::kCamera)) {
        MGlobal::displayError(MString("Node '") + cameraName.c_str() + "' is not a camera.");
        return MS::kFailure;
    }

    MFnCamera cameraFn(dagPath);

    // Create a new window with a viewport
    MString windowName = cameraName.c_str();
    windowName += " Preview";

    MString script = "import maya.cmds as cmds\n";
    script += "if cmds.window('" + windowName + "', exists=True):\n";
    script += "    cmds.deleteUI('" + windowName + "')\n";
    script += "window = cmds.window('" + windowName + "', title='" + windowName + "')\n";
    script += "layout = cmds.formLayout(parent=window)\n";
    script += "editor = cmds.modelEditor(parent=layout)\n";
    script += "cmds.formLayout(layout, edit=True, attachForm=[(editor, 'top', 0), (editor, 'left', 0), (editor, 'right', 0), (editor, 'bottom', 0)])\n";
    script += "cmds.showWindow(window)\n";

    // Set the camera in the model editor
    script += "cmds.modelEditor(editor, edit=True, camera='" + MString(cameraName.c_str()) + "')\n";

    MGlobal::executePythonCommand(script);

    return MS::kSuccess;
}
