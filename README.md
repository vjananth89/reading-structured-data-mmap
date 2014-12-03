reading-structured-data-mmap
==============
Quite often, data within files, or in memory, is structured according to some externally imposed standard. The layout of the bits representing such data is out of the control of a programmer who might in simple applications choose any layout he or she wants. 

An Intel Pentium processor documentation shows how the fields of a Pentium page table entry are fixed. Another example of externally standardized data structures is on-disk file systems. A file system is a system for structuring data that is typically stored on a disk so the familiar features of named hierarchical directories and files can be implemented.

This lab gives you practice with programming with one or more C pointers that point into the region of memory where a Microsoft bitmap (.bmp) file had been read using memory mapping. The pointer ptr will have the type pointer-to-structure. The fields laid out can be easily accessed according to the standard by using the field names in C, with code like ptr->fieldName or ptr[0].fieldName.

The C program analyze.c and accompanying header file bmp.h contains an example for these these techniques.

The execution of analyze.c will produce a blue stripe along the left edge of the image; and you'll see this result with gimp, a free/open source digital picture editing program.

How to compile and run
=====================

Once you have downloaded these files to your file folder, execute the command below. This command should work:
```
gcc analyze.c -I apue.2e/include apue.2e/lib/libapue.a -pthread -o analyze
```

Verify that *./analyze* they copies a named file into another named file. Verify with copying *Untitled.bmp* to some other name with the *.bmp* extension.

More information
=================

Now, Stevens (who wrote the code with which I have made changes to) specified that the segment mapping the original file be READ-ONLY, and of course, the segment that maps the copy be READ-WRITE. *Therefore, if you simply use the reading references in my analyze() function to write (say with prow[1].blue = 37; ) there will be a segmentation fault!* The code opening the destination file with read-write access and giving the destination segment read-write access is
```
open(argv[2], O_RDWR | O_CREAT | O_TRUNC,FILE_MODE);

mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0);
```
Therefore, the changes you program must be to the COPIED file, which is mapped to the "destination" segment.

Specifically, you must put the code to make the blue stripe AFTER the memcpy() and BEFORE the exit() calls!

You can take advantage of the fact that exit() causes all open files to be closed. Therefore, the pages of the destination segment that were made dirty by your code's blue-setting will be written to disk as a result of your process calling exit().


