
#include "Header.h"
    long double modRelu(long double x) {
        if (x < 0) return 0.01 * x;
        if (x >= 0 and x <= 1) return x;
        if (x > 1) return 1 + 0.01 * (x - 1);
    }

    long double derivative(long double x) {

        if (x < 0) return 0.01;
        if (x >= 0 && x <= 1) return 1;
        if (x > 1) return 0.01;
    }



    void DoLayers(vector<Layer>& layers, vector<int> sizes) {
        for (int i = 0; i < sizes.size(); i++) {
            int nextsize = 0;
            if (i < sizes.size() - 1) nextsize = sizes[i + 1];
            layers[i].neurons.resize(sizes[i]);
            layers[i].biases.resize(sizes[i]);
            layers[i].weights.resize(sizes[i]);
            for (int q = 0; q < sizes[i]; q++) {
                layers[i].weights[q].resize(nextsize);
            }
            for (int j = 0; j < sizes[i]; j++) {
                if (rand() % 2 == 0)
                    layers[i].biases[j] = ((rand() % 100)) / 1000.0;
                else
                    layers[i].biases[j] = -((rand() % 100)) / 1000.0;
                for (int k = 0; k < nextsize; k++) {
                    if (rand() % 2 == 0)
                        layers[i].weights[j][k] = ((rand() % 100)) / 1000.0;
                    else layers[i].weights[j][k] = -((rand() % 100)) / 1000.0;
                }
            }
        }
    }



    void forwardFeeding(vector<long double>input, vector<Layer>& layers) {
        for (int j = 0; j < input.size(); j++) {
            layers[0].neurons[j] = (input[j]);
        }
        for (int i = 1; i < layers.size(); i++) {
            for (int j = 0; j < layers[i].neurons.size(); j++) {
                layers[i].neurons[j] = 0;
                for (int k = 0; k < layers[i - 1].neurons.size(); k++) {
                    layers[i].neurons[j] += layers[i - 1].neurons[k] * layers[i - 1].weights[k][j];
                }
                layers[i].neurons[j] += layers[i].biases[j];
                layers[i].neurons[j] = modRelu(layers[i].neurons[j]);
            }
        }
        //softMax(layers[3].neurons);

    }





    void backPropagation(int predict, vector<Layer>& layers, double learningRate, vector<long double>errors) {

        for (int k = layers.size() - 2; k >= 0; k--) {
            vector<long double>errsNext;
            vector<long double>gradients;
            errsNext.resize(layers[k].neurons.size());
            gradients.resize(layers[k + 1].neurons.size());
            for (int i = 0; i < layers[k + 1].neurons.size(); i++) {
                gradients[i] = errors[i] * derivative(layers[k + 1].neurons[i]);
                gradients[i] *= learningRate;
            }
            vector<vector<long double> > delta;
            delta.resize(layers[k + 1].neurons.size());
            for (int i = 0; i < layers[k + 1].neurons.size(); i++) {
                delta[i].resize(layers[k].neurons.size());
            }
            for (int i = 0; i < layers[k + 1].neurons.size(); i++) {
                for (int j = 0; j < layers[k].neurons.size(); j++) {
                    delta[i][j] = gradients[i] * layers[k].neurons[j];
                }
            }
            for (int i = 0; i < layers[k].neurons.size(); i++) {
                errsNext[i] = 0;
                for (int j = 0; j < layers[k + 1].neurons.size(); j++) {
                    errsNext[i] += layers[k].weights[i][j] * errors[j];
                }
            }
            errors.resize(0);
            errors.resize(layers[k].neurons.size());
            for (int i = 0; i < layers[k].neurons.size(); i++) {
                errors[i] = errsNext[i];
            }
            vector<vector<long double> > newWeights;
            newWeights.resize(layers[k].neurons.size());
            for (int i = 0; i < newWeights.size(); i++) {
                newWeights[i].resize(layers[k + 1].neurons.size());
            }
            for (int i = 0; i < layers[k + 1].neurons.size(); i++) {
                for (int j = 0; j < layers[k].neurons.size(); j++) {
                    newWeights[j][i] = (layers[k].weights[j][i] + delta[i][j]);
                }
            }
            for (int i = 0; i < layers[k].weights.size(); i++) {
                for (int j = 0; j < layers[k].weights[i].size(); j++) {
                    layers[k].weights[i][j] = newWeights[i][j];
                }
            }
            for (int i = 0; i < layers[k + 1].biases.size(); i++) {
                layers[k + 1].biases[i] += gradients[i];
            }

        }

    }


    int predict(vector<Layer>& layers) {
        long double maxWeight = 0;
        int digit = 0;
        for (int i = 0; i < 10; i++) {
            if (layers[layers.size() - 1].neurons[i] > maxWeight) {
                maxWeight = layers[layers.size() - 1].neurons[i];
                digit = i;
            }
        }
        return digit;
    }



    void train(vector<Layer>& layers, vector<vector<long double>>arrayOfImages, vector<long double>arrayOfLabels, vector<int> sizes) {
        int batch = 100;

        int epochs = 2000;

        int indexOfImg = 0;
        for (int i = 0; i < epochs; i++) {
            vector<long double>errors;
            errors.resize(10);
            int count = 0;
            long double errSum = 0;
            for (int j = 0; j < batch; j++) {
                indexOfImg = rand() % 60000;
                int rightDigit = arrayOfLabels[indexOfImg];
                forwardFeeding(arrayOfImages[indexOfImg], layers);
                int predictedDigit = predict(layers);
                if (predictedDigit == rightDigit) count++;

                for (int i = 0; i < 10; i++) {
                    if (i == rightDigit) {
                        errSum += pow(1.0 - layers[layers.size() - 1].neurons[i], 2);
                        errors[i] = 1.0 - layers[layers.size() - 1].neurons[i];
                    }
                    else {
                        errSum += pow(0.0 - layers[layers.size() - 1].neurons[i], 2);
                        errors[i] = 0.0 - layers[layers.size() - 1].neurons[i];
                    }
                }
                backPropagation(predictedDigit, layers, 0.001, errors);
            }
            cout << "epoch: " << i << " right: " << count << "/100 " << "error: " << errSum << endl;
        }

    }


    void testFile(vector<Layer>& layers, vector<vector<long double>>arrayOfImages, vector<long double>arrayOfLabels) {
        int batch = 100;
        int epochs = 100;
        long double percentage = 0;
        int indexOfImg = 0;
        for (int i = 0; i < epochs; i++) {
            int count = 0;
            for (int j = 0; j < batch; j++) {
                int rightDigit = arrayOfLabels[indexOfImg];
                forwardFeeding(arrayOfImages[indexOfImg], layers);
                int predictedDigit = predict(layers);
                if (predictedDigit == rightDigit) count++;
                indexOfImg++;
            }
            percentage += count;
            cout << "Number of Pictures: " << (i + 1) * batch << " Right Answer: " << count << "/" << batch << endl;
        }
        cout << "Percentage of right answer: " << (percentage / (batch * epochs)) * 100 << '%' << endl;
    }


    void drawDigit(vector<Layer>& layers) {
        ifstream file;
        file.open("convertImage.txt");
        vector <long double> testImage;
        for (int i = 0; i < 784; i++) {

            string temp;
            file >> temp;
            testImage.push_back(stold(temp));
        }
        forwardFeeding(testImage, layers);
        int prediction = predict(layers);

        cout << "Predict: " << prediction << endl;
    }


    void NeuralNetwork() {
        int choise;


        layers.resize(_AMOUNT_OF_LAYERS);


        DoLayers(layers, sizes);



        cout << "Choose 1 option: " << endl;
        cout << "1. Train again" << endl;
        cout << "2. Test file" << endl;
        cout << "3. Test on your digit" << endl;
        cout << "Your choise: ";
        cin >> choise;
        switch (choise) {
        case 1:
            readImages(_PATH_OF_TRAIN_IMAGES, arrayOfImages);
            readLabels(_PATH_OF_TRAIN_LABELS,arrayOfLabels);
            train(layers, arrayOfImages, arrayOfLabels, sizes);
            saveWeights(layers);
            saveBiases(layers);
            break;
        case 2:

            readImages(_PATH_OF_IMAGES, arrayOfImages);

            readLabels(_PATH_OF_LABELS,arrayOfLabels);
            readWeights(layers);

            readBiases(layers);

            testFile(layers, arrayOfImages, arrayOfLabels);
            break;
        case 3:
            readWeights(layers);

            readBiases(layers);

            drawDigit(layers);
            getchar();
            break;
        }
    }

