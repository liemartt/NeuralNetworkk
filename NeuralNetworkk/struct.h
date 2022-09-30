#pragma once
#include <string>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#define _SIZES_OF_LAYERS {784,256,64,32,16,10};
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