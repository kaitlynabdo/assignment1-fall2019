
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <string>
#include <cstdlib>
#include <math.h>

using namespace std;

ofstream outF("KaitlynAbdo.txt");

void uppercase(string& s){ //making the string uppercase
    for(int i = 0; i<s.length(); i++){
        s[i] = toupper(s[i]);
    }
}

short variance(string file, float m, int c){
    int varCount = 0, varNum = 0, var = 0, unit = 0;
    ifstream path;
    char charact;
    path.open(file);

    while(!path.eof()){ // for each line in the doc
        varCount++;
        path >> charact;

        unit = varCount - m; // subtract val from mean
        varNum += pow(unit, 2); // variance sum
    }
    var = varNum / c; //variance calculation
    path.close();
    return var;
}

void bigram(int num, string file){

    ifstream path;
    path.open(file);


    int countAA = 0, countAT = 0, countAC = 0, countAG = 0;
    int countCA = 0, countCT = 0, countCC = 0, countCG = 0;
    int countTA = 0, countTT = 0, countTC = 0, countTG = 0;
    int countGA = 0, countGT = 0, countGC = 0, countGG = 0;
    string s = "";
    while(!path.eof()){
        path >> s; //read in from a file
        uppercase(s);
        for (int i = 0; i < s.length(); ++i){ //counting instances of bigrams
            if (i % 2 != 0){
                if (s.at(i) == 'A' && s.at(i) == 'A'){
                    countAA++;
                }
                if (s.at(i) == 'A' && s.at(i-1) == 'T'){
                    countAT++;
                }
                if (s.at(i) == 'A' && s.at(i-1) == 'C'){
                    countAC++;
                }
                if (s.at(i) == 'A' && s.at(i-1) == 'G'){
                    countAG++;
                }


                if (s.at(i) == 'C' && s.at(i-1) == 'A'){
                    countCA++;
                }
                if (s.at(i) == 'C' && s.at(i-1) == 'T'){
                    countCT++;
                }
                if (s.at(i) == 'C' && s.at(i-1) == 'C'){
                    countCC++;
                }
                if (s.at(i) == 'C' && s.at(i-1) == 'G'){
                    countCG++;
                }

                if (s.at(i) == 'T' && s.at(i-1) == 'A'){
                    countTA++;
                }
                if (s.at(i) == 'T' && s.at(i-1) == 'T'){
                    countTT++;
                }
                if (s.at(i) == 'T' && s.at(i-1) == 'C'){
                    countTC++;
                }
                if (s.at(i) == 'T' && s.at(i-1) == 'G'){
                    countTG++;
                }

                if (s.at(i) == 'G' && s.at(i-1) == 'A'){
                    countGA++;
                }
                if (s.at(i) == 'G' && s.at(i-1) == 'T'){
                    countGT++;
                }
                if (s.at(i) == 'G' && s.at(i-1) == 'C'){
                    countGC++;
                }
                if (s.at(i) == 'G' && s.at(i-1) == 'G'){
                    countGG++;
                }

            }
        }
    }
// calculating each probablity and printing to the file
    outF << "Probability of AA: " << (float)countAA / num << endl;
    outF << "Probability of AT: " << (float)countAT / num << endl;
    outF << "Probability of AC: " << (float)countAC / num << endl;
    outF << "Probability of AG: " << (float)countAG / num << endl;

    outF << "Probability of CA: " << (float)countCA / num << endl;
    outF << "Probability of CT: " << (float)countCT / num << endl;
    outF << "Probability of CC: " << (float)countCC / num << endl;
    outF << "Probability of CG: " << (float)countCG / num << endl;

    outF << "Probability of TA: " << (float)countTA / num << endl;
    outF << "Probability of TT: " << (float)countTT / num << endl;
    outF << "Probability of TC: " << (float)countTC / num << endl;
    outF << "Probability of TG: " << (float)countTG / num << endl;

    outF << "Probability of GA: " << (float)countGA / num << endl;
    outF << "Probability of GT: " << (float)countGT / num << endl;
    outF << "Probability of GC: " << (float)countGC / num << endl;
    outF << "Probability of GG: " << (float)countGG / num << endl;
}

float gaussian(float m, float sd){ // finding random length for 1000 strands using gaussian
    int a = rand() % 2;
    int b = rand() % 2;
    float c = 0, d = 0;

    c = sqrt(-2 * log(a)) * cos(2 * M_PI * b);
    d = sd * c + m;

    return d;
}

int main(int argc, char** argv){
    ifstream in_file;
    string dna;
    int countLines = 0, sumLines = 0, length = 0;
    float meanLines = 0, varianceLines = 0, stDev = 0;
    string filename = "";

    if (argc > 1){ // typing more than one argument, then use the imput from the command line (file name)
        filename = argv[1];
    }

    while(true){ // opening file - enter correct path or retry
        in_file.open(filename);
        if (in_file.fail()){
            cout << "Could not open file. Please try again." << endl;
        }

        else if (in_file.is_open()){ //if file exists
            while(!in_file.eof()){ // while not the end of the file
                in_file >> dna; //read in from a file
                uppercase(dna);

                length = dna.length();
                sumLines += length; //sum of all the lines
                countLines++; // counting lines

                cout << dna << endl;
            }
            meanLines = (float)sumLines/countLines; //computing the mean
            break;
        }
        else{
            cout << "File does not exist. Enter in a new file" << endl;
        }
        cout << "Enter a file path: ";
        cin >> filename;
        cout << endl;
    }
    in_file.close();

    varianceLines = variance(filename, meanLines, countLines); //variance and st dev
    stDev = sqrt(varianceLines);


    if (!outF){ //error checking out file
        cout << "Error. File was not created." << endl;
    }
    else{ // if its open, proceed
        outF << "Kaitlyn Abdo" << endl;
        outF << "2286311" << endl;
        outF << "CPSC 350 - 03" << endl;
        outF << "Professor Rene German" << endl;

        outF << "The sum of the strands is: " << sumLines << endl;
        outF << "The mean of the strands is : " << meanLines << endl;
        outF << "The variance of the strands is : " << varianceLines << endl;
        outF << "The standard deviation of the strands is : " << stDev << endl;

        bigram(sumLines, filename);

    }
    return 0;
}
