#pragma once
#include <vector>
#include <complex>

std::vector<double> generate_sine(double freq, double sample_rate, double duration);
std::vector<double> generate_cosine(double freq, double sample_rate, double duration);
std::vector<double> generate_square(double freq, double sample_rate, double duration);
std::vector<double> generate_sawtooth(double freq, double sample_rate, double duration);
std::vector<std::complex<double>> compute_dft(const std::vector<double>& input);
std::vector<double> compute_idft(const std::vector<std::complex<double>>& input);
std::vector<double> low_pass_filter(const std::vector<double>& input, int window_size);
std::vector<double> compute_derivative(const std::vector<double>& signal, double sample_rate);

