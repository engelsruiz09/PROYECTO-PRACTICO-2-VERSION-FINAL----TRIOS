#pragma once
#include "Nodo.h"
template<class T> 
class Lista
{
public:
	Nodo<T>* primero;
	Nodo<T>* ultimo;
	int cantidad;

	Lista() {
		primero = nullptr;
		ultimo = nullptr;
		cantidad = 0;
	}
	void Insertar(T valor) {
		Nodo<T>* nuevo_nodo = new Nodo<T>();
		nuevo_nodo->valor = valor;

		if (cantidad != 0)
		{
			nuevo_nodo->anterior = ultimo;
			ultimo->siguiente = nuevo_nodo;
			ultimo = nuevo_nodo;
		}
		else
		{
			primero = nuevo_nodo;
			ultimo = nuevo_nodo;
		}
		cantidad++;
	}
	T Extraer(int posicion)
	{
		Nodo<T>* nodo = ObtenerNodo(posicion);

		Nodo<T>* anterior = nodo->anterior;
		Nodo<T>* siguiente = nodo->siguiente;

		if (posicion == 0)
		{
			if (siguiente != nullptr)
				siguiente->anterior = nullptr;
			primero = siguiente;
		}
		else if (posicion == cantidad - 1)
		{
			if (anterior != nullptr)
				anterior->siguiente = nullptr;
			ultimo = anterior;
		}
		else
		{
			if (anterior != nullptr)
				anterior->siguiente = siguiente;
			if (siguiente != nullptr)
				siguiente->anterior = anterior;
		}
		cantidad--;
		return nodo->valor;
	}
	Nodo<T>* ObtenerNodo(int posicion)
	{
		Nodo<T>* anterior = primero;
		for (int i = 0; i < posicion; i++)
			anterior = anterior->siguiente;

		return anterior;
	}
	void Intercambiar(int pos1, int pos2)
	{
		Nodo<T>* nodo1 = ObtenerNodo(pos1);
		Nodo<T>* nodo2 = ObtenerNodo(pos2);

		std::swap(nodo1->valor, nodo2->valor);
	}
	T Modificar(T valor, int posicion)
	{
		Nodo<T>* nodo = ObtenerNodo(posicion);
		T antiguo = nodo->valor;
		nodo->valor = valor;
		return antiguo;
	}

	T Obtener(int posicion)
	{
		Nodo<T>* nodo = ObtenerNodo(posicion);
		return nodo->valor;
	}
	/*T operator[](int posicion)
	{
		Nodo<T>* nodo = ObtenerNodo(posicion);
		return nodo->valor;
	}*/
};