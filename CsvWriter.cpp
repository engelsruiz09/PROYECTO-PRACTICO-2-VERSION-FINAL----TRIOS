#include "CsvWriter.h"

CsvWriter::CsvWriter()
{
	setlocale(LC_ALL, "spanish");
	data = "";
	newLine = true;
}
void CsvWriter::Write(std::string info)
{
	if (newLine == false)
		data += ",";
	data += info;
	newLine = false;
}
void CsvWriter::NextLine()
{
	data += "\n";
	newLine = true;
}
void CsvWriter::Save(std::string path)
{
	std::ofstream file(path);//La biblioteca estándar fstream proporciona tres tipos de datos, a saber, ofstream, ifstream y fstream.
	file << data;
	file.close();
}