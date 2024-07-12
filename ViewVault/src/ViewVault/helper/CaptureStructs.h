#pragma once

#include <maya/M3dView.h>
#include <maya/MMatrix.h>
#include <maya/MDagPath.h>
#include <maya/MVector.h>
#include <maya/MQuaternion.h>

// For capturing view details
struct CapturedView {
    MString m_Name;
    M3dView m_View;
    MDagPath m_CameraPath;
    MMatrix m_TransformMatrix;
    MVector m_Translation;
    MQuaternion m_Rotation;
    double m_Scale[3];
    double m_Shear[3];
};

// For capturing camera details
struct CapturedCamera
{
    MString m_Name;
    MDagPath m_CameraPath;
    MVector m_Translation;
    MQuaternion m_Rotation;
    double m_FocalLength;
    double m_HorizontalFilmAperture;
    double m_VerticalFilmAperture;
    double m_NearClipping;
    double m_FarClipping;
};
