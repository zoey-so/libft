*This project has been created as part
of the 42 curriculum by smilch*

# libft – My very first own library

## Description
This project is an implementation of a subset of standard C library functions, plus additional utilities for string handling, memory management, and linked list operations. It is written from scratch in C, as a project for the 42 school and is designed to be lightweight, portable, and efficient as much as I can make it after \< 2months of programming in C. The library is compiled as a static archive (`libft.a`) and can be linked into any C project.



### Features

- **Standard libc replacements** – `atoi`, `bzero`, `calloc`, `mem*`, `str*`, etc.
- **Custom ctype macros** – `isalpha`, `isdigit`, `isalnum`, `isascii`, `isprint`, `isspace` – implemented as macros backed by a precomputed lookup table for maximum performance.
- **Bonus string utilities** – `substr`, `strjoin`, `strtrim`, `split`, `itoa`, `strmapi`, `striteri`, and file descriptor output functions (`putchar_fd`, `putstr_fd`, `putendl_fd`, `putnbr_fd`).
- **Linked list management** – create, add (front/back), size, last, delete one, clear all, iterate, and map a list.

---

## Instructions

The library is built using the provided `Makefile`.

### Requirements
- A C compiler (e.g., `cc`, `gcc`, `clang` - the Makefile uses cc command)
- Standard Unix/Linux environment (for `make` and POSIX headers)

### Build Targets
| Command           | Description |
|-------------------|-------------|
| `make` or `make all` | Compiles the the library into `libft.a` file using `ar rcs` |
| `make clean`      | Removes all object files (`.o`). |
| `make fclean`     | Removes object files and the static library `libft.a`. |
| `make re`         | Runs `fclean` followed by `all`. |

### Example
```bash
git clone <repository>   # or copy the source files
cd libft
make
```

After compilation, the file `libft.a` is created in the current directory. To use it in your project:

```bash
cc -Wall -Wextra -Werror -I . -c my_program.c
cc -o my_program my_program.o -L. -lft
```

Alternatively, you can include `libft.h` in your source files and link with `-lft`.

---

## Function Overview

### Part One – Libc Reimplementations
These functions behave exactly as their standard counterparts (same prototypes and semantics).

| Function       | Description |
|----------------|-------------|
| `ft_atoi`      | Convert a string to an integer. |
| `ft_bzero`     | Write zero bytes to a memory area. |
| `ft_calloc`    | Allocate and zero-initialize memory. |
| `ft_memchr`    | Locate a byte in a memory block. |
| `ft_memcmp`    | Compare two memory areas. |
| `ft_memcpy`    | Copy a memory area. |
| `ft_memmove`   | Copy a memory area with overlap handling. |
| `ft_memset`    | Fill a memory area with a constant byte. |
| `ft_strchr`    | Locate a character in a string. |
| `ft_strdup`    | Duplicate a string. |
| `ft_strlcat`   | Safely concatenate strings (size‑bounded). |
| `ft_strlcpy`   | Safely copy strings (size‑bounded). |
| `ft_strlen`    | Compute the length of a string. |
| `ft_strncmp`   | Compare two strings up to `n` characters. |
| `ft_strnstr`   | Locate a substring in a string with length limit. |
| `ft_strrchr`   | Locate the last occurrence of a character in a string. |
| `ft_tolower`   | Convert a character to lowercase. |
| `ft_toupper`   | Convert a character to uppercase. |

---

### Custom Ctype Macros (Optimised)

The library does not use the standard `<ctype.h>` functions. Instead, it provides **macros** that evaluate to a bit‑mask test on a precomputed lookup table (`g_lup`).
The table is indexed by `(unsigned char)(c + 1)`, which handles all 256 possible byte values and avoids undefined behaviour for negative inputs (EOF).

```c
#define ft_isalpha(c)  ((g_lup[(unsigned char)(c + 1)] & FT_A) != 0)
#define ft_isdigit(c)  ((g_lup[(unsigned char)(c + 1)] & FT_D) != 0)
#define ft_isalnum(c)  ((g_lup[(unsigned char)(c + 1)] & (FT_A | FT_D)) != 0)
#define ft_isascii(c)  (((c) & ~0x7F) == 0)
#define ft_isprint(c)  ((g_lup[(unsigned char)(c + 1)] & FT_P) != 0)
#define ft_isspace(c)  ((g_lup[(unsigned char)(c + 1)] & FT_S) != 0)
```

These macros are defined in `libft.h` and are **inline**, meaning they produce no function‑call overhead.

---

### Part Two – Additional String & Memory Utilities

| Function         | Description |
|------------------|-------------|
| `ft_substr`      | Extract a substring from a string. |
| `ft_strjoin`     | Concatenate two strings into a new allocation. |
| `ft_strtrim`     | Trim characters from the beginning and end of a string. |
| `ft_split`       | Split a string into an array of substrings using a delimiter. |
| `ft_itoa`        | Convert an integer to a string (ASCII). |
| `ft_strmapi`     | Apply a function to each character of a string with its index, producing a new string. |
| `ft_striteri`    | Apply a function to each character of a string (modify in place) with its index. |
| `ft_putchar_fd`  | Write a character to a file descriptor. |
| `ft_putstr_fd`   | Write a string to a file descriptor. |
| `ft_putendl_fd`  | Write a string followed by a newline to a file descriptor. |
| `ft_putnbr_fd`   | Write an integer (as a decimal string) to a file descriptor. |

---

### Linked List Functions

The library includes a simple single‑linked list implementation with the following structure defined in `libft.h`:

```c
typedef struct s_list {
    void          *content;
    struct s_list *next;
} t_list;
```

| Function          | Description |
|-------------------|-------------|
| `ft_lstnew`       | Create a new node with given content. |
| `ft_lstadd_front` | Add a node at the beginning of the list. |
| `ft_lstadd_back`  | Add a node at the end of the list. |
| `ft_lstsize`      | Count the number of nodes in the list. |
| `ft_lstlast`      | Return the last node of the list. |
| `ft_lstdelone`    | Delete a single node (free its content using a `del` function and free the node itself). |
| `ft_lstclear`     | Delete the entire list, freeing all nodes and content. |
| `ft_lstiter`      | Iterate over the list and apply a function to each node’s content. |
| `ft_lstmap`       | Create a new list by applying a function to each node’s content; deletes old content if allocation fails during creation of new list. |

---

## Implementation Notes

- **Memory safety** – All functions that allocate memory (`calloc`, `strdup`, `substr`, `join`, `split`, `itoa`, `lstnew`, `lstmap`) check for `malloc` failure and return `NULL` appropriately.
- **Overflow protection** – `ft_calloc` includes a check to avoid integer overflow when `count * size` would exceed `SIZE_MAX`.
- **Lookup tables** – `ft_tolower` and `ft_toupper` also use precomputed tables (`g_tolower_tab`, `g_toupper_tab`) for optimal speed.
- **Norm compliance** – All source files follow the 42 school coding style (42 Norm).

## Resources

The functions in this library were developed using a combination of `Google / man / the Internet`.

### Manual Pages
The primary resource for understanding the expected behavior, return values, and edge cases of each standard C function was the UNIX manual pages (`man`) on Linux and MacOS.

### Online Documentation and Community Resources
For additional clarification, implementation strategies, and debugging support, the following online resources were used:

- **Stack Overflow / Exchange** – various threads on topics like lookup table optimization, integer overflow detection in `calloc`, functions return values, POSIX compliance, system call usage.
- **GNU C Library Documentation** – for reference on expected edge cases and standards compliance (ISO C90 / C99).
- **42 peer2peer** – collaborative feedback from fellow students.

### AI Assistance
AI (DeepSeek) was utilized to assist in:

- Structuring and formatting this `README.md` document.
- Generating **repeatable, systematic test suites** for validation of the library functions based on cases listed by me.
  These test suites were written in C and used to compare the custom implementations against the original libc functions, doing my best to cover the edge cases. <br>
  **Note:** The test code is part of open repository on GitHub, but is not part of the project submission. The actual implementation of every function in the library was written manually by the project author.

## License

This project is provided as open‑source under the terms of the [MIT License](https://opensource.org/licenses/MIT). Feel free to use, modify, and distribute it in your own projects.

---

*The story so far: in the beginning, the libc was created.*
