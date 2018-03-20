#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

// Std`s Headers
#include <vector>

// OpenCV Headers
#include <opencv2/core/core.hpp>

#if defined(__linux__)

#if defined(FACEDETECTOR_LIBRARY)

#define API_FACEDETECTOR_EXPORT __attribute__((visibility("default")))
#endif // FACEDETECTOR_LIBRARY

#elif /* __linux__ */ defined(WIN32)

#if defined(FACEDETECTOR_LIBRARY)

#define API_FACEDETECTOR_EXPORT __declspec(dllexport)
#endif // FACEDETECTOR_LIBRARY

#endif // WIN32

struct Person
{
    std::string             FileName;

    cv::Rect                Face;

    std::vector <cv::Rect>  Eyes;

    std::vector <cv::Rect>  Mouths;
};

#if defined(FACEDETECTOR_LIBRARY)
/// Function detect Person (faces, eyes, mouths) on image.
extern "C" API_FACEDETECTOR_EXPORT void PersonDetecting (const std::string & fileName, std::vector <Person> & persons);
#endif // FACEDETECTOR_LIBRARY

#endif // FACEDETECTOR_H
