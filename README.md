# minishell_1

## Project Description
This project is the first stepping stone
to creating my own shell.

## Compile Instructions
To compile the standard version of minishell_1,
simply run make:

```bash
make
```

To compile a version with debug symbols enabled,
use the ``debug`` rule:

```bash
make debug
```

To compile a version with an address sanitizer enabled,
use the ``sanitize`` rule:

``` bash
make sanitize
```

When you're done, you can use the ``clean`` rule
to delete any temporary files, or the ``fclean``
rule to delete all compiled files.
