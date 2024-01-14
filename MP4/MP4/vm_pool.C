/*
 File: vm_pool.C
 
 Author:
 Date  :
 
 */

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "vm_pool.H"
#include "console.H"
#include "utils.H"
#include "assert.H"
#include "simple_keyboard.H"
#include "page_table.H"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* METHODS FOR CLASS   V M P o o l */
/*--------------------------------------------------------------------------*/

VMPool::VMPool(unsigned long  _base_addr,
               unsigned long  _size,
               ContFramePool *_frame_pool,
               PageTable     *_page_table) 
{
    base_addr = _base_addr;
    size = _size;
    frame_pool = _frame_pool;
    page_table = _page_table;
    page_table -> register_pool(this);

    memory_region * region_list = (memory_region *)base_addr;
    region_list[0].start_addr = _base_addr;
    region_list[0].size = Machine::PAGE_SIZE;
    for (int i = 1; i < 512; i++)
    {
        region_list[i].start_addr = 0;
        region_list[i].size = 0;
    }

    Console::puts("Constructed VMPool object.\n");
}

unsigned long VMPool::allocate(unsigned long _size) 
{
    int i;
    int allocated_size = Machine::PAGE_SIZE;
    
    if (_size > Machine::PAGE_SIZE)
        allocated_size = Machine::PAGE_SIZE * (_size/Machine::PAGE_SIZE) + ((_size % Machine::PAGE_SIZE == 0) ? 0 : Machine::PAGE_SIZE);

    memory_region * region_list = (memory_region *)base_addr;
    for (i = 1; i < 512; i++)
    {
        // Find the free region and allocate the memory
        if (region_list[i].size == 0)
        {
            region_list[i].start_addr = region_list[i-1].start_addr + region_list[i-1].size;
            region_list[i].size = allocated_size;
            break;
        }
    }

    Console::puts("Allocated region of memory.\n");
    return region_list[i].start_addr;
}

void VMPool::release(unsigned long _start_addr)
{
    memory_region * region_list = (memory_region *)base_addr;
    int i;
    for (i = 1; i < 512; i++)
    {
        if (region_list[i].start_addr == _start_addr)
            break;

    }


    for (int k = Machine::PAGE_SIZE; k <= region_list[i].size; k += Machine::PAGE_SIZE)
    page_table -> free_page(region_list[i].start_addr + k);

    while (i < 511)
    {
        if (region_list[i + 1].size != 0)
        {
            region_list[i].start_addr = region_list[i + 1].start_addr;
            region_list[i].size = region_list[i + 1].size;
        }
        else
        {
            region_list[i].start_addr = 0;
            region_list[i].size = 0;
        }
        i++;
    }


    Console::puts("Released region of memory.\n");

}

bool VMPool::is_legitimate(unsigned long _addr) 
{
    if (_addr == base_addr)
    {
        return true;
    }

    int flag = 0;
    memory_region * region_list = (memory_region *) (base_addr);
	

    for (int i = 0; i < 512; i++)
    {
        if ((_addr >= region_list[i].start_addr) && (_addr <= region_list[i].start_addr + region_list[i].size))
        {
            flag = 1;
            break;
        }
	}
	
	return (flag==1)? true: false;
    Console::puts("Checked whether address is part of an allocated region.\n");
}

