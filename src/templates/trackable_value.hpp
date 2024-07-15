//
// Created by César B. on 7/15/2024.
//

#pragma once

#include "delegate.hpp"

namespace templates
{	template<typename _type>
	class trackable_value
	{	typedef delegate<void(_type const &)> on_value_changed_t;
		public:
			on_value_changed_t on_value_changed;
		private:
			_type value;
		public:
			trackable_value() = default;
			trackable_value(_type value) : value(value) {}
			_type get() { return value; }
			void set(_type new_value)
			{	value = new_value;
				on_value_changed(value);
			}
			operator _type() { return get(); }
			void operator=(_type new_value) { set(new_value); }
	};
}
