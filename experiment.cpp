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

// Experimento 1
void exp1(vector<int> elements, vector<int> search) {
        cout << "Experimento 1: \n";
    BinTree binTree;
    SplayTree splayTree;

    auto start = chrono::high_resolution_clock::now();
    for (int i : elements) {
        binTree.insert(i);
    }
    for(int i : search){
        binTree.search(i);
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
    cout << "Binary Tree: " <<duration.count()/(float)1000 << " seconds\n";

    auto start2 = chrono::high_resolution_clock::now();
    for (int i : elements) {
        splayTree.insert(i);
    }
    for(int i : search) {
        splayTree.search(i);
    }
    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(stop2-start2);
    cout << "Splay Tree: " <<duration2.count()/(float)1000 << " seconds\n";
}
// Experimento 2
void exp2(vector<int> elements, vector<int> search, int M, int N) {

    auto rng = default_random_engine {};

    cout << "Experimento 2: \n";

    vector<int> search_f(M);
    for(int i =0; i<N; i++) {
        for(int j = 0; j< ((float)1/3)/((i+1)*(i+1))*M; j++) {
            search_f.push_back(elements[i]);
        }
    }
    shuffle(begin(search_f), end(search_f), rng);

    BinTree binTree2;
    SplayTree splayTree2;

    auto start3 = chrono::high_resolution_clock::now();
    for (int i : elements) {
        binTree2.insert(i);
    }
    for(int i : search){
        binTree2.search(i);
    }
    auto stop3 = chrono::high_resolution_clock::now();
    auto duration3 = chrono::duration_cast<chrono::milliseconds>(stop3-start3);
    cout << "Binary Tree: " <<duration3.count()/(float)1000 << " seconds\n";


    auto start4 = chrono::high_resolution_clock::now();
    for (int i : elements) {
        splayTree2.insert(i);
    }
    for(int i : search) {
        splayTree2.search(i);
    }
    auto stop4 = chrono::high_resolution_clock::now();
    auto duration4 = chrono::duration_cast<chrono::milliseconds>(stop4-start4);
    cout << "Splay Tree: " <<duration4.count()/(float)1000 << " seconds\n";
}
// Experimento 3
void exp3(vector<int> elements, vector<int> search) {
    cout << "Experimento 3: \n";
    sort(elements.begin(), elements.end());

    BinTree binTree3;
    SplayTree splayTree3;

    auto start5 = chrono::high_resolution_clock::now();
    for (int i : elements) {
        binTree3.insert(i);
    }
    for(int i : search){
        binTree3.search(i);
    }
    auto stop5 = chrono::high_resolution_clock::now();
    auto duration5 = chrono::duration_cast<chrono::milliseconds>(stop5-start5);
    cout << "Binary Tree: " <<duration5.count()/(float)1000 << " seconds\n";


    auto start6 = chrono::high_resolution_clock::now();
    for (int i : elements) {
        splayTree3.insert(i);
    }
    for(int i : search) {
        splayTree3.search(i);
    }
    auto stop6 = chrono::high_resolution_clock::now();
    auto duration6 = chrono::duration_cast<chrono::milliseconds>(stop6-start6);
    cout << "Splay Tree: " <<duration6.count()/(float)1000 << " seconds\n";
}
// Experimento 4
void exp4() {

}

// Main de la tarea.
int main(int argv, char* argc[]) {

    int N = static_cast<int>(pow(10,6)*stof(argc[1]));
    int M = N*100;

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
    
    exp1(elements, search);
    //exp2(elements, search, M, N);
    //exp3(elements, search);
    //exp4();
}