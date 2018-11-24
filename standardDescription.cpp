// basic file operations
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

void llenaMapa(unordered_map<string, int> &mapa, int index){
		string input_line;
		getline(cin, input_line);
		
		stringstream ss(input_line);
	    string elemento;

	    while (getline(ss, elemento, ' ')) {
	        mapa[elemento] = index;
	        index++;
	    }
}


void escribeStandard(unordered_map<string, int> &mapa, ofstream &sd, string primario, string secundario, string campo){
	sd << primario;
	for(int i = 0; i < mapa[campo]; i++){
		sd << secundario;
	}
}

void closeIO(ifstream &i, ofstream &o){
	i.close();
	o.close();
}
int main(){
	ifstream input ("input.txt");
	if (input.is_open()){
		//creación de out file
		ofstream standardD;
		standardD.open ("standardDescription.txt");
		
		//creación de lista de estados
		unordered_map<string, int> estados;

		cout << "Ingresa lista de tus estados separada por espacios" << endl;
		llenaMapa(estados, 1);

	    //creación de lista de alfabeto
	    unordered_map<string, int> alfabeto;
	    alfabeto["_"] = 0;
	    cout << "Ingresa el alfabeto de la cinta (Gamma) separado por espacios, sin ingresar el ESPACIO VACÍO (cuadrado)" << endl;
	    llenaMapa(alfabeto, 1);

		//procesar datos de input
		string input_line;
		while(getline (input, input_line)){
			stringstream ss(input_line);
		    string elemento;
		    int index = 0;
		    string campos[4];

		    while (getline(ss, elemento, '\t')) {
		    	int sizeElem = elemento.length();
		    	char last = elemento[sizeElem - 1];
		    	//hay casos donde los elementos leídos tienen un caracter extra en blanco
		    	if(sizeElem <= 1)
		    		campos[index] = elemento;
		    	else
		        	campos[index] = (isalnum(last)) ? elemento : elemento.substr(0,sizeElem - 1);
		        index++;
		    }

		    //campo de estado inicial
		    if(estados.find(campos[0]) != estados.end()){
		    	escribeStandard(estados, standardD, "D", "A", campos[0]);
		    }
		    else{
		    	cout << "Error de formato en primer campo" << endl;
		    	closeIO(input, standardD);
		    	return 0;
		    }

		    //campo de palabra encontrada
		    if(alfabeto.find(campos[1]) != alfabeto.end()){
		    	escribeStandard(alfabeto, standardD, "D", "C", campos[1]);
		    }
		    else{
		    	cout << "Error de formato en segundo campo" << endl;
		    	closeIO(input, standardD);
		    	return 0;
		    }

		    //campo de acción a hacer
		    if(alfabeto.find(campos[2].substr(0,1)) != alfabeto.end()){
		    	escribeStandard(alfabeto, standardD, "D", "C", campos[2].substr(0,1));
		    	standardD << campos[2].substr(2,3); // R, L o N
		    }
		    else{
		    	cout << "Error de formato en tercer campo" << endl;
		    	closeIO(input, standardD);
		    	return 0;
		    }

		    //campo de estado final
		    if(estados.find(campos[3]) != estados.end()){
		    	escribeStandard(estados, standardD, "D", "A", campos[3]);
		    	standardD << ";\n";
		    }
		    else{
		    	cout << "Error de formato en cuarto campo" << endl;
		    	closeIO(input, standardD);
		    	return 0;
		    }
		}
		closeIO(input, standardD);
	}
	else {
		cout << "Unable to open file"; 
		return 0;
	}
	return 0;
}