#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <string>
#include <vector>

#include "../../FaceDetectorLibrary/include/FaceDetector.h"

void WritePersonsToJsonFile (std::string fileName, std::vector <Person> persons);

#endif // JSONWRITER_H
