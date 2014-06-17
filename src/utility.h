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

namespace sbsmanip {

inline std::string FormatImpl(boost::format& formatter) {
    return formatter.str();
}

template<typename Head, typename... Tail>
std::string FormatImpl(boost::format& formatter, Head&& h, Tail&& ... args) {
    formatter % std::forward<Head>(h);
    return FormatImpl(formatter, std::forward<Tail>(args)...);
}

/**
* Variadic wrapper for boost.format.
*/
template<typename... Args>
std::string Format(std::string fmt, Args&& ... args) {
	boost::format message(fmt);
	try {
		return FormatImpl(message, std::forward<Args>(args)...);
	} catch (...) {}
	return std::string("[invalid format]: ") + fmt;
}

} // namespace sbsmanip