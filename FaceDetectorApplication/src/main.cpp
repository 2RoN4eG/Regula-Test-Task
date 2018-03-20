// Std`s Headers
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <string>
#include <memory>

// OpenCV`s Headers
#include <opencv2/highgui/highgui.hpp>

// DLL`s Headers
#include <FaceDetectorLibrary/include/FaceDetector.h>

// Tools` Headers
#include <Tools/ThreadPool.h>

// Other Headers
#include "JsonWriter.h"
#include "Direcory.h"

// Library`s functions

/// Function detect Person (faces, eyes, mouths) on image.
/// DLF - DynamicLibraryFunction
#if defined (__linux__)
#include <dlfcn.h>

typedef void (* DLFPersonDetecting)(const std::string & fileName, std::vector <Person> & persons);

#elif /* __linux__ */ defined (WIN32) //

// Window`s Headers
#include <Windows.h>

typedef void (__stdcall * DLFPersonDetecting)(const std::string & fileName, std::vector <Person> & persons);

#endif // WIN32

DLFPersonDetecting PersonDetecting = nullptr;

void Process (const std::string & fileName);

int main (int argc, char * argv [])
{
    std::cout << "argc " << argc << std::endl;

    for (int number = 0; number < argc; ++ number)
    {
        std::cout << "argv [" << number << "] " << argv [number] << std::endl;
    }

    std::string                 path;
    std::vector <std::string>   cascades;

    if (argc > 1)
    {
        path = std::string (argv [1]);
    }
    else
    {
        path = std::string ("../../../Data/");
    }

    if (argc > 2)
    {
        cascades.push_back (std::string (argv [2]));
    }

    if (argc > 3)
    {
        cascades.push_back (std::string (argv [3]));
    }

    if (argc > 4)
    {
        cascades.push_back (std::string (argv [4]));
    }

#if defined (__linux__)
    void * libraryHandle = dlopen ("./libFaceDetectorLibrary.so", RTLD_LAZY);
    
    if (libraryHandle == nullptr)
    {
        std::cerr << dlerror() << std::endl;

        exit (-1);
    }

    char * error;

    /// Pointer to DL function.
    PersonDetecting = (DLFPersonDetecting)dlsym (libraryHandle, "PersonDetecting");

    if ((error = dlerror()) != nullptr)
    {
        std::cerr << error << std::endl;

        exit (-1);
    }
#elif /* __linux__ */ defined (WIN32)
    HINSTANCE libraryHandle = LoadLibraryA ("./FaceDetectorLibrary.dll");

    if (!libraryHandle)
    {
        std::cout << "could not load the dynamic library, error " << GetLastError () << std::endl;

        return EXIT_FAILURE;
    }

    PersonDetecting = (DLFPersonDetecting)GetProcAddress (libraryHandle, "PersonDetecting");

    if (!PersonDetecting)
    {
        std::cout << "Could not locate the function" << std::endl;

        return EXIT_FAILURE;
    }
#else // WIN32
    return -1;
#endif

    std::deque <std::string> files = DirectoryFiles (path);

    ThreadPool * pool = new ThreadPool (8);

    for (std::string fileName : files)
    {
        std::cout << "File is " << fileName << std::endl;

        /// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        pool->runAsync (&Process, fileName);

        /// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }

    /// Waiting, until all workers will complete all work.
    delete pool;

    std::cout << "Good bye, I will see you later :)" << std::endl;

#if defined (__linux__)
    dlclose (libraryHandle);

    return 0;
#elif /* __linux__ */ defined (WIN32)
    CloseHandle (libraryHandle);

    return EXIT_SUCCESS;
#else /* WIN32 */
    return -1;
#endif
}

void Process (const std::string & fileName)
{
    std::vector <Person> persons;

    PersonDetecting (fileName, persons);

    cv::Mat frame = cv::imread (fileName);

    if (frame.empty ())
    {
        std::cout << "Error! Frame wasn`t loaded" << std::endl;

        return;
    }

    for (size_t number = 0; number < persons.size (); ++ number)
    {
        Person person = persons [number];

        /// Clone part frame with person`s face.
        cv::Mat face = frame (person.Face).clone ();

        /// Flip part frame with person`s face.
        cv::flip (face, face, 0 /*Vertical Flip*/);

        std::string faceFileName = fileName + std::string ("_Face_") + std::to_string (number) + std::string (".jpg");

        /// Write at file part frame with person`s face.
        cv::imwrite (faceFileName, face);

#if defined (DEBUG_EYES_AND_MOUTHS)
        cv::rectangle (frame, person.Face, cv::Scalar (0, 0, 255));

        for (cv::Rect eye : person.Eyes)
        {
            cv::rectangle (frame, eye, cv::Scalar (255, 0, 0));
        }

        for (cv::Rect mouth : person.Mouths)
        {
            cv::rectangle (frame, mouth, cv::Scalar (0, 255, 0));
        }
#endif // DEBUG_EYES_AND_MOUTHS
    }

    WritePersonsToJsonFile (fileName, persons);

#if defined (DEBUG_EYES_AND_MOUTHS)
    cv::imwrite (fileName + String("_result.jpg"), frame);
#endif // DEBUG_EYES_AND_MOUTHS

    // std::cout << "Process " << fileName << " End" << std::endl;
}
