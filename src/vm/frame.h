#include <stddef.h>
#include <list.h>

struct frame_entry
 {
    size_t page_num;
    struct thread *t;
    void *upage; 

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

void allocate_frame(uint32_t *pd, void *upage, void *kpage, bool writable);

struct frame_entry* make_fte(size_t page_num, void *upage);

bool
page_num_less (const struct list_elem *a,
               const struct list_elem *b,
               void *aux);

