#pragma once

#include <mystl/base/_ListNode.hpp>

#include <mystl/base/ListIterator.hpp>
#include <mystl/base/ConstIterator.hpp>
#include <mystl/base/ReverseIterator.hpp>

#include <mystl/functional.hpp>
#include <mystl/utility.hpp>

namespace mystl
{
	/**
	 * Doubly-Linked-List.
	 * 
	 * @author Jeongho Nam <http://samchon.org>
	 */
	template <typename T>
	class list
	{
	public:
		typedef base::ListIterator<T> iterator;
		typedef base::ConstIterator<iterator> const_iterator;
		typedef base::ReverseIterator<iterator> reverse_iterator;
		typedef base::ConstIterator<reverse_iterator> const_reverse_iterator;

	private:
		base::_ListNode<T> *begin_;
		base::_ListNode<T> *end_;
		size_t size_;

	public:
		/* ----------------------------------------------------------
			CONSTRUCTORS
		---------------------------------------------------------- */
		/**
		 * Default Constructor.
		 */
		list()
		{
			_Init();
		};

		/**
		 * Copy Constructor.
		 */
		list(const list<T> &obj)
			: list(obj.begin(), obj.end())
		{
		};

		/**
		 * Move Constructor.
		 */
		list(list<T> &&obj)
			: list()
		{
			this->swap(obj);
		}

		/**
		 * Fill Constructor.
		 */
		template <typename U>
		list(size_t n, const U &val)
			: list()
		{
			this->insert(this->end(), n, val);
		};

		/**
		 * Range Constructor.
		 */
		template <class InputIterator>
		list(InputIterator first, InputIterator last)
			: list()
		{
			this->assign(first, last);
		};

		/**
		 * Default Destructor.
		 */
		~list()
		{
			_Remove_all();
		};

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			clear();
			this->insert(this->end(), first, last);
		};

		void clear()
		{
			_Remove_all();
			_Init();
		};

	private:
		/**
		 * @hidden
		 */
		void _Init()
		{
			this->begin_ = this->end_ = new base::_ListNode<T>();
			this->size_ = 0;
		};

		/**
		 * @hidden
		 */
		void _Remove_all()
		{
			if (this->size_ == 0)
				delete this->begin_;
			else
				for (base::_ListNode<T> *it = this->begin_; it != this->end_; )
				{
					base::_ListNode<T> *targ = it;
					it = it->next;

					delete targ;
				}
		};

	public:
		/* ----------------------------------------------------------
			ACCESSORS
		---------------------------------------------------------- */
		auto empty() const -> bool
		{
			return this->size_ == 0;
		};

		auto size() const -> size_t
		{
			return this->size_;
		};

		auto front() -> T&
		{
			return this->begin_->value;
		};
		auto front() const -> const T&
		{
			return this->begin_->value;
		};

		auto back() -> T&
		{
			return this->end_->prev->value;
		};
		auto back() const -> const T&
		{
			return this->end_->prev->value;
		};

		auto begin() const -> iterator
		{
			return iterator(this->begin_);
		};
		auto cbegin() const -> const_iterator
		{
			return const_iterator(this->begin());
		};
		auto rbegin() const -> reverse_iterator
		{
			return reverse_iterator(this->end());
		};
		auto crbegin() const -> const_reverse_iterator
		{
			return const_reverse_iterator(this->rbegin());		
		};

		auto end() const -> iterator
		{
			return iterator(this->end_);
		};
		auto cend() const -> const_iterator
		{
			return const_iterator(this->end());
		};
		auto rend() const -> reverse_iterator
		{
			return reverse_iterator(this->begin());
		};
		auto crend() const -> const_reverse_iterator
		{
			return const_reverse_iterator(this->rend());
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
		template <typename U, typename ... Args>
		void push(const U &val, Args ...args)
		{
			this->push(val);
			this->push(args...);
		};
		
		template <typename U>
		void push(const U &val)
		{
			this->push_back(val);
		};

		template <typename U>
		void push_front(const U &val)
		{
			this->insert(this->begin(), val);
		};

		template <typename U>
		void push_back(const U &val)
		{
			this->insert(this->end(), val);
		};

		void pop_front()
		{
			this->erase(this->begin());
		};

		void pop_back()
		{
			this->erase(this->end());
		};

	public:
		/* ----------------------------------------------------------
			INSERT
		---------------------------------------------------------- */
		template <typename U>
		auto insert(iterator it, const U &val) -> iterator
		{
			return this->insert(it, (size_t)1, (const T&)val);
		};

		auto insert(iterator it, size_t n, const T &val) -> iterator
		{
			base::_ListNode<T> *prev = it._Get_node()->prev;
			base::_ListNode<T> *first_node = nullptr;

			for (size_t i = 0; i < n; i++)
			{
				// CONSTRUCT ITEM, THE NEW NODE
				base::_ListNode<T> *item = new base::_ListNode<T>(prev, nullptr, val);
				if (i == 0)
					first_node = item;

				// INSERT ITEM NEXT OF THE PREV
				prev->next = item;

				// SHIFT ITEM LEFT TO BE THE PREV
				prev = item;
			}

			// IF WAS EMPTY, THEN FIRST IS THE BEGIN
			if (empty() || it == begin())
				this->begin_ = first_node;

			// CONNECT BETWEEN LAST INSERTED ITEM AND IT
			prev->next = it._Get_node();
			it._Get_node()->prev = prev;

			// INCREASE NUMBER OF ELEMENTS
			this->size_ += n;

			return iterator(first_node);
		};

		template <class InputIterator>
		auto insert(iterator it, InputIterator first, InputIterator last) -> iterator
		{
			base::_ListNode<T> *prev = it._Get_node()->prev;
			base::_ListNode<T> *first_node = nullptr;

			size_t size = 0;
			for (InputIterator it = first; it != last; ++it)
			{
				// CONSTRUCT ITEM, THE NEW ELEMENT
				base::_ListNode<T> *item = new base::_ListNode<T>(prev, nullptr, *it);

				if (size == 0) first_node = item;
				if (prev != nullptr) prev->next = item;

				// SHIFT CURRENT ITEM TO PREVIOUS
				prev = item;
				size++;
			}

			// IF WAS EMPTY, FIRST NODE IS THE BEGIN
			if (this->empty() == true || it == this->begin())
				this->begin_ = first_node;

			// CONNECT BETWEEN LAST INSERTED ITEM AND IT
			prev->next = it._Get_node();
			it._Get_node()->prev = prev;

			// INCREASE NUMBER OF ELEMENTS
			this->size_ += size;

			return iterator(first_node);
		};

	public:
		/* ----------------------------------------------------------
			ERASE
		---------------------------------------------------------- */
		auto erase(iterator it) -> iterator
		{
			iterator last = it;
			++last;

			return erase(it, last);
		};

		auto erase(iterator first, iterator last) -> iterator
		{
			// PARAMETERS
			base::_ListNode<T> *firstNode = first._Get_node();
			base::_ListNode<T> *lastNode = last._Get_node();
			size_t distance = 0;

			// RECONNECT PREV AND NEXT DIRECTLY
			base::_ListNode<T> *prevNode = firstNode->prev;
			prevNode->next = lastNode;
			lastNode->prev = prevNode;

			// DELETE DISCONNECTED NODES
			for (base::_ListNode<T> *it = firstNode; it != lastNode; )
			{
				base::_ListNode<T> *target = it;
				it = it->next;

				delete target;
				distance++;
			}

			// SHRINK SIZE
			this->size_ -= distance;
			if (prevNode == this->begin_)
				this->begin_ = lastNode;

			return iterator(lastNode);
		};

	public:
		/* ===============================================================
			ALGORITHMS
				- UNIQUE & REMOVE (IF)
				- MERGE, SPLICE & SWAP
				- SORT
				- SWAP
		==================================================================
			UNIQUE & REMOVE (IF)
		--------------------------------------------------------------- */
		void unique()
		{
			unique(equal_to<T>());
		};

		template <class Predicate>
		void unique(Predicate predicate)
		{
			iterator it = this->begin();
			++it;

			while (it != this->end())
			{
				if (predicate(*it, it._Get_node()->prev->value))
					it = this->erase(it);
				else
					++it;
			}
		};

		template <typename U>
		void remove(const U &val)
		{
			for (iterator it = this->begin(); it != this->end(); )
				if (*it == val)
					it = this->erase(it);
				else
					++it;
		};

		template <class Predicate>
		void remove_if(Predicate predicate)
		{
			for (iterator it = this->begin(); it != this->end(); )
				if (predicate(*it))
					it = this->erase(it);
				else
					++it;
		};

	public:
		/* ---------------------------------------------------------
			MERGE, SPLICE & SWAP
		--------------------------------------------------------- */
		void merge(list<T> &obj)
		{
			merge(obj, less<T>());
		};

		template <class List, class Compare>
		void merge(list<T> &obj, Compare compare)
		{
			if (this == &obj)
				return;

			iterator it = this->begin();
			while (!obj.empty())
			{
				iterator first = obj.begin();
				while (it != this->end()) && compare(*it, *first)
					++it;

				splice(it, obj, first);
			}
		};

		void splice(iterator pos, list<T> &obj)
		{
			splice(pos, obj.begin(), obj.end());
		};

		void splice(iterator pos, list<T> &obj, iterator it)
		{
			iterator last = it;
			++last;

			splice(pos, obj, it, last);
		};

		void splice(iterator pos, list<T> &obj, iterator first, iterator last)
		{
			this->insert(pos, first, last);
			obj.erase(first, last);
		}

		void swap(list<T> &obj)
		{
			// SWAP MEMBERS
			mystl::swap(begin_, obj.begin_);
			mystl::swap(end_, obj.end_);
			mystl::swap(size_, obj.size_);
		};

	public:
		/* ---------------------------------------------------------
			SORT
		--------------------------------------------------------- */
		void sort()
		{
			sort(less<T>());
		};

		template <class Compare>
		void sort(Compare compare)
		{
			this->_Quick_sort(this->begin_, this->end_->prev, compare);
		};

	private:
		/**
		 * @hidden
		 */
		template <class Compare>
		void _Quick_sort(base::_ListNode<T> *first, base::_ListNode<T> *last, Compare compare)
		{
			if (first == last || last == this->end_ || first == last->next)
				return;

			// RETRIEVE THE MIDDLE POINT
			base::_ListNode<T> *mid = this->_Quick_partition(first, last, compare);

			// BINARY SORTING
			this->_Quick_sort(first, mid->prev, compare);
			this->_Quick_sort(mid->next, last, compare);
		};

		/**
		 * @hidden
		 */
		template <class Compare>
		auto _Quick_partition(base::_ListNode<T> *first, base::_ListNode<T> *last, Compare compare) -> base::_ListNode<T>*
		{
			const T &standard = last->value; // TO BE COMPARED
			base::_ListNode<T> *prev = first->prev;

			base::_ListNode<T> *it = first;
			for (; it != last; it = it->next)
				if (compare(it->value, standard))
				{
					// SWAP CONTENTS
					prev = (prev == this->end_) ? first : prev->next;
					mystl::swap(prev->value, it->value);
				}

			// DO IT ONCE AGAIN
			prev = (prev == this->end_) ? first : prev->next;
			mystl::swap(prev->value, it->value);

			return prev;
		};
	};
};