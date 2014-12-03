FileCopyThread
==============
Quite often, data within files, or in memory, is structured according to some externally imposed standard. The layout of the bits representing such data is out of the control of a programmer who might in simple applications choose any layout he or she wants. 

An Intel Pentium processor documentation shows how the fields of a Pentium page table entry are fixed. Another example of externally standardized data structures is on-disk file systems. A file system is a system for structuring data that is typically stored on a disk so the familiar features of named hierarchical directories and files can be implemented.

This lab gives you practice with programming with one or more C pointers that point into the region of memory where a Microsoft bitmap (.bmp) file had been read using memory mapping. The pointer ptr will have the type pointer-to-structure. The fields laid out can be easily accessed according to the standard by using the field names in C, with code like ptr->fieldName or ptr[0].fieldName.

The C program analyze.c and accompanying header file bmp.h contains an example for these these techniques.

The execution of analyze.c will produce a blue stripe along the left edge of the image; and you'll see this result with gimp, a free/open source digital picture editing program.
