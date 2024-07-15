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
	for(int i = 0; i < 80; ++i)
		logic::increase_counter();
	ensure(globals::counter, 80);
	logic::reset_counter();
	ensure(globals::counter, 0);
	return EXIT_SUCCESS;
}
