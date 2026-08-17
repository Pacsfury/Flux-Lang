# Flux: a functional language

> **WARNING**: Flux is in an indev stage. It may be unstable or bug prose.

## What is Flux
Flux is my new programming language, this time oriented to functional programming, more precisely, everything in Flux is a data flux, as seen in the example section.

## Status
Flux has **just been started**, with today the first movement to stdout being done.

## Build and execute using Python

**Building the executable**:
1. Go to `build.py` amd add a funtion call at the end, like this:
```python
build("yourcompiler") # Default compiler is g++
```
2. Once compiled, you can execute a `.flxx` file:
```python
execute(compiler="yourcompiler", filename="abc.flxx") # There are other default fields, full info at build.py
```

## Syntax

### Copying

`a<b`, `b>a`

In both `a == b`.

### Moving
`a<-b`, `b->a`

### Comments

```
a / A comment here is valid / < b;
/ Here too/
/You can put them anywhere (not inside of a string) /
```

In both, `b` dissappears.

## Example
For printing to screen, you can use the left copy operator (< and >) to move a data to **@stdout**.

`main.flxx`:
```
@stdout < "Hi,";
"Flux" > @stdout;
```
Now, you can also save and use variables, so we will make another example:

`main.flxx`:
```
/ This is a comment /
@stdout < "Hi, ";
"Flux" > / You can put comments here/ @stdout;
variable < ", Welcome";
@stdout < variable;
```

Then, you can execute the code:

```bash
flux run main.flxx 
```

_Change "flux" to the actual executable_

it will output:
```
Hi, Flux, Welcome
```

## Known bugs
- **"I'm" > " OK" > ", thanks" > @stdout;** Doesnt work left-to-right

**Last Fixed:** Doesn't detect strings with spaces correctly

## What are stdregs
Stdregs is the way Flux's standard variables are called. 

A example of a stdreg is **@stdout** and future **@stdin**.

## Future features

**Operators**:
*None*

**Stdregs**:
@stdin

