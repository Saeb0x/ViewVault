#pragma once

#include <maya/M3dView.h>
#include <maya/MMatrix.h>
#include <maya/MDagPath.h>
#include <maya/MVector.h>
#include <maya/MQuaternion.h>

struct CapturedView {
    std::string m_Name;
    M3dView m_View;
    MDagPath m_CameraPath;
    MVector m_Translation;
    MQuaternion m_Rotation;
    double m_Scale[3];
    double m_Shear[3];
    MMatrix m_TransformMatrix;
};
