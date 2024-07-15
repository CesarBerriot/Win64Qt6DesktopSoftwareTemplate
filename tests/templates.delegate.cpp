//
// Created by César B. on 7/15/2024.
//

#include "templates/delegate.hpp"

class foo
{	public:
		void bar(int & value)
		{	value += 2;
		}
};

int main()
{	int value = 0;
	templates::delegate<void(int &)> delegate;
	delegate.bind([](int & value) { value += 1; });
	foo instance;
	delegate.bind(&instance, &foo::bar);
	delegate(value);
	bool success = value == 3;
	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
