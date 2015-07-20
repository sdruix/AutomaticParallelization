#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
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

// just to check the numbers are right
long totalcombs(int n, int r){
long c=1;
if (r > n) return 0;
for (long d=1; d <= r; d++) {
c *= n--;
c /= d;
}
return c;
}


int getdir(string dir, vector<string> &files);
std::string getFileExtension(const std::string& FileName);
void doPause();
void compile(vector<string> files, string cP, string codesDir, string execDir, int pause, int verbose);
void execute(vector<string> files, string csvP, string errP, string codesDir, string execDir, int rep, int tries, int pause);
void compileAndExecute(string codesFolder, string execFolder, string logFolder, int methods, int rep, int tries, int pause, int verbose, string logFilename);
int doTransform(int inlin, int extKind,string codesFolder, string filename, string name);

int generateVersions(int call, int cod, int i, int j, string codesFolder, string filename, int extKind, int inlin);
void testFile(string filename, string logFolder, int extKind, int step, string logFilename);
void createFolders(string codesFolder, string logFolder, string execFolder);

int main(int argc, char *argv[]);


void binary(int number, int indx,int *array, int size) {
    int remainder;
    if(number <= 1) {
        array[indx]=number;
        return;
    }
 
 
    remainder = number%2;
    binary(number >> 1,indx-1, array, size);
    array[indx]=remainder;
}
int decimal(int *array, int size) {
    int power = size-1;
    int num = 0;
    for(int i=0;i<size;++i,--power){
        if(array[i])
            num+=pow(2,power) ;
    }
    return num;
}
int dec2dec(int number, int indx,int *array, int size) {
    binary(number, indx, array, size);
    int num = decimal(array,size);
    return num;
}
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

int getdir(string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    struct stat st;
    if ((dp = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    
    while ((dirp = readdir(dp)) != NULL) {
        if(string(dirp->d_name).compare(".")!=0
                && string(dirp->d_name).compare("..")!=0)
            
            lstat(dirp->d_name, &st);
            if(!S_ISDIR(st.st_mode))
                files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

std::string getFileExtension(const std::string& FileName) {
    if (FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".") + 1);
    return "";
}

void doPause() {
    
    cin.get(); //pausa
    cout<<"Press Key to Continue...\n";
}

void compile(vector<string> files, string cP, string codesDir, string execDir, int pause, int verbose) {
    ofstream compFile;
    int numFiles = 0;
    
    for (int i = 0; i < (signed)files.size(); i++) {
        if (files[i].length() > 4) {
            string extension = files[i].substr(files[i].length() - 4, files[i].length());
            if (extension == ".cpp") {

                if (numFiles > 0) {
                    compFile.open(cP.c_str(), ios::app);
                } else {
                    compFile.open(cP.c_str(), ios::trunc);
                }
                cout << "------------------------------------------------\n";
                cout << "Compiling " << files[i] << endl;
                compFile << "---------------------------Compiling " << files[i]
                        << "-------------------------" << "\n" << endl;
                compFile.close();
                std::stringstream complilationCommand, complilationCommandV;
                string name = files[i].substr(0, files[i].length() - 2);

                complilationCommand << "capsmc --codelet-path "<<codesDir<<"-d2 --nvcc-options -O3,-use_fast_math,-arch,sm_13 g++ -p -w -lm -lrt -fopenmp -o ./"
                        << codesDir << "/" << execDir
                        << "/" << name << ".out ./"
                        << codesDir << "/" << files[i]
                        << " 2>> " << cP << "\n";
                int check = system(complilationCommand.str().c_str());
                if (!(check == 0 || check == 256)) {
                    cerr << "Error using command: " << complilationCommand.str().c_str() << "\n";
                    exit(-1);
                    cerr << "------------------------------------------------\n";
                }
                cout << "------------------------------------------------\n";
                if (verbose) {
                    complilationCommandV << "capsmc --codelet-path "<<codesDir<<" -d2 --nvcc-options -O3,-use_fast_math,-arch,sm_13  g++ -p -w -lm -lrt -fopenmp -o ./"
                            << codesDir << "/" << execDir
                            << "/" << name << ".out ./"
                            << codesDir << "/" << files[i] << "\n";
                    system(complilationCommandV.str().c_str());
                }


                if (pause) {
                    doPause();
                }
            }
            extension = files[i].substr(files[i].length() - 2, files[i].length());
            if (extension == ".c") {

                if (numFiles > 0) {
                    compFile.open(cP.c_str(), ios::app);
                } else {
                    compFile.open(cP.c_str(), ios::trunc);
                }
                cout << "------------------------------------------------\n";
                cout << "Compiling " << files[i] << endl;
                compFile << "---------------------------Compiling " << files[i]
                        << "-------------------------" << "\n" << endl;
                compFile.close();
                std::stringstream complilationCommand, complilationCommandV;
                string name = files[i].substr(0, files[i].length() - 2);

                complilationCommand << "capsmc --codelet-path "<<codesDir<<" -d2 --nvcc-options -O3,-use_fast_math,-arch,sm_13 --codelet-required  gcc -p -w -lm -lrt -fopenmp -o ./"
                        << codesDir << "/" << execDir
                        << "/" << name << ".out ./"
                        << codesDir << "/" << files[i]
                        << " 2>> " << cP << "\n";
                int check = system(complilationCommand.str().c_str());
                if (!(check == 0 || check == 256)) {
                    cerr << "Error using command: " << complilationCommand.str().c_str() << "\n";
                    exit(-1);
                    cerr << "------------------------------------------------\n";
                }
                cout << "------------------------------------------------\n";
                if (verbose) {
                    complilationCommandV << "capsmc --codelet-path "<<codesDir<<" -d2 --nvcc-options -O3,-use_fast_math,-arch,sm_13 --codelet-required  gcc -p -w -lm -lrt -fopenmp -o ./"
                            << codesDir << "/" << execDir
                            << "/" << name << ".out ./"
                            << codesDir << "/" << files[i] << "\n";
                    system(complilationCommandV.str().c_str());
                }


                if (pause) {
                    doPause();
                }
            }
            numFiles++;
        }

    }
    if (numFiles <= 0) {
        cerr << "------------------------------------------------\n";
        cerr << "No *.cpp or *.c files in folder: " << codesDir << "\n" << endl;
        cerr << "------------------------------------------------\n";
        exit(-1);
    }

}
std::string createSignature(std::string filename){
    int transferNum =0;
    int lvl1A[4];
    int lvl2A[2];
    string transfer[5] = {"auto", "atfirstIn", "atfirstOut", "atfirstcallINOut", "atfirstcallIN"};
    string pragma_confLVL1[4] = {"Adv_load","Alloc","Rel","delStore"};
    string pragma_confLVL2[2] = {"Asyn", "NoUpdate"};

    std::cout<<"Describing signature of filename "<<filename<<":\n";
    for (int i = 0; i<4;++i){
        if(filename.find(pragma_confLVL1[i])>=0 && filename.find(pragma_confLVL1[i])<filename.length() && filename.length()-4>=pragma_confLVL1[i].length()) {
            lvl1A[i]=1;
            std::cout<<pragma_confLVL1[i]<<" finded\n";
        } else {
            lvl1A[i]=0;
        }
    }
    for (int i = 0; i<2;++i){
        if(filename.find(pragma_confLVL2[i])>=0 && filename.find(pragma_confLVL2[i])<filename.length() && filename.length()-4>=pragma_confLVL2[i].length()) {
            lvl2A[i]=1;
            std::cout<<pragma_confLVL2[i]<<" finded\n";
        } else {
            lvl2A[i]=0;
        }
    }
    for (int i = 0; i<5;++i){
        if(filename.find(transfer[i])>=0 && filename.find(transfer[i])<filename.length() && filename.length()-4>=transfer[i].length()) {
            std::cout<<transfer[i]<<" finded\n";
            transferNum=i;
        }
    }
    std::cout<<"Final signature:\n";
    
    for(int i=0;i<4;++i){
        if(i>0)
            std::cout<<", ";
        std::cout<<lvl1A[i];
    }
    
    std::cout<<" -> "<<decimal(lvl1A, 4)<<"\n";
    
    for(int i=0;i<2;++i){
        if(i>0)
            std::cout<<", ";
        std::cout<<lvl2A[i];
    }
    
    std::cout<<" -> "<<decimal(lvl2A, 2)<<"\n";
    
    std::stringstream signature;
    signature << decimal(lvl1A, 4) <<", "<<decimal(lvl2A,2)<<", "<<transferNum <<";";
    return signature.str();
    
}
void execute(vector<string> files, string csvP, string errP, string codesDir, string execDir, int rep, int tries, int pause, int energy) {
    std::cout.imbue(std::locale("es_ES.UTF-8"));
    int numFiles = 0;
    Timer tm;
    ofstream csvOut, execErrorsFile;


    ifstream inFile(csvP.c_str());
    string line;
    std::stringstream cpuTimes;


    int n = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n') + 1;
    ifstream inFile2(csvP.c_str());
    string firstS = "Original without OpenMp";
    string legend = "Version/Measure";
    if (n >= 3) {
        for (int nL = 0; nL < 4; ++nL) {
            getline(inFile2, line);
            istringstream linestream(line);
            string item;
            getline(linestream, item, ';');
            if (nL == 1 && item.compare(firstS) != 0) {
                nL = 4;
            } else {
                if (nL == 0 && item.compare(legend) != 0) {
                    if(energy){
                        cpuTimes << "Version/Measure;Signature;Time Expended(ms.); Energy Consumtion(J.); \n";
                    } else {
                        cpuTimes << "Version/Measure;Signature;Time Expended(ms.); \n";
                    }
                } else {
                    cpuTimes << line << "\n";
                }

            }
        }
    } else {
        if(energy)
            cpuTimes << "Version/Measure;Signature;Time Expended(ms.); Energy Consumtion(J.); \n";
        else
            cpuTimes << "Version/Measure;Signature;Time Expended(ms.); \n";
    }
    csvOut.open(csvP.c_str(), ios::trunc);
    csvOut << cpuTimes.str();
    csvOut.close();

    double cpu_time_used;
/*
     for (unsigned int i = 0; i < files.size(); i++) {
        if (files[i].length() > 4) {
            string extension = files[i].substr(files[i].length() - 4, files[i].length());
            if (extension == ".out") {
                cout<<i<<" -"<<files[i]<<" -> "<<extension<<endl;
                
            }
        }
     }
    cin.get();
 * */
    for (unsigned int i = 0; i < files.size(); i++) {
        if (files[i].length() > 4) {
            string extension = files[i].substr(files[i].length() - 4, files[i].length());
            if (extension == ".out") {

                numFiles++;
                csvOut.open(csvP.c_str(), ios::app);
                if (numFiles > 1) {
                    execErrorsFile.open(errP.c_str(), ios::app);
                } else {
                    execErrorsFile.open(errP.c_str(), ios::trunc);

                }
                cout << "------------------------------------------------\n";
                cout << "Executing ("<<codesDir<<") "<< files[i] << endl;
                csvOut << files[i]
                        << ";";
                csvOut << createSignature(files[i]);
                execErrorsFile << "---------------------------Executing ("<<codesDir<<") "<< files[i]
                        << "-------------------------" << endl;
                csvOut.close();
                execErrorsFile.close();
                std::stringstream executeCommand, energyCommand, executeErrorsCommand;
                executeCommand << "./"
                        << codesDir << "/" << execDir
                        << "/" << files[i] << " >> " << errP;
                executeErrorsCommand << "./"
                        << codesDir << "/" << execDir
                        << "/" << files[i] << " 2>> " << errP;
                cpu_time_used = 0;

                int failed=0, totalFail=0;
                for (int it = 0; it < rep; ++it) {
                    cout << "*Repetition(Time): " << it + 1 << "*\n" << endl;
                    double minimumTime = DBL_MAX;
                    int it1 = 0;
                    for (it1 = 0; it1 < tries; ++it1) {
                        if(tries>0)
                        cout << it1 << "...";
                        tm.start();
                        int check = system(executeCommand.str().c_str());
                        std::cout<<"C1: "<<check<<"\n";
                        if (check != 0 && check !=256)  {
                            failed++;
                            cerr << "Error using command: " << executeCommand.str().c_str() << "\n";
                           // exit(-1);
                            cerr << "------------------------------------------------\n";
                        }
                        tm.stop();
                        
                        if (tm.duration() < minimumTime) {
                            minimumTime = (double) tm.duration();
                        }
                        if(tries>0)
                        cout << "\n" << endl;
                    }
                    if(failed==tries){
                        totalFail++;
                    }
                    if (failed != it1) {
                        cpu_time_used += minimumTime;
                    }
                    failed = 0;
                }
                //cout<<"R: "<<rep<<endl;
                //cout<<"TF: "<<totalFail<<endl;
                //cout<<"TIM: "<< cpu_time_used <<endl;
                
                
                execErrorsFile.open(errP.c_str(), ios::app);
                execErrorsFile << system(executeErrorsCommand.str().c_str());
                execErrorsFile.close();
                double exec = cpu_time_used / (rep-totalFail);
                //cout<<"DTIM: "<< exec<<endl;
                csvOut.imbue(std::locale("es_ES.UTF-8"));
                csvOut.open(csvP.c_str(), ios::app);
                csvOut << exec << ";";
                if(energy){
                    double numexec = (10000/exec)*10;
                    ofstream codeEnergy;
                    system("touch energy.sh");
                    system("chmod 777 energy.sh");
                    codeEnergy.open("energy.sh", ios::trunc);
                    codeEnergy<<"#!/bin/bash\n"
                            << "export HMPPRT_PATH=./"<<codesDir<<"\n"
                            <<"for run in {1.."<<ceil(numexec)<<"}; do  "<<"./"
                            << codesDir<<"/"  << execDir
                            << "/" << files[i] << ";done";
                    codeEnergy.close();
                    energyCommand <<"conso-task.sh --res 10 --sum ./energy.sh > " << "temp.txt";
                    cout<<"Measuring energy: "<<"1.."<<ceil(numexec)<<endl;
                    std::stringstream energyString;
                    double totalE=0.0;
                   // cout<<"NEE: "<<ceil(numexec)<<endl;
                   // cin.get();
                    failed = 0;
                    for (int it = 0; it < rep; ++it) {
                        cout << "*Repetition(Energy): " << it + 1 << "*\n" << endl;
                        int check = system(energyCommand.str().c_str());
                        std::cout<<"C2: "<<check<<"\n";
                        if (check != 0) {
                            failed++;
                            cerr << "Error using command: " << energyCommand.str().c_str() << "\n";
        //                    exit(-1);
        //                    cerr << "------------------------------------------------\n";
                        }
                        cout << "------------------------------------------------\n";

                        ifstream auxCsv("temp.txt");

                        getline(auxCsv, line);
                        getline(auxCsv, line);
                        istringstream linestream(line);
                        string item;
                        string item1;
                        getline(linestream, item, ';');
                        istringstream linestream1(item);
                        getline(linestream, item, ';');
                        istringstream linestream2(item);
                        getline(linestream1, item1, ':');
                        getline(linestream1, item1, ':');
                        item1= item1.substr(0,item1.find(" J"));

                        totalE += atoi(item1.c_str());
                        cout<<"E: "<<atoi(item1.c_str())<<endl;
                    }

                    //cout<<"TE: "<<totalE/ceil(numexec)<<endl;
                    energyString.imbue(std::locale("es_ES.UTF-8"));
                    energyString<< totalE/(rep-failed)/ceil(numexec);
                    cout<<"To write: "<<energyString.str()<<endl;
                    //cin.get();
                    //csvOut.open(csvP.c_str(), ios::app);
                    csvOut << energyString.str().c_str()<<";";
                    
                } 
                csvOut << "\n";
                csvOut.close();
                if (pause) {
                    doPause();
                }

            }
        }
    }
    if (numFiles <= 0) {
        cerr << "------------------------------------------------\n";
        cerr << "No *.out files in folder: " << codesDir << "/" << execDir << "\n" << endl;
        cerr << "------------------------------------------------\n";
      //  exit(-1);
    }


}

void compileAndExecute(string codesFolder, string execFolder, string logFolder, int methods, int rep, int tries, int pause, int verbose, string logFilename, int energy) {
    string codesDir = codesFolder;
    string execDir = execFolder;


    vector<string> files = vector<string > ();

    std::stringstream logPath;
    logPath << logFolder << "/";


    if (methods == 0 || methods == 2) {
        std::stringstream compFilePath;
        getdir(codesDir, files);
        compFilePath << logPath.str() << "compilation.txt";
        string cP = compFilePath.str();
        compile(files, cP, codesDir, execDir, pause, verbose);
    }
    if (methods == 0 || methods == 2 || methods == 3) {
        std::stringstream csvFilePath, execErrorsPath, execF;
        execF << codesDir <<"/"<< execDir;
        getdir(execF.str().c_str(), files);
        csvFilePath << logPath.str() << logFilename;
        execErrorsPath << logPath.str() << "execErrors.txt";

        string csvFP = csvFilePath.str();
        string errP = execErrorsPath.str();
        execute(files,csvFP, errP, codesDir, execDir, rep, tries, pause, energy);

    }


}

int doTransform(int inlin, int extKind,string codesFolder, string filename, string name) {
    
    
    std::stringstream nameF, nameOUT, commandOUT, commandIN, nameFinal, commandRM;
    system("touch outlinedFunctions.data");
    system("rm outlinedFunctions.data");
    nameF << name;
    nameOUT << codesFolder << "/" << name << ".c";
    nameFinal << codesFolder << "/" << name << ".cpp";
    
    
    cout << "Outlineing....\n" << endl;
    if(inlin){
        if (extKind) {
            commandOUT << "outline-phasec++ -y -o " << nameFinal.str() << " " << filename << std::endl;
        } else {
            commandOUT << "outline-phasecc -y -o " << nameOUT.str() << " " << filename << std::endl;
        }
    } else {
        if (extKind) {
            commandOUT << "outline-phasec++ -y -o " << nameFinal.str() << " " << filename << std::endl;
        } else {
            commandOUT << "outline-phasecc -y -o " << nameOUT.str() << " " << filename << std::endl;
        }
        
    }

    cout << commandOUT.str() << endl;
    if(1)
    commandOUT <<" > /dev/null";
    //std::cin.get();
    int check = system(commandOUT.str().c_str());
    if (!(check == 0 || check == 256)) {
        cerr << "Error using command: " << commandOUT.str().c_str() << "\n";
        exit(-1);
        cerr << "------------------------------------------------\n";
    }
    cout << "------------------------------------------------\n";
    //system("rm csv.data");

    cout << "------------------------------------------------\n";
    
    if (inlin) {
            cout << "Inlineing....\n" << endl;

            if (extKind) {
                 commandIN << "inline-phasec++ -y -o " << nameFinal.str() << " " << nameFinal.str() << std::endl;
            } else {
                commandIN << "inline-phasecc -y -o " << nameOUT.str() << " " <<nameOUT.str() << std::endl;
            }
           

            cout << commandIN.str() << endl;
            if(1)
                commandIN <<" 2> /dev/null";
            int check = system(commandIN.str().c_str());
            if (!(check == 0 || check == 256)) {
                cerr << "Error using command: " << commandIN.str().c_str() << "\n";
                exit(-1);
                cerr << "------------------------------------------------\n";
            }
            
            
    }
    
    int diffResult;
    std::string diffExt;
    if(extKind)
        diffExt = ".cpp";
    else 
        diffExt = ".c";
    vector<string> files = vector<string > ();
    getdir(codesFolder, files);
    for (int i = 0; i < (signed)files.size(); i++) {
        if (files[i].length() > (unsigned)diffExt.length()) {
            string extension = files[i].substr(files[i].length() - diffExt.length(), files[i].length());
            stringstream completeFN;
            completeFN << codesFolder<<"/"<< files[i];
            if (extension.compare(diffExt)==0 && !(completeFN.str().compare(nameOUT.str())==0 || completeFN.str()
                    .compare(nameFinal.str())==0)) {
                stringstream diffCommand;
                if(extKind){
                    diffCommand << "diff ./"<< nameFinal.str() << " ./";
                    diffExt = ".cpp";

                } else {
                    diffCommand << "diff ./"<< nameOUT.str() << " ./";
                    diffExt = ".c";
                }
                diffCommand <<completeFN.str()<<" > /dev/null";
               // cin.get();
                diffResult=system(diffCommand.str().c_str());
                //std::cout<<diffResult<<"\n";
                //cin.get();
                if(diffResult==0) {
                    //std::cout<<"R: "<<diffResult<<"\n";
                    //cin.get();
                    stringstream rmCommand;
                    if(extKind)
                        rmCommand << "rm ./"<< nameFinal.str();
                    else
                        rmCommand << "rm ./"<< nameOUT.str();
                    system(rmCommand.str().c_str());
                    
                    return 0;
                }
                if(diffResult==512){
                    return 0;
                } else {
	           stringstream correctCreation;
		   if(extKind)
		   	correctCreation<<"[ -f "<<nameFinal.str()<<"] && echo 1 || echo 0 > correct.data";
		   else
			correctCreation<<"[ -f "<<nameOUT.str()<<"] && echo 1 || echo 0 > correct.data";
		   system(correctCreation.str().c_str());
		   ifstream correctFileCheck("correct.data");
		   string num;
		   getline(correctFileCheck, num);	
		   if(atoi(num.c_str())==0){
			return 0;
		   }
		}
            }
        }
    }
    //std::cout<<"R: "<<1<<"\n";
    //cin.get();
    ifstream outFun("numTransform.data");
    string num;
    getline(outFun, num);
//    cout<<"N: "<<num<<endl;
//    cin.get();
    int numTransform = atoi(num.c_str());
//    cout<<"N+1: "<<numTransform+1<<endl;
//    cin.get();
    ofstream transFile;
    transFile.open("numTransform.data", ios::trunc);
    transFile<<numTransform+1<<"\n";
    transFile.close();
    return 1;
}

int generatePragmaCombinationVersions(int inlin, int extKind,string codesFolder, string filename, string name){
    //Test all combinations
    ofstream transFile;
    ifstream outFun("outlinedFunctions.data");
    vector<string> outlinedFunctions;
    vector<string> fixedFunctions;
    string line;
    int numFunctions=0;
    while (getline(outFun, line)) {
        //std::cout<<line<<"\n";
        if(line.find("- fixed")>0 && line.find("- fixed")<line.length()) {
               fixedFunctions.push_back(line);
        } else  if(line.find("- check")>0 && line.find("- check")<line.length()){
                outlinedFunctions.push_back(line);
                numFunctions++;
        }
    }
    int numCombinations =0;
    if(outlinedFunctions.size()>1){
        vector<int> indx;
        
        int n=outlinedFunctions.size();
        int j=1;
        int k=outlinedFunctions.size();

            for(int twk=j;twk<=k;twk++){
                    int r=twk;
                    int ccount=1;
                    bool done=true;

                    for(int iwk=0;iwk<r;iwk++){
                            indx.push_back(iwk);
                    }
                            while(done){
                                    std::stringstream finalName;
                                    finalName<<name;
                                    std::stringstream nameF;
                                    nameF.clear();
                                    //cout<<"("<<twk;
                                    
                                    nameF << "_"<<twk<<"b_";
                                    done=false;
                                    transFile.open("toTransform.data", ios::trunc);
                                    for(int fixIn=0;fixIn<(signed)fixedFunctions.size();++fixIn){
                                        stringstream funGenericName;
                                        funGenericName << fixedFunctions[fixIn].substr(0,10);
                                        funGenericName << fixedFunctions[fixIn].substr(fixedFunctions[fixIn].find("_ol_"),fixedFunctions[fixIn].length());
                                        transFile<<funGenericName.str()<<"\n";
                                    }

    //                                cout << ccount << " of " << total << " ";

                                    for(int owk=0;owk<r;owk++){
                                            nameF <<"-"<<indx[owk];
                                    //      cout<<"-"<<owk;
    //                                        cout << outlinedFunctions[indx[owk]] << ", ";
                                            stringstream funGenericName;
                                            funGenericName << outlinedFunctions[indx[owk]].substr(0,10);
                                            funGenericName << outlinedFunctions[indx[owk]].substr(outlinedFunctions[indx[owk]].find("_ol_"),outlinedFunctions[indx[owk]].length());
                                            transFile<<funGenericName.str()<<"\n";
                                    }
                                    //cout<<"-"<<ccount<<")";
                                    //nameF<<"-"<<ccount<<"_";
                                    ccount++;
    //                                cout << "\n";



                                    //scout<<"Final Name: "<<finalName.str()<<"\n";
    //                                doPause();

                                    transFile.close();
                                    finalName<<nameF.str();
                                    if(twk<numFunctions) {
                                        numCombinations+=doTransform(inlin, extKind,codesFolder, filename, finalName.str());
                                    }
                                   // std::cin.get();
                                    //doPause();
                                    finalName.clear();
                                    for(int iwk=r-1;iwk>=0;iwk--){
                                            if(indx[iwk]<=(n-1)-(r-iwk)){
                                                    indx[iwk]++;
                                                            for(int swk=iwk+1;swk<r;swk++){
                                                                    indx[swk]=indx[swk-1]+1;
                                                            }
                                                    iwk=-1;
                                                    done=true;
                                            }	
                                    }	
                        }

                cout << " --------------------------- " << endl;
                indx.clear();

        }
    }
   // doPause();
    return numCombinations;
    
}




int generateVersions(int lvl1, int lvl2, int j, string codesFolder, string filename, int extKind, int inlin) {

    ofstream csv,transformations;
    string transfer[6] = {"", "auto", "atfirstIn", "atfirstOut", "atfirstcallINOut", "atfirstcallIN"};
    string pragma_confLVL1[5] = {"","Adv_load","Alloc","Rel","delStore"};
    string pragma_confLVL2[3] = {"","Asyn", "NoUpdate"};
    
    int *lvl1A;
    int *lvl2A;
    lvl1A = new int[4];
    lvl2A = new int[2];
    memset(lvl1A, 0, 4*sizeof(int));
    memset(lvl2A, 0, 2*sizeof(int));
    int indx = 3;
    binary(lvl1,indx, lvl1A,4);
    indx = 1;
    binary(lvl2,indx, lvl2A,2);

    int numCombinations =0;
    
    for (int t = j; t >= 0; --t) {
        stringstream name;
        for (int idx1=0;idx1<4;++idx1){
            if(idx1==0)
                std::cout<<"LVL1: ";
            if(idx1>0)
                std::cout<<", ";
            if(lvl1A[idx1]>0)
                name << pragma_confLVL1[idx1+1];
            std::cout<<lvl1A[idx1];
        }
        std::cout<<"\n";
        for (int idx2=0;idx2<2;++idx2){
            if(lvl2A[idx2]>0)
                name << pragma_confLVL2[idx2+1];
        }
        if(name.str().compare("")==0)
                name << "simple";
        cout << "------------------------------------------------\n";
        std::cout<<"Stored : "<<lvl1<<","<<lvl2<<","<<t<<"\n";
        csv.open("csv.data", ios::trunc);
        csv <<lvl1<<","<<lvl2<<","<<t<<"\n";
        csv.close();
        transformations.open("toTransform.data", ios::trunc);
        transformations << "all\n";
        transformations.close();
        name << transfer[t];
        
        numCombinations+= doTransform(inlin, extKind,codesFolder, filename, name.str());
        numCombinations+= generatePragmaCombinationVersions(inlin, extKind,codesFolder, filename, name.str());
    } 
    delete lvl1A;
    delete lvl2A;
    return numCombinations;
}


void testFile(string filename, string logFolder, int extKind, int step, string logFilename, int energy) {
    std::stringstream checkFile2trans, checkFile2transMP, timeFilePath, logPath;
    Timer tm;
    ofstream csvOut;
    logPath << logFolder << "/";
    timeFilePath << logPath.str() << logFilename;

    if (!step) {
        csvOut.open(timeFilePath.str().c_str(), ios::trunc);
        if(energy)
            csvOut << "Version/Measure;Signature;Time Expended(ms.); Energy Consumtion(J.); \n";
        else
            csvOut << "Version/Measure;Signature;Time Expended(ms.)\n";
    } else {
        csvOut.open(timeFilePath.str().c_str(), ios::app);
    }

    system("clear");

    if (!step) {
        cout << "---------------------------Compiling original file without transforms---------------------------\n";
    } else {
        cout << "---------------------------Compiling transformed file---------------------------\n";
    }
    std::stringstream filename_justOMP;
    int check;
    filename_justOMP << filename << "omp.c";
    ifstream origFile(filename.c_str());
    std::string lineF;
    std::ofstream ompFile;


    std::cout<<"Generated File OpenMP: "<<filename_justOMP.str()<<std::endl;
    ompFile.open(filename_justOMP.str().c_str(), std::ios::trunc);
    while(getline(origFile, lineF)) {
        if(lineF.find("pragma")>0 && lineF.find("pragma")<lineF.length()) {
            if(lineF.find("check")>0 && lineF.find("check")<lineF.length()) {
                std::cout<<"Pragma line detected: "<<lineF<<std::endl;
                lineF = lineF.substr(0,lineF.find("check"));
                std::cout<<"Pragma line detected(mod): "<<lineF<<std::endl;
            } 
            if(lineF.find("fixed")>0 && lineF.find("fixed")<lineF.length()) {
                std::cout<<"Pragma line detected: "<<lineF<<std::endl;
                lineF = lineF.substr(0,lineF.find("fixed"));
                std::cout<<"Pragma line detected(mod): "<<lineF<<std::endl;
            }
        }
        ompFile <<lineF <<"\n";
    }
    ompFile.close();
    origFile.close();

    if (!step) {
        std::cout << "With OpenMp...\n";
        if (extKind) {
            checkFile2transMP << "g++ " << filename_justOMP.str().c_str() << " -O3 -fopenmp -o MP.out";
        } else {
            checkFile2transMP << "gcc " << filename_justOMP.str().c_str() << " -O3 -fopenmp -o MP.out";
        }
        check = system(checkFile2transMP.str().c_str());
        if (!(check == 0)) {
            cerr << "Error compiling original file (OpenMP): " << filename_justOMP.str() << "\n";
            exit(-1);
        } else {
            cout << "compilation OK\n";
        }
    }
    cout << "Without OpenMp...\n";
    if (extKind) {
        checkFile2trans << "g++ " << filename_justOMP.str().c_str() << " -O3 -o noMP.out";
    } else {
        checkFile2trans << "gcc " << filename_justOMP.str().c_str() << " -O3 -o noMP.out";
    }
    check = system(checkFile2trans.str().c_str());
    if (!(check == 0)) {
        cerr << "Error compiling original file (No OpenMP): " << filename << "\n";
        exit(-1);
    } else {
        cout << "compilation OK\n";
    }


    if (!step) {
        csvOut << "Original without OpenMp;0,0,0,0;";
    } else {
        csvOut << "Transformed without OpenMp;0,0,0,0;";
    }
    std::cout<<"Measuring time..."<<std::endl;
    
    std::cout<<"Without OpenMP"<<std::endl;
    tm.start();
    check = system("./noMP.out");
    tm.stop();
    if (!(check == 0 || check == 256)) {
        cerr << "Execution error of file: " << "./noMP.out" << "\n";
    } else {
        cout << "execution OK\n";
    }
   
    csvOut << tm.duration()<<";";
  
    
    if(energy) {
        std::cout<<"Measuring ENERGY..."<<std::endl;
        double numexec = (10000/tm.duration())*10;
        if (numexec < 1)
	numexec = 1;
        std::cout<<"Time expeded("<<tm.duration()<<") -> rep: "<<numexec<<std::endl;
	std::stringstream energyCommand, csvAux;
	string line;
    	ofstream codeEnergy;
	system("touch energy.sh");
	system("chmod 777 energy.sh");
	codeEnergy.open("energy.sh", ios::trunc);
	codeEnergy<<"#!/bin/bash\n"
		<<"for run in {1.."<<ceil(numexec)<<"}; do  "<<"./noMP.out;done";
	codeEnergy.close();
	energyCommand <<"conso-task.sh --res 10 --sum ./energy.sh > " << "temp.txt";
	check = system(energyCommand.str().c_str());
	    if (check != 0) {
		cerr << "Error using command: " << energyCommand.str().c_str() << "\n";
	    }
	 ifstream auxCsv("temp.txt");
	getline(auxCsv, line);
	getline(auxCsv, line);
	istringstream linestream(line);
	string item;
	string item1;
	getline(linestream, item, ';');
	istringstream linestream1(item);
	getline(linestream, item, ';');
	istringstream linestream2(item);
	getline(linestream1, item1, ':');
	getline(linestream1, item1, ':');
	item1= item1.substr(0,item1.find(" J"));
	csvAux.imbue(std::locale("es_ES.UTF-8"));
        csvAux<< atoi(item1.c_str()) << ";";
        csvOut << csvAux.str().c_str();
    } 
        csvOut << "\n";
	std::cout<<"DOne"<<std::endl;
   

    if (!step) {
        cout << "With OpenMp..." << endl;
        csvOut << "Original with OpenMp;0,0,0,0;";
	std::cout<<"Measuring time..."<<std::endl;
        tm.start();
        check = system("./MP.out");
        tm.stop();
	if (!(check == 0 || check == 256)) {
	cerr << "Execution error of file: " << "./MP.out" << "\n";
        } else {
            cout << "execution OK\n";
        }
	
        csvOut << tm.duration() <<";";
	
        if(energy){
            std::cout<<"Measuring energy..."<<std::endl;
            double numexec = (10000/tm.duration())*10;
            if (numexec < 1)
		numexec = 1;
            std::stringstream energyCommand2, csvAux;
            string line;
            ofstream codeEnergy;
            std::cout<<"Time expeded("<<tm.duration()<<") -> rep: "<<numexec <<std::endl;
            codeEnergy.open("energy.sh", ios::trunc);
            codeEnergy<<"#!/bin/bash\n"
                    <<"for run in {1.."<<ceil(numexec)<<"}; do  "<<"./MP.out;done";
            codeEnergy.close();
            energyCommand2 <<"conso-task.sh --sum ./energy.sh 10 > " << "temp.txt";
            check = system(energyCommand2.str().c_str());
                if (check != 0) {
                    cerr << "Error using command: " << energyCommand2.str().c_str() << "\n";
                }
            ifstream auxCsv("temp.txt");
            std::cout<<"doNE"<<std::endl;
            getline(auxCsv, line);
            getline(auxCsv, line);
            istringstream linestream(line);
            string item;
            string item1;
            getline(linestream, item, ';');
            istringstream linestream1(item);
            getline(linestream, item, ';');
            istringstream linestream2(item);
            getline(linestream1, item1, ':');
            getline(linestream1, item1, ':');
            item1= item1.substr(0,item1.find(" J"));
            csvAux.imbue(std::locale("es_ES.UTF-8"));
            csvAux<< atoi(item1.c_str()) << ";";
            csvOut << csvAux.str().c_str();
        } 
        csvOut << "\n";
        std::cout<<"DOne"<<std::endl;
    }
    csvOut.close();

}

void createFolders(string codesFolder, string logFolder, string execFolder) {
    std::stringstream createCodesFolder, createExecFolder, createLogFolder;
    createCodesFolder << "mkdir " << codesFolder <<" > /dev/null";
    system(createCodesFolder.str().c_str());
    createLogFolder << "mkdir " << logFolder <<" > /dev/null";
    system(createLogFolder.str().c_str());
    createExecFolder << "mkdir " << codesFolder << "/" << execFolder <<" > /dev/null";
    system(createExecFolder.str().c_str());
}
inline bool exists(const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}
int main(int argc, char *argv[]) {

    ofstream groupFile;
    groupFile.open("numGroup.data", ios::trunc);
    groupFile <<0;
    groupFile.close();

    int methods = 0;
    int rep = 1;
    int tries = 1;
    int pause = 0;
    int inlin = 0;
    int verbose = 0;
    int energy = 0;
    string filename, codesFolder, execFolder, logFolder, logFilename;
    filename = "";
    codesFolder = "codes";
    execFolder = "executables";
    logFolder = "log";
    logFilename = "log.csv";
    bool checkOri = false;


    int nextOption; // return value of getopt
    while ((nextOption = getopt(argc, argv, "r:t:of:c:e:l:01234HpivL:x")) != -1) {
        switch (nextOption) {
            case 'r':
                rep = atoi(optarg);
                break;
            case 't':
                tries = atoi(optarg);
                break;
            case 'o':
                checkOri = true;
                break;
            case 'f':
                filename = optarg;
                break;
            case 'c':
                codesFolder = optarg;
                break;
            case 'e':
                execFolder = optarg;
                break;
            case 'l':
                logFolder = optarg;
                break;
            case 'L':
                logFilename = optarg;
                break;
            case '0':
                methods = 0;
                break;
            case '1':
                methods = 1;
                break;
            case '2':
                methods = 2;
                break;
            case '3':
                methods = 3;
                break;
            case '4':
                methods = 4;
                break;
            case 'p':
                pause = 1;
                break;
            case 'i':
                inlin = 1;
                break;
            case 'x':
                energy = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'H' || 'h':
                cout << argv[0] << "[-0|-1|-2|-3][-o][-i][-p][-x][-f[name]][-c[name]][-e[name]][-l[name]][-L[name]][-c[name]][-e[name]][-r[number]][-t[number]]\n"
                        " -0 Source to Source Compilation + HMPP Compilation & Execution\n"
                        " -1 Source to Source Compilation\n"
                        " -2 HMPP Compilation & Execution\n"
                        " -3 HMPP Execution\n"
                        " -4 HMPP Compilation\n"
                        " -o Check (Compile and Execute original file)\n"
                        " -f <filename to convert>\n"
                        " -c <output subfolder for transformed codes(default: 'codes')>\n"
                        " -e <output subfolder for executables (default: 'executables')>\n"
                        " -l <output subfolder for log files (default: 'log')>\n"
                        " -L <output filename for log files (default: 'log.csv')>\n"
                        " -r <number of code executions to extract average>\n"
                        " -p Pause after each iteration\n"
                        " -i Inline(on/off)\n"
                        " -x Report energy. \n"
                        " -v --verbose St0 Verbose HMPP compilation errors(on/off)\n"
                        " -h --help Display this usage information. \n"
                        " -t <number of tries for each execution repetition to get just the best execution time>\n" << endl;
                exit(0);
                break;
            default:
                cout << argv[0] << "[-0|-1|-2|-3][-o][-i][-p][-x][-f[name]][-c[name]][-e[name]][-l[name]][-L[name]][-c[name]][-e[name]][-r[number]][-t[number]]\n"
                        " -0 Source to Source Compilation + HMPP Compilation & Execution\n"
                        " -1 Source to Source Compilation\n"
                        " -2 HMPP Compilation & Execution\n"
                        " -3 HMPP Execution\n"
                        " -4 HMPP Compilation\n"
                        " -o Check (Compile and Execute original file)\n"
                        " -f <filename to convert>\n"
                        " -c <output subfolder for transformed codes(default: 'codes')>\n"
                        " -e <output subfolder for executables (default: 'executables')>\n"
                        " -l <output subfolder for log files (default: 'log')>\n"
                        " -L <output filename for log files (default: 'log.csv')>\n"
                        " -r <number of code executions to extract average>\n"
                        " -p Pause after each iteration\n"
                        " -i Inline(on/off)\n"
                        " -x Report energy. \n"
                        " -v --verbose St0 Verbose HMPP compilation errors(on/off)\n"
                        " -h --help Display this usage information.\n"
                        " -t <number of tries for each execution repetition to get just the best execution time>\n" << endl;
                exit(0);
                break;
                break;


        }

    }
    if(filename.compare("")==0){
	cerr<<"You Must to Specify the file to transform:"<<endl;
	cerr<<"-f <filename to convert>"<<endl;
	exit(-1);
    }
    
    if(!exists(filename.c_str())){
	cerr<<"The filename specified does not exist"<<endl;
	exit(-1);
    } 
    
    int extKind = 0;
    string extension = getFileExtension(filename);
    if (extension.compare("c") == 0) {
        extKind = 0;
    } else if (extension.compare("cpp") == 0) {
        extKind = 1;
    } else {
        cerr << "Trying to transform an unsupported file with extension: " << extension << "\n";
        cerr << "Just allowed .c and .cpp files\n";
        exit(-1);
    }
    vector<string> files = vector<string > ();

    createFolders(codesFolder, logFolder, execFolder);
    if (checkOri) {
        testFile(filename, logFolder, extKind, 0, logFilename, energy);
    }

    
//    ****************************************************
    int *lvl1A;
    int *lvl2A;
    lvl1A = new int[4];
    lvl2A = new int[2];
//    **********************************************
    ofstream transFile;
    transFile.open("numTransform.data", ios::trunc);
    transFile<<0<<"\n";
    transFile.close();
    
    std::stringstream numPath;
    numPath <<"echo 0>numGroup.data";
    system(numPath.str().c_str());
    std::stringstream expPath;
    expPath <<"export HMPPRT_PATH=./"<<codesFolder;
    system(expPath.str().c_str());
  //  std::cout<<expPath.str()<<std::endl;
  //  cin.get();
    int indx = 0;
    int transferMethods = 0;
    int lvl1=0; int lvl2=0;
    int version=0;
    int numExec = 0;
    if (methods == 0 || methods == 1) {
        for(lvl1=0;lvl1<pow(2,4);++lvl1){

            indx = 3;
            memset(lvl1A, 0, 4*sizeof(int));
            binary(lvl1,indx, lvl1A,4);

            if(lvl1==0){
                transferMethods = 5;
                version+=generateVersions(lvl1, lvl2, transferMethods - 1, codesFolder, filename, extKind, inlin);
            } else {
                transferMethods = 0;
                if(lvl1A[0]) {
                    for(int lvl2=0;lvl2<pow(2,2);++lvl2){
                        indx = 1;
                        memset(lvl2A, 0, 2*sizeof(int));
                        binary(lvl2,indx, lvl2A,2);
                        if(lvl2A[0]) {
                             if(lvl1A[3])
                                version+=generateVersions(lvl1, lvl2, transferMethods, codesFolder, filename, extKind, inlin);
                        } else {
                            version+=generateVersions(lvl1, lvl2, transferMethods, codesFolder, filename, extKind, inlin);
                        }
                    }
                } else {
                         version+=generateVersions(lvl1, lvl2, transferMethods, codesFolder, filename, extKind, inlin);
                }
                
               // system("clear");
                numExec++;
                //std::cout<<"\n";
            }
            if (pause) {
            doPause();
            }
        }
        
        delete lvl1A;
        delete lvl2A;


        cout << "------------------------------\n" << endl;
        cout << version << " createds and storeds in: ./" << codesFolder << " folder from file: " << filename << "\n" << endl;
        cout << "------------------------------\n" << endl;
    }


    if (methods == 0 || methods == 2 || methods == 3) {
        compileAndExecute(codesFolder, execFolder, logFolder, methods, rep, tries, pause, verbose, logFilename, energy);
    } else if(methods == 4){
        std::stringstream logPath;
        logPath << logFolder << "/";
        

        std::stringstream compFilePath;
        getdir(codesFolder, files);
        compFilePath << logPath.str() << "compilation.txt";
        string cP = compFilePath.str();
        compile(files, cP, codesFolder, execFolder, pause, verbose);
    }
    return 0;
}

