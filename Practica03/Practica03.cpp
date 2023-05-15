#include<bits/stdc++.h>
using namespace std;

/*
 * Práctica 02. Geometría Computacional.
 * Implementación del algoritmo Jarvis Match (Gift Wrapping).
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

/* Cálcula la orientación de giro respecto a 3 puntos. */
int OrientationTest(Point p, Point q, Point r)
{
  double valor =  (r.y - p.y)*(q.x - p.x) - (q.y - p.y)*(r.x - p.x);
  return (valor == 0) ? 0 : (valor > 0) ? 1 : -1;
}

/* Función que compara dos puntos. */
bool comparePoints(Point p, Point q)
{
  return ((p.y < q.y) || ((p.y == q.y) && (p.x < q.x))) ? true : false;
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
  // Jarvis Match (Gift Wrapping):
  std::list <Point> convexHull;
  // Encontrar el extremo:
  int minPointIndex = 0;
  for(int i = 0; i < cont; i++)
    {
      // Aquí
      Point p = puntos[minPointIndex];
      Point q = puntos[i];
      if(comparePoints(p, q) == false)
	minPointIndex = i;
    }
  int currentIndex = minPointIndex;
  Point p = puntos[currentIndex];
  convexHull.push_back(p);
  // Encontrar el resto de puntos:
  while(true)
    {
      int nextPointIndex = (currentIndex + 1) % cont;
      for(int i = 0; i < cont; i++)
	{
	  if(i == currentIndex || i == nextPointIndex) continue;
	  p = puntos[currentIndex];
	  Point q = puntos[i];
	  Point r = puntos[nextPointIndex];
	  int currentOrientation = OrientationTest(p, q, r);
	  if(currentOrientation == -1)
	    nextPointIndex = i;
	}
      currentIndex = nextPointIndex;
      if(currentIndex == minPointIndex) break;
      p = puntos[currentIndex];
      convexHull.push_back(p);
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
     " que conforman el cierre convexo se encuentran en el archivo <cierreConvexo.txt>." << endl;
  return 0;
}
