# README GRDECL Processing Script

The script itself is written in the `process.sh` file.

It is recommended to make the `process.sh` file executable:
- Set the file's permissions to be executable by running `chmod +x process.sh`

## Usage

### Patterns File
If the `process.sh` script detects a file named `patterns.txt` in its current working directory,
it will source its replacement patterns from it.

An example `patterns.txt` file can look like this.
```
PCW Pth_x   0
PCW Pth_z   0
PCW Pth_z   0 
```

A single line in a `patterns.txt` follows this format:
```
[What_to_replace] <TAB> [Replace_with] <TAB> [GLOBAL?]
```

Where `[What_to_replace]` is the pattern the script should look for, `[Replace_with]` is the string it will replace the pattern with, and `[GLOBAL?]` is an integer, either 0 or 1.
- A `[GLOBAL?]` value of 0 will cause the script to replace only the first pattern occurrence.
- A `[GLOBAL?]` value of 1 will cause the script to replace all pattern occurrences.

**Patterns are processed in-order.**
- A single-replacement pattern occurring before another will be processed first, allowing the user to replace, e.g., the first occurrence with a unique string before replacing the rest.

### Processing a single file
To convert a single file, run the command as outlined below:
```sh
./process.sh [filename].grdecl [outputname].grdecl
```

**IMPORTANT**: The file suffixes must be supplied.

### Processing a directory

The script supports handling a directory of `.grdecl` files.

```sh
./process.sh [input_directory] [output_directory]
```

If `[output_directory]` does not exist, the script will create it for you.

