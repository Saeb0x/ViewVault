#include "UIFunctions.h"

#include <maya/MGlobal.h>
#include <maya/MString.h>

void createUI() {
    MString script = "import maya.cmds as cmds;\n";
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
    script += "        cmds.captureViewport(view_name)\n";
    script += "def recall_viewport_py():\n";
    script += "    selected_items = cmds.textScrollList('viewList', query=True, selectItem=True)\n";
    script += "    if selected_items:\n";
    script += "        view_name = selected_items[0]\n";
    script += "        cmds.recallViewport(view_name)\n";
    script += "    else:\n";
    script += "        cmds.confirmDialog(title='No View Selected', message='Please select a view to recall.', button='OK')\n";
    script += "def add_active_camera_to_view():\n";
    script += "    selected_items = cmds.textScrollList('viewList', query=True, selectItem=True)\n";
    script += "    if selected_items:\n";
    script += "        view_name = selected_items[0]\n";
    script += "        cmds.newCameraToView(view_name)\n";
    script += "    else:\n";
    script += "        cmds.confirmDialog(title='No View Selected', message='Please select a view to add an active camera to.', button='OK')\n";
    script += "if cmds.window('ViewVaultWindow', exists=True):\n";
    script += "    cmds.deleteUI('ViewVaultWindow')\n";
    script += "cmds.window('ViewVaultWindow', title='ViewVault', sizeable=True, widthHeight=(300, 250))\n";
    script += "cmds.columnLayout(adjustableColumn=True)\n";
    script += "cmds.text(label='Captured Views', align='center')\n";
    script += "cmds.textScrollList('viewList', numberOfRows=8, allowMultiSelection=False)\n";
    script += "cmds.button(label='Save Current View', command='capture_viewport_py()')\n";
    script += "cmds.button(label='Restore View', command='recall_viewport_py()')\n";
    script += "cmds.button(label='Add Active Camera to View', command='add_active_camera_to_view()')\n";
    script += "cmds.showWindow('ViewVaultWindow')\n";
    MGlobal::executePythonCommand(script);
}

void deleteUI() {
    MString script = "import maya.cmds as cmds;\n";
    script += "if cmds.window('ViewVaultWindow', exists=True):\n";
    script += "    cmds.deleteUI('ViewVaultWindow')\n";
    MGlobal::executePythonCommand(script);
}