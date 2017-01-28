#pragma once
#include <utility>

namespace mystl
{
	template <typename T>
	void swap(T &x, T &y)
	{
		T temp(std::move(x));

		x = std::move(y);
		y = std::move(temp);
	};
};