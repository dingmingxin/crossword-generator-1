#ifndef XWS_H
#define XWS_H

// Chance of probabilistic motivated continuation.
const int P_M_C_FACTOR = 95;

void rand_seed();
double rand_double(double low, double high);

bool fill(Grid &xword, Dict &dict);
bool word_fits(char* word, const string &dict_word);

#endif