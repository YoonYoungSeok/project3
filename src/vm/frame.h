#include <stddef.h>
#include <list.h>

struct Frame_entry
 {
    size_t page_num;
    struct thread *t;
    uint32_t upage; 

    struct list_elem elem;
 };

struct Frame_table
 {
    struct Pages_cnt
     {
        size_t total;
        size_t valid;
     } pages_cnt;
   struct list frames; 

 } frame_table;

void init_frame_table(size_t pages);

void allocate_frame();
