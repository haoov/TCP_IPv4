#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <exception>

# ifndef _NOEXCEPT
# define _NOEXCEPT _GLIBCXX_NOTHROW
# endif //_NOEXCEPT

//states
#define UP		1
#define RUNNING	2
#define DOWN	3

//socket type
#define ACTIVE	1
#define PASSIVE	2

#endif //DEFINES_HPP