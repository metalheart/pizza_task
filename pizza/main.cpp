#include "Pizza.h"

#include <iostream>
#include <fstream>

int main()
{
	using namespace std;
	Pizza<IngradientType> pizza;

	ifstream input("data.txt");
	input >> pizza;

	auto tomatos = pizza.ingradient_table(IngradientType::Tomato);

	return 0;
}