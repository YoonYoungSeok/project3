#include "frame.h"
#include "threads/vaddr.h"
#include "threads/thread.h"
#include "threads/malloc.h"

//struct Frame_table frame_table;


void
init_frame_table(size_t pages)
{
    frame_table.pages_cnt.total = pages;
    frame_table.pages_cnt.valid = pages;
    
    list_init(&frame_table.frames);

}

struct frame_entry*
make_fte(size_t page_num, void *upage)
{
    struct frame_entry *fte = (struct frame_entry *) malloc (sizeof(struct frame_entry));
    fte->page_num = page_num;
    fte->t = thread_current();
    fte->upage = upage;

    return fte;
}

void
allocate_frame(uint32_t *pd, void *upage, void *kpage, bool writable)
{
    struct list_elem *e;
    size_t page_num = pg_no (vtop (kpage));
    bool is_exist = false;
    
    ASSERT(frame_table.pages_cnt.valid != 0);

    
    for (e = list_begin (&frame_table.frames); e != list_end (&frame_table.frames);
        e = list_next (e))
    {
        struct frame_entry *f = list_entry (e, struct frame_entry, elem);

        if (f->page_num == page_num)
        {
            is_exist = true;
            break;
        }
    }
    
    ASSERT(!is_exist);

    struct frame_entry *fte = make_fte(page_num, upage);
    list_insert_ordered (&frame_table.frames, &fte->elem,
                         &page_num_less, NULL);

   frame_table.pages_cnt.valid -= 1; 

}

bool
page_num_less (const struct list_elem *a,
               const struct list_elem *b,
               void *aux)
{
    struct frame_entry *fa = list_entry (a, struct frame_entry, elem);
    struct frame_entry *fb = list_entry (b, struct frame_entry, elem);

    return fa->page_num < fb->page_num ? true : false;
}

