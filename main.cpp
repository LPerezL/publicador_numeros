#include <iostream>
#include <cmath>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>

double get_env_double(const char* env_var, double default_value) {
    const char* val = std::getenv(env_var);
    if (val != nullptr) {
        try {
            return std::stod(val);
        } catch (...) {
            std::cerr << "Advertencia: Valor invalido para " << env_var 
                      << ". Usando valor por defecto: " << default_value << std::endl;
        }
    }
    return default_value;
}

int main() {
    const double amplitude    = get_env_double("WAVE_AMPLITUDE", 10.0);
    const double frequency    = get_env_double("WAVE_FREQUENCY", 1.0);
    const double phase        = get_env_double("WAVE_PHASE", 0.0);
    
    const double noise_mean   = get_env_double("NOISE_MEAN", 0.0);
    const double noise_stddev = get_env_double("NOISE_STDDEV", 1.5);

    const double sample_rate  = get_env_double("SAMPLE_RATE", 50.0);
    const double dt           = 1.0 / sample_rate;
    const auto step_delay     = std::chrono::milliseconds(static_cast<int>(dt * 1000));

    std::cerr << "--- Configuración de la Señal ---" << std::endl;
    std::cerr << "Amplitud: " << amplitude << " | Frecuencia: " << frequency << " Hz" << std::endl;
    std::cerr << "Ruido (media/stddev): " << noise_mean << " / " << noise_stddev << std::endl;
    std::cerr << "Tasa de muestreo: " << sample_rate << " Hz" << std::endl;
    std::cerr << "---------------------------------" << std::endl;

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