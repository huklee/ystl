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

	template <typename T>
	struct greater
	{
		auto operator()(const T &x, const T &y) const -> bool
		{
			return x > y;
		};
	};

	template <typename T>
	auto min(const T &x, const T &y) -> const T&
	{
		return min(x, y, less<T>());
	};

	template <typename T, typename Compare>
	auto min(const T &x, const T &y, Compare compare) -> const T&
	{
		return compare(x, y) ? x : y;
	};

	template <typename T>
	auto max(const T &x, const T &y) -> const T&
	{
		return max(x, y, greater<T>());
	};

	template <typename T, typename Compare>
	auto max(const T &x, const T &y, Compare compare) -> const T&
	{
		return compare(x, y) ? x : y;
	};
};