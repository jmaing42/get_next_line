# get_next_line

getline() alternative

```c
char    *get_next_line(int fd);
```

return line by line, `NULL` on EOF or error

## Usage

because of poor prototype of `get_next_line` function,

it uses `ft_get_line` internally which provides better prototype

- to handle error (was no distinction between EOF and error)
- to handle string containing null characters (provides length)
- to reduce overhead to find context associated with the fd
- to free context for fd at any time (was on EOF or error)

### 1. get_next_line

```c
int main(void)
{
    char    *line;

    line = get_next_line(YOUR_FD);
    while (str) // NULL on... error? EOF? IDK
    { // need strlen (can't handle if with null characters)
        write(STDOUT_FILENO, line, strlen(line));
        free(line);
        line = get_next_line(YOUR_FD);
    }
    return (EXIT_SUCCESS); // not sure
}
```

### 2. ft_get_line

```c
int    main(int argc, char **argv)
{
    t_ft_get_line_context *const    context
        = ft_get_line_context(NULL, YOUR_FD); // initialize context
    char                            *line;
    size_t                          length;

    if (ft_get_line(&line, &length, context))
        return (EXIT_FAILURE); // error
    while (line) // NULL on EOF only, not on error
    {
        write(STDOUT_FILENO, str, length); // use length
        free(str);
        if (ft_get_line(&str, &length, context))
            return (EXIT_FAILURE);
    }
    ft_get_line_context(context, -1); // destroy context
    return (EXIT_SUCCESS);
}
```

## Restrictions

- Norm
- 2 C files
- external functions: `malloc`, `free`, `read`

## Key points

- push/pop context to/from map - $O(1)$ (files)
- split a chunk into massive lines - $O(n)$ (characters)
- join massive chunks into a line - $O(n)$ (characters)

## Why

It was unacceptable to sacrifice performance due to restrictions
