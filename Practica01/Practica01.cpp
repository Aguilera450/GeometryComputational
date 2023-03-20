#include<bits/stdc++.h>
using namespace std;

/*
 * Práctica 01. Geometría Computacional.
 * Implementación del algoritmo Extreme Points.
 * Autor: Adrian Aguilera Moreno.
 * No. Cta. 421005200.
 * La realización de esta práctica fue pensada en una
 * implementación para concursos de programación competitiva,
 * así que no se siguieron buenas prácticas de programación.
 */


/**************** Funciones auxiliares y subrutinas. *****************/
using num = int;
/*
 * Estructura para modelar un punto:
 */
struct Point
{
  num id, x, y;
  Point() {}
  Point(num id_, num x_, num y_) : id(id_), x(x_), y(y_) {} 
};

/* Cálcula la resta de dos puntos. */
Point resta(Point p1, Point p2)
{
  return Point(-1, p1.x - p2.x, p1.y - p2.y);
}

/* Cálcula el producto de dos puntos. */
double productoCruz(Point p1, Point p2)
{
  return (p1.x * p2.y) - (p1.y * p2.x);
}

/* Cálcula la orientación de giro respecto a 3 puntos. */
int OrientationTest(Point p, Point q, Point r)
{
  double valor =  (r.y - p.y)*(q.x - p.x) - (q.y - p.y)*(r.x - p.x); //productoCruz(resta(p, q), resta(r, q));  
  return (valor == 0) ? 0 : (valor > 0) ? 1 : -1;
}

/* Indica si el punto current es interno al triángulo formado por los puntos: p, q, r.*/
bool isPointInsideTriangle(Point p, Point q, Point r, Point current)
{
  double orientacion1 = OrientationTest(p, q, current);
  double orientacion2 = OrientationTest(q, r, current);
  double orientacion3 = OrientationTest(r, p, current);
  return ((orientacion1 + orientacion2 + orientacion3 == -3) || (orientacion1 + orientacion2 + orientacion3 == 3)) ? true : false;
}



int main()
{
  /**************** Subrutina de lectura y creación de los puntos. *****************/
  string nombreArchivo = "puntos.txt";
  ifstream lectura(nombreArchivo.c_str());
  string cadenaPuntos;
  getline(lectura, cadenaPuntos);
  
  int cont = 0;
  for(char x : cadenaPuntos)
    if(x == ',')
      {
	cont++;
      }
  if(cont != 0) cont++; // Contamos el último punto después de la última coma.
  Point puntos[cont];
  cont = 0;
  int contador = 0;
  std::string id;
  std::string pX;
  std::string pY;
  for(char x : cadenaPuntos)
    {
      if(x == ',')
	{
	  contador = 0;
	  puntos[cont++] = Point(std::stoi(id), std::stoi(pX), std::stoi(pY));
	  id = ""; pX = ""; pY = "";
	}
      else if(x != ':' && contador == 0) id += x;
      else if(x != ':' && contador == 1) pX += x;
      else if(x != ':' && contador == 2) pY += x;
      else if(x == ':') contador++;
    }
  puntos[cont] = Point(std::stoi(id), std::stoi(pX), std::stoi(pY)); // Falta el último valor, pues no tiene coma.
  
  /*for(Point p : puntos)
    cout << "ID: " << p.id << ", X: " << p.x << ", Y: " << p.y << endl;*/
  
  /**************** Algoritmo. *****************/
  // EXTREME POINTS:
  std::list <Point> convexHull;
  for(int pointIndex = 0; pointIndex <= cont; pointIndex++)
    {
      bool isInside = false;
      for(int i = 0; i <= cont; i++)
	{
	  if(i == pointIndex) continue;
	  for(int j = i +1; j <= cont; j++)
	    {
	      if(j == pointIndex) continue;
	      for(int k = j + 1; k <= cont; k++)
		{
		  if(k == pointIndex) continue;
		  Point p = puntos[i];
		  Point q = puntos[j];
		  Point r = puntos[k];
		  Point current = puntos[pointIndex];
		  if(isPointInsideTriangle(p, q, r, current))
		    {
		      isInside = true;
		      break;
		    }
		}
	      if(isInside == true) break;
	    }
	  if(isInside == true) break;
	}
      if(isInside == false) convexHull.push_back(puntos[pointIndex]);
    }

  /**************** Subrutina de escritura de archivo. *****************/
  nombreArchivo = "cierreConvexo.txt";
  ofstream escritura;
  escritura.open(nombreArchivo.c_str(), fstream::out);

   for(Point x : convexHull)
     {
       escritura << x.id << endl;
     }
   
   escritura.close();
   
   // Regreso:
   cout << "Hola. El programa se ha ejecutado con éxito, los id's de los puntos" <<
     "que conforman el cierre convexo se encuentran en el archivo <cierreConvexo.txt>." << endl;
  return 0;
}
