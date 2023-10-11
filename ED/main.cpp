#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;
int main() {

	stack<string> pilha; //cria uma pilha de strings

    char xmlfilename[100];

    cin >> xmlfilename;  // entrada
    
    ifstream arquivo;
    string linha;
    arquivo.open(xmlfilename);
    if (arquivo.is_open()) {
    	while (getline(arquivo, linha)) {
    		size_t tamanho = linha.size();
    		for (size_t i = 0; i < tamanho; i++) {
    			string forPilha = "";
    			//cout << linha[i] << endl;
    			if (linha[i] == '<' && linha[i+1] != '/') {
    				i++; // para tirar o '<'
    				while (linha[i] != '>') {
    					if (!isspace(linha[i])) {
                            forPilha.push_back(linha[i]);
                        } 
    					i++;
    				}
    				pilha.push(forPilha);
	    			forPilha = "";
    			}
    			if (linha[i] == '<' && linha[i+1] == '/') {
    				i+=2;
    				while (linha[i] != '>') {
    					if (!isspace(linha[i])) {
                           	forPilha.push_back(linha[i]);
                        } 
    					i++;
    				}
    				if (forPilha == pilha.top()) {
    					//cout << pilha.top() << endl;
    					pilha.pop();
    				} else {
    					cout << "erro" << endl;
    					exit(1);
    				}
    			} 
                
    				
        	
    			

    		} 
    	}
        if (!pilha.empty()) {
            cout << "erro" << endl;
    		exit(1);
        }
    	arquivo.close();
    } 
    /*size_t tamPilha = pilha.size();
    for (size_t i = 0; i < tamPilha; i++ ) {
    	cout << pilha.top() << endl;
        pilha.pop(); // Remova o elemento do topo da pilha
    } */
    //std::cout << xmlfilename << std::endl;  // esta linha deve ser removida

    return 0;
}
