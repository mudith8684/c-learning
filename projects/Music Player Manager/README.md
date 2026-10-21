v1:
- This project, labelled "Music Player Manager", is a simple implementation of linked lists to perform operations, with respect to songs. 
- Songs are represented by the struct Node {...}; structure. 
- The program uses a typedef to call the 'struct Song' type with just Song.
- In the struct Song, the variable entries are id, title, artist, duration, and the traversing pointers needed for a doubly linked list.
- The function createSong creates a node of type 'Song'  and returns it.
- There are three forms of insert in this program. 
- Deleting is done by the ID of the song.
- Searching songs is done by two ways:
    a. By title
    b. By artist
- A function, containsIgnoreCase(...), is a helper function to search for songs when inputs are partial or are not in the precise upper or lower case.
- The songs can be displayed in order or in reverse.
- The program is menu-driven.
- Modularization is yet to be done.
