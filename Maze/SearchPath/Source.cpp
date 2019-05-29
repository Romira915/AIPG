#include "List.h"
#include <iostream>

int main() {

	List list;
	initList(&list);

	Cell* c = createCell();
	c->x = 0;
	c->y = 0;
	c->value = 100;
	c->id = 12222;
	addBottom(&list, c);

	std::cout << takeBottom(&list)->x << '\n';
}