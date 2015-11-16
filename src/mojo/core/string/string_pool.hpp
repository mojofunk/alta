#ifndef MOJO_CORE_STRING_POOL_H
#define MOJO_CORE_STRING_POOL_H

/**
 * A template parameter for the container type could be added to test
 * performance of set vs unordered_set
 */
template <class StringType>
class StringPool {
public:
	using InternedString = const char*;

public:
	// SFINAE may not work in VS2015?
	// C++17 required for is_constructible?
	template <typename... Args>
	typename std::enable_if<std::is_constructible<std::string, Args...>::value,
	                        InternedString>::type
	emplace_string(Args&&... args)
	{
		return m_interned.emplace(std::forward<Args>(args)...).first->c_str();
	}

private:
	std::unordered_set<StringType> m_interned;
};

#endif // MOJO_CORE_STRING_POOL_H
