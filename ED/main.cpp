#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <queue>
#include <vector>
#include <utility> 

using namespace std;
void fun(int **M, int **R, int x, int y, string nome, int Nlinha, int Ncoluna) {
    vector<pair<int, int>> coordenadas;
    coordenadas.push_back(make_pair(x, y));

    queue<pair<int, int>> fila;

    for (const auto& coord : coordenadas) {
        fila.push(coord);
    }

    while (!fila.empty()) {
        pair<int, int> temp = fila.front();
        fila.pop();
        
        int l = temp.first;
        int c = temp.second;

        if (l >= 0 && l < Nlinha && c >= 0 && c < Ncoluna) {
            if (M[l][c] == 1 && R[l][c] == 0) {
                R[l][c] = 1;
                //cout << "Coloquei 1 na posição (" << l << ", " << c << ")" << endl;

                fila.push(make_pair(l - 1, c)); // Vizinho acima
                fila.push(make_pair(l + 1, c)); // Vizinho abaixo
                fila.push(make_pair(l, c - 1)); // Vizinho à esquerda
                fila.push(make_pair(l, c + 1)); // Vizinho à direita
            }
        }
    }
    /*cout << "Matriz R:" << endl;
    for (int i = 0; i < Nlinha; ++i) {
        for (int j = 0; j < Ncoluna; ++j) {
            cout << R[i][j] << " ";
        }
        cout << endl;
    }*/
    int contador = 0;
    for (int i = 0; i < Nlinha; ++i) {
        for (int j = 0; j < Ncoluna; ++j) {
            if (R[i][j] == 1) {
            	contador+= 1;
            }
        }
    }
    cout << nome << " " << contador << endl;
    return;
}

int main() {
    stack<string> pilha; // cria uma pilha de strings

    char xmlfilename[100]; // para armazenar o nome do arquivo xml

    cin >> xmlfilename;  // entrada

    ifstream arquivo; // cria uma variável do tipo ifstream
    string linha; // uma string para armazenar a linha
    arquivo.open(xmlfilename); // abrindo o arquivo

    if (arquivo.is_open()) { // if para saber se o arquivo está aberto
        while (getline(arquivo, linha)) { // enquanto conseguirmos pegar a linha de um arquivo, armazenamos na variável linha
            size_t tamanho = linha.size(); // pegamos o tamanho da linha
            for (size_t i = 0; i < tamanho; i++) { // for para percorrer cada caractere da linha.
                string forPilha = ""; // uma variável para concatenar os caracteres.
                if (linha[i] == '<' && linha[i + 1] != '/') { // se encontrarmos um '<' e o próximo caractere não for um '/', entramos no if (verificamos uma abertura de tag)
                    i++; // para tirar o '<'
                    while (linha[i] != '>') { // enquanto o caractere for diferente de '>'
                        if (!isspace(linha[i])) { // se for diferente de espaço
                            forPilha.push_back(linha[i]); // adicionamos ao final da string forPilha, concatenamos.
                        }
                        i++; // incrementa o índice
                    }
                    pilha.push(forPilha); // adicionamos à pilha
                    forPilha = ""; // "limpamos" a string
                }

                if (linha[i] == '<' && linha[i + 1] == '/') {
                    i += 2;
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
        bool isMatrizSection = false;  // Variável para rastrear se estamos dentro da seção <matriz>
        int Nlinha = 0;
        int Ncoluna = 0;
		string nome = "";
		int x = 0;
		int y = 0;
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
    					//cout << nome << endl;
    					
    				} else if (forPilha == "altura") {
    					i++;
    					while (linha[i] != '<') {
    						temp.push_back(linha[i]);
    						i++;	
    					}
    					Nlinha = stoi(temp);
    					temp = "";
    					//cout << Nlinha << endl;
    					
    				} else if (forPilha == "largura") {
    					i++;
    					while (linha[i] != '<') {
    						temp.push_back(linha[i]);
    						i++;
    					}
    					Ncoluna = stoi(temp);
    					temp = "";
    					//cout << Ncoluna << endl;
    					
    				} else if (forPilha == "x") {
    					i++;
    					while (linha[i] != '<') {
    						temp.push_back(linha[i]);
    						i++;
    					}
    					x = stoi(temp);
    					temp = "";
    					//cout << x << endl;
    					
    				} else if (forPilha == "y") {
    					i++;
    					while (linha[i] != '<') {
    						temp.push_back(linha[i]);
    						i++;
    					}
    					y = stoi(temp);
    					temp = "";
    					//cout << y << endl;
    					
    				} else if (forPilha == "matriz") {
		                // Encontrou a tag <matriz>, indica que estamos dentro da seção <matriz>
		                isMatrizSection = true;
		                int **M = new int*[Nlinha];  // Aloca dinamicamente a matriz M
		                int **R = new int*[Nlinha];  // Aloca dinamicamente a matriz R

		                for (int i = 0; i < Nlinha; ++i) {
		                    M[i] = new int[Ncoluna];
		                    R[i] = new int[Ncoluna];
		                }

		                // Lê e preenche as matrizes M e R com os valores da linha
		                for (int i = 0; i < Nlinha; ++i) {
		                    getline(arquivo, linha);
		                    for (int j = 0; j < Ncoluna; ++j) {
		                    	if (linha[j] != '<'){
		                    		M[i][j] = linha[j] - '0';
		                        	R[i][j] = 0;
		                    	} else {
		                    		break;
		                    	}
		                       
		                    }
		                }

		                // Imprime a matriz M
		                /*cout << "Matriz M:" << endl;
		                for (int i = 0; i < Nlinha; ++i) {
		                    for (int j = 0; j < Ncoluna; ++j) {
		                        cout << M[i][j] << " ";
		                    }
		                    cout << endl;
		                }*/

		                // Imprime a matriz R
		                /*cout << "Matriz R:" << endl;
		                for (int i = 0; i < Nlinha; ++i) {
		                    for (int j = 0; j < Ncoluna; ++j) {
		                        cout << R[i][j] << " ";
		                    }
		                    cout << endl;
		                }*/

		                fun(M, R, x, y, nome, Nlinha, Ncoluna);
		                // Libera a memória alocada para as matrizes M e R
		                for (int i = 0; i < Nlinha; ++i) {
		                    delete[] M[i];
		                    delete[] R[i];
		                }
		                delete[] M;
		                delete[] R;
		                nome = "";
		                Nlinha = 0;
		                Ncoluna = 0;
		                x = 0;
		                y = 0;
		            }
		        }
            }
        }
		arquivo.close(); // fecha o arquivo
	}
}
