#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

#include <iostream>

//some define
const int MAX_BYTES = 65536;
const int BLOCK_SIZE = 64;  //each block has 64 bytes
const int FREELIST_NUM = MAX_BYTES / BLOCK_SIZE;//The initialized number of free_list

//union freelist_node, when it is in free_list it is a pointer. Otherwise it is a allocated data.
union Slot_ {
    union Slot_* next;//free_list_pointer
    char client_data[1];
};

class MemoryPool
{
private:
    static Slot_* free_list[FREELIST_NUM]; //the whole list 
    static char* start; //free list start
    static char* end; //free list end
    static std::size_t heap_size;//total size of the list

    static std::size_t round(std::size_t bytes) //align the block
    {
        return (((bytes)+BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1));  //(bytes + BLOCK_SIZE) / BLOCK_SIZE
                                                                //get the block numbers bytes need
    }
    
    static std::size_t freelist_index(std::size_t bytes)    //function to determine the index of free list what we will use
    {                                                              
        return ((bytes)+BLOCK_SIZE - 1) / BLOCK_SIZE - 1;   //(bytes + BLOCK_SIZE) / BLOCK_SIZE
                                                            //get the block numbers bytes need
    }
    // return an object with the space of n
    static void* fill(std::size_t n) {
        int cnt_flnodes = 128;//the number of nodes added each time
        char* chunk = chunk_alloc(n, cnt_flnodes);//get n bytes blocks from the memory pool
        Slot_** now_list;//pointer to now free_list
        Slot_* res;
        Slot_* current_node, * next_node;

        size_t i;
        if (cnt_flnodes == 1) return chunk; //only get one block
        now_list = free_list + freelist_index(n);//update the free list
        res = (Slot_*)chunk;// first block return
        *now_list = next_node = (Slot_*)(chunk + n);
        //get link for block left
        for (i = 1; i < cnt_flnodes; i++) {
            current_node = next_node;
            next_node = (Slot_*)((char*)next_node + n);
            if (cnt_flnodes - 1 == i) {
                current_node->next = nullptr;
                break;
            }
            else {
                current_node->next = next_node;
            }
        }

        return res;
    }

    //Use memory pool optimization
    static char* chunk_alloc(std::size_t size, int& cnt_flnodes)
    {
        char* res; //result
        // space we will use
        std::size_t total_size = size * cnt_flnodes;
        // unused space in memory pool
        std::size_t space_left = end - start;
        if (space_left >= total_size)
        { //no need to update space
            res = start;
            start += total_size;
            return res;
        }
        else if (space_left >= size)
        {
            // the remaining space in the memory pool is available for partial
            cnt_flnodes = space_left / size;
            total_size = size * cnt_flnodes;
            res = start;
            start += total_size;
            return res;
        }
        else
        {
            // the remaining space in the memory pool cannot be provided for one block
            //apply for memory from the system heap
            std::size_t bytes_to_get = 2 * total_size + round(heap_size >> 4);
            // try to make use of the scattered space
            if (bytes_to_get > 0 && start != nullptr)
            {
                // if there is still some space
                Slot_** now_free_list =
                    free_list + freelist_index(space_left);
                // update the free list
                ((Slot_*)start)->next = *now_free_list;
                *now_free_list = (Slot_*)start;
            }

            // malloc new space
            start = (char*)malloc(bytes_to_get);
            heap_size += bytes_to_get;
            end = start + bytes_to_get;

            // recursive
            return chunk_alloc(size, cnt_flnodes);
        }
    }

public:
    static void* allocate(std::size_t n) {
        if (n > MAX_BYTES) {
            return malloc(n);
        }
        Slot_** now_fl = free_list + freelist_index(n);
        Slot_* res = *now_fl;
        //if res = NULL fill the free list
        if (res == nullptr) {
            return fill(round(n));
        }

        //update free list
        *now_fl = res->next;
        return res;
    }

    static void deallocate(void* p, std::size_t n) {
        if (n > MAX_BYTES) {
            free(p);//if the requested memory is greater than MAX_BYTES, call free directly
            return;
        }
        //else put in free list
        Slot_* h = (Slot_*)p;
        Slot_** now_fl = free_list + freelist_index(n);
        h->next = *now_fl;
        *now_fl = h;
    }

    static void* reallocate(void* p, std::size_t old_sz, std::size_t new_sz) {
        if (old_sz > MAX_BYTES) {
            void* res = realloc(p, new_sz);
            return res;
        }
        else {
            deallocate(p, old_sz);
            return allocate(new_sz);
        }
    }
};

// initialize MemoryPool
char* MemoryPool::start = nullptr;
char* MemoryPool::end = nullptr;
std::size_t MemoryPool::heap_size = 0;
Slot_* MemoryPool::free_list[FREELIST_NUM] = { nullptr };
// mempory_allocator
template <class T>
class Allocator
{
public:

    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;
    template <typename U>
    struct rebind
    {
        typedef Allocator<U> Other;
    };

    //constructor
    Allocator() = default;
    Allocator(const Allocator& allocator) = default;
    Allocator(Allocator&& allocator) = default;
    template <class U>
    Allocator(const Allocator<U>& allocator) noexcept;
    //compute address
    pointer address(reference _Val) const noexcept {//return address of value
        return &_Val;
    }
    const_pointer address(const_reference _Val) const noexcept {
        return &_Val;
    }
    //deallocate
    void deallocate(pointer ptr, size_type _Count) {
        MemoryPool::deallocate(ptr, _Count);
    }
    //use memortpool to allocate
    pointer allocate(size_type _Count) {
        if (auto res = static_cast<pointer>(MemoryPool::allocate(_Count * sizeof(value_type))))
            return res;
        else throw std::bad_alloc();
    }
    template <class _Uty>
    void destroy(_Uty* ptr) {
        ptr->~_Uty();
    }
    template <class object, class type>
    void construct(object* ptr, type && args) {
        new(ptr) object(std::forward<type>(args));
        return;
    }
};
#endif