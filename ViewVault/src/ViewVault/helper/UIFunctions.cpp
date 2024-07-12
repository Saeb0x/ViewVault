#pragma once

#include <maya/MGlobal.h>
#include <maya/MString.h>

void createUI() {
    MString script = "import maya.cmds as cmds\n";

    // To capture viewport
    script += "def capture_viewport_py():\n";
    script += "    view_name = cmds.promptDialog(\n";
    script += "        title='Capture View',\n";
    script += "        message='Enter a name for the captured view:',\n";
    script += "        button=['Capture', 'Cancel'],\n";
    script += "        defaultButton='Capture',\n";
    script += "        cancelButton='Cancel',\n";
    script += "        dismissString='Cancel'\n";
    script += "    )\n";
    script += "    if view_name == 'Capture':\n";
    script += "        view_name = cmds.promptDialog(query=True, text=True)\n";
    script += "        if view_name:\n"; // Check if view_name is not empty or None
    script += "            view_list = cmds.textScrollList('viewList', query=True, allItems=True)\n";
    script += "            if view_list and view_name in view_list:\n"; // Check if view_name already exists
    script += "                cmds.confirmDialog(title='Duplicate View Name', message='View with this name already exists.', button='OK')\n";
    script += "            else:\n";
    script += "                cmds.captureViewport(view_name)\n";
    script += "        else:\n"; // Handle case where view_name is empty
    script += "            cmds.confirmDialog(title='Invalid View Name', message='Please enter a valid view name.', button='OK')\n";

    // To recall viewport
    script += "def recall_viewport_py():\n";
    script += "    selected_items = cmds.textScrollList('viewList', query=True, selectItem=True)\n";
    script += "    if selected_items:\n";
    script += "        view_name = selected_items[0]\n";
    script += "        cmds.recallViewport(view_name)\n";
    script += "    else:\n";
    script += "        cmds.confirmDialog(title='No View Selected', message='Please select a view to recall.', button='OK')\n";

    // To add active camera to view
    script += "def add_active_camera_to_view():\n";
    script += "    selected_items = cmds.textScrollList('viewList', query=True, selectItem=True)\n";
    script += "    if selected_items:\n";
    script += "        view_name = selected_items[0]\n";
    script += "        camera_list = cmds.textScrollList('cameraList', query=True, allItems=True)\n";
    script += "        if camera_list and view_name in camera_list:\n"; // Check if camera with the same name already exists
    script += "            cmds.confirmDialog(title='Duplicate Camera Name', message='Camera with this name already exists.', button='OK')\n";
    script += "        else:\n";
    script += "            cmds.newCameraToView(view_name)\n";
    script += "    else:\n";
    script += "        cmds.confirmDialog(title='No View Selected', message='Please select a view to add an active camera to.', button='OK')\n";

    // To delete selected views
    script += "def delete_selected_views():\n";
    script += "    selected_items = cmds.textScrollList('viewList', query=True, selectItem=True)\n";
    script += "    if selected_items:\n";
    script += "        cmds.textScrollList('viewList', edit=True, removeItem=selected_items)\n";
    script += "    else:\n";
    script += "        cmds.confirmDialog(title='No View Selected', message='Please select views to delete.', button='OK')\n";

    // To delete selected cameras
    script += "def delete_selected_cameras():\n";
    script += "    selected_items = cmds.textScrollList('cameraList', query=True, selectItem=True)\n";
    script += "    if selected_items:\n";
    script += "        cmds.textScrollList('cameraList', edit=True, removeItem=selected_items)\n";
    script += "    else:\n";
    script += "        cmds.confirmDialog(title='No Camera Selected', message='Please select cameras to delete.', button='OK')\n";

    // If window exists and delete it
    script += "if cmds.window('ViewVaultWindow', exists=True):\n";
    script += "    cmds.deleteUI('ViewVaultWindow')\n";

    // Create main window and layout
    script += "cmds.window('ViewVaultWindow', title='ViewVault', sizeable=True, widthHeight=(400, 250))\n";
    script += "cmds.columnLayout(adjustableColumn=True)\n";

    // Main features buttons
    script += "cmds.button(label='Save Current View', command='capture_viewport_py()')\n";
    script += "cmds.button(label='Restore View', command='recall_viewport_py()')\n";
    script += "cmds.button(label='Add Active Camera to View', command='add_active_camera_to_view()')\n";
    script += "cmds.separator(style='single', height=10)\n";

    // Views List
    script += "viewListFrame = cmds.frameLayout('viewListFrame', label='Captured Views', collapse=True, collapsable=True)\n";
    script += "viewListLayout = cmds.columnLayout()\n";
    script += "cmds.textScrollList('viewList', parent=viewListLayout, numberOfRows=8, allowMultiSelection=True, visible=True)\n";
    script += "cmds.button(label='Delete Selected Views', command='delete_selected_views()')\n";  // Delete views button
    script += "cmds.setParent('..')\n";
    script += "cmds.setParent('..')\n";

    // Cameras List
    script += "cameraListFrame = cmds.frameLayout('cameraListFrame', label='Cameras', collapse=True, collapsable=True)\n";
    script += "cameraListLayout = cmds.columnLayout()\n";
    script += "cmds.textScrollList('cameraList', parent=cameraListLayout, numberOfRows=8, allowMultiSelection=True, visible=True)\n";
    script += "cmds.button(label='Delete Selected Cameras', command='delete_selected_cameras()')\n";  // Delete cameras button
    script += "cmds.setParent('..')\n";
    script += "cmds.setParent('..')\n";

    script += "cmds.showWindow('ViewVaultWindow')\n";

    MGlobal::executePythonCommand(script);
}

void deleteUI() {
    MString script = "import maya.cmds as cmds\n";
    script += "if cmds.window('ViewVaultWindow', exists=True):\n";
    script += "    cmds.deleteUI('ViewVaultWindow')\n";

    MGlobal::executePythonCommand(script);
}