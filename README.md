#rshell
rshell is a command shell written in C++. rshell mimics the bash terminal, starting with the `username@hostname$` and reading in commands given by the user. Multiple commands are allowed on a single line, and whether they are executed or not are determined by the connectors between the commands. 

##Additional Features

###Precedence Operators
In addition to logical operators such as && || and ; in the original bash, rshell also emulates bash with its precedence operators, or parentheses. The parentheses () operators are used to change the priority of certain commands in a single line, altering whether certain commands are executed. 
For example, while
`$ echo A && echo B || echo C && echo D`
would print
```
A
B
D
```
Using parentheses,
`$ (echo A && echo B) || (echo C && echo D)
would print
```
A
B
```

###The Test Command
rshell contains an additional command, the test command, not available in the original bash. The test command accepts up to two inputs, a flag and a path `test/file/path`. The test returns whether the path is a valid one from either the home directory or the current relative directory. The command returns one of two values, (True) or (False). The flag returns further information regarding whether the path leads to a file or a directory. 

For example:
`-e` checks if the file/directory exists.
`-f` checks if the file/directory exists and is a regular file.
`-d` checks if the file/directory exists and is a directory.

There are two ways to format the test command, both of which will return the same value:

`$ test -e test/file/path`
or:
`$ [ -e test/file/path ]

In addition, the test command works with all logic operators and precedence operators (). 

##Installation
To load the program, run the following code in your terminal:

```
$ git clone https://github.com/aminwatad/rshell.git
$ cd rshell
$ git checkout hw2
$ make
$ bin/rshell
```
##Limitations
* The program handles a hostname up to 29 characters.
* The program handles a username up to 19 characters.
* The user can enter up to 40 words command.

##Known Bugs

* `echo "hello"` does not produce `hello` as the original bash terminal does. It produces `"hello"`.

If there are any additional bugs discovered please feel free to let us know to further improve this program. Thank you!
