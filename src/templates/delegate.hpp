//
// Created by César B. on 3/21/2024.
//

#pragma once

#include <functional>
#include <map>
#include <assert.h>

namespace templates
{
	template<typename>
	class delegate { public: delegate() { assert(!"the given type was not a function pointer"); } };
	template<typename _ret, typename... _args>
	class delegate<_ret(_args...)>
	{	public:
			typedef _ret(_func)(_args...);
			typedef int bond_handle;
		private:
			std::map<bond_handle, std::function<_func>> bound_functions;
			bond_handle last_callback_handle = -1;
		public:
			bond_handle bind(std::function<_func> func) { return internal_bind(func); }
			template<typename _class>
			bond_handle bind(_class * object, _ret(_class::*method)(_args...)) { return internal_bind([=](_args... args) { return (object->*method)(args...); }); }
			void broadcast(_args... args) { for(auto pair : bound_functions) pair.second(args...); }
			void unbind(bond_handle callback_handle) { bound_functions.erase(callback_handle); }
			void operator()(_args... args) { broadcast(args...); }
		private:
			bond_handle internal_bind(std::function<_func> func)
			{	++last_callback_handle;
				bound_functions[last_callback_handle] = func;
				return last_callback_handle;
			}
	};
}
