#include "generators.hpp"
#include <cmath>
#include <vector>
#include <complex>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

std::vector<double> generate_sine(double freq, double sample_rate, double duration) {
    std::vector<double> signal;
    int samples = static_cast<int>(sample_rate * duration);
    for (int i = 0; i < samples; ++i) {
        double t = i / sample_rate;
        signal.push_back(sin(2 * M_PI * freq * t));
    }
    return signal;
}

std::vector<double> generate_cosine(double freq, double sample_rate, double duration) {
    std::vector<double> signal;
    int samples = static_cast<int>(sample_rate * duration);
    for (int i = 0; i < samples; ++i) {
        double t = i / sample_rate;
        signal.push_back(cos(2 * M_PI * freq * t));
    }
    return signal;
}

std::vector<double> generate_square(double freq, double sample_rate, double duration) {
    std::vector<double> signal;
    int samples = static_cast<int>(sample_rate * duration);
    for (int i = 0; i < samples; ++i) {
        double t = i / sample_rate;
        double value = sin(2 * M_PI * freq * t);
        signal.push_back(value >= 0 ? 1.0 : -1.0);
    }
    return signal;
}

std::vector<double> generate_sawtooth(double freq, double sample_rate, double duration) {
    std::vector<double> signal;
    int samples = static_cast<int>(sample_rate * duration);
    for (int i = 0; i < samples; ++i) {
        double t = i / sample_rate;
        signal.push_back(2.0 * (t * freq - floor(t * freq + 0.5)));
    }
    return signal;
}

std::vector<std::complex<double>> compute_dft(const std::vector<double>& input) {
    int N = input.size();
    std::vector<std::complex<double>> output(N);

    for (int k = 0; k < N; ++k) {
        std::complex<double> sum = 0;
        for (int n = 0; n < N; ++n) {
            double angle = -2 * M_PI * k * n / N;
            sum += input[n] * std::exp(std::complex<double>(0, angle));
        }
        output[k] = sum;
    }
    return output;
}

std::vector<double> compute_idft(const std::vector<std::complex<double>>& input) {
    int N = input.size();
    std::vector<double> output(N);

    for (int n = 0; n < N; ++n) {
        std::complex<double> sum = 0;
        for (int k = 0; k < N; ++k) {
            double angle = 2 * M_PI * k * n / N;
            sum += input[k] * std::exp(std::complex<double>(0, angle));
        }
        output[n] = sum.real() / N;
    }
    return output;
}
std::vector<double> low_pass_filter(const std::vector<double>& input, int window_size) {
    std::vector<double> output;
    int N = input.size();
    output.reserve(N);

    for (int i = 0; i < N; ++i) {
        double sum = 0.0;
        int count = 0;
        for (int j = i - window_size / 2; j <= i + window_size / 2; ++j) {
            if (j >= 0 && j < N) {
                sum += input[j];
                count++;
            }
        }
        output.push_back(sum / count);
    }

    return output;
}

std::vector<double> compute_derivative(const std::vector<double>& signal, double sample_rate) {
    std::vector<double> derivative(signal.size(), 0.0);
    for (size_t i = 1; i < signal.size(); ++i) {
        derivative[i] = (signal[i] - signal[i - 1]) * sample_rate;
    }
    return derivative;
}
