#pragma once

#include <mystl/base/ConstIterator.hpp>

namespace mystl
{
namespace base
{
	/**
	 * Reverse iterator.
	 * 
	 * @author Jeongho Nam <http://samchon.org>
	 */
	template <class Iterator, typename T>
	class ReverseIterator
	{
		template <typename Iterator> friend class ConstIterator;

	public:
		typedef T value_type;

	private:
		/**
		 * @hidden
		 */
		Iterator base_;

	public:
		/* ----------------------------------------------------------
			CONSTRUCTORS
		---------------------------------------------------------- */
		/**
		 * Initializer Constructor.
		 */
		ReverseIterator(const Iterator &base)
		{
			this->base_ = base;
			--this->base_;
		};

	private:
		/**
		* @hidden
		*/
		ReverseIterator()
		{
		};

	public:
		/* ----------------------------------------------------------
			ACCESSORS
		---------------------------------------------------------- */
		auto base() const -> Iterator
		{
			Iterator it = this->base_;
			it++;

			return it;
		};

		auto operator*() -> T&
		{
			return this->base_.operator*();
		};
		auto operator*() const -> const T&
		{
			return this->base_.operator*();
		};

		auto operator->() -> T*
		{
			return this->base_.operator->();
		};
		auto operator->() const -> const T*
		{
			return this->base_.operator->();
		};

	public:
		/* ----------------------------------------------------------
			MOVERS
		---------------------------------------------------------- */
		auto operator--() -> ReverseIterator<Iterator, T>&
		{
			++this->base_;
			return *this;
		};
		auto operator--(int) -> ReverseIterator<Iterator, T>
		{
			ReverseIterator<Iterator, T> it = *this;
			--(*this);

			return it;
		};
		auto operator-(size_t n) -> ReverseIterator<Iterator, T>
		{
			ConstIterator<Iterator> it = *this;
			while (n-- != 0)
				--it;

			return it;
		};

		auto operator++() -> ReverseIterator<Iterator, T>&
		{
			--this->base_;
			return *this;
		};
		auto operator++(int) -> ReverseIterator<Iterator, T>
		{
			ReverseIterator<Iterator, T> it = *this;
			++(*this);

			return it;
		};
		auto operator+(size_t n) -> ReverseIterator<Iterator, T>
		{
			ConstIterator<Iterator> it = *this;
			while (n-- != 0)
				++it;

			return it;
		};

	public:
		/* ----------------------------------------------------------
			COMPARES
		---------------------------------------------------------- */
		auto operator==(const ReverseIterator<Iterator, T> &obj) const -> bool
		{
			return this->base_ == obj.base_;
		};
		auto operator==(const ConstIterator<ReverseIterator<Iterator, T>> &obj) const -> bool
		{
			return this->base_ == obj._Base();
		};

		auto operator!=(const ReverseIterator<Iterator, T> &obj) const -> bool
		{
			return !this->operator==(obj);
		};
		auto operator!=(const ConstIterator<ReverseIterator<Iterator, T>> &obj) const -> bool
		{
			return !this->operator==(obj);
		};
	};
};
};