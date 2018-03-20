#include "include/FaceDetector.h"

#include <vector>
#include <string>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


enum CascadeIDs
{
    FaceCascadeID   = 0,
    EyeCascadeID    = 1,
    MouthCascadeID  = 2
};


int CascadesLoaded = 0;

const std::string faceHaarCascade ("../../../HaarCascades/haarcascade_frontalface_default.xml");
const std::string eyeHaarCascade ("../../../HaarCascades/haarcascade_eye.xml");
const std::string mouthHaarCascade ("../../../HaarCascades/haarcascade_mcs_mouth.xml");


// #if defined(__linux__)
// #if defined(__cplusplus)
// extern "C"
// {
// #endif // __cplusplus
// std::vector <Person> PersonDetecting (const std::string & fileName)
// #elif /*__linux__*/ defined(WIN32)
// #endif // WIN32

void PersonDetecting (const std::string & fileName, std::vector <Person> & persons)
{
    persons.clear ();

    cv::CascadeClassifier FaceDetector;
    cv::CascadeClassifier EyeDetector;
    cv::CascadeClassifier MouthDetector;

    int cascadesLoaded = 0;

    if (FaceDetector.load (faceHaarCascade/*cascades [FaceCascadeID]*/) == false)
    {
        std::cout << "Error! Haar cascade for faces was not loaded, path " << faceHaarCascade << std::endl;
    }
    else
    {
        cascadesLoaded ++;
    }

    if (EyeDetector.load (eyeHaarCascade/*cascades [EyeCascadeID]*/) == false)
    {
        std::cout << "Haar cascade for eyes was not loaded" << std::endl;
    }
    else
    {
        CascadesLoaded ++;
    }

    if (MouthDetector.load (mouthHaarCascade/*cascades [MouthCascadeID]*/) == false)
    {
        std::cout << "Haar cascade for mouths was not loaded" << std::endl;
    }
    else
    {
        cascadesLoaded ++;
    }

    if (cascadesLoaded == 0)
    {
        return;
    }

    cv::Mat frame = cv::imread (fileName);

    cv::Mat grayFrame;

    if      (frame.channels () == 3)
    {
        /// If frame is 3 channels image, than convert to single channel (gray scale) image.
        cv::cvtColor (frame, grayFrame, CV_RGB2GRAY);
    }
    else if (frame.channels () == 1)
    {
        grayFrame = frame.clone ();
    }
    else // if frame`s cnannel not equal 1 or 3.
    {
        return;
    }

    cv::equalizeHist (grayFrame, grayFrame);

    /// Detecting

    /// First. Function is detecting faces at frame.

    std::vector <cv::Rect> faces;

    FaceDetector.detectMultiScale (grayFrame, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size (30, 30));

    // std::cout << "Faces were detected, faces` number is " << faces.size () << std::endl;


    /// Second. Function is detecting eyes at frame.

    std::vector <cv::Rect> eyes;

    EyeDetector.detectMultiScale (grayFrame, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size (30, 30));

    // std::cout << "Eyes were detected, Eyes` number is " << eyes.size () << std::endl;


    /// Third. Function is detecting mouth at frame.

    std::vector <cv::Rect> mouths;

    MouthDetector.detectMultiScale (grayFrame, mouths, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size (30, 30));

    // std::cout << "Mouths were detected, Mouths` number is " << mouths.size () << std::endl;

    for (cv::Rect face : faces)
    {
        Person person;

        person.FileName = fileName;
        person.Face     = face;

        /// Code is finding eyes for face.
        for (size_t number = 0; number < eyes.size (); ++ number)
        {
            cv::Rect eye = eyes [number];

            if ((face & eye).area () == eye.area ())
            {
                person.Eyes.push_back (eye);
            }
        }

        /// Code is finding mouths for face.
        for (size_t number = 0; number < mouths.size (); ++ number)
        {
            cv::Rect mouth = mouths [number];

            if ((face & mouth).area () == mouth.area ())
            {
                person.Mouths.push_back (mouth);
            }
        }

        persons.push_back (person);
    }

    std::cout << "Frame was processed, frame`s path is " << fileName << ", "
              << persons.size () << " persons were found in the frame." << std::endl;

    return;
}

// #if defined(__linux__)
// #if defined(__cplusplus)
// }
// #endif // __cplusplus
// #endif // __linux__
