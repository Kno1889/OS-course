#include <stdio.h>

#define BUFFER_SIZE 10

#define OFFSET_MASK 0xFFF

#define PAGES 8
#define OFFSET_BITS 12 // bits needed for 4KB page
#define PAGE_SIZE 4096 // 4KB

int page_table[PAGES] = {6, 4, 3, 7, 0, 1, 2, 5};

int main()
{
    FILE *fptr = fopen("labaddr.txt", "r");


    char buff[BUFFER_SIZE];
    while (fgets(buff, BUFFER_SIZE, fptr) != NULL)
    {

        // printf("Logical Address: %s", buff);

        unsigned int virtual_address;
        sscanf(buff, "%u", &virtual_address); 
        // Convert string to unsigned int

        // printf("Logical Address: %d\n", virtual_address);
        
        unsigned page_number = virtual_address >> OFFSET_BITS;
        unsigned int offset = virtual_address & OFFSET_MASK;

        // // Extract frame number from page table
        unsigned int frame_number = page_table[page_number];

        // // Compute physical address using frame number and offset
        unsigned int physical_address = (frame_number << OFFSET_BITS) | offset;

        printf("Logical Address: %d, Page Number: %u, Offset: %u, Physical Address: %d\n", 
        virtual_address, page_number, offset, physical_address);
    }

    fclose(fptr);
    return 0;
}
