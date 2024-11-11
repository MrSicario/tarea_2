#include <chrono>
#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <print>
#include "bin_tree.hpp"
#include "splay_tree.hpp"

// Imports
using std::print,
    std::vector, 
    std::chrono::high_resolution_clock, 
    std::chrono::duration_cast,
    std::chrono::milliseconds;
// Aliases
typedef binTree::BinTree BinTree;
typedef splayTree::SplayTree SplayTree;

// Global Variable
auto rng = std::default_random_engine {};

// Auxiliary Functions
/**
 * 
 * Devuelve un vector de `n` elementos aleatorios
 * 
 * @param n Tamaño del vector a devolver.
 * @return Vector con `n` elementos aleatorios.
 */
vector<int> create_random_data(int n) {
    std::random_device r;
    std::seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937       eng(seed); // a source of random data    
    std::uniform_int_distribution<int> dist;
    vector<int> v(n);   
    generate(begin(v), end(v), bind(dist, eng));
    return v;
}
/** 
 * 
 * Calcula la constante C, utilizada en los experimentos 2 y 4, mediante sumatoria.
 * 
 * @param N El `N` a usar en el calculo de la constante
 * @return La constante C como un double.
 * */ 
double get_c(int N) {
    int sum=0;
    for (int i=0; i<N; i++) {
        sum += (i+1)*(i+1);
    }
    return 1/sum;
}
/** 
 * 
 * Función de probabilidad para los experimentos 2 y 4.
 * 
 * @param i El indice del elemento para el cual se calcula la probabilidad.
 * @param c La constante C a utilizar en el calculo de la probabilidad.
 * @return La probabilidad del elemento a buscar.
 */ 
double f(int i, double c) {
    return c/((i+1)*(i+1));
}
// Experimento 1
void exp1(vector<int> A, int M) {
    print("Experimento 1:\n\tPreparando arreglos...\n");
    // Arreglo de busqueda
    vector<int> B(M);
    for (int i : A ){
        for(int j=0; j<100;j++){
            B.push_back(i);
        }
    }
    shuffle(begin(B), end(B), rng);
    print("\tRealizando pruebas...\n");
    BinTree binTree;
    SplayTree splayTree;

    // Test A.B.B.
    auto startBinTree = high_resolution_clock::now();
    for (int i:A) {
        binTree.insert(i);
    }
    for (int i:B){
        binTree.search(i);
    }
    auto stopBinTree = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stopBinTree-startBinTree);
    print("\tBinary Tree: {0} seconds\n", duration.count()/1000.0);

    // Test Splay Tree
    auto startSplayTree = high_resolution_clock::now();
    for (int i:A) {
        splayTree.insert(i);
    }
    for (int i:B) {
        splayTree.search(i);
    }
    auto stopSplayTree = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stopSplayTree-startSplayTree);
    print("\tSplay Tree: {0} seconds\n", duration.count()/1000.0);
}
// Experimento 2
void exp2(vector<int> A, int N, int M) {
    print("Experimento 2:\n\tPreparando arreglos...\n");
    // Arreglo de busqueda.
    vector<int> B(M);
    double c = get_c(N);
    for(int i=0; i<N; i++) {
        int t = floor(f(i, c)*M);
        for(int j = 0; j<t; j++) {
            B.push_back(A[i]);
        }
    }
    shuffle(begin(B), end(B), rng);
    print("\tRealizando pruebas...\n");
    BinTree binTree;
    SplayTree splayTree;

    // Test A.B.B.
    auto startBinTree = high_resolution_clock::now();
    for (int i:A) {
        binTree.insert(i);
    }
    for (int i:B){
        binTree.search(i);
    }
    auto stopBinTree = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stopBinTree-startBinTree);
    print("\tBinary Tree: {0} seconds\n", duration.count()/1000.0);

    // Test Splay Tree
    auto startSplayTree = high_resolution_clock::now();
    for (int i:A) {
        splayTree.insert(i);
    }
    for (int i:B) {
        splayTree.search(i);
    }
    auto stopSplayTree = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stopSplayTree-startSplayTree);
    print("\tSplay Tree: {0} seconds\n", duration.count()/1000.0);
}
// Experimento 3
void exp3(vector<int> A, int M) {
    print("Experimento 3: \n\tPreparando arreglos...\n");
    // Arreglo de busqueda
    vector<int> B(M);
    for (int i:A){
        for(int j=0; j<100;j++){
            B.push_back(i);
        }
    }
    shuffle(begin(B), end(B), rng);
    // Sort del arreglo de inserción.
    sort(A.begin(), A.end());
    print("\tRealizando pruebas...\n");
    BinTree binTree;
    SplayTree splayTree;

    // Test A.B.B.
    auto startBinTree = high_resolution_clock::now();
    for (int i:A) {
        binTree.insert(i);
    }
    for (int i:B){
        binTree.search(i);
    }
    auto stopBinTree = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stopBinTree-startBinTree);
    print("\tBinary Tree: {0} seconds\n", duration.count()/1000.0);

    // Test Splay Tree
    auto startSplayTree = high_resolution_clock::now();
    for (int i:A) {
        splayTree.insert(i);
    }
    for (int i:B) {
        splayTree.search(i);
    }
    auto stopSplayTree = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stopSplayTree-startSplayTree);
    print("\tSplay Tree: {0} seconds\n", duration.count()/1000.0);
}
// Experimento 4
void exp4(vector<int> A, int N, int M) {
    print("Experimento 4: \n\tPreparando arreglos...\n");
    // Arreglo de inserción
    vector<int> C = A;
    sort(C.begin(), C.end());
    double c = get_c(N);
    // Arreglo de busqueda
    vector<int> B(M);
    for (int i=0; i<N; i++) {
        int t = floor(f(i, c)*M);
        for(int j = 0; j<t; j++) {
            B.push_back(A[i]);
        }
    }
    shuffle(begin(B), end(B), rng);
    print("\tRealizando pruebas...\n");
    BinTree binTree;
    SplayTree splayTree;

    // Test A.B.B.
    auto startBinTree = high_resolution_clock::now();
    for (int i:C) {
        binTree.insert(i);
    }
    for (int i:B){
        binTree.search(i);
    }
    auto stopBinTree = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stopBinTree-startBinTree);
    print("\tBinary Tree: {0} seconds\n", duration.count()/1000.0);

    // Test Splay Tree
    auto startSplayTree = high_resolution_clock::now();
    for (int i:C) {
        splayTree.insert(i);
    }
    for (int i:B) {
        splayTree.search(i);
    }
    auto stopSplayTree = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stopSplayTree-startSplayTree);
    print("\tSplay Tree: {0} seconds\n", duration.count()/1000.0);
}

// Main de la tarea.
int main(int argv, char* argc[]) {
    int base = 10*10*10*10*10*10;
    int N, M, experiment;
    if (argv == 2) {
        experiment = 0;
        N = static_cast<int>(base*std::stof(argc[1]));
        M = N*100;
    } else {
        experiment = atoi(argc[1]);
        N = static_cast<int>(base*std::stof(argc[2]));
        M = N*100;
    }
    vector<int> A(N);
    A = create_random_data(N);
    // Switch para correr experimentos
    switch (experiment) {
    case 1:
        exp1(A, M);
        break;

    case 2:
        exp2(A, M, N);
        break;

    case 3:
        exp3(A, M);
        break;

    case 4:
        exp4(A, N, M);
        break;

    default:
        exp1(A, M);
        exp2(A, M, N);
        exp3(A, M);
        exp4(A, N, M);
        break;
    }
}