#include <vector>
using namespace std;

enum Bando {
	Jugador,
	Enemigo
};


enum TipoAccion;

class Unit {

	// Estadísticas. Cada tipo de unidad tiene unas estadísticas fijas/o variables si se añade experiencia

	int ATQ;
	int DEF;
	int MAG;
	int VIT_MAX;
	short dist;
	short rango;

	
	// Estado fijo que depende de cada unidad individualmente

	Bando bando;

	// Estado de la unidad, variable cada turno

	bool puedeMover;
	bool puedeActuar;
	int x_map;
	int y_map;
	int VIT;

public:

int update(int time);
int render();


// Cada unidad tiene un switch para cada una de las acciones disponibles. En caso de poder actuarse, aplicará cada acción con los datos pertinentes.
int accion(TipoAccion accion, Unit * unidad);
int avanzar(vector < pair<int, int>> * path);

// 

	

};