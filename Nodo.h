#pragma once
#include <iostream>
template <class T>
class Nodo
{
public:
	Nodo* siguiente;
	Nodo* anterior;
	T valor;

	Nodo()
	{
		siguiente = nullptr;
		anterior = nullptr;
	}
};