#pragma once

namespace mystl
{
namespace base
{
	/**
	 * @hidden
	 */
	template <typename T>
	class _ListNode
	{
	public:
		_ListNode<T> *prev;
		_ListNode<T> *next;
		T value;

	public:
		/* ----------------------------------------------------------
			CONSTRUCTORS
		---------------------------------------------------------- */
		/**
		 * Default Constructor.
		 */
		_ListNode()
		{
			this->prev = this;
			this->next = this;
		};
		
		/**
		 * Initializer Constructor.
		 *
		 * @param prev Previous node.
		 * @param next Next node.
		 * @param value Value to contain.
		 */
		_ListNode(_ListNode<T> *prev, _ListNode<T> *next, const T &value)
		{
			this->prev = prev;
			this->next = next;
			this->value = value;
		};
		_ListNode(_ListNode<T> *prev, _ListNode<T> *next, T &&value)
		{
			this->prev = prev;
			this->next = next;
			this->value = std::forward<T>(value);
		};
	};
};
};