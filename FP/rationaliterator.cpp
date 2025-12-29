//file header
#include "rationaliterator.h"

namespace rationaliterator{
    vector<cpp_int> iterateGenUntil(vector<cpp_int> goal, const string& filePath, const string& filePath2){
        int goalType = goal.size();
        //TROUBLESHOOT
            cout << "Iterating until goal " << iterVectorToString(goal) << " at filePath" << filePath << "with prime filePath" << filePath2 << "..." << endl;
            cout << "Appending and opening file " << filePath << endl;
            cout << "goalType = " << goalType << endl;
        //open file
        ifstream iterFile(filePath);
        ofstream writeIterFile(filePath, std::ios::app);
        //check if open
        if(iterFile.fail() || writeIterFile.fail()){
            cerr << "Error: Unable to open file for appending at " << filePath << endl;
            return vector<cpp_int>{-1};
        }
        //find last generation
        cpp_int lastGen;
        string line;
        iterFile.clear();
        iterFile.seekg(0); 
        getline(iterFile, line);
        while(getline(iterFile,line)){
            //TROUBLESHOOT
                cout << "line = " << line << ", gen = " << lastGen << endl;
            lastGen = iterStringToVector(line)[0];
        }
        bool goalMet = false;
        cpp_int newGen = lastGen + 1;
        string iterLine;
        cpp_int i;
        vector<cpp_int> iterVector;
        //SAFETY
            cpp_int dontPassGen = 21;
        while(!goalMet){
            iterFile.clear();
            iterFile.seekg(0); 
            getline(iterFile, line);
            getline(iterFile, line);
            i = 1;
            while(getline(iterFile,line) && newGen <= dontPassGen){
                lastGen = newGen;
                //TROUBLESHOOT
                    cout << "i = " << i << endl;
                iterLine = iterateOnceFrom(newGen, line, filePath2);
                iterVector = iterStringToVector(iterLine);
                if (gcd(iterVector[1], iterVector[2]) == 1) writeIterFile << "\n" << iterLine << flush;
                //TROUBLESHOOT
                    cout << "iterLine = " << iterLine << endl;
                if (goalType == 1){
                    if (goal[0] == i) goalMet = true;
                } else {
                    if (cpp_rational(goal[0],goal[1]) == cpp_rational(iterVector[1],iterVector[2])) goalMet = true;
                }
                i++;
                if (lastGen != newGen) break;
                if (dontPassGen <= newGen){
                    goalMet = true;
                    cout << "Stopped for safety.  Change dontPassGen in rationaliterator::iterateGenUntil to go any further generations.";
                }
            }
            if (newGen == lastGen && !goalMet){
                //TROUBLESHOOT
                    cout << "Finishing gen.  Reading line " << iterLine << " and iterating." << endl;
                iterLine = iterateOnceFrom(newGen, iterLine, filePath2);
                iterVector = iterStringToVector(iterLine);
                if (gcd(iterVector[1], iterVector[2]) == 1) writeIterFile << "\n" << iterLine << flush;
                if (goalType == 1){
                    if (goal[0] == i) goalMet = true;
                } else {
                    iterVector = iterStringToVector(iterLine);
                    if (cpp_rational(goal[0],goal[1]) == cpp_rational(iterVector[1],iterVector[2])) goalMet = true;
                }
            }
        }
        iterFile.close();
        writeIterFile.close();
        //TROUBLESHOOT
            cout << "iterLine = " << iterLine << endl;
            cout << "Closing file " << filePath << endl;
            cout << "...Done iterating until goal type " << goalType << endl;
        return iterVector;
    }

    string iterateOnceFrom(cpp_int& newGen, const string& iterString, const string& filePath2){
        //TROUBLESHOOT
            cout << "\tIterating once at generation " << newGen << " for iteration " << iterString << "..." << endl;
        vector<cpp_int> oldIterLine = iterStringToVector(iterString);
        cpp_int oldGen = oldIterLine[0];
        cpp_int oldNum = oldIterLine[1];
        cpp_int oldDen = oldIterLine[2];
        //TROUBLESHOOT
            cout << "\t\toldGen = " << oldGen << ", oldNum = " << oldNum << ", oldDen = "  << oldDen << endl;
        string newIterLine;
        if (newGen == 0) newIterLine = "0       0       1"; //shouldn't happen since I skip this line I think
        else if (newGen == 1) newIterLine = "1       1       1";
        else if (oldGen == newGen){
            newIterLine = iterVectorToString(vector<cpp_int>{newGen, newGen, cpp_int(1)});
            newGen++;
            //TROUBLESHOOT
                cout << "\t\tnewGen = " << newGen << endl;
        } else {
            //open file
            //TROUBLESHOOT
                cout << "\t\tOpening file " << filePath2 << endl;
            ifstream primeFile(filePath2);
            //check if opened
            if(primeFile.fail()){
                cerr << "Error: Unable to open file for appending at " << filePath2 << endl;
                return "-1";
            }
            string prime;
            cpp_int gensNextPrime;
            cpp_int factor;
            //CORE OF CALCULATIONS!!!
            cpp_int oldDenFactored = oldDen;
            cpp_int greatestFactor = 1;
            cpp_int nthFactor = 0;
            cpp_int primesSoFar = 0;
            if (oldDenFactored >= 2) primesSoFar++;
            while (oldDenFactored % 2 == 0){
                greatestFactor = 2;
                oldDenFactored /= 2;
            }
            for (factor = 3; factor <= oldDenFactored; factor += 2){
                bool notPrime = false;
                for (cpp_int i = 2; i * i <= factor; i += 2){
                    if (factor % i == 0) { notPrime = true; break; }
                }
                if (!notPrime) primesSoFar++;
                while (oldDenFactored % factor == 0){
                    nthFactor = primesSoFar;
                    greatestFactor = factor;
                    oldDenFactored /= factor;
                }
                //TROUBLESHOOT
                    cout << "\t\tgreatestFactor = " << greatestFactor << ", nThFactor = " << nthFactor << endl;
            }
            nthFactor = (nthFactor == 0) ? 1 : nthFactor; //if denom is 1, no use duplicating that
            //give it it's (nthFactor + (newGen - oldGen - 1)nth prime
            for(cpp_int i = 1; getline(primeFile, prime) && i <= (nthFactor + (newGen - oldGen) - 1); i++){ //2 bc 2nd generation uses 1st prime
                //TROUBLESHOOT
                    cout << "\t\ti = " << i << ", prime = " << prime << endl;
                gensNextPrime = cpp_int(prime);
                //TROUBLESHOOT
                    cout << "\t\tensNextPrime = " << gensNextPrime << endl;
            }
            newIterLine = iterVectorToString(vector<cpp_int>{newGen, oldNum, oldDen * gensNextPrime});
            //close File
            primeFile.close();
        }
        //TROUBLESHOOT
            cout << "\tnewIterLine = " << newIterLine << endl;
            cout << "\tClosing file " << filePath2 << endl;
            cout << "\tDone iterating once..." << endl;
        return newIterLine;
    }

    cpp_rational ratFromLine(const cpp_int& iter, const string& filePath){
        //TROUBLESHOOT
            cout << "...Getting rational number from iteration " << iter << "of filePath" <<  filePath << endl;
            cout << "\tOpening file " << filePath << endl;
        //open file
        ifstream iterFile(filePath);
        //TROUBLESHOOT
            cout << "Opening file " << filePath << endl;
        //check if opened
        if(iterFile.fail()){
            cerr << "\tError: Unable to open file for appending at " << filePath << endl;
            return -1;
        }
        //read iteration/line#
        vector<cpp_int> iterationLine = readLine(iter, iterFile);
        //TROUBLESHOOT
            cout << "\titerationLine = ";
            for(cpp_int num : iterationLine){
                cout << num << " ";
            }
            cout << endl;
            cout << "\tcpp_rational(iterationLine[1],iterationLine[2]) =  " << cpp_rational(iterationLine[1],iterationLine[2]) << endl;
        //TROUBLESHOOT
            cout << "\tClosing file " << filePath << endl;
            cout << "...done getting rational number." << endl;
        iterFile.close();
        //TROUBLESHOOT
            if (iterationLine[0] == -1) cout << "Warning!  iterationLine[0] == -1" << endl;
        return cpp_rational(iterationLine[1],iterationLine[2]);
    }

    cpp_int findRat(const cpp_rational& goal, const string& filePath){ // would have its own building block, but the return is just the number of loops, no conversion necessary
        //TROUBLESHOOT
            cout << "Finding rational " << goal << " in file " << filePath << "..." << endl;
        //open file
        ifstream iterFile(filePath);
        //check if opened
        if (iterFile.fail()){
            cerr << "\tError: Unable to open file for appending at " << filePath << endl;
            return -1;
        }
        //start reading through lines to find the right rational
        string line;
        getline(iterFile,line);
        cpp_int iter = -1;
        vector<cpp_int> iterationLine;
        cpp_rational rat;
        while(getline(iterFile,line)){
            iterationLine = {};
            iter++;
            //TROUBLESHOOT
                cout << "\titer = " << iter << ", line = " << line << endl;
            iterationLine = iterStringToVector(line); 
            rat = cpp_rational(iterationLine[1],iterationLine[2]);
            //TROUBLESHOOT
                cout << "\trat = " << rat << endl;
            if (rat == goal){
                //TROUBLESHOOT
                    cout << "\t...done finding rational." << endl;
                return iter;
            }
        }
        //close file
        iterFile.close();
        //TROUBLESHOOT
            cout << "Closing file " << filePath << endl;
            cout << "...failed at finding rational." << endl;
        return cpp_int(-1);
    }

    vector<cpp_int> readLine(const cpp_int& iter, ifstream& iterFile){ //building block of readLine
        //TROUBLESHOOT
            cout << "\tReading line " << iter << "..." << endl;
        string line;
        getline(iterFile,line);
        for(cpp_int i = 0; getline(iterFile,line); i++){ //starts at 1 to skip label row
            //TROUBLESHOOT
                cout << "\t\ti = " << i << ", line = " << line << endl;
            if (i == iter){
                vector<cpp_int> iterationLine = iterStringToVector(line);
                //TROUBLESHOOT
                    cout << "\t...done reading line." << endl;
                return iterationLine;
            }
        }
        //TROUBLESHOOT
            cout << "\t...failed at reading line." << endl;
        return vector<cpp_int>{-1};
    }

    vector<cpp_int> iterStringToVector(const string& iterString){
        //TROUBLESHOOT
            cout << "\t\tChanging iter string " << iterString << " to a vector..." << endl;
        string num;
        vector<cpp_int> iterationLine;
        stringstream ss(iterString);
        while(getline(ss,num,' ')){
            if(num.find_first_not_of(" ") != string::npos){
                //TROUBLESHOOT
                    cout << "\t\t\tnum = " << num << endl;
                iterationLine.push_back(cpp_int(num));
                //TROUBLESHOOT
                    cout << "\t\t\titerationLine = ";
                    for(cpp_int num2 : iterationLine){
                        cout << num2 << " ";
                    }
                    cout << endl;
            }
        }
        //TROUBLESHOOT
            cout << "\t\t...Done changing iter string to a vector" << endl;
        return iterationLine;
    }

    string iterVectorToString(const vector<cpp_int>& iterVector){
        //TROUBLESHOOT
            cout << "\t\tChanging iter vector ";
            for(cpp_int num : iterVector){
                cout << num << " ";
            }
            cout << "to a string..." << endl;
        string iterationLine = "";
        for (int i = 0; i <= int(iterVector.size() - 1); i++){
            iterationLine.append(iterVector[i].str());
            iterationLine.append("       ");
        }
        //TROUBLESHOOT
            cout << "\t\t...Done changing iter vector to a string..." << endl;
        return iterationLine;
    }
}