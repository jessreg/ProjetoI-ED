#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;
int main() {

	stack<string> pilha; // cria uma pilha de strings

    char xmlfilename[100]; // para armazenar o nome do arquivo xml

    cin >> xmlfilename;  // entrada
    
    ifstream arquivo; // cria uma variavel do tipo ifstream
    string linha; // uma string para armazenar a linha
    arquivo.open(xmlfilename); // abrindo o arquivo
    if (arquivo.is_open()) { // if para saber se o arquivo está aberto
    	while (getline(arquivo, linha)) { // enquanto conseguirmos pegar a linha de um arquivo, armazenamos na variavel linha
    		size_t tamanho = linha.size(); // pegamos o tamanho da linha
    		for (size_t i = 0; i < tamanho; i++) { // for para percorrer cada caracter da linha.
    			string forPilha = ""; // uma variavel para concatenar os caracteres.
    			//cout << linha[i] << endl;
    			if (linha[i] == '<' && linha[i+1] != '/') { // se encontrarmos um < e o proximo caracter n for um /, entramos no if (verificamos uma abertura de tag)
    				i++; // para tirar o '<'
    				while (linha[i] != '>') { // enquanto o caracter for diferente de >
    					if (!isspace(linha[i])) { // se for diferente de espaço
                            forPilha.push_back(linha[i]); // adicionamos ao final da string for pilha, concatenamos.
                        } 
    					i++; // incrementa o indice
    				}
    				pilha.push(forPilha); // adicionamos a pilha
	    			forPilha = ""; // "limpamos" a string
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

        arquivo.clear();          // Limpa os flags de erro do arquivo
		arquivo.seekg(0, ios::beg);  // Reposiciona o ponteiro de leitura no início do arquivo
		bool flag = false;
		int Nlinha = "";
		string nome = "";
		int Ncoluna = "";
		string x = "";
		string y = "";
		int row = 0;
		int col = 0;
		int** M = nullptr;  // ma matriz para armazenar os valores
		bool isMatrizSection = false;  // Variável para rastrear se estamos dentro da seção <matriz>
		string temp = "";
        while (getline(arquivo, linha)) {
    		size_t tamanho = linha.size();
    		
    		for (size_t i = 0; i < tamanho; i++) {
    			//cout << linha[i] << endl;
    			string forPilha = "";
	    		if (linha[i] == '<' && linha[i+1] != '/') {
    				i++;
    				while (linha[i] != '>') { // enquanto o caracter for diferente de >
    					if (!isspace(linha[i])) { // se for diferente de espaço
                            forPilha.push_back(linha[i]); // adicionamos ao final da string for pilha, concatenamos.
                        } 
    					i++; // incrementa o indice
    				}
    				if (forPilha == "nome") {
    					i++;
    					while (linha[i] != '<') {
    						nome.push_back(linha[i]);
    						i++;
    					}
    					cout << nome << endl;
    					
    				} else if (forPilha == "altura") {
    					i++;
    					while (linha[i] != '<') {
    						temp.push_back(linha[i]);
    						i++;	
    					}
    					Nlinha = stoi(temp);
    					temp = "";
    					cout << Nlinha << endl;
    					
    				} else if (forPilha == "largura") {
    					i++;
    					while (linha[i] != '<') {
    						temp.push_back(linha[i]);
    						i++;
    					}
    					Ncoluna = stoi(temp);
    					temp = "";
    					cout << Ncoluna << endl;
    					
    				} else if (forPilha == "x") {
    					i++;
    					while (linha[i] != '<') {
    						x.push_back(linha[i]);
    						i++;
    					}
    					cout << x << endl;
    					
    				} else if (forPilha == "y") {
    					i++;
    					while (linha[i] != '<') {
    						y.push_back(linha[i]);
    						i++;
    					}
    					cout << y << endl;
    					
    				}

    				if (forPilha == "matriz")
    					flag = true;
    					isMatrizSection = true;  // Entrou na seção <matriz>
                		M = new int*[stoi(Nlinha)];
                		for (int j = 0; j < stoi(Nlinha); j++) {
                   			M[j] = new int[stoi(Ncoluna)];
    					}



    				if (flag == true) {
       					int R[stoi(Nlinha)][stoi(Ncoluna)];
       					for (int i = 0; i < stoi(Nlinha); i++) {
       						for (int j = 0; j < stoi(Ncoluna); j++) {
       							R[i][j] = 0;
       						}
       					}
       					for (int i = 0; i < stoi(Nlinha); i++) {
        					for (int j = 0; j < stoi(Ncoluna); j++) {
            					cout << R[i][j] << " ";
        					}
       						cout << endl; // Nova linha após cada linha da matriz
    					}
    					 if (isMatrizSection) {  // Se estamos dentro da seção <matriz>
        				// Preencha a matriz M na posição apropriada com os valores da linha
					        if (row < stoi(Nlinha) && col < stoi(Ncoluna)) {
					            if (linha.size() == stoi(Ncoluna)) {
					                for (int j = 0; j < stoi(Ncoluna); j++) {
					                    M[row][j] = linha[j] - '0';
					                }
					                row++;
					            } else {
					                cerr << "Erro: linha da matriz não tem o número correto de colunas." << endl;
					                exit(1);
					            }
					        } else {
					            cerr << "Erro: posição fora dos limites da matriz." << endl;
					            exit(1);
					        }
					    }
					    // Verifique se estamos saindo da seção <matriz>
					    if (forPilha == "matriz") {
					        flag = false;
					        isMatrizSection = false;  // Saímos da seção <matriz>
					        row = 0;
					        col = 0;
					        // Imprima a matriz M
							for (int i = 0; i < stoi(Nlinha); i++) {
							    for (int j = 0; j < stoi(Ncoluna); j++) {
							        cout << M[i][j] << " ";
							    }
							    cout << endl;
							}

							// Libere a memória alocada para a matriz M
							for (int i = 0; i < stoi(Nlinha); i++) {
							    delete[] M[i];
							}
							delete[] M;
							M = nullptr;
					    }
					}


       					Nlinha = "";
						nome = "";
						Ncoluna = "";
						x = "";
						y = "";
						flag = false;

    				}

    			}

    		}

    		

    	arquivo.close();
    } 
    
    return 0;
}
