#pragma once
#include <string>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#define _AMOUNT_OF_LAYERS 6
#define _PATH_OF_IMAGES "testImages.idx3-ubyte"
#define _PATH_OF_LABELS "testLabels.idx1-ubyte"
#define _SIZES_OF_LAYERS {784,256,64,32,16,10};
#define _PATH_OF_TRAIN_IMAGES "train-images.idx3-ubyte"
#define _PATH_OF_TRAIN_LABELS "train-labels.idx1-ubyte"
using namespace std;
struct Layer {
    vector<long double>neurons;
    vector<long double>biases;
    vector<vector<long double>>weights;
};
vector<vector<long double> >arrayOfImages;
vector<long double>arrayOfLabels;
vector<int> sizes = _SIZES_OF_LAYERS;
vector<Layer> layers;


 int fromBigToLittleEndian(int i);
 void readImages(string path, vector<vector<long double> >& Images);
 void readLabels(string path, vector<long double>& Labels);
 long double modRelu(long double x);
 long double derivative(long double x);
 void DoLayers(vector<Layer>& layers, vector<int> sizes);
 void forwardFeeding(vector<long double>input, vector<Layer>& layers);
 void backPropagation(int predict, vector<Layer>& layers, double learningRate, vector<long double>errors);
 int predict(vector<Layer>& layers);
 void saveWeights(vector<Layer>& layers);
 void saveBiases(vector<Layer>& layers);
 void train(vector<Layer>& layers, vector<vector<long double>>arrayOfImages, vector<long double>arrayOfLabels, vector<int> sizes);
 void readWeights(vector<Layer>& layers);
 void readBiases(vector<Layer>& layers);
 void testFile(vector<Layer>& layers, vector<vector<long double>>arrayOfImages, vector<long double>arrayOfLabels);
 void drawDigit(vector<Layer>& layers);
 void NeuralNetwork();
