#include "Direcory.h"

#if defined (__linux__)

#include <iostream>
#include <string.h>
#include <dirent.h>

std::deque <std::string> DirectoryFiles (std::string path)
{
    std::deque <std::string> files;

    DIR           * directory;
    struct dirent * directoryOrFile;

    directory = opendir (path.c_str ());

    if (directory)
    {
        while ((directoryOrFile = readdir (directory)) != NULL)
        {
            // printf ("%s\n", directoryOrFile->d_name);

            if (strcmp (directoryOrFile->d_name, ".")  == 0)
            {
                // std::cout << "Name" << directoryOrFile->d_name
                //           << "Type" << int (directoryOrFile->d_type)
                //           << std::endl;

                continue;
            }

            if (strcmp (directoryOrFile->d_name, "..") == 0)
            {
                // std::cout << "Name" << " " << directoryOrFile->d_name << " "
                //           << "Type" << " " << int (directoryOrFile->d_type)
                //           << std::endl;

                continue;
            }

            if (directoryOrFile->d_type == DT_REG)
            {
                /// DT_REG - This is a regular file.
                /// source: http://man7.org/linux/man-pages/man3/readdir.3.html

                files.push_back (path + "/" + std::string (directoryOrFile->d_name));
            }
            else if (directoryOrFile->d_type == DT_DIR)
            {
                std::deque <std::string> childDirectoryFiles = DirectoryFiles (path + std::string (directoryOrFile->d_name));

                files.insert (files.end (), childDirectoryFiles.begin (), childDirectoryFiles.end ());
            }
        }

        closedir (directory);
    }

    return files;
}

#elif /* __linux__ */ defined WIN32

#include <iostream>
#include <Windows.h>
#include <string.h>

std::deque <std::string> DirectoryFiles (std::string path)
{
    std::cout << "Path " << path << std::endl;

    std::deque <std::string> files;

    if (path [path.size () - 1] == '\\' || path [path.size () - 1] == '/')
    {
        path = path.substr (0, path.size () - 1);
    }

    WIN32_FIND_DATA findData;
    HANDLE          handle = FindFirstFile (std::string (path).append ("\\*").c_str (), &findData);

    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (strcmp (findData.cFileName, ".") != 0 && strcmp (findData.cFileName, "..") != 0)
            {
                if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    std::deque <std::string> directoryFiles = DirectoryFiles (path + "/" + findData.cFileName);

                    files.insert (files.end (), directoryFiles.begin (), directoryFiles.end ());

                    // continue; // a diretory
                }
                else
                {
                    files.push_back (path + std::string ("/") + std::string (findData.cFileName));
                }
            }
        }
        while (FindNextFile (handle, &findData) != 0);
    }
    else
    {
        std::cerr << "can't open directory" << std::endl;

        return std::deque <std::string> ();
    }

    if (GetLastError () != ERROR_NO_MORE_FILES)
    {
        FindClose (handle);

        // std::cerr << "some other error with opening directory: " << GetLastError () << endl;

        return std::deque <std::string> ();
    }

    FindClose (handle);
    handle = INVALID_HANDLE_VALUE;

    return files;
}

#endif // WIN32


