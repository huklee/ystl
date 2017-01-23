#pragma once

#include <functional>

namespace mystl
{
	template <typename T>
	struct less
	{
		auto operator()(const T &x, const T &y) const -> bool
		{
			return x < y;
		};
	};

	template <typename T>
	struct equal_to
	{
		auto operator()(const T &x, const T &y) const -> bool
		{
			return x == y;
		};
	};
};