#include "frame.h"
#include <stddef.h>

//struct Frame_table frame_table;


void init_frame_table(size_t pages)
{
    frame_table.pages_cnt.total = pages;
    frame_table.pages_cnt.valid = pages;
    
    list_init(&frame_table.frames);

}

