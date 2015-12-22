## free-style requirements ##
  * User-oriented [Requirements](Requirements2.md).
  * [Full version](Requirements2.md)

## phased implementation requirements ##

PHASE 1.

limitations:

  1. one-file program
  1. linear program only - commands are "paint" and "move"
  1. no interpreter working, no map shown

program scenarios:

  1. open/save/close program
  1. add/delete/update operators in required position
  1. set operator parameters
  1. full-featured standard Windows operations in main window

## previous contents ##
# 1. Working version #
  1. Robot program editing (Commands: moving + painting, "while", "if")
  1. Robot program saving/opening (in good format)
  1. Changing place of Robot
  1. Changing type of each wall(Absent/Present), each cell(printed, unprinted)
  1. Running program
  1. Changing speed while running program
  1. Some error message with going throw the wall
# 2.School-suitable version #
> Working version +
  1. Using functions in Robot program
  1. Any-levels conditions (if(!((A&B)&((!C)|(D...)))))