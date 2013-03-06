#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include "Utils/Conductors.h"
#include <ctime>

using namespace std;

int main() {

	int N = 11;   // number of eq.p. lines
	int n = 200;
	int m = 200;

	double Emax=100;
	double Emin=-100;

	Grid first_grid(n,m);

	first_grid.set_flow(Emax, Emin);
	Conductors conductors(n,m,50.,-50.);
	conductors.new_conductor(150,130,40,0,circle);
	conductors.new_conductor(50,70,40,0,circle);
	conductors.set_precision(0);
	conductors.set_maxit(10000);
	Grid sol = conductors.get_solution(FD);


//	Finite_Difference fd (first_grid);
//	fd.set_precision(0.00001);
//	fd.set_maxit(10000);
//	Grid sol = fd.get_solution();

	sol.print_points_to("results.dat");
	Gnuplot gp(sol);
	sol.equip_values(N,n,m,Emax,1,1);
	sol.print_contours_to("eq_lines.dat", N);
	sol.print_figure_to("figure.dat", 2); // 2 - the number of figures


	gp.add_command("set term jpeg");
	gp.add_command("set output 'test.jpg'");
	gp.add_command("set palette defined");
	gp.add_command("plot 'results.dat' with image, 'eq_lines.dat' with lines ls -1, 'figure.dat' with filledcurve ls -3"); // white = ls -3; black = ls -1; red = ls 1; green = 2; blue = ls 3; violet = ls 4;
	gp.sendString();

	return 0;

	}
