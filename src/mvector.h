//
// Created by joseph on 1/8/21.
//

/// init_vectors - fill the vectors array with an initial value.
/// @param [in] size Number of vectors to use. Should match size of vectors.
/// @param [in] dimensions Number of dimensions. Should not count the multiplier.
/// @param [in] vectors Array of vectors with a multiplier in form of (i, j, k..., C).
/// @param [in] init An initial value to assign to each field.

void init_vectors(int size, int dimensions, float *vectors, float init);


/// add_vectors - add the vectors
/// @param [in] size Number of vectors to use. Should not exceed size of `vectors`.
/// @param [in] dimensions Number of dimensions. Should not count the multiplier.
/// @param [in] vectors Array of vectors with a multiplier in form of (i, j, k..., C).
/// @param [out] destination Array representing the sum vector with multiplier.
/// @param [in] multiplier Multiplier to factor out at the end.

void add_vectors(int size, int dimensions, float *vectors, float *destination,
                 float multiplier);
