//
// Created by joseph on 1/8/21.
//

#include "mvector.h"

void init_vectors(int size, int dimensions, float *vectors, float init) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < dimensions; j++) {
            *((vectors + i * (dimensions + 1)) + j) = init;
        }
        *(vectors + i * (dimensions + 1) + dimensions) = 1;
    }
}

void add_vectors(int size, int dimensions, float *vectors, float *destination, float multiplier) {

    // Initialize destination vector
    for (int i = 0; i < dimensions; i++) {
        destination[i] = 0;
//        *(destination + i) = 0;
    }
    *(destination + dimensions) = 1;

    // Add to destination vector
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < dimensions; j++) {
//            destination[j] += vectors[i][j] * vectors[i][dimensions];
            *(destination + j) +=
                    *(vectors + i * (dimensions + 1) + j) * *(vectors + i * (dimensions + 1) + dimensions);
        }
    }

    // Factor out multiplier
    for (int i = 0; i < dimensions; i++) {
        *(destination + i) /= multiplier;
    }
    *(destination + dimensions) = multiplier;
}
