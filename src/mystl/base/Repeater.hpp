#pragma once

namespace mystl
{
namespace base
{
	template <typename T>
	class Repeater
	{
	private:
		/**
		 * @hidden
		 */
		const T *ptr_;

		/**
		 * @hidden
		 */
		size_t index_;

	public:
		/* ----------------------------------------------------------
			CONSTRUCTORS
		---------------------------------------------------------- */
		/**
		 * Initializer Constructor.
		 */
		Repeater(const T *ptr, size_t index)
		{
			this->ptr_ = ptr;
			this->index_ = index;
		};

		Repeater(const Repeater<T> &obj)
			: Repeater(obj.ptr_, obj.index_)
		{
		};

	public:
		/* ----------------------------------------------------------
			ACCESSORS
		---------------------------------------------------------- */
		auto operator*() const -> const T&
		{
			return *this->ptr_;
		};

		auto operator->() const -> const T*
		{
			return this->ptr_;
		};

	public:
		/* ----------------------------------------------------------
			COMPARES
		---------------------------------------------------------- */
		auto operator==(const Repeater<T> &obj) const -> bool
		{
			return this->ptr_ == obj.ptr_ && this->index_ == obj.index_;
		};

		auto operator!=(const Repeater<T> &obj) const -> bool
		{
			return !this->operator==(obj);
		};

	public:
		/* ----------------------------------------------------------
			MOVERS
		---------------------------------------------------------- */
		auto operator--() -> Repeater<T>&
		{
			this->index_--;
			return *this;
		};
		auto operator--(int) -> Repeater<T>
		{
			Repeater<T> it = *this;
			--(*this);

			return it;
		};

		auto operator++() -> Repeater<T>&
		{
			this->index_++;
			return *this;
		};
		auto operator++(int) -> Repeater<T>
		{
			Repeater<T> it = *this;
			++(*this);

			return it;
		};
	};
};
};