#include "Pizza.h"
#include "MaxAlgo.h"

#include <iostream>
#include <fstream>

int main()
{
	using namespace std;
	Pizza<IngradientType> pizza;

	ifstream input("data.txt");
	input >> pizza;

	auto tomatos = pizza.ingradient_table(IngradientType::Tomato);

	auto sat = SAT(tomatos);

	return 0;
}