Please report any bug to the author:

Author: Tuhin Paul

Email: tup500@mail.usask.ca

Phone: 306 880 5494



Last updated: Dec 21, 2016
--------------------------


What this program does:
-----------------------

Calculates LZ entropy rate of a sequence of 2D coordinates whose elements have long data type.

Learn about the LZ entropy rate calculation from the supporting online material for the following paper.
This is not the primary source of the entropy rate equation. In this paper, they mention entropy, not entropy rate.

> Song, Chaoming, Zehui Qu, Nicholas Blumm, and Albert-László Barabási. "Limits of predictability in human mobility." Science 327, no. 5968 (2010): 1018-1021.


### How to compile and link:

>	make

### How to clean:

>	make cleam

### How to run:
	./Debug/lzEntropy <input_file> <input_file_record_count_without_header>


Limitations:
------------

For my project, I needed to calculate entropy rate of a sequence of 2D coordinates. And the coordinate elements are expected to be long data types.
I shall remove limitations on the number of items in each row if I need to - no plan to do it now.

As of now, there is no sanity check for input data types - no plan to update now.

There should be a newline at the end of the input file. I ran this program on linux but this program should run okay on windows/mac.


Naming confusion:
-----------------

Each line is represented as a Row instance. Each line of the input file is stored as a linked list of Row type. In a row, each element is actually a Row instance (as of now).
It probably makes better sense if the elements of a row are named something like cell or node.
For now, I would leave it as it is.

