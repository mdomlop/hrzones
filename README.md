![retrosmart-preview](https://raw.githubusercontent.com/mdomlop/hrzones/master/preview.png "hrzones running")

HRZones
=======

Calculate heart rate training zones, based on Karvonen formula.

Usage:
        hrzones [-a] n1 [n2]

Options:

        n1    An integer positive which is maximun heart rate (or age, if `-a'
              flag is present).
        n2    An integer positive number which is resting heart rate.
              If provided, Karvonen's formula will be used.

        -a    Indicate that `n1' is an age and not the maximum heart rate.
              Therebefore `n1' will be used to calculate the maximum heart 
              rate with the Tanaka's formula.
        -h    Show this help.
        -v    Show program version and exit.

Install
-------

Run:

	make && make install

or

	make arch_pkg && pacman -U *.pkg.*
