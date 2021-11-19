#pragma once
#include "Empleado.h"
#include "Lista.h"
#include "Curso.h"

class Docente : public Empleado
{
public:
	Lista<Curso*>* Cursos = new Lista<Curso*>;
};