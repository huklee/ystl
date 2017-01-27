#pragma once

#include <mystl/base/ReverseIterator.hpp>

#include <mystl/functional.hpp>
#include <mystl/iterator.hpp>

namespace mystl
{
	template <typename T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef base::ReverseIterator<iterator, T> reverse_iterator;
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

		vector(const vector<T> &v)
			: vector(v.begin(), v.end())
		{
		};

		vector(vector<T> &&v)
			: vector()
		{
			this->swap(v);
		};

		vector(size_t n, const T &val)
			: vector()
		{
			this->assign(n, val);
		};

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			: vector()
		{
			this->assign(first, last);
		};

		~vector()
		{
			delete[] this->data_;
		};

		/* ----------------------------------------------------------
			ASSIGNERS
		---------------------------------------------------------- */
		void assign(size_t n, const T &val)
		{
			this->clear();
			this->insert(this->end(), n, val);
		};

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			this->clear();
			this->insert(this->end(), first, last);
		};

		void clear()
		{
			this->size_ = 0;
		}

		void reserve(size_t n)
		{
			if (n < this->capacity_)
				return;

			this->_Expand_capacity(n);
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
			// NEW ARRAY
			T *data = new T[n];

			if (this->size_ != 0)
			{
				// MIGRATE DATA
				T *last = this->data_ + this->size_;
				for (T *it = this->data_; it != last; it++)
					*(data++) = std::move(*it);
			}

			// ORDINARY DATA ARE TRUNCATED
			delete[] this->data_;

			// ASSIGN NEW MEMBERS
			this->data_ = data - this->size_;
			this->capacity_ = n;
		};

		// Migrate from [first, last) to target.
		//
		// @param first First position of the source array.
		// @param last Last position of the source array.
		// @param target Target array to migrate.
		//
		// @return Advanced position from target by the migration.
		auto _Migrate(const T *first, const T *last, T *target) -> T*
		{
			for (; first != last; first++)
				*(target++) = std::move(*first);

			return target;
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
			return this->data_;
		};
		auto begin() const -> const_iterator
		{
			return this->data_;
		};
		auto cbegin() const -> const_iterator
		{
			return this->data_;
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
			return this->data_ + this->size_;
		};
		auto end() const -> const_iterator
		{
			return this->data_ + this->size_;
		};
		auto cend() const -> const_iterator
		{
			return this->data_ + this->size_;
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
				- SWAP
		=============================================================
			PUSH & POP
		---------------------------------------------------------- */
		template <typename ... Args>
		void push(const T &val, Args ...args)
		{
			this->push(val);
			this->push(args...);
		};

		template <typename ... Args>
		void push(T &&val, Args ...args)
		{
			this->push(std::forward<T>(val));
			this->push(args...);
		};

		void push(const T &val)
		{
			this->push_back(val);
		};
		void push(T &&val)
		{
			this->push_back(std::forward<T>(val));
		};

		void push_back(const T &val)
		{
			if (this->capacity_ == this->size_)
				this->_Expand_capacity(max(this->capacity_ + 1, (size_t)(this->capacity_ * 1.5)));
			
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
		auto insert(iterator it, const T &val) -> iterator
		{
			return iterator(it, (size_t)1, val);
		};

		auto insert(iterator it, T &&val) -> iterator
		{
			size_t index = (size_t)(it - this->data_);
			if (index == this->size_)
				this->push_back(val);
			else
			{
				size_t size = this->size_ + 1;
				size_t capacity = max(size, (size_t)(this->capacity_ * 1.5));
				T *data = new T[capacity];

				// DATA DATA IN THE FRONT
				T *ptr = this->_Migrate(this->begin(), it, data);

				// MIDDLE, THE NEWLY INSERTED DATA
				*(ptr++) = std::forward<T>(val);

				// MIGRATE DATA IN THE BACK
				this->_Migrate(it, this->end(), ptr);

				// NEWLY ASSIGNED MEMBERS
				this->data_ = data;
				this->size_ = size;
				this->capacity_ = capacity;
			}

			return iterator(this->data_ + index);
		};

		auto insert(iterator it, size_t n, const T &val) -> iterator
		{
			size_t index = it - this->data_;
			if (it == this->end())
			{
				size_t size = this->size_ + n;
				if (size > this->capacity_)
					this->_Expand_capacity(max(size, (size_t)(this->capacity_ * 1.5)));

				T *it = this->data_ + this->size_;
				while (n-- != 0)
					*(it++) = val;

				this->size_ = size;
			}
			else
			{
				size_t size = this->size_ + n;
				size_t capacity = max(size, (size_t)(this->capacity_ * 1.5));
				T *data = new T[capacity];

				// DATA DATA IN THE FRONT
				T *ptr = this->_Migrate(this->begin(), it, data);

				// MIDDLE, THE NEWLY INSERTED DATA
				for (size_t i = 0; i < n; i++)
					*(ptr++) = val;

				// MIGRATE DATA IN THE BACK
				this->_Migrate(it, this->end(), ptr);

				// NEWLY ASSIGNED MEMBERS
				this->data_ = data;
				this->size_ = size;
				this->capacity_ = capacity;
			}

			return iterator(this->data_ + index);
		};

		template <class InputIterator>
		auto insert(iterator it, InputIterator first, InputIterator last) -> iterator
		{
			size_t index = it - this->data_;
			if (it == this->end())
			{
				size_t size = this->size_ + distance(first, last);
				if (size > this->capacity_)
					this->_Expand_capacity(max<size_t>(size, this->capacity_ * 1.5));

				T *ptr = this->data_ + this->size_;
				for (; first != last; first++)
					*(ptr++) = *first;

				this->size_ = size;
			}
			else
			{
				size_t size = this->size_ + distance(first, last);
				size_t capacity = max<size_t>(size, this->capacity_ * 1.5);
				T *data = new T[capacity];

				// DATA DATA IN THE FRONT
				T *ptr = this->_Migrate(this->begin(), it, this->data_);

				// MIDDLE, THE NEWLY INSERTED DATA
				for (; first != last; first++)
					*(ptr++) = *first;

				// MIGRATE DATA IN THE BACK
				this->_Migrate(it, this->end(), ptr);

				// NEWLY ASSIGNED MEMBERS
				this->data_ = data;
				this->size_ = size;
				this->capacity_ = capacity;
			}

			return iterator(this->data_ + index);
		};

		/* ----------------------------------------------------------
			ERASE
		---------------------------------------------------------- */
		auto erase(iterator it) -> iterator
		{
			return erase(it, it + 1);
		};

		auto erase(iterator first, iterator last) -> iterator
		{
			size_t size = last - first;

			this->_Migrate(last, this->end(), first);
			this->size_ -= size;

			return first;
		};

		/* ----------------------------------------------------------
			SWAP
		---------------------------------------------------------- */
		void swap(vector<T> &v)
		{
			mystl::swap(this->data_, v.data_);
			mystl::swap(this->size_, v.size_);
			mystl::swap(this->capacity_, v.capacity_);
		};

		auto operator=(const vector<T> &v) -> vector<T>&
		{
			this->assign(v.begin(), v.end());

			return *this;
		};

		auto operator=(vector<T> &&v) -> vector<T>&
		{
			this->clear();
			this->swap(v);

			return *this;
		};
	};
};