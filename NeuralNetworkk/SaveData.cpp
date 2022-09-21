#include "Header.h"
void saveWeights(vector<Layer>& layers) {
    ofstream file;
    file.open("Weights.txt");
    for (int i = 0; i < layers.size() - 1; i++) {
        for (int j = 0; j < layers[i].neurons.size(); j++) {
            for (int k = 0; k < layers[i + 1].neurons.size(); k++) {
                file << layers[i].weights[j][k];
                file << ' ';
            }
        }
    }
}

void saveBiases(vector<Layer>& layers) {
    ofstream file;
    file.open("Biases.txt");
    for (int i = 0; i < layers.size(); i++) {
        for (int j = 0; j < layers[i].neurons.size(); j++) {
            file << layers[i].biases[j];
            file << ' ';
        }
    }
}
