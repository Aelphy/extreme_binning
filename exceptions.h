//
// Created by Mikhail Usvyatsov on 19.07.16.
//

#ifndef EXTREME_BINNING_EXCEPTIONS_H
#define EXTREME_BINNING_EXCEPTIONS_H
    #include <iostream>
    #include <exception>

    class BrokenOrderException: public std::exception {
        virtual const char* what() const throw() {
            return "Operations did not follow the order of its application";
        }
    };

    class FileOpenException: public std::exception {
        virtual const char* what() const throw() {
            return "Failure on opening file";
        }
    };

    class FileReadException: public std::exception {
        virtual const char* what() const throw() {
            return "Failure on opening file";
        }
    };
#endif //EXTREME_BINNING_EXCEPTIONS_H
