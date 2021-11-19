#pragma once
#include <iostream>
#include <string>
#include <locale>//see utilizan para definir información específica de la configuración regional
#include <fstream>//para leer los datos del archivo
#include "Lista.h"

class CsvReader
{
private:
    int cursor;
    Lista<std::string> content;
    std::string line;
public:
    CsvReader(std::string path)
    {
        //para la lectura del csv 
        setlocale(LC_ALL, "spanish"); // ANSI Codification
        line = "";//dentro de la variable content se va guardar todo texto de las canciones
        cursor = 0;//un cursor literalmente ;v, que se posiciona en todo el string de canciones

        std::ifstream file(path);

        std::string data;
        while (std::getline(file, data))
            content.Insertar(data);
        file.close();
    }
    bool ReadLine()
    {
        if (content.cantidad == 0)
            return false;

        cursor = 0;
        line = content.Extraer(0);
        return true;
    }
    bool Read(std::string& data)
    {
        data = "";//vacia la variable de entrada

        if (cursor >= line.length())
            return false;//por si no encuentra nada en content o no a podido leer nada

        while (true)
        {
            if (cursor >= line.length())//ha llegado al final de la cadena
                return true;//hasta aqui llega por que ya termino de leer la cadena
            if (line[cursor] == ',') {//si se encuentra una coma
                cursor++;//pasa a la siguiente 
                return true;//lo lee satisfactoriamente y lo devuelve
            }
            data += line[cursor];//agrega la letra a la data actual la primera donde este apuntando cursor y asi sucesivamente
            cursor++;//recorre cada letra del arreglo de nombres
        }
    }
};
