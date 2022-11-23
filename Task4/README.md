**ls**
there were problems with the flag -R - memory is not allocated dynamically, the rest of the flags and ls work fine

**cmp**
compares two files, provides information about the first difference in files

**cp**
copies the first file to the address of the second
one, while the first argument cannot be a directory, and if the second directory, the file is copied to the specified directory

**echo**
Flags are possible: -e -E enabling and disabling escaping of escape sequences
And the flag -n: with which the last \n is not displayed

**pwd**
Implemented using getcwd - returns the absolute path of the current folder

**tail**
Outputs the last 10 lines of the file by default, or the last n, with a flag -n. Or all lines starting from n to the end with a flag +n.
Character - by - character implementation

