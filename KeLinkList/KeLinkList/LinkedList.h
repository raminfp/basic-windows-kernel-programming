#pragma once

#include "AutoLock.h"
#include "FastMutex.h"

template<typename T, typename TLock = FastMutex>
class LinkedList {
public:
	void Init() {
		InitializeListHead(&_head);
		_lock.Init();
	}

	// expects a LIST_ENTRY named "Entry"

	void PushBack(T* item) {
		AutoLock<TLock> locker(_lock);
		InsertTailList(&_head, &item->Entry);
	}

	void PushFront(T* value) {
		AutoLock locker(_lock);
		InsertHeadList(&_head, &item->Entry);
	}

	T* RemoveHead() {
		AutoLock locker(_lock);
		auto entry = RemoveHeadList(&_head);
		return CONTAINING_RECORD(entry, T, Entry);
	}

	T* GetHeadItem() {
		AutoLock locker(_lock);
		auto entry = _head->Flink;
		return CONTAINING_RECORD(entry, T, Entry);
	}

private:
	LIST_ENTRY _head;
	TLock _lock;
};