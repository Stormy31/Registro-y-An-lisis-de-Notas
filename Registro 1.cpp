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
void registrarEstudiante() {
    if (numEstudiantes >= MAX_ESTUDIANTES) {
        cout << "No se pueden registrar más estudiantes.\n";
        return;
    }
    
    Estudiante nuevoEstudiante;
    cout << "Ingrese el ID del estudiante: ";
    cin >> nuevoEstudiante.id;
    cin.ignore(); // Limpiar el buffer
    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, nuevoEstudiante.nombre);
    
    estudiantes[numEstudiantes++] = nuevoEstudiante;
    cout << "Estudiante registrado correctamente.\n";
}
void matricularEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante a matricular: ";
    cin >> id;

    for (int i = 0; i < numEstudiantes; ++i) {
        if (estudiantes[i].id == id) {
            if (estudiantes[i].numMaterias >= MAX_MATERIAS) {
                cout << "El estudiante ya está matriculado en el máximo de materias.\n";
                return;
            }
            cout << "Seleccione la materia a matricular :\n";
            cout << "1. Matemática\n2. Programación\n3. Literatura\n";
            int opcion;
            cin >> opcion;
            cin.ignore(); // Limpiar el buffer

            Materia* materia = new Materia;
            switch (opcion) {
                case 1: materia->nombreMateria = "Matemática"; break;
                case 2: materia->nombreMateria = "Programación"; break;
                case 3: materia->nombreMateria = "Literatura"; break;
                default: cout << "Opción inválida.\n"; return;
            }
            if (materia->numTrabajos == 0) { // Solo se crean una vez
                cout << "Ingrese el número de trabajos para " << materia->nombreMateria << ": ";
                cin >> materia->numTrabajos;
                cin.ignore(); // Limpiar el buffer

                for (int k = 0; k < materia->numTrabajos; ++k) {
                    cout << "Ingrese el nombre del trabajo #" << (k + 1) << ": ";
                    getline(cin, materia->trabajos[k].nombreTrabajo);
                    materia->trabajos[k].nota = 0; // Inicializar nota
                }
            }
            estudiantes[i].materias[estudiantes[i].numMaterias++].materia = materia;
            cout << "Estudiante matriculado en " << materia->nombreMateria << ".\n";
            return;
        }
    }
    cout << "Estudiante no encontrado.\n";
}
void crearTrabajosPorMateria() {
    // Solo un administrador puede crear trabajos
    cout << "Creando trabajos para las materias...\n";
    for (int i = 0; i < numEstudiantes; ++i) {
        for (int j = 0; j < estudiantes[i].numMaterias; ++j) {
            Materia* materia = estudiantes[i].materias[j].materia;
            if (materia->numTrabajos == 0) { // Solo se crean una vez
                cout << "Ingrese el número de trabajos para " << materia->nombreMateria << ": ";
                cin >> materia->numTrabajos;
                cin.ignore(); // Limpiar el buffer

                for (int k = 0; k < materia->numTrabajos; ++k) {
                    cout << "Ingrese el nombre del trabajo #" << (k + 1) << ": ";
                    getline(cin, materia->trabajos[k].nombreTrabajo);
                    materia->trabajos[k].nota = 0; // Inicializar nota
                }
                cout << "Trabajos creados para " << materia->nombreMateria << ".\n";
            }
        }
    }
}
void asignarNotas() {
    int id;
    cout << "Ingrese el ID del estudiante para asignar notas: ";
    cin >> id;

    for (int i = 0; i < numEstudiantes; ++i) {
        if (estudiantes[i].id == id) {
            cout << "Asignando notas para " << estudiantes[i].nombre << ":\n";
            for (int j = 0; j < estudiantes[i].numMaterias; ++j) {
                Materia* materia = estudiantes[i].materias[j].materia;
                cout << "Trabajos para " << materia->nombreMateria << ":\n";
                for (int k = 0; k < materia->numTrabajos; ++k) {
                    cout << "Trabajo: " << materia->trabajos[k].nombreTrabajo << "\n";
                    cout << "Ingrese la nota: ";
                    cin >> materia->trabajos[k].nota;
                }
            }
            return;
        }
    }
    cout << "Estudiante no encontrado.\n";
}
void mostrarResumenNotas() {
    int id;
    cout << "Ingrese el ID del estudiante para mostrar resumen de notas: ";
    cin >> id;

    for (int i = 0; i < numEstudiantes; ++i) {
        if (estudiantes[i].id == id) {
            cout << "Resumen de notas para " << estudiantes[i].nombre << ":\n";
            for (int j = 0; j < estudiantes[i].numMaterias; ++j) {
                Materia* materia = estudiantes[i].materias[j].materia;
                cout << "Materia: " << materia->nombreMateria << "\n";
                for (int k = 0; k < materia->numTrabajos; ++k) {
                    cout << "Trabajo: " << materia->trabajos[k].nombreTrabajo 
                         << ", Nota: " << fixed << setprecision(2) 
                         << materia->trabajos[k].nota << "\n";
                }
            }
            return;
        }
    }
    cout << "Estudiante no encontrado.\n";
}
//                 cout << "Promedio de " << materia->nombreMateria << ": "
//                      << setprecision(2) << fixed << promedio << "\n";
int main() {
    int opcion;
    do {
        cout << "1. Registrar estudiante\n";
        cout << "2. Matricular estudiante\n";
        cout << "3. Crear trabajos por materia\n";
        cout << "4. Asignar notas\n";
        cout << "5. Mostrar resumen de notas\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1: registrarEstudiante(); break;
            case 2: matricularEstudiante(); break;
            case 3: crearTrabajosPorMateria(); break;
            case 4: asignarNotas(); break;
            case 5: mostrarResumenNotas(); break;
            case 6: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion != 6);

    return 0;
}

