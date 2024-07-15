//
// Created by César B. on 7/15/2024.
//

#include "api/api.hpp"
#include <templates/trackable_value.hpp>

int main()
{	int tracks_count = 0;

	templates::trackable_value<int> value = 4;
	ensure(value, 4);

	value.on_value_changed.bind([&tracks_count](int) { ++tracks_count; });

	value = 12;
	ensure(value, 12);
	ensure(tracks_count, 1);

	value = 1762;
	ensure(value, 1762);
	ensure(tracks_count, 2);

	value = -46;
	ensure(value, -46);
	ensure(tracks_count, 3);

	return EXIT_SUCCESS;
}
