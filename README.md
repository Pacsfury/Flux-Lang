# Flux: a functional language

## What is Flux
Flux is my new programming language, this time oriented to functional programming, more precisely, everything in Flux is a data flux, as seen in the example section.

## Status
Flux has **just been started**, with today the first movement to stdout being done.

## Example
For printing to screen, you can use the left copy operator (<) to move a data to **@stdout**.
```
@stdout < "Hi"
```

Then, you can execute the VM:

```bash
cd vm
go run .
```

it will output:
```
"Hi"
```

## Future features
Coming soon