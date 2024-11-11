#include <chrono>
#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <iostream>
#include "bin_tree.hpp"
#include "splay_tree.hpp"

using std::cout,
    std::vector, 
    std::chrono::high_resolution_clock, 
    std::chrono::duration_cast,
    std::chrono::milliseconds;
typedef binTree::BinTree BinTree;
typedef splayTree::SplayTree SplayTree;

auto rng = std::default_random_engine {};

vector<int> create_random_data(int n) {
    std::random_device r;
    std::seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937       eng(seed); // a source of random data    
    std::uniform_int_distribution<int> dist;
    vector<int> v(n);   
    generate(begin(v), end(v), bind(dist, eng));
    return v;
}

double get_c(int N) {
    int sum=0;
    for (int i=0; i<N; i++) {
        sum += (i+1)*(i+1);
    }
    return 1/sum;
}

double f(int i, double c) {
    return c/((i+1)*(i+1));
}

// Experimento 1
void exp1(vector<int> A, int M) {
    cout << "Experimento 1:\n";
    cout << "Preparando arreglos...\n";
    vector<int> B(M);
    for (int i : A ){
        for(int j=0; j<100;j++){
            B.push_back(i);
        }
    }
    shuffle(begin(B), end(B), rng);
    cout << "Realizando pruebas...\n";
    BinTree binTree;
    SplayTree splayTree;
    auto startBinTree = high_resolution_clock::now();
    for (int i : A) {
        binTree.insert(i);
    }
    for(int i : B){
        binTree.search(i);
    }
    auto stopBinTree = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stopBinTree-startBinTree);
    cout << "Binary Tree: " << duration.count()/(float)1000 << " seconds\n";

    auto startSplayTree = high_resolution_clock::now();
    for (int i : A) {
        splayTree.insert(i);
    }
    for(int i : B) {
        splayTree.search(i);
    }
    auto stopSplayTree = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stopSplayTree-startSplayTree);
    cout << "Splay Tree: " << duration.count()/(float)1000 << " seconds\n";

    return;
}
// Experimento 2
void exp2(vector<int> A, int N, int M) {
    cout << "Experimento 2: \n";
    cout << "Preparando arreglos...\n";
    
    vector<int> B(M);
    double c = get_c(N);
    for(int i=0; i<N; i++) {
        int t = floor(f(i, c)*M);
        for(int j = 0; j<t; j++) {
            B.push_back(A[i]);
        }
    }
    shuffle(begin(B), end(B), rng);
    cout << "Realizando pruebas...\n";
    BinTree binTree;
    SplayTree splayTree;

    auto startBinTree = high_resolution_clock::now();
    for (int i : A) {
        binTree.insert(i);
    }
    for(int i : B){
        binTree.search(i);
    }
    auto stopBinTree = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stopBinTree-startBinTree);
    cout << "Binary Tree: " << duration.count()/(float)1000 << " seconds\n";


    auto startSplayTree = high_resolution_clock::now();
    for (int i : A) {
        splayTree.insert(i);
    }
    for(int i : B) {
        splayTree.search(i);
    }
    auto stopSplayTree = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stopSplayTree-startSplayTree);
    cout << "Splay Tree: " << duration.count()/(float)1000 << " seconds\n";

    return;
}
// Experimento 3
void exp3(vector<int> A, int M) {
    cout << "Experimento 3: \n";
    cout << "Preparando arreglos...\n";
    vector<int> B(M);
    for (int i : A ){
        for(int j=0; j<100;j++){
            B.push_back(i);
        }
    }
    shuffle(begin(B), end(B), rng);
    sort(A.begin(), A.end());
    cout << "Realizando pruebas...\n";
    BinTree binTree;
    SplayTree splayTree;

    auto startBinTree = high_resolution_clock::now();
    for (int i : A) {
        binTree.insert(i);
    }
    for(int i : B){
        binTree.search(i);
    }
    auto stopBinTree = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stopBinTree-startBinTree);
    cout << "Binary Tree: " << duration.count()/(float)1000 << " seconds\n";


    auto startSplayTree = high_resolution_clock::now();
    for (int i : A) {
        splayTree.insert(i);
    }
    for(int i : B) {
        splayTree.search(i);
    }
    auto stopSplayTree = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stopSplayTree-startSplayTree);
    cout << "Splay Tree: " << duration.count()/(float)1000 << " seconds\n";

    return;
}
// Experimento 4
void exp4(vector<int> A, int N, int M) {
    cout << "Experimento 4: \n";
    cout << "Preparando arreglos...\n";
    vector<int> C = A;
    sort(C.begin(), C.end());
    double c = get_c(N);
    vector<int> B(M);
    for(int i=0; i<N; i++) {
        int t = floor(f(i, c)*M);
        for(int j = 0; j<t; j++) {
            B.push_back(A[i]);
        }
    }
    shuffle(begin(B), end(B), rng);
    cout << "Realizando pruebas...\n";
    BinTree binTree;
    SplayTree splayTree;

    auto startBinTree = high_resolution_clock::now();
    for (int i : C) {
        binTree.insert(i);
    }
    for(int i : B){
        binTree.search(i);
    }
    auto stopBinTree = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stopBinTree-startBinTree);
    cout << "Binary Tree: " << duration.count()/(float)1000 << " seconds\n";


    auto startSplayTree = high_resolution_clock::now();
    for (int i : C) {
        splayTree.insert(i);
    }
    for(int i : B) {
        splayTree.search(i);
    }
    auto stopSplayTree = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stopSplayTree-startSplayTree);
    cout << "Splay Tree: " << duration.count()/(float)1000 << " seconds\n";

    return;
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