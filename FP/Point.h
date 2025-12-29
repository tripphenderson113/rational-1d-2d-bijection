#ifndef POINT_H
#define POINT_H

//for math
#include <boost/multiprecision/cpp_int.hpp>
//for file use
#include <string>
#include "rationaliterator.h"

using namespace std;
using namespace boost::multiprecision;

class Point{
    private: //three variables to convert between
    //point identification
    int _pointNum;
    //iterationFile path
    string _filePath;
    //primeFile path
    string _filePath2;
    //dimension info
    int _dimension; //1 for 1D, 2 for 2D, or 3 for both
    //2D variables
    cpp_rational _x;
    cpp_rational _y;
    //1D variable
    cpp_rational _d;
    //intermediate variables
    cpp_rational _boxDist;
    cpp_int _boxNum;
    double _circ;
    
    
    public:
    /**
     * @brief construct point with initial values _x, _y, _d = 0
     * @param integer to remember identity of object, and filePath to use later
     * @param filePath2
     */
    Point(const int, const string&, const string&);

    /**
     * @brief function to set the 2D variables _x and _y
     * @param two strings of value to set _x and _y as
     */
    void inputXY(const string&, const string&);

    /**
     * @brief function to set 1D variable _d
     * @param string of value to set _d as
     */
    void inputD(const string& d);
    
    /**
     * @brief calculate first intermediate variable, boxDist. Chooses between calculating from _d or from _x and _y
     */
    void calcBoxDist();

    //functions used in calcBoxDist:
        private:
        /**
         * @brief calculate boxDist from _d.  Works by iterating through rational numbers until int of _d is found
         */
        void calcBoxDistFromD();
        /**
         * @brief calculate boxDist from _x and _y.  Works by determining which side of the box and calculating distance to it from origin.
        */
        void calcBoxDistFromXY();
        
};

#endif