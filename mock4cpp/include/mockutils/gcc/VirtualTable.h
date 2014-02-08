#ifndef VirtualTable_h__
#define VirtualTable_h__

template <int SIZE, class C>
struct VirtualTable {

	VirtualTable(){
		auto array = new void*[SIZE + 2];
		for (unsigned int i = 0; i < SIZE + 2; i++){
			array[i] = 0;
		}
		array[1] = (void*)&typeid(C); // initialize type_info pointer
		firstMethod = array;
		firstMethod++; // top_offset
		firstMethod++; // type_info ptr
	}

	~VirtualTable() {
		firstMethod--;
		firstMethod--;
		delete [] firstMethod;
	}

	void setMethod(unsigned int index, void *method)
	{
		if (index >= SIZE){
			throw "error";
		}
		firstMethod[index] = method;
	}

	void * getMethod(unsigned int index){
		return firstMethod[index];
	}

	unsigned int getSize(){
		return SIZE;
	}

private:
	void** firstMethod;
};
#endif // VirtualTable_h__