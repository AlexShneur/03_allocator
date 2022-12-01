#include "Block.h"
#include <memory>

template <typename T, size_t N>
struct My_Allocator
{
	using value_type = T;

	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template <typename U>
	struct rebind {
		using other = My_Allocator<U, N>;
	};

	My_Allocator() = default;
	~My_Allocator() = default;

	My_Allocator(My_Allocator& other)
	{
		block = other.block;
	}

	template <typename U>
	My_Allocator(My_Allocator<U, N>& p)
	{

	}

	T* allocate(std::size_t n)
	{
		if (block==nullptr)
			block = std::make_unique<Block>(sizeof(T) * (N+1));
		return reinterpret_cast<T*>(block->getBytes(sizeof(T) * n));
	}

	void deallocate(T* p, std::size_t n)
	{
		if (block!=nullptr)
			block->freeBytes(sizeof(T)* n);
	}

private:
	std::unique_ptr<Block> block = nullptr;
};
#pragma once
