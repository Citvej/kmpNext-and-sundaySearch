#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

// void prefixSum(vector<int> *C){
//     for(int i = 1; i <= C->size(); i++){
//         // *C[i] += *C[i-1];
//         C->at(i) += C->at(i-1);
//     }
// }

void knuttMorrisPratt(string x, string y){
    int m, n, k;
    string ujemanje;

    m = x.length();
    n = y.length();
    vector<int> kmpNext(m, 0); 
    
    kmpNext[0] = -1;
    kmpNext[1] = 0;

    k = 0;   //spremlja index prefiksa
    for(int i = 1; i<m-1; i++){ //gre skozi x in predprocesira kmpNext
        if(x[k] == x[i]){       // če se ujemata znaka damo na naslednji index eno cifro več kot na sedanjem kar naredi da je zaporedje znakov enako
            kmpNext.at(i+1) = kmpNext.at(i) + 1;
            k++;
        }else{
            k = 0;
        }
    }
    
    ujemanje = "";
    for(int j=0; j<n; j++){
        for(int i=0; i<m; i++){
            if(x[i] != y[j+i]){  //če se ne ujemata znaka v x in y na respektivnih indeksih se zgodi preskok
                j+=i-kmpNext[i]-1;
                break;
            }else{
                if(i == m-1) ujemanje+=to_string(j) + " "; //če se dolžina ujemajočih znakov ujema z dolžino iskanega niza shranimo
            }
        }
    }

    ofstream outputFile("out.txt");
    for(int i=0; ujemanje[i] != '\0'; i++){
        outputFile << ujemanje[i];
    }


    outputFile.close();
}

void sundaySearch(string x, string y){
    int m, n, intermediary;
    string ujemanje;

    m = x.length();
    n = y.length();

    vector<int> BCH(256, m);

    for(int i=0; i<=m; i++){
        BCH[x[i]] = m-i;
    }

    ujemanje = "";
    for(int j=0; j<n; j++){
        for(int i=0; i<m; i++){
            if(x[i] != y[j+i]){
                intermediary = y[j+m];
                j+=BCH[intermediary]-1;
                break;
            }else{
                if(i == m-1){ 
                    ujemanje += to_string(j) + " ";
                    j+=m;
                    i=0;
                }
            }
        }
    }

    ofstream outputFile("out.txt");

    for(int i=0; ujemanje[i] != '\0'; i++){
        outputFile << ujemanje[i];
    }

    outputFile.close();


}

string fileToString(string pot){
    string y;
    ifstream inputFile;
    stringstream strStream;

    inputFile.open(pot);
    if(!inputFile)                                                                                  // preveri ce se je datoteka uspesno odprla
	{
		cout<<"Napaka pri odpiranju datoteke! \n";
		exit(1);
	}

    strStream << inputFile.rdbuf();
    y = strStream.str();

    inputFile.close();

    return y;
}

int main(int argc, char *argv[]){
    char izbira;                                                                          // če je prvi argument 0 potem bomo izvajali counting sort v primeru 1ke pa roman sort
    string x, y;                                                                // pot do vhodne datoteke podana v argumentu 2

    izbira = *argv[1];
    x = argv[2];
    y = fileToString(argv[3]);

    if(izbira == '0'){
        knuttMorrisPratt(x, y);
    }else if(izbira == '1'){
        sundaySearch(x,y);
    }


    return 0;
}