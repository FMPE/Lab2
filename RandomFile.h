#include <iostream>
#include<fstream>
#include<cstdio>
#include <map>
using namespace std;

struct Record
{
    char nombre[30];
    char carrera[20];
    int ciclo;

    void setData() {
        cout << "Alumno:";
        cin >> nombre;
        cout << "Carrera: ";
        cin >> carrera;
        cout << "Ciclo: ";
        cin >> ciclo;
    }

    void showData() {
        cout << "\nNombre: " << nombre;
        cout << "\nCarrera: " << carrera;
        cout << "\nCiclo : " << ciclo;
    }

    string getKey(){
        string res = nombre;
        return res;
    }  
};

class RandomFile {
private:
    string fileName;
    string indexName;
    //map: mantiene ordenado las entradas
    map<string, long> index;

public:
    RandomFile(string _fileName) {
        this->fileName = _fileName;
        this->indexName = _fileName + "_ind";
        readIndex();
    }
    
    ~RandomFile(){
        writeIndex();
    }

    /*
    * leer el indice desde disco
    */
    void readIndex()
    {
      
    }

    /*
    * Regresa el indice al disco
    */
    void writeIndex(){
        
    }

    /*
    * Escribe el registro al final del archivo de datos. Se actualiza el indice. 
    */
    void write_record(Record record) {
       ofstream dataFile;
       dataFile.open(this->fileName, ios::app | ios::binary);
       long posFisica = dataFile.tellp();
       dataFile.write((char*)&record, sizeof(Record));
       this->index[record.getKey()] = posFisica;
       dataFile.close();
    }


    /*
    * Busca un registro que coincida con la key
    */
    Record* search(string key) {
        Record* result = nullptr;
                
        return result;
    }

    /*
   * Muestra todos los registros de acuerdo como fueron insertados en el archivo de datos
   */
    void scanAll() {
       
    }

    /*
   * Muestra todos los registros de acuerdo a como estan ordenados en el indice
   */
    void scanAllByIndex() {
       
    }

};


