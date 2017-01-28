#pragma once

#include <mystl/vector.hpp>
#include <mystl/list.hpp>

#include <mystl/base/ArrayIterator.hpp>
#include <mystl/base/Repeater.hpp>

namespace mystl
{
	template <typename T>
	class deque
	{
	private:
		// Row size of the {@link matrix_ matrix} which contains elements.
		// 
		// Note that the {@link ROW_SIZE} affects on time complexity of accessing and inserting element. 
		// Accessing element is {@link ROW_SIZE} times slower than ordinary {@link vector} and inserting element 
		// in middle position is {@link ROW_SIZE} times faster than ordinary {@link vector}.
		// 
		// When the {@link ROW_SIZE} returns 8, time complexity of accessing element is O(8) and inserting 
		// element in middle position is O(N/8). ({@link vector}'s time complexity of accessement is O(1)
		// and inserting element is O(N)).
		/**
		 * @hidden
		 */
		static const size_t ROW_SIZE = 8;

		// Minimum {@link capacity}.
		// 
		// Although a {@link deque} has few elements, even no element is belonged to, the {@link deque} 
		// keeps the minimum {@link capacity} at least.
		/**
		 * @hidden
		 */
		static const size_t MIN_CAPACITY = 32;

	public:
		typedef T value_type;

		typedef base::ArrayIterator<deque<T>> iterator;
		typedef base::ConstIterator<iterator> const_iterator;
		typedef base::ReverseIterator<iterator, T> reverse_iterator;
		typedef base::ConstIterator<reverse_iterator> const_reverse_iterator;

	private:
		// A matrix containing elements.
		// 
		// This {@link matrix_} is the biggest difference one between {@link Vector} and {@link deque}.
		// Its number of rows follows {@link ROW_SIZE} and number of columns follows {@link get_col_size} which 
		// returns divide of {@link capacity} and {@link ROW_SIZE}.
		//  
		// By separating segment of elements (segment: row, elements in a segment: col), {@link deque} takes
		// advantage of time complexity on inserting element in middle position. {@link deque} is {@link ROW_SIZE}
		// times faster than {@link Vector} when inserting elements in middle position.
		// 
		// However, separating segment of elements from matrix, {@link deque} also takes disadvantage of
		// time complexity on accessing element. {@link deque} is {@link ROW_SIZE} times slower than {@link Vector}
		// when accessing element.
		/**
		 * @hidden
		 */
		list<vector<T>> matrix_;

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
		deque()
		{
			this->matrix_.push_back(vector<T>());
			this->size_ = 0;
			this->capacity_ = MIN_CAPACITY;
		};

		deque(const deque<T> &obj)
			: deque()
		{
			this->assign(obj.begin(), obj.end());
		};

		deque(deque<T> &&obj)
			: deque()
		{
			this->swap(obj);
		};

		deque(size_t n, const T &val)
			: deque()
		{
			this->assign(n, val);
		};

		template <typename InputIterator>
		deque(InputIterator first, InputIterator last)
		{
			this->assign(first, last);
		};
		
	public:
		/* ----------------------------------------------------------
			ASSIGNERS
		---------------------------------------------------------- */
		void assign(size_t n, const T &val)
		{
			this->clear();
			this->insert(this->end(), n, val);
		};

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			this->clear();
			this->insert(this->end(), first, last);
		};

		void reserve(size_t capacity)
		{
			if (capacity < this->capacity_)
				return;

			// NEW MEMBERS TO BE ASSSIGNED
			list<vector<T>> matrix;
			
			size_t col_size = this->_Compute_col_size(capacity);
			matrix.push_back(vector<T>());
			matrix.back().reserve(col_size);

			// RE-FILL
			for (auto row = this->matrix_.begin(); row != this->matrix_.end(); ++row)
				for (size_t col = 0; col < row->size(); ++col)
				{
					if (matrix.back().size() >= col_size)
					{
						matrix.push_back(vector<T>());
						matrix.back().reserve(col_size);
					}
					matrix.back().push_back(row->operator[](col));
				}

			// ASSIGN MEMBERS
			this->matrix_ = std::move(matrix);
			this->capacity_ = capacity;
		};

		void clear()
		{
			// CLEAR CONTENTS
			this->matrix_.clear();
			this->matrix_.push_back(vector<T>());

			// RE-INDEX
			this->size_ = 0;
			this->capacity_ = MIN_CAPACITY;
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
			return this->size_ == 0;
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

	public:
		/* ----------------------------------------------------------
			ITERATORS
		---------------------------------------------------------- */
		auto begin() -> iterator
		{
			return empty() ? end() : iterator(this, 0);
		};
		auto begin() const -> const_iterator
		{
			return const_iterator(iterator(empty() ? end() : iterator((deque<T>*)this, 0)));
		};
		auto cbegin() const -> const_iterator
		{
			return this->begin();
		};

		auto rbegin() -> reverse_iterator
		{
			return reverse_iterator(this->end());
		};
		auto rbegin() const -> const_reverse_iterator
		{
			iterator it((deque<T>*)this, (size_t)-1);

			return const_reverse_iterator(reverse_iterator(it));
		};
		auto crbegin() const -> const_reverse_iterator
		{
			return this->rbegin();
		};

		auto end() -> iterator
		{
			return iterator(this, (size_t)-1);
		};
		auto end() const -> const_iterator
		{
			return const_iterator(iterator((deque<T>*)this, -1));
		};
		auto cend() const -> const_iterator
		{
			return this->end();
		};

		auto rend() -> reverse_iterator
		{
			return reverse_iterator(this->begin());
		};
		auto rend() const -> const_reverse_iterator
		{
			iterator it((deque<T>*)this, this->empty() ? (size_t)-1 : 0);

			return const_reverse_iterator(reverse_iterator(it));
		};
		auto crend() const -> const_reverse_iterator
		{
			return this->rend();
		};

	public:
		/* ----------------------------------------------------------
			INDEX ACCESSORS
		---------------------------------------------------------- */
		auto operator[](size_t index) -> T&
		{
			// FETCH INDEX
			list<vector<T>>::iterator row;
			size_t col;

			this->_Fetch_index(index, row, col);

			// RETURN VALUE
			return row->operator[](col);
		};
		auto operator[](size_t index) const -> const T&
		{
			// FETCH INDEX
			list<vector<T>>::iterator row;
			size_t col;

			this->_Fetch_index(index, row, col);

			// RETURN VALUE
			return row->operator[](col);
		};

		auto at(size_t index) -> T&
		{
			return this->operator[](index);
		};

		auto at(size_t index) const -> const T&
		{
			return this->operator[](index);
		};

	private:
		/**
		 * @hidden
		 */
		void _Fetch_index(size_t index, typename list<vector<T>>::iterator &r, size_t &c) const
		{
			list<vector<T>>::iterator row;
			for (row = this->matrix_.begin(); row != this->matrix_.end(); ++row)
			{
				size_t size = row->size();
				if (index < size)
					break;

				index -= size;
			}

			if (row == this->matrix_.end())
				row--;

			// RETURN
			r = row;
			c = index;
		};

		/**
		 * @hidden
		 */
		auto _Compute_col_size() const -> size_t
		{
			return this->_Compute_col_size(this->capacity_);
		};

		/**
		 * @hidden
		 */
		auto _Compute_col_size(size_t capacity) const -> size_t
		{
			return capacity / ROW_SIZE;
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

		void push_front(const T &val)
		{
			// ADD CAPACITY & ROW
			this->_Try_expand_capacity(this->size_ + 1);
			this->_Try_add_row_at_front();

			// INSERT VALUE
			this->matrix_.front().insert(this->matrix_.front().begin(), val);
			this->size_++;
		};
		void push_front(T &&val)
		{
			// ADD CAPACITY & ROW
			this->_Try_expand_capacity(this->size_ + 1);
			this->_Try_add_row_at_front();

			// INSERT VALUE
			this->matrix_.front().insert(this->matrix_.front().begin(), std::forward<T>(val));
			this->size_++;
		};

		void push_back(const T &val)
		{
			// ADD CAPACITY & ROW
			this->_Try_expand_capacity(this->size_ + 1);
			this->_Try_add_row_at_back();

			// INSERT VALUE
			this->matrix_.back().push_back(val);
			this->size_++;
		};
		void push_back(T &&val)
		{
			// ADD CAPACITY & ROW
			this->_Try_expand_capacity(this->size_ + 1);
			this->_Try_add_row_at_back();

			// INSERT VALUE
			this->matrix_.back().push_back(std::forward<T>(val));
			this->size_++;
		};

		void pop_front()
		{
			if (this->empty())
				return;

			this->matrix_.front().erase(this->matrix_.front().begin());
			this->size_--;

			if (this->matrix_.front().empty() && this->matrix_.size() > 1)
				this->matrix_.pop_front();
		};

		void pop_back()
		{
			if (this->empty())
				return;

			this->matrix_.back().pop_back();
			this->size_--;

			if (this->matrix_.back().empty() && this->matrix_->size() > 1)
				this->matrix_.pop_back();
		};

	public:
		/* ----------------------------------------------------------
			INSERT
		----------------------------------------------------------*/
		auto insert(iterator pos, const T &val) -> iterator
		{
			return insert(pos, (size_t)1, val);
		};

		auto insert(iterator pos, size_t n, const T &val) -> iterator
		{
			base::Repeater<T> first(&val, 0);
			base::Repeater<T> last(&val, n);

			return this->insert(pos, first, last);
		};

		template <typename InputIterator>
		auto insert(iterator pos, InputIterator first, InputIterator last) -> iterator
		{
			size_t size = this->size_ + distance(first, last);

			if (pos == this->end())
			{
				// EXPAND CAPACITY IF REQUIRED
				this->_Try_expand_capacity(size);
				
				// INSERT TO END
				this->_Insert_to_end(first, last);
			}
			else
			{
				// INSERT ITEMS IN THE MIDDLE
				if (size > this->capacity_)
				{
					deque<T> v;
					v.reserve(max((size_t)(this->capacity_ * 1.5), size));

					v._Insert_to_end(this->begin(), pos);
					v._Insert_to_end(first, last);
					v._Insert_to_end(pos, this->end());

					this->swap(v);
				}
				else
					this->_Insert_to_middle(pos, first, last);
			}
			this->size_ = size;
			return pos;
		};

	private:
		/**
		 * @hidden
		 */
		template <typename InputIterator>
		void _Insert_to_end(InputIterator first, InputIterator last)
		{
			// INSERT ITEMS IN THE BACK
			for (; first != last; ++first)
			{
				// ADD ROW IF REQUIRED
				this->_Try_add_row_at_back();

				// INSERT VALUE
				this->matrix_.back().push_back(*first);
			}
		};

		/**
		 * @hidden
		 */
		template <typename InputIterator>
		void _Insert_to_middle(iterator pos, InputIterator first, InputIterator last)
		{
			size_t col_size = this->_Compute_col_size();

			// POSITION OF MATRIX
			list<vector<T>>::iterator row;
			size_t index;

			this->_Fetch_index(pos._Get_index(), row, index);

			// MOVE BACK SIDE TO TEMPORARY VECTOR
			vector<T> back_array;
			back_array.reserve(col_size);

			for (T *it = row->begin() + index; it != row->end(); ++it)
				back_array.push_back(std::move(*it));
			row->erase(row->begin() + index, row->end());

			// INSERT ITEMS
			while (first != last)
			{
				if (row->size() == col_size && this->matrix_.size() < ROW_SIZE)
				{
					row = this->matrix_.insert(++row, vector<T>());
					row->reserve(col_size);
				}
				row->push_back(*first);
				++first;
			}

			// INSERT THE BACK SIDE ITEMS
			for (auto it = back_array.begin(); it != back_array.end(); it++)
			{
				if (row->size() == col_size && this->matrix_.size() < ROW_SIZE)
				{
					row = this->matrix_.insert(++row, vector<T>());
					row->reserve(col_size);
				}
				row->push_back(std::move(*it));
			}
		};

		/**
		 * @hidden
		 */
		auto _Try_expand_capacity(size_t size) -> bool
		{
			if (size <= this->capacity_)
				return false;

			// MAX (CAPACITY * 1.5, TARGET SIZE)
			this->reserve(max((size_t)(this->capacity_ * 1.5), size));
			return true;
		};

		/**
		 * @hidden
		 */
		auto _Try_add_row_at_front() -> bool
		{
			size_t col_size = this->_Compute_col_size();

			if (this->matrix_.front().size() >= col_size && this->matrix_.size() < ROW_SIZE)
			{
				this->matrix_.push_front(vector<T>());
				this->matrix_.front().reserve(col_size);

				return true;
			}
			else
				return false;
		};

		/**
		 * @hidden
		 */
		auto _Try_add_row_at_back() -> bool
		{
			size_t col_size = this->_Compute_col_size();

			if (this->matrix_.back().size() >= col_size && this->matrix_.size() < ROW_SIZE)
			{
				this->matrix_.push_back(vector<T>());
				this->matrix_.back().reserve(col_size);

				return true;
			}
			else
				return false;
		};

	public:
		/* ----------------------------------------------------------
			ERASE
		---------------------------------------------------------- */
		auto erase(iterator it) -> iterator
		{
			return erase(it, it + 1);
		};

		auto erase(iterator first, iterator last) -> iterator
		{
	 		if (first == this->end())
				return first;

			// INDEXING
			size_t size;
			if (last == this->end())
				size = this->size() - first._Get_index();
			else
				size = last._Get_index() - first._Get_index();

			// ERASING
			list<vector<T>>::iterator first_row = this->matrix_.end();
			list<vector<T>>::iterator second_row = this->matrix_.end();
			size_t i = 0;

			size_t left_size = size;
			while (left_size != 0)
			{
				// FIND MATCHED ROW AND COLUMN
				list<vector<T>>::iterator row;
				size_t col;

				this->_Fetch_index(first._Get_index(), row, col);

				// ERASE FROM THE ROW
				size_t my_delete_size = min(left_size, row->size() - col);
				row->erase(row->begin() + col, row->begin() + col + my_delete_size);

				// TO MERGE
				if (!row->empty())
					if (i == 0)
						first_row = row;
					else
						second_row = row;

				// ERASE THE ENTIRE ROW IF REQUIRED
				if (row->empty() && this->matrix_.size() > 1)
					this->matrix_.erase(row);

				// TO THE NEXT STEP
				left_size -= my_delete_size;
				i++;
			}

			// MERGE FIRST AND SECOND ROW
			if (first_row != this->matrix_.end() && second_row != this->matrix_.end()
				&& first_row->size() + second_row->size() <= this->_Compute_col_size())
			{
				for (auto it = second_row->begin(); it != second_row->end(); ++it)
					first_row->push_back(std::move(*it));

				this->matrix_.erase(second_row);
			}

			// RETURN
			this->size_ -= size;
			if (first._Get_index() >= this->size())
				return this->end();
			else
				return first;
		};

	public:
		/* ----------------------------------------------------------
			SWAP
		---------------------------------------------------------- */
		void swap(deque<T> &v)
		{
			mystl::swap(this->matrix_, v.matrix_);
			mystl::swap(this->size_, v.size_);
			mystl::swap(this->capacity_, v.capacity_);
		};

		auto operator=(const deque<T> &v) -> deque<T>&
		{
			this->assign(v.begin(), v.end());

			return *this;
		};

		auto operator=(deque<T> &&v) -> deque<T>&
		{
			this->clear();
			this->swap(v);

			return *this;
		};
	};
};