#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>

const unsigned NUM_PARTICLES = 25;
const double MAX_TIME = 1000;
const double DT = 1;

const double EPSILON = 0.001;

const double ETA = 0.05;
const double TAU = 1.0;

const unsigned K = 3;
const double C = 1.0;

const double GAMMA[] = { 0.04, 0.1, 0.5 };

// seed random number based on time
std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<double> init_pos_dist(0.0, 1.0);
std::normal_distribution<double> force_dist(0.0, TAU);

struct Particle {
  Particle() : r(0), v(0), a(0) { }
  double r;
  double v;
  double a;

  static constexpr double Mass = 1.0;
};

Particle P[NUM_PARTICLES];

double R[K];

void GenR() {
  for (unsigned k = 0; k < K; ++k)
    R[k] = force_dist(gen);
}

double g(double x) {
  return C * exp(-(x*x));
}

double F(double r) {
  double f = 0.0;
  for (unsigned k = 0; k < K; ++k) {
    f += g(r - k*EPSILON) * R[k];
  }
  return f;
}

void Init() {
  for (Particle& p : P)
    p.r = init_pos_dist(gen); //0.0;
}

void Run(double gamma) {
  std::cout << "running gamma: " << gamma << "\n";
  std::ostringstream suffix;
  suffix << ".G" << gamma << ".E" << EPSILON << ".P" << NUM_PARTICLES;
  std::ofstream positions(("out/pos" + suffix.str()).c_str());
  std::ofstream density(("out/dens" + suffix.str()).c_str());

  unsigned i = 0;
  double t = 0.0;
  while (t < MAX_TIME) {
    positions << ++i << " ";
    density << ++i << " ";
    double min_pos = std::numeric_limits<double>::max();
    double max_pos = std::numeric_limits<double>::min();

    // Build this frame's random number table.
    GenR();

    // TODO: omp if necessary
    for (Particle& p : P) {
      // Velocity verlet
      const double half_v = p.v + p.a*DT/2;
      const double force = EPSILON*F(p.r) - gamma*half_v*Particle::Mass;
      p.r += half_v*DT;
      p.a = force / Particle::Mass;
      p.v = half_v + p.a*DT/2;

      positions << p.r << " ";

      min_pos = std::min(min_pos, p.r);
      max_pos = std::max(max_pos, p.r);
    }
    t += DT;
    positions << "\n";
    density << (NUM_PARTICLES * Particle::Mass) / (max_pos - min_pos) << "\n";
  }
}

int main() {
  for (const double& g : GAMMA) {
    Init();
    Run(g);
  }
  std::cout << "Done.\n";
  return 0;
}
