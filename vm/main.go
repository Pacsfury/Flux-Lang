package main

func main() {
	for pc < len(program) {
		pc = execute(program[pc], pc)
	}
}
