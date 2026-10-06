#include <iostream>
#include <cmath>
#include <random>
#include <thread>
#include <chrono>

int main() {
    // Parámetros de la onda
    const double amplitude = 10.0;
    const double frequency = 1.0;
    const double phase = 0.0;
    
    // Parámetros del ruido blanco
    const double noise_mean = 0.0;
    const double noise_stddev = 1.5;

    // Frecuencia de muestreo (50 Hz -> 20 ms por muestra)
    const double sample_rate = 50.0;
    const double dt = 1.0 / sample_rate;
    const auto step_delay = std::chrono::milliseconds(static_cast<int>(dt * 1000));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> noise_dist(noise_mean, noise_stddev);

    double t = 0.0;
    const double pi = std::acos(-1.0);

    while (true) {
        double signal = amplitude * std::sin(2.0 * pi * frequency * t + phase);
        double noise = noise_dist(gen);
        double sample = signal + noise;

        std::cout << sample << std::endl;

        t += dt;
        std::this_thread::sleep_for(step_delay);
    }

    return 0;
}