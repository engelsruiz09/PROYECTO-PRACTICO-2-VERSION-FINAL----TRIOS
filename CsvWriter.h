#pragma once
#include <iostream>
#include <string>
#include <locale>//see utilizan para definir información específica de la configuración regional
#include <fstream>//para leer los datos del archivo

class CsvWriter
{
	std::string data;
	bool newLine;
public:
	CsvWriter()
	{
		setlocale(LC_ALL, "spanish");
		data = "";
		newLine = true;
	}
	void Clear()
	{
		data = "";
	}
	void Write(std::string info)
	{
		if (newLine == false)
			data += ",";
		data += info;
		newLine = false;
	}
	void NextLine()
	{
		data += "\n";
		newLine = true;
	}
	void Save(std::string path)
	{
		std::ofstream file(path);//La biblioteca estándar fstream proporciona tres tipos de datos, a saber, ofstream, ifstream y fstream.
		file << data;
		file.close();
	}
};

