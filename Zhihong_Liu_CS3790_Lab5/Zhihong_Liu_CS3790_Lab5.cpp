//The Banker's algorithm
#include<iterator>
#include<type_traits>
#include<algorithm>
#include<utility>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include <sstream> 
#include <cctype> 


using namespace std;
using VEC = vector<int>;
using MAT = vector<VEC>;

int processN = 0;
int resourceM = 0;

int userSelectionProcess = 0;
string userString;

VEC Available;
MAT Max;
MAT Allocation;
MAT Need;

bool operator<=(const VEC& need,const VEC& work) {

    for (int i = 0; i < work.size();++i) {

        if (need[i]>work[i]) {
            return false;
        }
    }

    return true;
}


VEC operator+(const VEC& v1,const VEC &v2) {

    VEC tmp(v1.size(), 0);

    for (int i = 0; i < v1.size();++i) {
        tmp[i] = v1[i] + v2[i];
    }

    return tmp;

}


VEC operator-(const VEC& v1, const VEC& v2) {

    VEC tmp(v1.size(), 0);

    for (int i = 0; i < v1.size(); ++i) {
        tmp[i] = v1[i] - v2[i];
    }

    return tmp;

}








MAT operator-(const MAT & m1,const MAT & m2) {
    
    MAT tmp(processN, VEC(resourceM, 0));

    for (int i = 0; i < m1.size();++i) {
        for (int j = 0; j < m1[i].size();++j) {
            tmp[i][j] = m1[i][j] - m2[i][j];
        }

    }

    return tmp;
}



void dumpMatrix(MAT matrix) {

    for (int i = 0; i < matrix.size();++i) {
        for (int j = 0; j < matrix[i].size();++j) {
            cout << matrix[i][j] << " ";
            }
        cout << endl;
    }

}

void dumpVector(VEC vector) {
    for (int i = 0; i < vector.size();++i) {
        cout << vector[i] << " ";
    }
    cout << endl;
}

void dumpResourceAllocationState() {

    cout << "The AVAILABLE VECTOR\n";
    dumpVector(Available);

    cout << "\n" << string(50, '*') << "\n" << endl;

    cout << "The MAX MATRIX\n";
    dumpMatrix(Max);

    cout << "\n" << string(50, '*') << "\n" << endl;

    cout << "The ALLOCATION MATRIX\n";
    dumpMatrix(Allocation);

    cout << "\n" << string(50, '*') << "\n" << endl;

    cout << "The NEED MATRIX\n";
    dumpMatrix(Need);

}





bool safetyAlgorithm() {

    VEC Work = Available;
    vector<bool> Finish(processN,false);
    bool madeProgress;

    do {
        madeProgress = false; // Reset progress flag for this iteration

        for (int i = 0; i < processN; ++i) {

            if (!Finish[i] && (Need[i] <= Work)) { //  overloaded operator<= is invoked

                Work = Work + Allocation[i];       //   overloaded operator+ is invoked            
                Finish[i] = true;
                madeProgress = true; // Mark progress
            }
        }

    } while (madeProgress); // Continue if progress was made


    for (int i = 0; i < Finish.size();++i) {

        if (!Finish[i]) {
            return false;
        }

    }

    return true;
}

int main()
{
    string inputData = " ";
    

    std::ifstream myFile;
    myFile.open("file.txt", std::ifstream::in);

    // Check if the file was opened successfully  
    if (!myFile) {
        std::cerr << "Unable to open file file.txt";
        return 1; // Return with an error code  
    }

    getline(myFile,inputData);
   
    // Create a string stream from the input string  
    istringstream iss(inputData);

    // Extract the two numbers  
    if (!(iss >> processN >> resourceM)) {
        cerr << "Failed to extract numbers." << endl;
    }

    //Initialize the Available vector and Max matrix
    Available=VEC(resourceM,0);
    Max=MAT(processN,VEC(resourceM,0));
    Allocation=MAT(processN, VEC(resourceM, 0));
    Need=MAT(processN, VEC(resourceM, 0));
    
    //Get the data of Max matrix
    for (int i = 0; i < processN;++i) {//Process row

        int tmp = 0;

        getline(myFile, inputData);

        // Create a string stream from the input string  
        istringstream iss_temp1(inputData);

        for (int j = 0; j < resourceM;++j) {
            iss_temp1 >> Max[i][j];
        }
    
    }

  
    //Get the data of  Availabe vector
    getline(myFile, inputData);

    // Create a string stream from the input string  
    istringstream iss_temp2(inputData);

    //Update the value of Availabe vector
    for (int i = 0; i < resourceM;++i) {
        iss_temp2 >> Available[i];
    }

   

    myFile.close();

    Need = Max - Allocation;

    //The follwing data is the same as the lecture slide, used as test purpose
    /*
    VEC temp1 = {3,3,2};
    Available = temp1;

    MAT temp2 = {
        {7,4,3},
        {1,2,2},
        {6,0,0},
        {0,1,1},
        {4,3,1}
    
    };
    Need = temp2;

    MAT temp3 = {
       {0,1,0},
       {2,0,0},
       {3,0,2},
       {2,1,1},
       {0,0,2}

    };
    Allocation = temp3;
    */

    do {
        cout << "Which process would you like to select ? Please input a number from 0 to " << (processN - 1)<<" :";
        cin >> userString;


        try {
            userSelectionProcess = stoi(userString);
        }
        catch (...) {
            cerr << "Your input is not a valid number !";
            return 1;
        }

        if (userSelectionProcess == -1) {
            break;
        }

       
        if (  (userSelectionProcess<0)||(userSelectionProcess> (processN - 1))) {
            std::cerr << "Your input is out of the range !";
            return 1; // Return with an error code  
        }

        // Clear the input buffer before taking the next line of input  
        cin.ignore(); // This clears the newline left in the buffer 

        cout << "Please input the resource request vector for that process(A sequence of integers separated by space) : ";
        getline(cin,userString);


        // Create a string stream from the input string  
        istringstream iss_temp3(userString);

        VEC resourceRequest;

        //Store the resource request vector
        string tmp111 = " ";
        int tmp222 = 0;
        while (!iss_temp3.eof()) {

            iss_temp3 >> tmp111;
            
            try {
                tmp222 = stoi(tmp111);
            }
            catch (...) {
                cerr << "Your input is not a valid number !";
                return 1;
            }

            resourceRequest.push_back(tmp222);
        }

        

        if (resourceRequest.size()== resourceM) {

            if (!(resourceRequest <= Need[userSelectionProcess])) {
                cout << "\n\nThis request is denied,since it exceeds its maximun claim !\n\n";

                dumpResourceAllocationState();
            }
            else if (      !      (resourceRequest<=Available)            ) {
                cout << "\n\nThis request is denied,since resources are not available !\n\n";

                dumpResourceAllocationState();

            }else {
                Available = Available - resourceRequest;
                Allocation[userSelectionProcess]= Allocation[userSelectionProcess]+ resourceRequest;
                Need[userSelectionProcess]= Need[userSelectionProcess]- resourceRequest;

                if (   safetyAlgorithm()  ) {

                    cout << "\n\nThis request is granted successfully.\n\n";

                    dumpResourceAllocationState();

                }
                else {
                    //Safety Algorithm fails,rollback
                    Available = Available + resourceRequest;
                    Allocation[userSelectionProcess] = Allocation[userSelectionProcess] - resourceRequest;
                    Need[userSelectionProcess] = Need[userSelectionProcess] + resourceRequest;

                    cout << "\n\nThis request is denied,since it produces an unsafe state !\n\n";

                    dumpResourceAllocationState();


                }

            }


        }
        else {
            cout << "Your resource request vector is not accpetable !"<<"\n\n";
        }

       

    } while (true);

    

    cout << "\n\n*******Dumping the Resource Allocation State before exit*******\n\n";

    dumpResourceAllocationState();

    

    return 0;
}
