#include "Header.h"


int fromBigToLittleEndian(int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}


void readImages(string path, vector<vector<long double> >& Images) {
    ifstream file;
    file.open(path, ios::binary);
    if (file.is_open())
    {
        int magicNumber = 0;
        int numOfImages = 0;
        int Rows = 0;
        int Cols = 0;
        file.read((char*)&magicNumber, sizeof(magicNumber));
        magicNumber = fromBigToLittleEndian(magicNumber);
        file.read((char*)&numOfImages, sizeof(numOfImages));
        numOfImages = fromBigToLittleEndian(numOfImages);
        file.read((char*)&Rows, sizeof(Rows));
        Rows = fromBigToLittleEndian(Rows);
        file.read((char*)&Cols, sizeof(Cols));
        Cols = fromBigToLittleEndian(Cols);
        for (int i = 0; i < numOfImages; i++)
        {
            Images.push_back({});
            for (int r = 0; r < (Rows * Cols); r++)
            {
                unsigned char pixel = 0;
                file.read((char*)&pixel, sizeof(pixel));
                Images[i].push_back(pixel);
            }
        }
    }

}


void readLabels(string path, vector<long double>& Labels) {
    ifstream file;
    file.open(path, ios::binary);
    if (file.is_open())
    {
        int magicNumber = 0;
        int numOfLabels = 0;
        file.read((char*)&magicNumber, sizeof(magicNumber));
        magicNumber = fromBigToLittleEndian(magicNumber);
        file.read((char*)&numOfLabels, sizeof(numOfLabels));
        numOfLabels = fromBigToLittleEndian(numOfLabels);
        for (int i = 0; i < numOfLabels; i++)
        {
            unsigned char label = 0;
            file.read((char*)&label, sizeof(label));;
            Labels.push_back(label);
        }
        cout << magicNumber << endl << numOfLabels << endl;
    }
}


void readWeights(vector<Layer>& layers) {
    ifstream file;
    file.open("Weights.txt");
    for (int i = 0; i < layers.size() - 1; i++) {
        for (int j = 0; j < layers[i].neurons.size(); j++) {
            for (int k = 0; k < layers[i + 1].neurons.size(); k++) {
                string temp;
                file >> temp;
                long double weight{ stold(temp) };
                layers[i].weights[j][k] = weight;
            }
        }
    }

}

void readBiases(vector<Layer>& layers) {
    ifstream file;
    file.open("Biases.txt");

    for (int i = 0; i < layers.size(); i++) {
        for (int j = 0; j < layers[i].neurons.size(); j++) {

            string temp;
            file >> temp;
            long double bias{ stold(temp) };
            layers[i].biases[j] = bias;
        }
    }
}