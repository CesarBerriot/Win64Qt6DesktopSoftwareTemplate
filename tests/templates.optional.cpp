//
// Created by César B. on 7/15/2024.
//

#include "api/api.hpp"
#include <templates/optional.hpp>

class foo
{	public:
	void bar(int & value)
	{	value += 2;
	}
};

int main()
{	templates::optional<int> value;
	ensure(value.is_set(), false);

	templates::optional<int> other_value = 7;
	ensure(other_value.is_set(), true);
	ensure(other_value, 7);

	value = 4;
	ensure(value.is_set(), true);
	ensure(value, 4);

	value.reset();
	ensure(value.is_set(), false);

	return EXIT_SUCCESS;
}
