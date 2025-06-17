#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // Para std::setprecision
using namespace std;

const int MAX_ESTUDIANTES = 10;
const int MAX_MATERIAS = 3;
const int MAX_TRABAJOS = 3;

struct Trabajo {
    string nombreTrabajo;
    float nota;
};

struct Materia {
    string nombreMateria; // Solo puede ser: Matemática, Programación, Literatura
    Trabajo trabajos[MAX_TRABAJOS];
    int numTrabajos = 0;
};

struct Matricula {
    Materia* materia;
};

struct Estudiante {
    int id;
    string nombre;
    Matricula materias[MAX_MATERIAS];
    int numMaterias = 0;
};

Estudiante estudiantes[MAX_ESTUDIANTES];
int numEstudiantes = 0;