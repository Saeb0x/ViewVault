#include "DeleteViewCmd.h"

#include <maya/MGlobal.h>

#include "../core/ViewVault.h"

MStatus DeleteViewCmd::doIt(const MArgList& args)
{
    if (args.length() < 1) {
        MGlobal::displayError("Usage: deleteView <name>");
        return MS::kFailure;
    }

    deleteCapturedView(args.asString(0).asChar());

    return MS::kSuccess;
}

MStatus DeleteViewCmd::deleteCapturedView(const std::string& viewName)
{
    // Iterate through the captured views vector to find and remove the selected view
    auto& views = ViewVault::m_CapturedViews;

    auto it = std::remove_if(views.begin(), views.end(), [&](const CapturedView& view) {
        return view.m_Name == viewName.c_str();
        });

    if (it != views.end()) {
        views.erase(it, views.end());
        return MS::kSuccess;
    }
    else {
        return MS::kFailure;
    }
}
