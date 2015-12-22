# Program components #
# Components interactions #
| | control | interpreter | map | mapui | program | programui | framework (vc60) |
|:|:--------|:------------|:----|:------|:--------|:----------|:-----------------|
| control | -       |             |     |       |         |           |                  |
| interpreter |         | -           | execute command |       | get command |           |                  |
| map |         |             | -   | draw map |         |           |                  |
| mapui |         |             | change (from framework)| -     |         |           | draw in GUI      |
| program |         |             |     |       | -       | inform about changes |                  |
| programui |         |             |     |       | take program | -         | draw in GUI      |
| framework (vc60) |         |             |     | inform about changes |         | inform about changes| -                |

# Components responsibility #
| | control | interpreter | map | mapui | program | programui | framework (vc60) |
|:|:--------|:------------|:----|:------|:--------|:----------|:-----------------|
| Редактирует код |         |             |     |       |         | x         | x                |
| Сохраняет/удаляет |         |             |     |       |x        |           |                  |
| Выделяет несколько команд |         |             |     |       |         |           | x                |
| Сtrl + Z (для кода) |         |             |     |       |         |           |                  |
| Знает, где роботы |         |             | x   |       |         |           |                  |
| Рисует поле |         |             | х   |       |         |           |                  |
| Рисует робота |         |             | x   |       |         |           |                  |
| Знает о стиле поля |         |             | х   |       |         |           |                  |
| Генерирует случайное поле |         |             | х   |       |         |           |                  |
| Сохраняет/открывает поле  |         |             | х   |       |         |           |                  |
| Управляет скоростью |         |             | x   |       |         |           |                  |
| Работает с тестами |         |             |     |       |         |           |                  |
| Ctrl + Z (для выполнения) |         |             | х    |       |         |           |                  |
| Выполняет код |         | x           |     |       |         |           |                  |
| Хранит список доступных команд |         | x           | ?   |       |         |           |                  |
| -|- условий |         | x           | ?   |       |         |           |                  |
| -|- направлений |         | x           | ?   |       |         |           |                  |

# Components notes #

From UI perspective:
ProgramWindow - holds a list of commands, doesn't know about program as a whole, all events are about commands
Application - manages known programs, doesn't know about separate commands. Now we limit program to one file.
MapUI - is able to show robots, cells and walls with perfect view, show move "video".

Model perspective:
Program - knows that the program is a set of procedures, including "main" one, knows about types of commands and their hierarchical structure. Has no ideas on how to execute program.
Map - is aware about list of possible commands (though some commands will lead to "beep" for some cells). Map surely knows about topology of walls, margins, current state of cells, list of robots, their current positions.
Interpreter - knows what Map methods to call to execute given command, what command is to be executed next.