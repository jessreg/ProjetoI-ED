#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main() {

    char xmlfilename[100];

    cin >> xmlfilename;  // entrada
    
    ifstream arquivo;
    string linha;
    arquivo.open(xmlfilename);
    if (arquivo.is_open()) {
    	while (getline(arquivo, linha)) {
    		size_t tamanho = linha.size();
    		for (size_t i = 0; i < tamanho; i++) {
    			cout << linha[i] << endl;
    		} 
    	}
    	arquivo.close();
    } 



    //std::cout << xmlfilename << std::endl;  // esta linha deve ser removida

    return 0;
}
