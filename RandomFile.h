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
    ifstream indexFile;
    indexFile.open(this->indexName, ios::in | ios::binary);
    if (!indexFile.is_open())
    {
        // El archivo no existe todavía
        return;
    }
    while (!indexFile.eof())
    {
        string key;
        long value;
        indexFile.read((char*)&key, sizeof(string));
        indexFile.read((char*)&value, sizeof(long));
        this->index[key] = value;
    }
    indexFile.close();
    }


    /*
    * Regresa el indice al disco
    */
    void writeIndex()
    {
    ofstream indexFile;
    indexFile.open(this->indexName, ios::out | ios::binary);
    for (auto& entry : this->index)
    {
        string key = entry.first;
        long value = entry.second;
        indexFile.write((char*)&key, sizeof(string));
        indexFile.write((char*)&value, sizeof(long));
    }
    indexFile.close();
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
    if (this->index.count(key) > 0)
    {
        // La clave existe en el índice, leemos el registro
        long posFisica = this->index[key];
        ifstream dataFile;
        dataFile.open(this->fileName, ios::in | ios::binary);
        dataFile.seekg(posFisica);
        Record* record = new Record();
        dataFile.read((char*)record, sizeof(Record));
        dataFile.close();
        result = record;
    }
    return result;
}


    /*
   * Muestra todos los registros de acuerdo como fueron insertados en el archivo de datos
   */
    void scanAll() {
    ifstream dataFile;
    dataFile.open(this->fileName, ios::in | ios::binary);
    while (!dataFile.eof())
    {
        Record record;
        dataFile.read((char*)&record, sizeof(Record));
        if (!dataFile.eof())
        {
            record.showData();
        }
    }
    dataFile.close();
}


    /*
   * Muestra todos los registros de acuerdo a como estan ordenados en el indice
   */
    void scanAll() {
    ifstream dataFile;
    dataFile.open(this->fileName, ios::in | ios::binary);
    while (!dataFile.eof())
    {
        Record record;
        dataFile.read((char*)&record, sizeof(Record));
        if (!dataFile.eof())
        {
            record.showData();
        }
    }
    dataFile.close();
}

};


