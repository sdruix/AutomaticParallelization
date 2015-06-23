#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <float.h>
#include <cstdlib>
#include <sys/time.h>
#include <algorithm>
#include <getopt.h>
#include "math.h"
#include <cstring>
#include <locale>

using namespace std;
string _includesOnExec;
int _firstExecuted;

class Timer {
    timeval timer[2];
    
public:
    
    timeval start() {
        gettimeofday(&this->timer[0], NULL);
        return this->timer[0];
    }
    
    timeval stop() {
        gettimeofday(&this->timer[1], NULL);
        return this->timer[1];
    }
    
    int duration() const {
        int secs(this->timer[1].tv_sec - this->timer[0].tv_sec);
        int usecs(this->timer[1].tv_usec - this->timer[0].tv_usec);
        
        if (usecs < 0) {
            --secs;
            usecs += 1000000;
        }
        
        return static_cast<int> (secs * 1000 + usecs / 1000.0 + 0.5);
    }
};

string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
void createFolders(string codesFolder, string logFolder, string execFolder) {
    std::stringstream createCodesFolder, createExecFolder, createLogFolder, cleanCodesFolder, cleanExecutablesFolder;
    createCodesFolder << "mkdir " << codesFolder << " > /dev/null";
    system(createCodesFolder.str().c_str());
    createLogFolder << "mkdir " << logFolder << " > /dev/null";
    system(createLogFolder.str().c_str());
    createExecFolder << "mkdir " << codesFolder << "/" << execFolder << " > /dev/null";
    system(createExecFolder.str().c_str());
    cleanCodesFolder << "rm " << codesFolder << "/*.c* ";
    //cout << cleanCodesFolder.str() << endl;
    system(cleanCodesFolder.str().c_str());
    cleanExecutablesFolder << "rm " << codesFolder << "/" << execFolder << "/*.out ";
    //cout << cleanCodesFolder.str() << endl;
    system(cleanExecutablesFolder.str().c_str());
}



std::string getFileExtension(const std::string& FileName) {
    if (FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".") + 1);
    return "";
}

string cleanWhiteSpaces(string toClean) {
    if(!toClean.empty()) {
        while(std::string(toClean).find_first_of(" ")==0){                       
            toClean = std::string(toClean).substr(1,std::string(toClean).length());
        }
        while(std::string(toClean).find_last_of(" ")==std::string(toClean).length()-1){
            toClean = std::string(toClean).substr(0,std::string(toClean).length()-1);
        }
    }
    return toClean;
}

void doPause() {
    
    cin.get(); //pausa
    cout << "Press Key to Continue...\n";
}







inline bool exists(const std::string& name) {
    return ( access(name.c_str(), F_OK) != -1);
}

int main(int argc, char *argv[]) {
    int nextOption;
    string filename = "", name, codesFolder = "filesWithTraces", logFolder = "log";
    
    string traceFiles = "mem_trace.c memtrace.h";
    while ((nextOption = getopt(argc, argv, "f:hHc:I:t:l:")) != -1) {
        switch (nextOption) {
             case 't':
                if(traceFiles.compare("mem_trace.c memtrace.h")==0)
                  traceFiles = "";
                traceFiles = traceFiles+" "+optarg;
                break;
            case 'l':
                logFolder =optarg;
                break;
            case 'c':
                codesFolder = optarg;
                break;
             case 'I':
                _includesOnExec = _includesOnExec + " -I" + optarg;
                break;
            case 'f':
                filename = optarg;
                break;
            case 'H':
            case 'h':
                cout << argv[0] << " "
                        " -[h|H] --help Display this usage information. \n" << endl;
                exit(0);
                break;
            default:
                cout << argv[0] << " "
                        " -[h|H] --help Display this usage information. \n" << endl;
                exit(0);
                
        }
        
    }
    std::stringstream createCodesFolder, createTracesFolder, createLogFolder;
    createCodesFolder << "mkdir " << codesFolder << " > /dev/null";
    system(createCodesFolder.str().c_str());
    if (filename.compare("") == 0 ) {
        cerr << "You Must to Specify the file or a folder of files to transform:" << endl;
        cerr << "-f <filename to convert>" << endl;
        cerr << "-F <folder of files to convert>" << endl;
        exit(-1);
    }
    if (filename.find_last_of("/") >= 0 && filename.find_last_of("/") < filename.length())
        name = filename.substr(filename.find_last_of("/"), filename.length());
    else
        name = filename;
    int extKind = 0;
    string extension = getFileExtension(filename);
    if (extension.compare("c") == 0) {
        extKind = 0;
        name = name.substr(0, name.length() - 2) + "+traces";
    } else if (extension.compare("cpp") == 0) {
        extKind = 1;
        name = name.substr(0, name.length() - 4) + "+traces";
    } else {
        cout << filename << " is not a supported file\n";
    }
    
    
    
    cout << "Starting transformation of file: " << filename << endl;
    string line, firstLine, firstLineAlternative, firstLineNoKeys, firstLineAlternativeNoKeys;
    ifstream preprocessFile(filename);
    int found = 0;
    string includeS = "#include";
    vector<string> includeVector;
    int opened = 0;
    while (getline(preprocessFile, line) && !found) {
        
        // line = cleanWhiteSpaces(line);
        
        string subline = line.substr(0, includeS.length());
        string subsubline = line.substr(0, 2);
        string firstChar = line.substr(0, 1);
        if (subline.compare(includeS) == 0) {
                includeVector.push_back(line);
        }
        
        if (subline.compare(includeS) != 0 && line.compare("") != 0
                && subsubline.compare("//") != 0
                && subsubline.compare("/*") != 0
                && firstChar.compare("#") != 0 && (line.find_first_of("*/")<0 || line.find_first_of("*/")>line.length()) && !opened) {
            if (line.find_first_of("[") >= 0 && line.find_first_of("[") < line.size())
                line = line.substr(0, line.find_first_of("[") + 1);
            int correct = 0;
            for(int n=0;n<line.length();++n){
                if(line[n]!=' ') {
                    correct = 1;
                    break;
                }
            }
            if(correct) {
                firstLine = line;
                firstLineAlternative = firstLine.substr(0,firstLine.find_first_of(" ")+1) + replaceAll(firstLine.substr(firstLine.find_first_of(" "),firstLine.length())," ","");
                
                if(line.find("{")>=0 && line.find("{")<line.length()) {
                    firstLineNoKeys = cleanWhiteSpaces(firstLine.substr(0,firstLine.find_first_of("{")));
                    firstLineAlternativeNoKeys = cleanWhiteSpaces(firstLineAlternative.substr(0,firstLineAlternative.find_first_of("{")));
                }
                
                found = 1;
            }
        } else if(subsubline.compare("/*") == 0) {
            opened = 1;
            if(line.find("*/")>=0 && line.find("*/")<line.length()) {
                opened = 0;
            }
        } else if(line.find("*/")>=0 && line.find("*/")<line.length()) {
            opened = 0;
        }
    }
    if(firstLineNoKeys.empty()) {
        firstLineNoKeys = "bsduifgelawbbuigv bailsadnlnvass+d+¡335r";
    }
    if(firstLineAlternativeNoKeys.empty()) {
        firstLineAlternativeNoKeys = "bsduifgelawbbuigv bailsadnlnvass+d+¡335r";
    }
    preprocessFile.close();
    std::stringstream mergeToAddMPI, deleteTempFile, createTempFile;
    string tempName;
    if (extKind)
        tempName = "temp.cpp";
    else
        tempName = "temp.c";
    createTempFile << "echo '//Temp source code' >" << tempName;
    
    system(createTempFile.str().c_str());
    
    
    
    int check;
    
    mergeToAddMPI << "cat " << filename << " >> " << tempName;
    check = system(mergeToAddMPI.str().c_str());
    if (!(check == 0 || check == 256)) {
        cerr << "Error using command: " << mergeToAddMPI.str().c_str() << "\n";
        exit(-1);
        cerr << "------------------------------------------------\n";
    }
    std::stringstream nameOUT,commandOUT, newNameWithExtendion;
    if (extKind) {
        newNameWithExtendion << name <<".cpp";
        nameOUT << codesFolder << "/" << newNameWithExtendion.str();
                            cout<<nameOUT.str()<<endl;
        commandOUT << "addTracesOnFor-phasec++ -y " << tempName << " -o " << nameOUT.str();  
    } else {
        newNameWithExtendion << name <<".c";
        nameOUT << codesFolder << "/" << newNameWithExtendion.str();
                            cout<<nameOUT.str()<<endl;
        commandOUT << "addTracesOnFor-phasecc -y " << tempName << " -o " << nameOUT.str() << " -std=c99 ";
    }
    if(_includesOnExec.compare("")!=0)
         commandOUT <<_includesOnExec;
    
    cout<<commandOUT.str()<<endl;
    check = system(commandOUT.str().c_str());
    if (!(check == 0 || check == 256)) {
        cerr << "Error using command: " << commandOUT.str().c_str() << "\n";
        exit(-1);
        cerr << "------------------------------------------------\n";
    }
    cout << "------------------------------------------------\n";
    ifstream postprocessFile(nameOUT.str());
    found = 0;
    int lines = 0;
    while (getline(postprocessFile, line)) {
        if (line.find(firstLine) == 0 || line.find(firstLineAlternative) == 0 ||
                line.find(firstLineNoKeys) == 0 || line.find(firstLineAlternativeNoKeys) == 0
                || found) {
            includeVector.push_back(line);
            found = 1;
            lines++;
        }
        
    }
    postprocessFile.close();
    
    if(found) {
        ofstream transFile;
        transFile.open(nameOUT.str(), ios::trunc);
        
        for (unsigned int incN = 0; incN < includeVector.size(); ++incN) {
            transFile << includeVector[incN] << "\n";
            lines++;
        }
        transFile.close();
        if (lines == 0) {
            cerr<<"deleting generated file"<<endl;
            stringstream rmFile;
            rmFile << "rm " << nameOUT.str();
            system(rmFile.str().c_str());
        }
    } else {
        cerr<<"Input file includes could not be compressed again after transformation, please substitute the expansion on these on"
                "the generated output file before execution.";
        cin.get();
        
    }
    name = name.substr(0,name.find_last_of("."));
    cout<<"create exec folder"<<endl;
    createTracesFolder << "mkdir " << codesFolder << name <<  " > /dev/null";
    system(createTracesFolder.str().c_str());
    cout<<"Compiling generated file..."<<endl;
    std::stringstream complilationCommand;
    
    
    
  
    if(extKind)
        complilationCommand <<" g++";
    else
        complilationCommand <<" gcc";
    complilationCommand << " -std=c99 -fopenmp -lm "
            <<codesFolder<< newNameWithExtendion.str() << traceFiles
            << " -o ./"<< codesFolder << name <<"/"<<name << ".out ";
     if(_includesOnExec.compare("")!=0)
        complilationCommand << _includesOnExec;
    cout<<complilationCommand.str()<<endl;
    check = system(complilationCommand.str().c_str());
    if (!(check == 0 || check == 256)) {
        cerr << "Error using command: " << complilationCommand.str().c_str() << "\n";
        exit(-1);
        cerr << "------------------------------------------------\n";
    }

    cout<<"Executing generated file..."<<endl;
    std::stringstream executeCommand;
    executeCommand << "./"<< codesFolder << name <<"/"<<name << ".out";
    cout<<executeCommand.str()<<endl;
    check = system(executeCommand.str().c_str());
    if (!(check == 0 || check == 256)) {
        cerr << "Error using command: " << executeCommand.str().c_str() << "\n";
        exit(-1);
        cerr << "------------------------------------------------\n";
    }
    
    
    logFolder = codesFolder + logFolder;
    cout<<"creating log folder"<<endl;
    createLogFolder << "mkdir " << logFolder << " > /dev/null";
    system(createLogFolder.str().c_str());
    stringstream mvResult;
    mvResult << "mv mem.log "<< logFolder <<"/";
    system(mvResult.str().c_str());
    
    
    
    
    return 0;
}


