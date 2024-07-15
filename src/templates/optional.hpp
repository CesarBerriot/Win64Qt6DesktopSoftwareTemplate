//
// Created by César B. on 7/15/2024.
//

#pragma once

#include <cassert>

namespace templates
{
	/// based on unreal engine's TOptional
	template<typename _type>
	class optional
	{	private:
			_type * value_ptr = nullptr;
		public:
			optional() = default;
			optional(_type value) { set(value); }
			bool is_set() { return value_ptr; }
			void reset()
			{	if(value_ptr)
					delete value_ptr;
				value_ptr = nullptr;
			}
			_type get()
			{	assert(value_ptr);
				return *value_ptr;
			}
			void set(_type new_value)
			{	if(!value_ptr)
					value_ptr = new _type(new_value);
				else
					*value_ptr = new_value;
			}
			void operator=(_type new_value) { set(new_value); }
			operator _type() { return get(); }
	};
}