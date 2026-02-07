#include <iostream>
#include <cstring>
using namespace std;

struct Estudiante {
    int carnet;
    char nombre[50];
    float nota;
    Estudiante* izq;
    Estudiante* der;
};

// Función auxiliar
Estudiante* crearEstudiante(int carnet, char nom[], float nota) {
    Estudiante* nuevo = new Estudiante();
    nuevo->carnet = carnet;
    nuevo->nota = nota;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    
    int i = 0;
    while(nom[i] != '\0' && i < 49) {
        nuevo->nombre[i] = nom[i];
        i++;
    }
    nuevo->nombre[i] = '\0';
    return nuevo;
}

// FUNCIÓN 1: Agregar estudiante
Estudiante* insertar(Estudiante* raiz, int carnet, char nombre[], float nota) {
    if (raiz == NULL) {
        return crearEstudiante(carnet, nombre, nota);
    }
    
    if (carnet < raiz->carnet) {
        raiz->izq = insertar(raiz->izq, carnet, nombre, nota);
    } else if (carnet > raiz->carnet) {
        raiz->der = insertar(raiz->der, carnet, nombre, nota);
    }
    
    return raiz;
}

// FUNCIÓN 2: Mostrar todos los estudiantes
void mostrarEstudiantes(Estudiante* raiz) {
    if (raiz != NULL) {
        mostrarEstudiantes(raiz->izq);
        cout << "\nCarnet: " << raiz->carnet 
             << "\nNombre: " << raiz->nombre 
             << "\nNota: " << raiz->nota 
             << "\n------------------------" << endl;
        mostrarEstudiantes(raiz->der);
    }
}

// FUNCIÓN 3: Buscar estudiante por carnet
void buscarEstudiante(Estudiante* raiz, int carnet) {
    if (raiz == NULL) {
        cout << "\nEstudiante con carnet " << carnet << " no encontrado." << endl;
        return;
    }
    
    if (carnet < raiz->carnet) {
        buscarEstudiante(raiz->izq, carnet);
    } else if (carnet > raiz->carnet) {
        buscarEstudiante(raiz->der, carnet);
    } else {
        cout << "\n=== ESTUDIANTE ENCONTRADO ===" << endl;
        cout << "Carnet: " << raiz->carnet << endl;
        cout << "Nombre: " << raiz->nombre << endl;
        cout << "Nota: " << raiz->nota << endl;
        cout << "Estado: " << (raiz->nota >= 6.0 ? "Aprobado" : "Reprobado") << endl;
    }
}

// Menú principal con opciones 1, 2 y 3
int main() {
    Estudiante* sistema = NULL;
    int opcion;
    
    do {
        cout << "\n==== SISTEMA DE GESTION DE ESTUDIANTES =====" << endl;
        cout << "1. Agregar estudiante" << endl;
        cout << "2. Mostrar todos los estudiantes" << endl;
        cout << "3. Buscar estudiante por carnet" << endl;
        cout << "4. Mostrar estudiantes aprobados" << endl;
        cout << "5. Mostrar estudiantes reprobados" << endl;
        cout << "6. Calcular promedio general" << endl;
        cout << "7. Mostrar estudiante con mejor nota" << endl;
        cout << "8. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                int carnet;
                char nombre[50];
                float nota;
                
                cout << "\n=== AGREGAR ESTUDIANTE ===" << endl;
                cout << "Ingrese carnet: ";
                cin >> carnet;
                cout << "Ingrese nombre: ";
                cin.ignore();
                cin.getline(nombre, 50);
                cout << "Ingrese nota: ";
                cin >> nota;
                
                sistema = insertar(sistema, carnet, nombre, nota);
                cout << "\nEstudiante agregado exitosamente!" << endl;
                break;
            }
            case 2:
                if (sistema == NULL) {
                    cout << "\nNo hay estudiantes registrados." << endl;
                } else {
                    cout << "\n=== LISTA DE ESTUDIANTES ===" << endl;
                    mostrarEstudiantes(sistema);
                }
                break;
            case 3: {
                int carnet;
                cout << "\n=== BUSCAR ESTUDIANTE ===" << endl;
                cout << "Ingrese carnet a buscar: ";
                cin >> carnet;
                buscarEstudiante(sistema, carnet);
                break;
            }
            case 8:
                cout << "\nSaliendo del sistema..." << endl;
                break;
            default:
                cout << "\nOpcion no valida. Intente de nuevo." << endl;
        }
        
    } while(opcion != 8);
    
    return 0;
}