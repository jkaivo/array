# array

translate files to C arrays

## Synopsis

`array [-s] [file...]`

## Description

The `array` utility translates its input into C arrays (of type
`unsigned char`) that can then be used (via `#include`) in larger C programs.
This is useful if you need to embed a binary (e.g. an image) or text (e.g.
a template) file and need to ship a program as a single, self-contained
executable.

## Options

The `array` utility conforms to the XBD Utility Syntax Guidelines. It supports
one option:

`-s`	Include an additional identifier in the output indicating
	the size of the array. See STDOUT below for a detailed
	description.

## Operands

The `array` utility supports the following operands:

`file`	A pathname of an input file. If `-` is specified, `array`
	reads from the standard input.

## STDIN

The standard input is used if no `file` operands are provided or if `-` is
specified as an operand.

## Input Files

Input files are treated as raw binary streams, with no requirements on format.

## STDOUT

A definition of a C array of type `unsigned char` and unspecified length, with
members initialized to the bytes of the input file. Each array is named with
the name of the input file, except all non alphanumeric characters (as
identified by the function `isalnum()`) are translated to `_`. If the input
file is the standard input, the name of the array is `stdin`.

If the `-s` option is specified, the standard output also includes the
definition of a size identifier. This identifier has the same name as the
array, suffixed with `_size`, and type `size_t`.

## STDERR

The standard error is used for printing diagnostic messages.

## Output Files

None.

## Extended Description

None.

## Exit Status

0	Successful completion.
>0	An error occurred.

## Consequence of Errors

If one or more input files cannot be opened, `array` will print a diagnostic
message to standard error and that file will not produe any output to
standard output.
