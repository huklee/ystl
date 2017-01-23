#pragma once

namespace mystl
{
	template <class Iterator, typename Distance>
	void advance(Iterator &it, Distance distance)
	{
		if (distance > 0)
			while (distance != 0)
			{
				++it;
				distance--;
			}
		else
			while (distance != 0)
			{
				--it;
				distance++;
			}
	};
};