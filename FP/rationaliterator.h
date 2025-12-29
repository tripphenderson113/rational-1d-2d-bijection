#ifndef RATIONALITERATOR_H
#define RATIONALITERATOR_H

//for file use
#include <fstream>
#include <string>
#include <sstream>
//for math
#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
//for troubleshooting
#include <iostream>

using namespace boost::multiprecision;
using namespace std;

namespace rationaliterator {

    //write

    /**
     * @brief starts at the last generation, reads lines before it and appends generations of iterations until goal of type T is found
     * @param goal a vector of cpp_int to either be the iteration or rational
     * @param filePath path to the file being used
     * @param filePath2 path to the file for primes
     * @return vector of iteration line produced by final iteration
    */
    vector<cpp_int> iterateGenUntil(vector<cpp_int>, const string&, const string&);

    //write building block

    /**
     * @brief returns a line when given a line to iterate off of and a generation
     * @param gen current generation iterating at
     * @param iterationLine line iterating off of
     * @param filePath2 path to the file for primes
     * @return more readable string of iteration line produced by final iteration
    */
    string iterateOnceFrom(cpp_int&, const string&, const string&);
    

    //read

    /**
     * @brief gets rational from iteration
     * @param iter cpp_int& of the iteration/line#.
     * @param filePath path to the file being used
     * @return returns cpp_rational, but -1 if line doesn't exist
    */
    cpp_rational ratFromLine(const cpp_int&, const string&);

    /**
     * @brief reads file for rational and gives corresponding iteration
     * @param goal cpp_rational& of goal rational to search for. 
     * @param filePath is the file path to use
     * @return returns cpp_rational, but -1 if line doesn't exist
    */
    cpp_int findRat(const cpp_rational&, const string&);

    //also create "skim file", outputs every iteration line
    
    //read building blocks

    /**
     * @brief gets a vector of the requested iteration/line#
     * @param iter cpp_int& of the iteration/line#.
     * @param iterFile ifstream& reference to iterFile  
     * @return vector of iteration line
    */
    vector<cpp_int> readLine(const cpp_int&, ifstream& iterFile);

    /**
     * @brief converts from iteration line string to iteration line vector
     * @param iterString string of iteration line
     * @return vector of iteration line
     */
    vector<cpp_int> iterStringToVector(const string&);

    /**
     * @brief converts from iteration line string to iteration line vector
     * @param iterVector string of iteration line
     * @return string of iteration line
     */
    string iterVectorToString(const vector<cpp_int>&);

}

#endif