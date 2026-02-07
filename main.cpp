#include <iostream>
#include <cstring>
using namespace std;

struct Estudiante {
    int carnet;
    char nombre[50];
    float nota;
    Estudiante* izquierdo;
    Estudiante* derecho;
};

Estudiante* crearEstudiante(int carnet, char nom[], float nota) {
    Estudiante* nuevo = new Estudiante();
    nuevo->carnet = carnet;
    nuevo->nota = nota;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    

    int i = 0;
    while(nom[i] != '\0' && i < 49) {
        nuevo->nombre[i] = nom[i];
        i++;
    }
    nuevo->nombre[i] = '\0';
    return nuevo;
}

// 1. Insertar un estudiante en el árbol (ordenado por carnet)
Estudiante* insertar(Estudiante* raiz, int carnet, char nombre[], float nota) {
    if (raiz == NULL) {
        return crearEstudiante(carnet, nombre, nota);
    }
    
    if (carnet < raiz->carnet) {
        raiz->izquierdo = insertar(raiz->izquierdo, carnet, nombre, nota);
    } else if (carnet > raiz->carnet) {
        raiz->derecho = insertar(raiz->derecho, carnet, nombre, nota);
    }
    
    return raiz;
}

// 2. Mostrar todos los estudiantes en orden de carnet
void mostrarEstudiantes(Estudiante* raiz) {
    if (raiz != NULL) {
        mostrarEstudiantes(raiz->izquierdo);
        cout << "\nCarnet: " << raiz->carnet 
             << "\nNombre: " << raiz->nombre 
             << "\nNota: " << raiz->nota 
             << "\n------------------------" << endl;
        mostrarEstudiantes(raiz->derecho);
    }
}

// 3. Buscar un estudiante por carnet y mostrar sus datos
void buscarEstudiante(Estudiante* raiz, int carnet) {
    if (raiz == NULL) {
        cout << "\nEstudiante con carnet " << carnet << " no encontrado." << endl;
        return;
    }
    
    if (carnet < raiz->carnet) {
        buscarEstudiante(raiz->izquierdo, carnet);
    } else if (carnet > raiz->carnet) {
        buscarEstudiante(raiz->derecho, carnet);
    } else {
        cout << "\n=== ESTUDIANTE ENCONTRADO ===" << endl;
        cout << "Carnet: " << raiz->carnet << endl;
        cout << "Nombre: " << raiz->nombre << endl;
        cout << "Nota: " << raiz->nota << endl;
        cout << "Estado: " << (raiz->nota >= 6.0 ? "Aprobado" : "Reprobado") << endl;
    }
}

// 4. Mostrar estudiantes aprobados (nota >= 6.0)
void mostrarAprobados(Estudiante* raiz) {
    if (raiz != NULL) {
        mostrarAprobados(raiz->izquierdo);
        if (raiz->nota >= 6.0) {
            cout << "\nCarnet: " << raiz->carnet 
                 << "\nNombre: " << raiz->nombre 
                 << "\nNota: " << raiz->nota 
                 << "\n------------------------" << endl;
        }
        mostrarAprobados(raiz->derecho);
    }
}

// 5. Mostrar estudiantes reprobados (nota < 6.0)
void mostrarReprobados(Estudiante* raiz) {
    if (raiz != NULL) {
        mostrarReprobados(raiz->izquierdo);
        if (raiz->nota < 6.0) {
            cout << "\nCarnet: " << raiz->carnet 
                 << "\nNombre: " << raiz->nombre 
                 << "\nNota: " << raiz->nota 
                 << "\n------------------------" << endl;
        }
        mostrarReprobados(raiz->derecho);
    }
}

// 6. Calcular el promedio de todas las notas
float calcularPromedio(Estudiante* raiz, int* contador, float* suma) {
    if (raiz != NULL) {
        calcularPromedio(raiz->izquierdo, contador, suma);
        (*contador)++;
        (*suma) += raiz->nota;
        calcularPromedio(raiz->derecho, contador, suma);
    }
    return (*contador > 0) ? (*suma / *contador) : 0.0;
}

int main() {
    
    return 0;
}