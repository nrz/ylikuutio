#!/usr/bin/awk -f
BEGIN{
    # This program generates source list to be used in `CMakeLists.txt`
    # or elsewhere using `foo.txt` produced by `make >foo.txt 2>&1` as input.

    array_index = 0;
    split("", dir_array);
    current_dir = "";
    new_filename = "";
    current_filename = "";
    entering_directory_regex = "Entering directory '";
    cpp_regex = "\\<[a-zA-Z0-9_-]+\\.cpp\\>";
    c_regex = "\\<[a-zA-Z0-9_-]+\\.c\\>";
} # BEGIN

function get_filename()
{
    # OK, there's a `.cpp` file on this line.
    cpp_filename = substr($0, RSTART, RLENGTH);
    new_filename = current_dir "/" cpp_filename;

    if (new_filename != current_filename && new_filename != "")
    {
        current_filename = new_filename;

        # find out if there's a matching source file.
        if (system("test -f " current_filename) == 0)
        {
            # print the filename.
            print current_filename;
        }

        # find out if there's a matching `*.h` header file too.
        header_filename = gensub(/(^.*\.)c(|pp)$/, "\\1h", "g", current_filename);

        if (system("test -f " header_filename) == 0)
        {
            # header exists, so print its filename too!
            print header_filename;
        }
    }
}
{
    entering_directory_match_index = match($0, entering_directory_regex);
    cpp_match_index = match($0, cpp_regex);
    c_match_index = match($0, c_regex);

    if (entering_directory_match_index > 0)
    {
        # OK, we are entering a new directory on this line.
        junk_part_length = entering_directory_match_index + length(entering_directory_regex);

        # read current dir.
        current_dir = substr($0, junk_part_length, length($0) - junk_part_length);

        # store current dir into array.
        dir_array[array_index++] = current_dir "/";
    }
    else if (cpp_match_index > 0)
    {
        match($0, cpp_regex); # update `RSTART` & `RLENGTH`.
        get_filename();
    }
    else if (c_match_index > 0)
    {
        match($0, c_regex); # update `RSTART` & `RLENGTH`.
        get_filename();
    }
}
END{
    asort(dir_array);

    print "";
    print "include_directories(";

    for (i in dir_array) print dir_array[i];
} # END
