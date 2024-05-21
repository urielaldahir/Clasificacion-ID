#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> // Para la función sort

using namespace std;

// Definición de la clase Punto para representar un punto en el espacio
class Punto {
public:
    double x, y;

    Punto(double x_val, double y_val) : x(x_val), y(y_val) {}

    // Método para calcular la distancia euclidiana entre dos puntos
    double calcularDistancia(const Punto& otroPunto) const {
        return sqrt(pow(x - otroPunto.x, 2) + pow(y - otroPunto.y, 2));
    }
};

// Definición de la clase kNN para realizar la clasificación
class KNN {
private:
    vector<Punto> puntosEntrenamiento; // Puntos de entrenamiento
    vector<int> etiquetas; // Etiquetas correspondientes a los puntos de entrenamiento

public:
    // Método para agregar un punto de entrenamiento con su etiqueta
    void agregarPuntoEntrenamiento(const Punto& punto, int etiqueta) {
        puntosEntrenamiento.push_back(punto);
        etiquetas.push_back(etiqueta);
    }

    // Método para predecir la etiqueta de un nuevo punto utilizando k-NN
    int predecir(const Punto& nuevoPunto, int k) const {
        // Crear un vector para almacenar las distancias entre el nuevo punto y los puntos de entrenamiento
        vector<pair<double, int>> distanciasEtiquetas;

        // Calcular y almacenar las distancias
        for (size_t i = 0; i < puntosEntrenamiento.size(); ++i) {
            double distancia = nuevoPunto.calcularDistancia(puntosEntrenamiento[i]);
            distanciasEtiquetas.emplace_back(distancia, etiquetas[i]);
        }

        // Ordenar las distancias de menor a mayor
        sort(distanciasEtiquetas.begin(), distanciasEtiquetas.end(),
                  [](const auto& a, const auto& b) { return a.first < b.first; });

        // Contar las etiquetas de los k puntos más cercanos
        vector<int> conteoEtiquetas(k, 0);
        for (int i = 0; i < k; ++i) {
            conteoEtiquetas[distanciasEtiquetas[i].second]++;
        }

        // Encontrar la etiqueta con mayor conteo
        int etiquetaPredicha = -1;
        int maxConteo = 0;
        for (int i = 0; i < k; ++i) {
            if (conteoEtiquetas[i] > maxConteo) {
                etiquetaPredicha = i;
                maxConteo = conteoEtiquetas[i];
            }
        }

        return etiquetaPredicha;
    }
};

int main() {
    // Crear un conjunto de datos de entrenamiento
    KNN knn;
    knn.agregarPuntoEntrenamiento(Punto(1, 2), 0);
    knn.agregarPuntoEntrenamiento(Punto(2, 3), 0);
    knn.agregarPuntoEntrenamiento(Punto(3, 4), 1);
    knn.agregarPuntoEntrenamiento(Punto(4, 5), 1);

    // Crear un nuevo punto para predecir su etiqueta
    Punto nuevoPunto(21, 31);

    // Predecir la etiqueta del nuevo punto utilizando k-NN con k=2
    int etiquetaPredicha = knn.predecir(nuevoPunto, 2);

    // Mostrar el resultado
    cout << "La etiqueta predicha para el nuevo punto es: " << etiquetaPredicha << endl;

    return 0;
}