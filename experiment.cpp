#include <iostream>
#include <chrono>
#include <cmath>
#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include "bin_tree.hpp"
#include "splay_tree.hpp"

using namespace std;
typedef binTree::BinTree BinTree;
typedef splayTree::SplayTree SplayTree;

vector<int> create_random_data(int n) {
  random_device r;
  seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
  mt19937       eng(seed); // a source of random data

  uniform_int_distribution<int> dist;
  vector<int> v(n);

  generate(begin(v), end(v), bind(dist, eng));
  return v;
}

double sum_N(int N) {
    int sum=0;
    for (int i=0; i<N; i++) {
        sum += (i+1)*(i+1);
    }
    return 1/sum;
}

double f(int i, int N) {
    double C = sum_N(N);
    return C/((i+1)*(i+1));
}

// Experimento 1
void exp1(vector<int> elements, vector<int> search) {
    cout << "Experimento 1: \n";
    BinTree binTree;
    SplayTree splayTree;
    cout << "Realizando pruebas..." << endl;
    auto startBinTree = chrono::high_resolution_clock::now();
    for (int i : elements) {
        binTree.insert(i);
    }
    for(int i : search){
        binTree.search(i);
    }
    auto stopBinTree = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stopBinTree-startBinTree);
    cout << "Binary Tree: " << duration.count()/(float)1000 << " seconds\n";

    auto startSplayTree = chrono::high_resolution_clock::now();
    for (int i : elements) {
        splayTree.insert(i);
    }
    for(int i : search) {
        splayTree.search(i);
    }
    auto stopSplayTree = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stopSplayTree-startSplayTree);
    cout << "Splay Tree: " << duration.count()/(float)1000 << " seconds\n";
}
// Experimento 2
void exp2(vector<int> elements, int N, int M) {
    cout << "Experimento 2: \n";
    auto rng = default_random_engine {};
    cout << "Preparando arreglos..." << endl;
    vector<int> search;
    for(int i =0; i<N; i++) {
        int t = floor(f(i, N)*M);
        for(int j = 0; j<t; j++) {
            search.push_back(elements[i]);
        }
    }
    shuffle(begin(search), end(search), rng);
    cout << "Realizando pruebas..." << endl;
    BinTree binTree;
    SplayTree splayTree;

    auto startBinTree = chrono::high_resolution_clock::now();
    for (int i : elements) {
        binTree.insert(i);
    }
    for(int i : search){
        binTree.search(i);
    }
    auto stopBinTree = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stopBinTree-startBinTree);
    cout << "Binary Tree: " << duration.count()/(float)1000 << " seconds\n";


    auto startSplayTree = chrono::high_resolution_clock::now();
    for (int i : elements) {
        splayTree.insert(i);
    }
    for(int i : search) {
        splayTree.search(i);
    }
    auto stopSplayTree = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stopSplayTree-startSplayTree);
    cout << "Splay Tree: " << duration.count()/(float)1000 << " seconds\n";
}
// Experimento 3
void exp3(vector<int> elements, vector<int> search) {
    cout << "Experimento 3: \n";
    cout << "Preparando arreglos..." << endl;
    sort(elements.begin(), elements.end());
    cout << "Realizando pruebas..." << endl;
    BinTree binTree;
    SplayTree splayTree;

    auto startBinTree = chrono::high_resolution_clock::now();
    for (int i : elements) {
        binTree.insert(i);
    }
    for(int i : search){
        binTree.search(i);
    }
    auto stopBinTree = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stopBinTree-startBinTree);
    cout << "Binary Tree: " << duration.count()/(float)1000 << " seconds\n";


    auto startSplayTree = chrono::high_resolution_clock::now();
    for (int i : elements) {
        splayTree.insert(i);
    }
    for(int i : search) {
        splayTree.search(i);
    }
    auto stopSplayTree = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stopSplayTree-startSplayTree);
    cout << "Splay Tree: " << duration.count()/(float)1000 << " seconds\n";
}
// Experimento 4
void exp4(vector<int> elements, int N, int M) {
    cout << "Experimento 4: \n";
    cout << "Preparando arreglos..." << endl;
    sort(elements.begin(), elements.end());
    auto rng = default_random_engine {};
    vector<int> search;
    for(int i =0; i<N; i++) {
        int t = floor(f(i, N)*M);
        for(int j = 0; j<t; j++) {
            search.push_back(elements[i]);
        }
    }
    shuffle(begin(search), end(search), rng);
    cout << "Realizando pruebas..." << endl;
    BinTree binTree;
    SplayTree splayTree;

    auto startBinTree = chrono::high_resolution_clock::now();
    for (int i : elements) {
        binTree.insert(i);
    }
    for(int i : search){
        binTree.search(i);
    }
    auto stopBinTree = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stopBinTree-startBinTree);
    cout << "Binary Tree: " << duration.count()/(float)1000 << " seconds\n";


    auto startSplayTree = chrono::high_resolution_clock::now();
    for (int i : elements) {
        splayTree.insert(i);
    }
    for(int i : search) {
        splayTree.search(i);
    }
    auto stopSplayTree = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stopSplayTree-startSplayTree);
    cout << "Splay Tree: " << duration.count()/(float)1000 << " seconds\n";
}

// Main de la tarea.
int main(int argv, char* argc[]) {

    int N, M, experiment;

    if (argv == 2) {
        experiment = 0;
        N = static_cast<int>(pow(10,6)*stof(argc[1]));
        M = N*100;
    } else {
        experiment = atoi(argc[1]);
        N = static_cast<int>(pow(10,6)*stof(argc[2]));
        M = N*100;
    }

    vector<int> elements(N);
    vector<int> search(M);
    elements = create_random_data(N);
    for (int i : elements ){
        for(int j=0; j<100;j++){
            search.push_back(i);
        }
    }
    auto rng = default_random_engine {};
    shuffle(begin(search), end(search), rng);

    switch (experiment) {
    case 0:
        exp1(elements, search);
        exp2(elements, N, M);
        exp3(elements, search);
        exp4(elements, N, M);
        break;
    
    case 1:
        exp1(elements, search);
        break;

    case 2:
        exp2(elements, M, N);
        break;

    case 3:
        exp3(elements, search);
        break;

    case 4:
        exp4(elements, N, M);
        break;

    default:
        exp1(elements, search);
        exp2(elements, M, N);
        exp3(elements, search);
        exp4(elements, N, M);
        break;
    }
}