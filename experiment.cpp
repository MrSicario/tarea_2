#include <iostream>
#include "bin_tree.hpp"
#include "splay_tree.hpp"

using namespace std;

constexpr bool DEBUG = true; // Cambiar a false cuando no se está corriendo debug.

// Main de la tarea.
int main() {
    if (DEBUG) {
        bt::test_binTree();
        st::test_splayTree();
    }
}