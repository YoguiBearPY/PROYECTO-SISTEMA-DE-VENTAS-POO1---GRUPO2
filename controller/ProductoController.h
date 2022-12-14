#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "../model/producto.h"
#include "categoriaController.h"
#include <fstream>
using namespace std;
using std::string;
class ProductoController
{
private:
	vector<Producto> vectorProducto;

public:
	ProductoController();
	void add(Producto);
	Producto get(int);
	int size();
	int getCorrelativo();
	Producto buscar(int);
	void listarPorNombre(string);
	bool modificar(Producto, Producto);
	int getPostVector(Producto);
	void eliminar(Producto);
	void listar();
	void grabarEnArchivo(Producto);
	void grabarModificarEliminar();
	void cargarDatosDelArchivoAlVector();
};
ProductoController::ProductoController()
{
	cargarDatosDelArchivoAlVector();
}
void ProductoController::add(Producto obj)
{
	vectorProducto.push_back(obj); // Usuario obj;
}
Producto ProductoController::get(int pos)
{
	return vectorProducto[pos]; // vectorUsuario[0].getCodigo() = 1; vectorUsuario[0].getContra() = "xd";
}
int ProductoController::size()
{
	return vectorProducto.size(); // si el vectorUsuario tiene posicion 0 y 1, vectorUsuario.size() = 2 porque empieza a contar desde 1;
}
int ProductoController::getCorrelativo()
{
	if (size() == 0)
	{
		return 1; 
	}
	else
	{
		return vectorProducto[size() - 1].getCodPro() + 1;
	}
}
Producto ProductoController::buscar(int dato)
{
	Producto objError;
	objError.setNomApe("Error");
	for (int i = 0; i < vectorProducto.size(); i++)
	{
		if (dato == vectorProducto[i].getCodPro())
		{
			return vectorProducto[i];
		}
	}
	return objError;
}

void ProductoController::listarPorNombre(string dato)
{	
	for (size_t i = 0; i < vectorProducto.size(); ++i)
	{
		const string& nombre = vectorProducto[i].getNomApePro();
		std::string::size_type pos = nombre.find(dato);
		if (pos != string::npos)
		{
			cout	<< "000" << setw(6) << left << vectorProducto[i].getCodPro() 
					<< setw(28) << left <<vectorProducto[i].getNomApePro()
					<< vectorProducto[i].getPrePro() << endl;
		}
		else
		{
			
		}
		
	}

}
bool ProductoController::modificar(Producto ObjOld, Producto ObjNew)
{
	for (int i = 0; i < vectorProducto.size(); i++)
	{
		if (ObjOld.getCodPro() == vectorProducto[i].getCodPro())
		{
			vectorProducto[i].setNomApe(ObjNew.getNomApePro());
			vectorProducto[i].setPrePro(ObjNew.getPrePro());
			vectorProducto[i].setStockPro(ObjNew.getStockPro());
			vectorProducto[i].setCodCat(ObjNew.getCodCat());
			return true;
		}
	}
	return false;
}
int ProductoController::getPostVector(Producto obj)
{
	for (int i = 0; i < vectorProducto.size(); i++)
	{
		if (obj.getCodPro() == vectorProducto[i].getCodPro())
		{
			return i;
		}
	}
	return -1;
}
void ProductoController::eliminar(Producto objEncontrado)
{
	vectorProducto.erase(vectorProducto.begin() + getPostVector(objEncontrado));
}
void ProductoController::listar()
{
	CategoriaController *obj = new CategoriaController;
	cout	<< setw(28) << left << "NOMBRE DEL PRODUCTO"
			<< setw(9) << left << "PRECIO"
			<< setw(8) << left << "STOCK"
			<< left << "CATEGORIA\n\n";
	for (int i = 0; i < vectorProducto.size(); i++)
	{
		cout	<< setw(28) << left << vectorProducto[i].getNomApePro()
				<< setw(9) << left << vectorProducto[i].getPrePro()
				<< setw(8) << left << vectorProducto[i].getStockPro()
				<< setw(17) << left << obj->listarCategoria(vectorProducto[i]) << "\n";
	}
}
void ProductoController::grabarEnArchivo(Producto obj)
{
	try
	{
		fstream archivoProducto;
		archivoProducto.open("productos.csv", ios::app); // ios::app = las operaciones se realizan al final del archivo
		if (archivoProducto.is_open())
		{
			archivoProducto << obj.getCodPro() << ";" << obj.getNomApePro() << ";" << obj.getPrePro() << ";" << obj.getStockPro() << ";" << obj.getCodCat() << ";" << endl;
			archivoProducto.close();
		}
	}
	catch (exception e)
	{
		cout << "Ocurrio un error al grabar el archivo";
	}
}
void ProductoController::grabarModificarEliminar()
{
	try
	{
		fstream archivoProducto;
		archivoProducto.open("productos.csv", ios::out);
		if (archivoProducto.is_open())
		{
			for (Producto x : vectorProducto)
			{
				archivoProducto << x.getCodPro() << ";" << x.getNomApePro() << ";" << x.getPrePro() << ";" << x.getStockPro() << ";" << x.getCodCat() << ";" << endl;
			}
			archivoProducto.close();
		}
	}
	catch (exception e)
	{
		cout << "Ocurrio un error al grabar el archivo";
	}
}
void ProductoController::cargarDatosDelArchivoAlVector()
{
	try
	{
		int i;
		size_t posi;
		string linea;
		string temporal[5];
		fstream archivoProducto;
		archivoProducto.open("productos.csv", ios::in); // ios::in = modo lectura(entrada)
		if (archivoProducto.is_open())
		{
			while (!archivoProducto.eof() && getline(archivoProducto, linea)) // mientras archivoUsuario tenga datos;
			{
				i = 0;
				while ((posi = linea.find(";")) != string::npos) // string::npos = -1, posi = 1
				{
					temporal[i] = linea.substr(0, posi); // temporal[0] = linea.substr(0, 1); temporal[0] = 1
					linea.erase(0, posi + 1);			 // linea.erase(0,2);
					++i;								 // i = 1
					// Vuelve a iterar
				}
				Producto objPro(stoi(temporal[0]), temporal[1], stof(temporal[2]), stoi(temporal[3]), stoi(temporal[4]));
				add(objPro);
			}
		}
	}
	catch (exception e)
	{
		cout << "Ocurrio  un error al grabar el archivo";
	}
}
