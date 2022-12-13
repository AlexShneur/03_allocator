#pragma once

struct Block
{
public:
	Block(size_t n)
	{
		size = avaliable = n;
	}
	std::byte* getBytes(size_t n)
	{
		if (n > avaliable)
		{
			throw std::bad_alloc();
		}
		else
		{
			if (memoryBlock == nullptr)
			{
				auto p = std::malloc(size);
				if (!p)
				{
					std::free(memoryBlock);
					throw std::bad_alloc();
				}

				memoryBlock = reinterpret_cast<std::byte*>(p);
			}
			auto pos = size - avaliable;
			avaliable -= n;
			return &memoryBlock[pos];
		}
	}

	void freeBytes(size_t n)
	{
		avaliable += n;
		if (avaliable==size)
		{
			std::free(memoryBlock);
		}
	}

private:
	std::byte* memoryBlock = nullptr;
	size_t size;
	size_t avaliable;
};
