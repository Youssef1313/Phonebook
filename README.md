# Phonebook Project in C

My final project for programming 1 course.

**Note:** This project is built using Visual Studio IDE. It might not work in other IDEs like CodeBlocks without a slight modifications.

## Coding style

- Use PascalCase for functions (except for `main`), structs, and unions names.
- Use camelCase for function parameters, local variables, structs members, and unions members.
- Use ALL_UPPER_CASE_WITH_UNDERSCORE to define macros.
- Prefix pointer variables with `p`. For example, `Date *pBirthDate`, not `Date *birthDate`. `char *` is an exception if the variable name is obvious to be a string.
- Use allman braces. Curly braces should be put in their own line.
- Use 4 spaces indentation instead of a tab. To let Visual Studio do that for you, **Tools** > **Options** > **Text Editor** > **C/C++** > **Tabs** > **Insert spaces**.

## Colored output

The printed output should be shown in colors. If you're getting strange characters at the beginning of the `printf`s, You'll need to run the following command in the cmd and re-open the program:

```
REG ADD HKCU\CONSOLE /f /v VirtualTerminalLevel /t REG_DWORD /d 1
```

> Credits goes to [this answer](https://stackoverflow.com/a/56150498/5108631) on stackoverflow.

**Another solution** is to run the *EnableColors.bat* file besides this *README.md* file. It will automatically run the previous command and enable the ANSI escape code in the registry.

## User manual

Before you start using the program, please, read the user manual (*User-manual.pdf*) file to get an idea on how to use this program.
