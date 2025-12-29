//header file
#include "Point.h"

Point::Point(const int pointNum, const string& filePath, const string& filePath2){
    _pointNum = pointNum; //for identification.
    _dimension = 3; //luckily 0 maps to itself in this process, so its both 1D and 2D
    _filePath = filePath;
    _filePath2 = filePath2;
    _x = 0;
    _y = 0;
    _d = 0;
}

void Point::inputXY(const string& x, const string& y){
    //TROUBLESHOOT
        cout << "\nInputting x and y to point " << _pointNum << "..." << endl << "x = " << x << ", y = " << y << endl; 
    //set
    _x = cpp_rational(x);
    _y = cpp_rational(y);
    //TROUBLESHOOT
        cout << "_x = " << _x << ", _y = " << _y << endl;
        cout << "...done inputting x and y.\n" << endl;
    //change dimension to just 2 since _d may no longer map
    _dimension = 2;
}

void Point::inputD(const string& d){
    //TROUBLESHOOT
        cout << "\nInputting d to point " << _pointNum << "..." << endl << "d = " << d << endl; 
    //set
    _d = cpp_rational(d);
    //TROUBLESHOOT
        cout << "_d = " << _d << endl;
        cout << "...done inputting d.\n" << endl;
    //change dimension to just 2 since _x and _y may no longer map
    _dimension = 1;
}

void Point::calcBoxDist(){
    //TROUBLESHOOT
        cout << "\nCalculating boxDist for point " << _pointNum << "..." << endl << "_dimension = " << _dimension << endl;
    switch (_dimension){
        case 1: this->calcBoxDistFromD(); break;
        case 2: this->calcBoxDistFromXY(); break;
        case 3: cout << "boxDist has already been calculated!" << endl; break;
    }
    //TROUBLESHOOT
        cout << "...done calculating boxDist.\n" << endl;
}

void Point::calcBoxDistFromD(){
    //TROUBLESHOOT
        cout << "Calculating BoxDist from D for point " << _pointNum << "..." << endl;
        cout << "_d = " << _d << endl;
    cpp_int iterGoal = numerator(_d)/denominator(_d); //makes whole number
    //TROUBLESHOOT
        cout << "iterGoal = " << iterGoal << endl;
    cpp_rational searchOrCalcResult = rationaliterator::ratFromLine(iterGoal, _filePath); //checks file's iteration/line# for a corresponding rational
    if (searchOrCalcResult == -1){ //if it isn't found
        //iterate from last iteration to goal 
        vector<cpp_int> calcResult = rationaliterator::iterateGenUntil(vector<cpp_int>{iterGoal}, _filePath, _filePath2);
        searchOrCalcResult = cpp_rational(calcResult[1],calcResult[2]);
    }
    //TROUBLESHOOT
        cout << "searchOrCalcResult = " << searchOrCalcResult << endl;
        cout << "...done calculating BoxDist from D" << endl;
}
//
void Point::calcBoxDistFromXY(){
    
}
//