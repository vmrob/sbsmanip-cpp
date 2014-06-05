#pragma once

#include <memory>

#ifndef HAS_MAKE_UNIQUE
#define HAS_MAKE_UNIQUE

namespace std {

	template <typename T, typename ... Args>
	std::unique_ptr<T> make_unique(Args&& ... args) {
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
	
} // namespace std

#endif