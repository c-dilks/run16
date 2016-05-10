GUI MAP
-------
Execute `root GUI_MAP.C` for a GUI look-up table of channel
coordinates. Type in a full row of coordinates, then
click `Obtain Coordinates` to obtain information about the 
requested channel; if successful, all the other fields will
be filled in with that channel's info, and the cells current
voltage, gain, bitshift, and mask will be printed in the 
status line.

If it says `ERROR: too many entries`, you have more than one
completed row; click `Clear` and only enter 1 row

If it says `ERROR: too few entries`, you have not entered
a complete row of information

If it says `[hvtr error]` or `[qtbstr error]`, there are problems
reading the data tables for the current iteration (the files 
of the current iteration are copied to `current_iteration/`


SCRIPT CHAIN
------------
- `mk_tree.C : FULL_MAP --> geotr.root`
- `draw.C : geotr.root --> maps.root`
- `print.C : maps.root --> maps.pdf`
- `mk_table.C : geotr.root --> table_{large,small}.txt`


MAKING MAP CHANGES
------------------
- make your changes in:
  - `FULL_MAP`
  - `excel_{small,large}.ods` (and print new pdfs)
  - In Thomas's code:
    - `fmsvoltages2015/tables/2015fmsCellInfoTable.txt`
- then run the scripts listed above in the script chain
- execute: `print_unused_lecroy_channels.C > unused_list.txt`
  - remove first two lines
  - move `unused_list.txt` to `../voltage_stability/unused_list.txt`

