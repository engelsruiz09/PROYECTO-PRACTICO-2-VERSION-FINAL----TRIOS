#pragma once
#include "Persona.h"
#include "Lista.h"
#include "Curso.h"

class Alumno : public Persona
{
public:
	int Carnet;
	int Ingreso;
	std::string Facultad;
	std::string Modalida;
	Lista<Curso*>* Cursos = new Lista<Curso*>;
};