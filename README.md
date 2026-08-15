# Flux: a functional language

> **WARNING**: Flux is in an indev stage. It may be unstable or bug prose.

## What is Flux
Flux is my new programming language, this time oriented to functional programming, more precisely, everything in Flux is a data flux, as seen in the example section.

## Status
Flux has **just been started**, with today the first movement to stdout being done.

## Example
For printing to screen, you can use the left copy operator (< and >) to move a data to **@stdout**.

`main.flxx`:
```
@stdout < "Hi,";
"Flux" > @stdout;
```

Then, you can execute the VM:

```bash
flux run main.flxx 
```

_Change "flux" to the actual executable_

it will output:
```
Hi,Flux
```

## Known bugs
- Doesnt detect strings with spaces correctly

## What are stdregs
Stdregs is the way Flux's standard variables are called. 

A example of a stdreg is **@stdout** and future **@stdin**.

## Future features

**Operators**:
->: right move (copy & delete)
<-: right move (copy & delete)

**Stdregs**:
@stdin

**Functionalities**:
- Variable saving and retrieving
