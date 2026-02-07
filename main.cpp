#include <iostream>
#include <cstring>
using namespace std;

struct Estudiante
{
    int carnet;
    char nombre[50];
    float nota;
    Estudiante *izquierdo;
    Estudiante *derecho;
};

Estudiante *crearEstudiante(int carnet, char nom[], float nota)
{
    Estudiante *nuevo = new Estudiante();
    nuevo->carnet = carnet;
    nuevo->nota = nota;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;

    int i = 0;
    while (nom[i] != '\0' && i < 49)
    {
        nuevo->nombre[i] = nom[i];
        i++;
    }
    nuevo->nombre[i] = '\0';
    return nuevo;
}

// 1. Insertar un estudiante en el árbol (ordenado por carnet)
Estudiante *insertar(Estudiante *raiz, int carnet, char nombre[], float nota)
{
    if (raiz == NULL)
    {
        return crearEstudiante(carnet, nombre, nota);
    }

    if (carnet < raiz->carnet)
    {
        raiz->izquierdo = insertar(raiz->izquierdo, carnet, nombre, nota);
    }
    else if (carnet > raiz->carnet)
    {
        raiz->derecho = insertar(raiz->derecho, carnet, nombre, nota);
    }

    return raiz;
}

// 2. Mostrar todos los estudiantes en orden de carnet
void mostrarEstudiantes(Estudiante *raiz)
{
    if (raiz != NULL)
    {
        mostrarEstudiantes(raiz->izquierdo);
        cout << "\nCarnet: " << raiz->carnet
             << "\nNombre: " << raiz->nombre
             << "\nNota: " << raiz->nota
             << "\n------------------------" << endl;
        mostrarEstudiantes(raiz->derecho);
    }
}

// 3. Buscar un estudiante por carnet y mostrar sus datos
void buscarEstudiante(Estudiante *raiz, int carnet)
{
    if (raiz == NULL)
    {
        cout << "\nEstudiante con carnet " << carnet << " no encontrado." << endl;
        return;
    }

    if (carnet < raiz->carnet)
    {
        buscarEstudiante(raiz->izquierdo, carnet);
    }
    else if (carnet > raiz->carnet)
    {
        buscarEstudiante(raiz->derecho, carnet);
    }
    else
    {
        cout << "\n=== ESTUDIANTE ENCONTRADO ===" << endl;
        cout << "Carnet: " << raiz->carnet << endl;
        cout << "Nombre: " << raiz->nombre << endl;
        cout << "Nota: " << raiz->nota << endl;
        cout << "Estado: " << (raiz->nota >= 6.0 ? "Aprobado" : "Reprobado") << endl;
    }
}

// 4. Mostrar estudiantes aprobados (nota >= 6.0)
void mostrarAprobados(Estudiante *raiz)
{
    if (raiz != NULL)
    {
        mostrarAprobados(raiz->izquierdo);
        if (raiz->nota >= 6.0)
        {
            cout << "\nCarnet: " << raiz->carnet
                 << "\nNombre: " << raiz->nombre
                 << "\nNota: " << raiz->nota
                 << "\n------------------------" << endl;
        }
        mostrarAprobados(raiz->derecho);
    }
}

// 5. Mostrar estudiantes reprobados (nota < 6.0)
void mostrarReprobados(Estudiante *raiz)
{
    if (raiz != NULL)
    {
        mostrarReprobados(raiz->izquierdo);
        if (raiz->nota < 6.0)
        {
            cout << "\nCarnet: " << raiz->carnet
                 << "\nNombre: " << raiz->nombre
                 << "\nNota: " << raiz->nota
                 << "\n------------------------" << endl;
        }
        mostrarReprobados(raiz->derecho);
    }
}

// 6. Calcular el promedio de todas las notas
float calcularPromedio(Estudiante *raiz, int *contador, float *suma)
{
    if (raiz != NULL)
    {
        calcularPromedio(raiz->izquierdo, contador, suma);
        (*contador)++;
        (*suma) += raiz->nota;
        calcularPromedio(raiz->derecho, contador, suma);
    }
    return (*contador > 0) ? (*suma / *contador) : 0.0;
}

// 7. Encontrar al estudiante con la nota más alta
Estudiante *encontrarMejorNota(Estudiante *raiz)
{
    if (raiz == NULL)
        return NULL;

    Estudiante *mejor = raiz;
    Estudiante *mejorIzq = encontrarMejorNota(raiz->izquierdo);
    Estudiante *mejorDer = encontrarMejorNota(raiz->derecho);

    if (mejorIzq != NULL && mejorIzq->nota > mejor->nota)
    {
        mejor = mejorIzq;
    }
    if (mejorDer != NULL && mejorDer->nota > mejor->nota)
    {
        mejor = mejorDer;
    }

    return mejor;
}

int main() {
    Estudiante* sistema = NULL;
    int opcion;
    
    do {
        cout << "\n==== SISTEMA DE GESTION DE ESTUDIANTES =====" << endl;
        cout << "1. Agregar estudiante (insertar)" << endl;
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
                
                // Llamar a la función 1: insertar
                sistema = insertar(sistema, carnet, nombre, nota);
                cout << "\n✓ Estudiante agregado exitosamente!" << endl;
                break;
            }
            case 2:
                if (sistema == NULL) {
                    cout << "\n✗ No hay estudiantes registrados." << endl;
                } else {
                    cout << "\n=== LISTA DE ESTUDIANTES (Ordenados por carnet) ===" << endl;
                    // Llamar a la función 2: mostrarEstudiantes
                    mostrarEstudiantes(sistema);
                }
                break;
            case 3: {
                int carnet;
                cout << "\n=== BUSCAR ESTUDIANTE ===" << endl;
                cout << "Ingrese carnet a buscar: ";
                cin >> carnet;
                // Llamar a la función 3: buscarEstudiante
                buscarEstudiante(sistema, carnet);
                break;
            }
            case 4:
                if (sistema == NULL) {
                    cout << "\n✗ No hay estudiantes registrados." << endl;
                } else {
                    cout << "\n=== ESTUDIANTES APROBADOS ===" << endl;
                    // Llamar a la función 4: mostrarAprobados
                    mostrarAprobados(sistema);
                }
                break;
            case 5:
                if (sistema == NULL) {
                    cout << "\n✗ No hay estudiantes registrados." << endl;
                } else {
                    cout << "\n=== ESTUDIANTES REPROBADOS ===" << endl;
                    // Llamar a la función 5: mostrarReprobados
                    mostrarReprobados(sistema);
                }
                break;
            case 6: {
                int contador = 0;
                float suma = 0.0;
                // Llamar a la función 6: calcularPromedio
                float promedio = calcularPromedio(sistema, &contador, &suma);
                
                if (contador == 0) {
                    cout << "\n✗ No hay estudiantes registrados." << endl;
                } else {
                    cout << "\n=== PROMEDIO GENERAL ===" << endl;
                    cout << "Total estudiantes: " << contador << endl;
                    cout << "Suma de notas: " << suma << endl;
                    cout << "Promedio: " << promedio << endl;
                }
                break;
            }
            case 7: {
                // Llamar a la función 7: encontrarMejorNota
                Estudiante* mejor = encontrarMejorNota(sistema);
                if (mejor == NULL) {
                    cout << "\n✗ No hay estudiantes registrados." << endl;
                } else {
                    cout << "\n=== ESTUDIANTE CON MEJOR NOTA ===" << endl;
                    cout << "Carnet: " << mejor->carnet << endl;
                    cout << "Nombre: " << mejor->nombre << endl;
                    cout << "Nota: " << mejor->nota << endl;
                }
                break;
            }
            case 8:
                cout << "\nSaliendo del sistema..." << endl;
                break;
            default:
                cout << "\n✗ Opcion no valida. Intente de nuevo." << endl;
        }
        
    } while(opcion != 8);
    
    while (sistema != NULL) {
        
        Estudiante* temp = sistema;
        sistema = insertar(sistema->izquierdo, temp->carnet, temp->nombre, temp->nota);
        delete temp;
        
    }
    
    return 0;
}