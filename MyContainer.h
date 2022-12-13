#pragma once

template <typename T, typename Allocator = std::allocator<T>>
struct MyContainer
{
private:
	struct Node
	{
		Node(const T& _data)
		{
			data = _data;
			next = nullptr;
		}
		T data;
		Node* next;
	};

	struct Iterator
	{
	private:
		Node* node;

	public:
		Iterator(Node* _node)
		{
			node = _node;
		}
		T& operator*()
		{
			return node->data;
		}
		Iterator& operator++()
		{
			node = node->next;
			return *this;
		}
		bool operator==(const Iterator& iter) const
		{
			return node == iter.node;
		}
		bool operator!=(const Iterator& iter) const
		{
			return node != iter.node;
		}
	};

	using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

	Node* head = nullptr;
	Node* tail = nullptr;
	NodeAllocator myNodeAllocator;

public:
	MyContainer() = default;
	~MyContainer()
	{
		tail = std::move(tail->next);
		while (head != tail)
		{
			head = std::move(head->next);
			std::allocator_traits<NodeAllocator>::destroy(myNodeAllocator, head);
			std::allocator_traits<NodeAllocator>::deallocate(myNodeAllocator, head, 1);
		}
		std::allocator_traits<NodeAllocator>::destroy(myNodeAllocator, tail);
		std::allocator_traits<NodeAllocator>::deallocate(myNodeAllocator, tail, 1);
	}

	void push(const T& data)
	{
		Node* node = std::allocator_traits<NodeAllocator>::allocate(myNodeAllocator, 1);
		std::allocator_traits<NodeAllocator>::construct(myNodeAllocator, node, data);

		if (head == nullptr)
		{
			head = node;
			tail = head;
		}
		else
		{
			tail->next = node;
			tail = node;
		}
		tail->next = nullptr;
	}

	Iterator begin() const
	{
		return Iterator(head);
	}

	Iterator end() const
	{
		return Iterator(nullptr);
	}
};