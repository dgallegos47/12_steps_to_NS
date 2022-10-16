#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <cstring>

void print(const std::vector<double> &v)
{
	for (auto i: v)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void set_hat_ic(std::vector<double> &u, const double &dx)
{
	for (size_t i = 0; i < u.size(); i++)
	{
		if (i >= 0.5/dx && i <= 1/dx + 1)
		{
			u[i] = 2.0;
		}
	}
}

void write_vector(const std::vector<double> &v)
{
	std::ofstream outFile("res.txt", std::ios_base::app);

	for (const auto &e : v)
	{
		outFile << e << "\t";
	}
	outFile << std::endl;
	outFile.close();
}

int main(int argc, char **argv)
{
	if (argc == 2 && strcmp(argv[1], "--help") == 0)
	{
		std::cout << "Linear convection solver over [0, 2]\n";
		std::cout << "With hat-function initial condtiison.\n";
		std::cout << "Usage: linear_convection nx nt dt c\n";
		std::cout << "Where:\n";
		std::cout << "\t nx: number of x grid points (41)\n";
		std::cout << "\t nt: number of timesteps (25)\n";
		std::cout << "\t dt: timestep (0.025)\n";
		std::cout << "\t c: wave speed (1)\n" << std::endl;
			
		return 0;
	}

	if (argc != 5)
	{
		std::cout << "Incorrect number of arguments\n";
		std::cout << "Usage: linear_convection nx nt dt c\n";
	
		return -1;
	}	
	
	int nx {std::stoi(argv[1])};
	int nt {std::stoi(argv[2])};
	double dt {std::stod(argv[3])};
	double c {std::stod(argv[4])};

	double dx {2/(static_cast<double>(nx) - 1)};
	std::vector<double> u(nx, 1);

	set_hat_ic(u, dx);

	std::cout << "Linear convection solver" << "\n";

	int status {remove("res.txt")};

	if (status != 0)
		std::cout << "Result file could not be overwritten\n";

	write_vector(u);

	auto start = std::chrono::high_resolution_clock::now();

	for (int n = 0; n < nt; n++)
	{
		std::vector<double> un(u.begin(), u.end());

		for (int i = 1; i < nx; i++)
		{
			u[i] = u[i] - c * (dt/dx) * (un[i] - un[i - 1]);
			/* print(u); */
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto diff_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

	std::cout << "Calcuation time: " << diff_ns.count() << " ns" << "\n";
	std::cout << "Writing final u(x) to res.txt" << std::endl;

	write_vector(u);

	return 0;
}
