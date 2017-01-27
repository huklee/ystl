#pragma once

#include <mystl/base/ConstIterator.hpp>
#include <mystl/base/ReverseIterator.hpp>

namespace mystl
{
namespace base
{
	template <class Array>
	class ArrayIterator
	{
	public:
		typedef typename Array::value_type value_type;

	private:
		Array *array_;
		size_t index_;

	public:
		/* ----------------------------------------------------------
			CONSTRUCTORS
		---------------------------------------------------------- */
		ArrayIterator()
		{
			this->array_ = nullptr;
			this->index_ = (size_t)-1;
		};

		ArrayIterator(Array *array, size_t index)
		{
			this->array_ = array;
			this->index_ = index;
		};

		ArrayIterator(const ArrayIterator<Array> &obj)
		{
			this->array_ = obj.array_;
			this->index_ = obj.index_;
		};

		ArrayIterator(const ConstIterator<ArrayIterator<Array>> &obj)
		{
		this->array_ = obj._Base().array_;
		this->index_ = obj._Base().index_;
		};

	public:
		/* ----------------------------------------------------------
			ACCESSORS
		---------------------------------------------------------- */
		auto operator*() -> value_type&
		{
			return this->array_->operator[](this->index_);
		};
		auto operator*() const -> const value_type&
		{
			return this->array_->operator[](this->index_);
		};

		auto operator->() -> value_type*
		{
			return &(this->array_->operator[](this->index_));
		};
		auto operator->() const -> const value_type*
		{
			return &(this->array_->operator[](this->index_));
		};

		auto _Get_index() const -> size_t
		{
			return this->index_;
		};

	public:
		/* ----------------------------------------------------------
			COMPARES
		---------------------------------------------------------- */
		auto operator==(const ArrayIterator<Array> &obj) const -> bool
		{
			return this->array_ == obj.array_ && this->index_ == obj.index_;
		};
		auto operator==(const ConstIterator<ArrayIterator<Array>> &obj) const -> bool
		{
			return this->array_ == obj._Base().deque_ && this->index_ == obj._Base().index_;
		};

		auto operator!=(const ArrayIterator<Array> &obj) const -> bool
		{
			return !this->operator==(obj);
		};
		auto operator!=(const ConstIterator<ArrayIterator<Array>> &obj) const -> bool
		{
			return !this->operator==(obj);
		};

	public:
		/* ----------------------------------------------------------
			MOVERS
		---------------------------------------------------------- */
		auto operator--() -> ArrayIterator<Array>&
		{
			this->index_--;
			return *this;
		};
		auto operator--(int) -> ArrayIterator<Array>&
		{
			ArrayIterator<Array> it = *this;
			--(*this);

			return it;
		};
		auto operator-(size_t n) -> ArrayIterator<Array>
		{
			ArrayIterator<Array> it = *this;
			it.index_ -= n;

			if (it.index_ >= this->array_->size())
				it.index_ = (size_t)-1;

			return it;
		};

		auto operator++() -> ArrayIterator<Array>&
		{
			if (++this->index_ == this->array_->size())
				this->index_ = (size_t)-1;

			return *this;
		};
		auto operator++(int) -> ArrayIterator<Array>&
		{
			ArrayIterator<Array> it = *this;
			++(*this);

			return it;
		};
		auto operator+(size_t n) -> ArrayIterator<Array>
		{
			ArrayIterator<Array> it = *this;
			it.index_ += n;

			if (it.index_ >= this->array_->size())
				it.index_ = (size_t)-1;

			return it;
		};
	};
};
};