# Hackertyper

Hackertyper is a c program which copies the functionality of http://hackertyper.net, reading characters from a file, and writing said characters to stdout.

# Requirements

* make
* ncurses

On linux and mac, you almost definitely have these. On Windows, you probably don't

# Installation
    make
    sudo make install


# Testing
To test this program without installing, run the command
    `make DATADIR=data`

Note that if this commmand is used, then the file must be recompiled without this option to be installed


