// This file demos using the matrix class to solve the heat equation in a periodic domain

#include "Matrix.h"

#include<iostream>
#include<vector>
#include<numbers>
#include<cmath>

namespace math = basic_math;

template<typename ... Types>
void printline(Types&& ... params);

class HeatEq {
private:
	// type to store times and solutions
	using solpair = std::pair < double, math::matrix<> >;

	double xlow, xup;
	double tend;
	size_t Nx, Nt;
	math::matrix<> FwdEul, ImpEul; // explicit and implicit operators
	std::vector<solpair> sol;
	double dt, dx, wt;

public:
	/**
	Constructor for Heat Equation solver
	@param _xlow the x lower bound
	@param _xup the x upper bound 
	@param _tend the end time
	@param _Nx the x meshing parameter
	@param _Nt the t meshing parameter
	@param ic the initial conditions
	@param _wt the weight for numerical time stepping: 0 = Euler, 1 = implicit Euler,
	0.5 (default) gives Crank-Nicolson
	*/
	HeatEq(double _xlow, double _xup, double _tend, size_t _Nx,
		size_t _Nt, math::matrix<> ic, double _wt = 0.5);

	/**
	Solves the pde u_t = u_{xx} on the domain with u=0 on x-boundary,
	returns a vector of pairings between time and u
	*/
	[[nodiscard]] const std::vector<solpair>& solve();
};

int main() {

	// set up domain: [0,1]
	// time [0, 0.25]
	const double low = 0, up = 1;
	const double tend = 0.25;
	const size_t Nx = 20;
	const size_t Nt = 50;

	const double pi = std::numbers::pi;

	double (*sine)(double) = std::sin; // store sin function pointer

	// linear space x: Nx+1 points on [0,1]
	auto x = math::linspace(0., 1., Nx + 1);
	// initial condition, u = 1 + sin(2 pi x)
	auto ic = 1 + sine % (2 * pi * x);
	// remove the endpoint since periodic
	ic = ic.select(0, ic.size(0) - 1, 1, 0, ic.size(1), 1);
	const double dx = x(1, 0) - x(0, 0);	

	printline("initial condition:\n", ic);

	// setup and solve
	// can add extra weight argument on [0,1] interval (default is =0.5 for Crank-Nicolson, 0 gives Euler, 1 gives implicit Euler)
	HeatEq solver{ low, up, tend, Nx, Nt, ic };
	auto sol = solver.solve();

	// analytic solution
	// u = 1 + exp(-4 pi^2 t)*sin(2 pi x)
	auto u_an = [=](double t, double x) {
		return 1 + std::exp(-4 * pi * pi * t / std::pow(up-low,2))
			* std::sin(2 * pi * x / (up - low));
	};

	// print approximate and exact at different t's
	for (auto& [t,u] : sol) {
		printline("t=", t);
		printline("uapprox=", u.T());
		auto u_ex = apply_to([&](const auto& x) {
			return u_an(t, x); }, x);
		printline("uex=", u_ex.T());		
	}	

}

template<typename ... Types>
void printline(Types&& ... params) {
	(std::cout << ... << std::forward<Types>(params));
	std::cout << '\n';
}

HeatEq::HeatEq(double _xlow, double _xup, double _tend, size_t _Nx,
	size_t _Nt, math::matrix<> ic, double _wt) :
	xlow(_xlow), xup(_xup), tend(_tend), Nx(_Nx), Nt(_Nt), FwdEul(),
	ImpEul(), sol(), dt(tend / Nt), dx((xup - xlow) / Nx), wt(_wt) {

	math::matrix D2(Nx, Nx);

	for (size_t i = 0, rows = D2.size(0); i < rows; ++i) {
		if (i == 0) [[unlikely]] {
			D2(i, 0) = -2;
			D2(i, 1) = 1;
			D2(i, D2.size(1) - 1) = 1;
		}
		else if (i == rows - 1) [[unlikely]] {
			D2(i, i) = -2;
			D2(i, i - 1) = 1;
			D2(i, 0) = 1;
		}
		else [[likely]] {
			D2(i, i + 1) = 1;
			D2(i, i) = -2;
			D2(i, i - 1) = 1;
		}
	}

	D2 *= 1 / (dx * dx);

	FwdEul = math::make_identity<double>(Nx) + (1 - wt) * dt * D2;

	ImpEul = math::make_identity<double>(Nx) - wt * dt * D2;
	ImpEul = inverse(ImpEul);

	sol.emplace_back(0., std::move(ic));
}

auto HeatEq::solve() -> const std::vector<solpair>& {
	double t = 0;

	for (size_t i = 0; i < Nt; ++i) {
		auto& curr = sol.back().second;
		auto next = ImpEul * FwdEul * curr;
		t += dt;
		sol.emplace_back(t, std::move(next));
	}
	return sol;
}
