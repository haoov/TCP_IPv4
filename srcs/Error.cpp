#include "Error.hpp"

IRC::Error::Error(std::string what) : m_what("Error: " + what) {
	if (errno)
		m_cause = ::strerror(errno);
}

IRC::Error::~Error() _NOEXCEPT {}

const char *IRC::Error::what() const _NOEXCEPT {
	return m_what.c_str();
}

const std::string &IRC::Error::cause() const _NOEXCEPT {
	return m_cause;
}