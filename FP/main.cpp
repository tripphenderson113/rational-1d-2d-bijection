#include "Point.h"
#include "rationaliterator.h"
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

int main(){
    string filePath = "/Users/tripphenderson/Desktop/CPP/CODE/FP/iterationFile";
    string filePath2 = "/Users/tripphenderson/Desktop/CPP/CODE/FP/primes.0000.txt";
    //rationaliterator::_filePath = filePath;
    // Point firstPoint(1,filePath);
    // firstPoint.inputXY("1/2","2/1");
    // Point secondPoint(2,filePath);
    // secondPoint.inputD("6/2");
    
    // secondPoint.calcBoxDist();
    //rationaliterator::readLine(1, filePath);
    //rationaliterator::ratFromLine(1, filePath);
    //rationaliterator::findRat(cpp_rational(2,3),filePath);
    //string p = "0   0   1";
    vector<cpp_int> v = {20,1};
    vector<cpp_int> w = {3,4,2};
    //rationaliterator::iterateGenUntil(v, filePath, filePath2);
    //cout << (cpp_rational(v[0],v[1]) == cpp_rational(w[1],w[2])) << endl;
    rationaliterator::iterateGenUntil(v, filePath, filePath2);
    // cpp_int i = 405;
    // rationaliterator::ratFromLine(i,filePath);
}