#include <iostream>
#include <vector>
#include <cmath>  // For log and isnan functions

// Assuming Y_to_sigma is a defined function
double Y_to_sigma(std::vector<double> YY);

// Granger causality function
std::vector<std::vector<double>> Granger_causality(const std::vector<std::vector<double>>& sigma_MVAR, 
                                                   const std::vector<std::vector<double>>& YY) {
    size_t len_sigma_MVAR = sigma_MVAR.size();
    std::vector<std::vector<double>> GC(len_sigma_MVAR, std::vector<double>(len_sigma_MVAR, 0));

    for (size_t i = 0; i < len_sigma_MVAR; ++i) {
        for (size_t j = 0; j < len_sigma_MVAR; ++j) {
            double sigmaj = Y_to_sigma(YY[j]);
            double sigmaij = Y_to_sigma({YY[i], YY[j]});  // This is a simplification

            // Calculating GC values
            GC[i][j] = log(sigmaj / sigmaij);  // Assuming this calculation is correct

            // Handling NaN and threshold
            if (isnan(GC[i][j]) || abs(GC[i][j]) < 0.05) {
                GC[i][j] = 0;
            }
        }
    }

    return GC;
}

// Main function or further implementation needed
