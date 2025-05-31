#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <matplot/matplot.h>
#include "generators.hpp"

using namespace std;
using namespace matplot;

vector<double> global_signal;
string global_type = "sin";
double global_freq = 1.0;
double global_sample_rate = 100.0;
double global_duration = 1.0;

void get_signal_input() {
    cout << "Typ sygnalu (sin/cos/square/saw): ";
    cin >> global_type;
    cout << "Czestotliwosc [Hz]: ";
    cin >> global_freq;
    cout << "Czestotliwosc probkowania [Hz]: ";
    cin >> global_sample_rate;
    cout << "Czas trwania [s]: ";
    cin >> global_duration;

    if (global_type == "sin")
        global_signal = generate_sine(global_freq, global_sample_rate, global_duration);
    else if (global_type == "cos")
        global_signal = generate_cosine(global_freq, global_sample_rate, global_duration);
    else if (global_type == "square")
        global_signal = generate_square(global_freq, global_sample_rate, global_duration);
    else if (global_type == "saw")
        global_signal = generate_sawtooth(global_freq, global_sample_rate, global_duration);
    else {
        cout << "Nieznany typ. Uzycie sinusa jako domyslna funkcja.\n";
        global_signal = generate_sine(global_freq, global_sample_rate, global_duration);
    }
}

void draw_signal() {
    figure(true);
    vector<double> x(global_signal.size());
    for (size_t i = 0; i < x.size(); ++i)
        x[i] = i / global_sample_rate;
    plot(x, global_signal);
    title("Sygnał " + global_type);
    xlabel("Czas [s]");
    ylabel("Amplituda");
    show();
}

void filter_signal() {
    figure(true);
    auto filtered = low_pass_filter(global_signal, 5);
    vector<double> x(global_signal.size());
    for (size_t i = 0; i < x.size(); ++i)
        x[i] = i / global_sample_rate;
    plot(x, global_signal, "b");
    hold(on);
    plot(x, filtered, "r");
    legend({ "Zakłócony", "Po filtracji" });
    title("Filtracja 1D");
    xlabel("Czas [s]");
    ylabel("Amplituda");
    show();
}

void filter_2d() {
    int rows = 200, cols = global_signal.size();
    vector<vector<double>> matrix(rows, global_signal);
    vector<vector<double>> filtered(rows, vector<double>(cols, 0.0));

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            double sum = 0.0;
            for (int di = -1; di <= 1; ++di)
                for (int dj = -1; dj <= 1; ++dj)
                    sum += matrix[i + di][j + dj];
            filtered[i][j] = sum / 9.0;
        }
    }

    matplot::imagesc(filtered);
    matplot::colorbar();
    matplot::title("Filtracja 2D na sygnale");
    matplot::show();
}


void dft_and_idft() {
    auto dft = compute_dft(global_signal);
    auto idft = compute_idft(dft);

    vector<double> x(global_signal.size());
    for (size_t i = 0; i < x.size(); ++i)
        x[i] = i / global_sample_rate;

    vector<double> magnitude(dft.size());
    vector<double> freq(dft.size());
    for (size_t i = 0; i < dft.size(); ++i) {
        magnitude[i] = abs(dft[i]);
        freq[i] = i * global_sample_rate / dft.size();
    }

    figure();
    subplot(3, 1, 0);
    plot(x, global_signal);
    title("Oryginalny sygnał");
    xlabel("Czas [s]");
    ylabel("Amplituda");

    subplot(3, 1, 1);
    plot(freq, magnitude);
    title("Widmo DFT");
    xlabel("Częstotliwość [Hz]");
    ylabel("Amplituda");

    subplot(3, 1, 2);
    plot(x, idft);
    title("Sygnał po IDFT");
    xlabel("Czas [s]");
    ylabel("Amplituda");

    show();
}


void draw_derivative() {
    figure(true);
    auto derivative = compute_derivative(global_signal, global_sample_rate);
    vector<double> x(derivative.size());
    for (size_t i = 0; i < x.size(); ++i)
        x[i] = i / global_sample_rate;

    plot(x, derivative);
    title("Pochodna sygnału " + global_type);
    xlabel("Czas [s]");
    ylabel("dA/dt");
    show();
}

int main() {
    get_signal_input();
    while (true) {
        cout << "\n==============================\n";
        cout << "PROJEKT 3 - TECHNIKI PROGRAMOWANIA\n";
        cout << "==============================\n";
        cout << "MENU:\n";
        cout << "1. Rysowanie sygnalu\n";
        cout << "2. Filtracja 1D\n";
        cout << "3. Filtracja 2D\n";
        cout << "4. DFT i IDFT\n";
        cout << "5. Pochodna sygnalu\n";
        cout << "6. Zmiana sygnalu\n";
        cout << "7. Zakoncz dzialanie programu\n";
        cout << "Wybor: ";

        int wybor;
        cin >> wybor;

        switch (wybor) {
        case 1: draw_signal(); break;
        case 2: filter_signal(); break;
        case 3: filter_2d(); break;
        case 4: dft_and_idft(); break;
        case 5: draw_derivative(); break;
        case 6: get_signal_input(); break;
        case 7: cout << "Zamykanie programu...\n"; return 0;
        default: cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n"; break;
        }
    }
}
