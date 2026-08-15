package main

import "fmt"

func isOpcode(value int) bool {
	switch value {
	case PUSH, ADD, SUB, MUL, DIV, OUT, JMP, JNZ, JIZ, POP, DUP, COUT, EQ, NEQ, LT, LTE, GT, GTE, AND, OR, XOR, NOT, SHL, SHR, SCRT, SPUSH, SPOP, SRUN, SGO, SDROP:
		return true
	default:
		return false
	}
}

func ensureSubstack(id int) []int {
	if substacks == nil {
		substacks = make(map[int][]int)
	}
	if _, ok := substacks[id]; !ok {
		substacks[id] = []int{}
	}
	return substacks[id]
}

func currentSubstack() []int {
	if activeSubstack < 0 {
		activeSubstack = 0
	}
	return ensureSubstack(activeSubstack)
}

func runOnSubstack(id int, opcode int) {
	target := ensureSubstack(id)
	for _, item := range target {
		stack = append(stack, item)
		switch opcode {
		case OUT:
			fmt.Println(stack)
		case POP:
			if len(stack) > 0 {
				stack = stack[:len(stack)-1]
			}
		case DUP:
			if len(stack) > 0 {
				stack = append(stack, stack[len(stack)-1])
			}
		case COUT:
			if len(stack) > 0 {
				fmt.Print(string(rune(stack[len(stack)-1])))
			}
		case NOT:
			if len(stack) > 0 {
				value := stack[len(stack)-1]
				stack = stack[:len(stack)-1]
				stack = append(stack, ^value)
			}
		}
	}
}

func execute(op int, pcIndex int) int {
	switch op {
	case PUSH:
		stack = append(stack, program[pcIndex+1])
		return pcIndex + 2
	case ADD:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		b := stack[len(stack)-2]
		stack = stack[:len(stack)-2]
		stack = append(stack, a+b)
		return pcIndex + 1
	case SUB:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		b := stack[len(stack)-2]
		stack = stack[:len(stack)-2]
		stack = append(stack, a-b)
		return pcIndex + 1
	case MUL:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		b := stack[len(stack)-2]
		stack = stack[:len(stack)-2]
		stack = append(stack, a*b)
		return pcIndex + 1
	case DIV:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		b := stack[len(stack)-2]
		if b == 0 {
			return pcIndex + 1
		}
		stack = stack[:len(stack)-2]
		stack = append(stack, a/b)
		return pcIndex + 1
	case OUT:
		fmt.Println(stack)
		return pcIndex + 1
	case JMP:
		return program[pcIndex+1]
	case JNZ:
		condition := stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		if condition != 0 {
			return program[pcIndex+1]
		}
		return pcIndex + 2
	case JIZ:
		condition := stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		if condition == 0 {
			return program[pcIndex+1]
		}
		return pcIndex + 2
	case POP:
		if len(stack) > 0 {
			stack = stack[:len(stack)-1]
		}
		return pcIndex + 1
	case DUP:
		if len(stack) > 0 {
			stack = append(stack, stack[len(stack)-1])
		}
		return pcIndex + 1
	case COUT:
		if len(stack) > 0 {
			fmt.Print(string(rune(stack[len(stack)-1])))
		}
		return pcIndex + 1
	case EQ:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		result := 0
		if stack[len(stack)-1] == stack[len(stack)-2] {
			result = 1
		}
		stack = stack[:len(stack)-2]
		stack = append(stack, result)
		return pcIndex + 1
	case NEQ:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		result := 1
		if stack[len(stack)-1] != stack[len(stack)-2] {
			result = 0
		}
		stack = stack[:len(stack)-2]
		stack = append(stack, result)
		return pcIndex + 1
	case LT:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		result := 0
		if stack[len(stack)-2] < stack[len(stack)-1] {
			result = 1
		}
		stack = stack[:len(stack)-2]
		stack = append(stack, result)
		return pcIndex + 1
	case GT:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		result := 0
		if stack[len(stack)-2] > stack[len(stack)-1] {
			result = 1
		}
		stack = stack[:len(stack)-2]
		stack = append(stack, result)
		return pcIndex + 1
	case LTE:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		result := 0
		if stack[len(stack)-2] <= stack[len(stack)-1] {
			result = 1
		}
		stack = stack[:len(stack)-2]
		stack = append(stack, result)
		return pcIndex + 1
	case GTE:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		result := 0
		if stack[len(stack)-2] >= stack[len(stack)-1] {
			result = 1
		}
		stack = stack[:len(stack)-2]
		stack = append(stack, result)
		return pcIndex + 1
	case AND:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		b := stack[len(stack)-2]
		stack = stack[:len(stack)-2]
		stack = append(stack, a&b)
		return pcIndex + 1
	case OR:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		b := stack[len(stack)-2]
		stack = stack[:len(stack)-2]
		stack = append(stack, a|b)
		return pcIndex + 1
	case XOR:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		b := stack[len(stack)-2]
		stack = stack[:len(stack)-2]
		stack = append(stack, a^b)
		return pcIndex + 1
	case NOT:
		if len(stack) < 1 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		stack = append(stack, ^a)
		return pcIndex + 1
	case SHL:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		b := stack[len(stack)-2]
		stack = stack[:len(stack)-2]
		stack = append(stack, a<<b)
		return pcIndex + 1
	case SHR:
		if len(stack) < 2 {
			return pcIndex + 1
		}
		a := stack[len(stack)-1]
		b := stack[len(stack)-2]
		stack = stack[:len(stack)-2]
		stack = append(stack, a>>b)
		return pcIndex + 1
	case SCRT:
		id := program[pcIndex+1]
		ensureSubstack(id)
		activeSubstack = id
		return pcIndex + 2
	case SPUSH:
		if len(stack) == 0 {
			return pcIndex + 1
		}
		value := stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		target := ensureSubstack(activeSubstack)
		target = append(target, value)
		substacks[activeSubstack] = target
		return pcIndex + 1
	case SPOP:
		target := ensureSubstack(activeSubstack)
		if len(target) == 0 {
			return pcIndex + 1
		}
		value := target[len(target)-1]
		target = target[:len(target)-1]
		substacks[activeSubstack] = target
		stack = append(stack, value)
		return pcIndex + 1
	case SRUN:
		var targetID int = activeSubstack
		var opcode int
		if pcIndex+1 >= len(program) {
			return pcIndex + 1
		}
		next := program[pcIndex+1]
		if isOpcode(next) {
			opcode = next
		} else {
			targetID = next
			if pcIndex+2 >= len(program) {
				return pcIndex + 1
			}
			opcode = program[pcIndex+2]
			if !isOpcode(opcode) {
				opcode = next
				targetID = activeSubstack
			}
		}
		if !isOpcode(opcode) {
			return pcIndex + 1
		}
		runOnSubstack(targetID, opcode)
		if isOpcode(program[pcIndex+1]) {
			return pcIndex + 2
		}
		return pcIndex + 3
	case SGO:
		id := program[pcIndex+1]
		ensureSubstack(id)
		activeSubstack = id
		return pcIndex + 2
	case SDROP:
		id := program[pcIndex+1]
		delete(substacks, id)
		if activeSubstack == id {
			activeSubstack = -1
		}
		return pcIndex + 2
	default:
		return pcIndex + 1
	}
}
