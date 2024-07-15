//
// Created by César B. on 7/15/2024.
//

#include "api/api.hpp"
#include "globals/globals.hpp"
#include "logic/logic.hpp"
#include "ui/ui.hpp"

int main()
{	ui::init();
	ensure(globals::counter, 0);
	logic::increase_counter();
	ensure(globals::counter, 1);
	for(int i = 0; i < 80; ++i)
		logic::increase_counter();
	ensure(globals::counter, 81);
	return EXIT_SUCCESS;
}
