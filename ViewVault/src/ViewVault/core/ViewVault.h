#pragma once

#include "../helper/UIFunctions.h"
#include "../features/CaptureViewCmd.h"
#include "../features/RecallViewCmd.h"
#include "../features/NewCameraToViewCmd.h"
#include "../helper/ViewStructs.h"

#include <vector>

class ViewVault
{
public:
	static MStatus initPlugin(MObject obj);
	static MStatus uninitPlugin(MObject obj);
	static std::vector<CapturedView> m_CapturedViews;
};
