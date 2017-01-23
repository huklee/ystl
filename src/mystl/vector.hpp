#pragma once

#include <mystl/base/VectorIterator.hpp>
#include <mystl/base/ConstIterator.hpp>
#include <mystl/base/ReverseIterator.hpp>

#include <mystl/functional.hpp>

namespace mystl
{
	template <typename T>
	class vector
	{
	public:
		typedef base::VectorIterator<T> iterator;
		typedef base::ConstIterator<iterator> const_iterator;
		typedef base::ReverseIterator<iterator> reverse_iterator;
		typedef base::ConstIterator<reverse_iterator> const_reverse_iterator;

	private:
		/**
		 * @hidden
		 */
		T *data_;

		/**
		 * @hidden
		 */
		size_t size_;

		/**
		 * @hidden
		 */
		size_t capacity_;

	public:
		/* ==========================================================
			CONSTRUCTORS
				- BASIC CONSTRUCTORS
				- ASSIGNERS
		=============================================================
			BASIC CONSTRUCTOR
		---------------------------------------------------------- */
		/**
		 * Default Constructor.
		 */
		vector()
		{
			this->data_ = nullptr;
			this->size_ = 0;
			this->capacity_ = 0;
		};

		/* ----------------------------------------------------------
			ASSIGNERS
		---------------------------------------------------------- */
		void reserve(size_t n)
		{
			if (n < this->capacity_)
				return;

			this->_Set_capacity(n);
		};

		void resize(size_t n)
		{
			if (n <= this->size_)
			{
				this->size_ = n;
				return;
			}

			this->_Expand_capacity(n);
			this->size_ = n;
		};

		void resize(size_t n, const T &val)
		{
			size_t old_size = n > this->size_;
			this->resize(n);

			if (this->size_ > old_size)
			{
				T *last = this->data_ + this->size_;
				for (T *it = this->data_ + old_size; it != last; it++)
					*it = val;
			}
		};

		void shrink_to_fit()
		{
			if (this->capacity_ > this->size_)
				this->_Expand_capacity(this->size_);
		};

	private:
		void _Expand_capacity(size_t n)
		{
			T *last = this->data_ + this->size_;

			// NEW ARRAY
			T *data = new T[n];
			for (T *it = this->data_; it != last; it++)
				*(data++) = std::move(*it);

			// ORDINARY DATA ARE TRUNCATED
			delete[] this->data_;

			// ASSIGN NEW MEMBERS
			this->data_ = data;
			this->capacity_ = n;
		};

	public:
		/* ==========================================================
			ACCESSORS
				- BASIC ELEMENTS
				- ITERATORS
				- INDEX ACCESSORS
		=============================================================
			BASIC ELEMENTS
		---------------------------------------------------------- */
		auto data() const -> const T*
		{
			return this->data_;
		};
		auto size() const -> size_t
		{
			return this->size_;
		};
		auto capacity() const -> size_t
		{
			return this->capacity_;
		};

		auto empty() const -> bool
		{
			return this->size_ != 0;
		};

		auto front() -> T&
		{
			return this->operator[](0);
		};
		auto front() const -> const T&
		{
			return this->operator[](0);
		};

		auto back() -> T&
		{
			return this->operator[](this->size_ - 1);
		};
		auto back() const -> const T&
		{
			return this->operator[](this->size_ - 1);
		};
		
		/* ----------------------------------------------------------
			ITERATORS
		---------------------------------------------------------- */
		auto begin() -> iterator
		{
			return iterator(this->data_);
		};
		auto begin() const -> const_iterator
		{
			return const_iterator(this->begin());
		};
		auto cbegin() const -> const_iterator
		{
			return const_iterator(this->begin());
		};

		auto rbegin() -> reverse_iterator
		{
			return reverse_iterator(this->end());
		};
		auto rbegin() const -> const_reverse_iterator
		{
			return const_reverse_iterator(this->rbegin());
		};
		auto crbegin() const -> const_reverse_iterator
		{
			return const_reverse_iterator(this->rbegin());
		};

		auto end() -> iterator
		{
			return iterator(nullptr);
		};
		auto end() const -> const_iterator
		{
			return const_iterator(this->end());
		};
		auto cend() const -> const_iterator
		{
			return const_iterator(this->end());
		};

		auto rend() -> reverse_iterator
		{
			return reverse_iterator(this->begin());
		};
		auto rend() const -> const_reverse_iterator
		{
			return reverse_iterator(this->begin());
		};
		auto crend() const -> const_reverse_iterator
		{
			return const_reverse_iterator(this->rend());
		};

		/* ----------------------------------------------------------
			INDEX ACCESSORS
		---------------------------------------------------------- */
		auto operator[](size_t index) -> T&
		{
			return this->data_[index];
		};
		auto operator[](size_t index) const -> const T&
		{
			return this->data_[index];
		};

		auto at(size_t index) -> T&
		{
			return this->operator[](index);
		};
		auto at(size_t index) const -> const T&
		{
			return this->operator[](index);
		};

	public:
		/* ==========================================================
			ELEMENTS I/O
				- PUSH & POP
				- INSERT
				- ERASE
		=============================================================
			PUSH & POP
		---------------------------------------------------------- */
		void push_back(const T &val)
		{
			if (this->capacity_ == this->size_)
				this->_Expand_capacity(max<size_t>(this->capacity_ + 1, this->capacity_ * 1.5));
			
			this->data_[this->size_++] = val;
		};

		void push_back(T &&val)
		{
			if (this->capacity_ == this->size_)
				this->_Expand_capacity(max<size_t>(this->capacity_ + 1, this->capacity_ * 1.5));

			this->data_[this->size_++] = std::forward<T>(val);
		};

		void pop_back()
		{
			this->size_--;
		};

		/* ----------------------------------------------------------
			INSERT
		---------------------------------------------------------- */

		/* ----------------------------------------------------------
			ERASE
		---------------------------------------------------------- */
	};
};