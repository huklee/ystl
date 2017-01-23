#pragma once

#include <mystl/base/ConstIterator.hpp>
#include <mystl/base/ReverseIterator.hpp>

namespace mystl
{
namespace base
{
	template <typename T>
	class VectorIterator
	{
	public:
		typedef T value_type;

	private:
		T *ptr_;

	public:
		/* ----------------------------------------------------------
			CONSTRUCTORS
		---------------------------------------------------------- */
		/**
		 * Initializer Constructor.
		 */
		VectorIterator(T *ptr)
		{
			this->ptr_ = ptr;
		};

	public:
		/* ----------------------------------------------------------
			ACCESSORS
		---------------------------------------------------------- */
		auto operator*() -> T&
		{
			return *this->ptr_;
		};
		auto operator*() const -> const T&
		{
			return *this->ptr_;
		};

		auto operator->() -> T*
		{
			return this->ptr_;
		};
		auto operator->() const -> const T*
		{
			return this->ptr_;
		};

	public:
		/* ----------------------------------------------------------
			COMPARES
		---------------------------------------------------------- */
		auto operator==(const VectorIterator<T> &obj) const -> bool
		{
			return this->ptr_ == obj.ptr_;
		};
		auto operator==(const ConstIterator<VectorIterator<T>> &obj) const -> bool
		{
			return this->ptr_ == obj._Base().ptr;
		};

		auto operator!=(const VectorIterator<T> &obj) const -> bool
		{
			return !this->operator==(obj);
		};
		auto operator!=(const ConstIterator<VectorIterator<T>> &obj) const -> bool
		{
			return !this->operator==(obj);
		};

	public:
		/* ----------------------------------------------------------
			MOVERS
		---------------------------------------------------------- */
		auto operator--() -> VectorIterator<T>&
		{
			--this->ptr_;
			return *this;
		};

		auto operator++() -> VectorIterator<T>&
		{
			++this->ptr_;
			return *this;
		};
	};
};
};