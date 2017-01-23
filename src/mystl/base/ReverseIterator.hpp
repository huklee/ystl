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
	template <class Iterator>
	class ReverseIterator
	{
		template <typename Iterator> friend class ConstIterator;

	public:
		typedef typename Iterator::value_type value_type;

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

		auto operator*() -> typename Iterator::value_type&
		{
			return this->base_.operator*();
		};
		auto operator*() const -> const typename Iterator::value_type&
		{
			return this->base_.operator*();
		};

		auto operator->() -> typename Iterator::value_type*
		{
			return this->base_.operator->();
		};
		auto operator->() const -> const typename Iterator::value_type*
		{
			return this->base_.operator->();
		};

	public:
		/* ----------------------------------------------------------
			MOVERS
		---------------------------------------------------------- */
		auto operator--() -> ReverseIterator<Iterator>&
		{
			++this->base_;
			return *this;
		};

		auto operator++() -> ReverseIterator<Iterator>&
		{
			--this->base_;
			return *this;
		};

	public:
		/* ----------------------------------------------------------
			COMPARES
		---------------------------------------------------------- */
		auto operator==(const ReverseIterator<Iterator> &obj) const -> bool
		{
			return this->base_ == obj.base_;
		};
		auto operator==(const ConstIterator<ReverseIterator<Iterator>> &obj) const -> bool
		{
			return this->base_ == obj._Base();
		};

		auto operator!=(const ReverseIterator<Iterator> &obj) const -> bool
		{
			return !this->operator==(obj);
		};
		auto operator!=(const ConstIterator<ReverseIterator<Iterator>> &obj) const -> bool
		{
			return !this->operator==(obj);
		};
	};
};
};