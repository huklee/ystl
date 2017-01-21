#pragma once

#include <mystl/base/_ListNode.hpp>

#include <mystl/base/ConstIterator.hpp>
#include <mystl/base/ReverseIterator.hpp>

namespace mystl
{
namespace base
{
	template <typename T>
	class ListIterator
	{
		template <class Iterator> friend class ConstIterator;
		template <class Iterator> friend class ReverseIterator;

	public:
		typedef T value_type;

	private:
		/**
		 * @hidden
		 */
		_ListNode<T> *node_;

	public:
		/* ----------------------------------------------------------
			CONSTRUCTORS
		---------------------------------------------------------- */
		/**
		 * Initializer Constructor.
		 */
		ListIterator(_ListNode<T> *node)
		{
			this->node_ = node;
		};

		/**
		 * Copy Constructor.
		 */
		ListIterator(const ListIterator<T> &obj)
		{
			this->node_ = obj.node_;
		};

		/**
		 * Copy Constructor.
		 */
		ListIterator(const ConstIterator<ListIterator<T>> &obj)
		{
			this->node_ = obj._Base().node_;
		};

	private:
		/**
		 * @hidden
		 */
		ListIterator()
			: ListIterator(nullptr)
		{
		};

	public:
		/* ----------------------------------------------------------
			ACCESSORS
		---------------------------------------------------------- */
		auto operator*() -> T&
		{
			return this->node_->value;
		};
		auto operator*() const -> const T&
		{
			return this->node_->value;
		};

		auto operator->() -> T*
		{
			return &(this->node_->value);
		};
		auto operator->() const -> const T*
		{
			return &(this->node_->value);
		};

		auto _Get_node() const -> _ListNode<T>*
		{
			return this->node_;
		};

	public:
		/* ----------------------------------------------------------
			COPARES
		---------------------------------------------------------- */
		auto operator==(const ListIterator<T> &obj) const -> bool
		{
			return this->node_ == obj.node_;
		};
		auto operator==(const ConstIterator<ListIterator<T>> &obj) const -> bool
		{
			return this->node_ == obj._Base().node_;
		};

		auto operator!=(const ListIterator<T> &obj) const -> bool
		{
			return !this->operator==(obj);
		};
		auto operator!=(const ConstIterator<ListIterator<T>> &obj) const -> bool
		{
			return !this->operator==(obj);
		};

	public:
		/* ----------------------------------------------------------
			MOVERS
		---------------------------------------------------------- */
		auto operator--() -> ListIterator<T>&
		{
			this->node_ = this->node_->prev;
			return *this;
		};
		auto operator++() -> ListIterator<T>&
		{
			this->node_ = this->node_->next;
			return *this;
		};
	};
};
};