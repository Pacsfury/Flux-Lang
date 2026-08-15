package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

const (
	PUSH  = 1
	ADD   = 2
	SUB   = 3
	MUL   = 4
	DIV   = 5
	OUT   = 6
	JMP   = 7
	JNZ   = 8
	JIZ   = 9
	POP   = 10
	DUP   = 11
	COUT  = 12
	EQ    = 13
	NEQ   = 14
	LT    = 15
	GT    = 16
	LTE   = 17
	GTE   = 18
	AND   = 19
	OR    = 20
	XOR   = 21
	NOT   = 22
	SHL   = 23
	SHR   = 24
	SCRT  = 25
	SPUSH = 26
	SPOP  = 27
	SRUN  = 28
	SGO   = 29
	SDROP = 30
	SPSH  = SPUSH
)

var program []int
var stack []int
var substacks map[int][]int
var activeSubstack int = -1
var pc int = 0

func init() {
	bytes, err := os.ReadFile("program.gosb")
	if err != nil {
		fmt.Println("Error reading file:", err)
		os.Exit(1)
	}

	text := string(bytes)

	text = strings.ReplaceAll(text, "{", " ")
	text = strings.ReplaceAll(text, "}", " ")
	text = strings.ReplaceAll(text, ",", " ")

	opcodes := map[string]int{
		"PUSH": PUSH, "ADD": ADD, "SUB": SUB, "MUL": MUL, "DIV": DIV,
		"OUT": OUT, "JMP": JMP, "JNZ": JNZ, "JIZ": JIZ, "POP": POP,
		"DUP": DUP, "COUT": COUT, "EQ": EQ, "NEQ": NEQ, "LT": LT,
		"GT": GT, "LTE": LTE, "GTE": GTE, "AND": AND, "OR": OR,
		"XOR": XOR, "NOT": NOT, "SHL": SHL, "SHR": SHR,
		"SCRT": SCRT, "SPUSH": SPUSH, "SPOP": SPOP, "SRUN": SRUN, "SGO": SGO, "SDROP": SDROP,
		"SPSH": SPUSH,
	}

	tokens := strings.Fields(text)

	for _, token := range tokens {
		upperToken := strings.ToUpper(token)

		if op, isOpcode := opcodes[upperToken]; isOpcode {
			program = append(program, op)
		} else {
			val, err := strconv.Atoi(token)
			if err != nil {
				fmt.Printf("Syntax Error: Unknown command or invalid number '%s'\n", token)
				os.Exit(1)
			}
			program = append(program, val)
		}
	}
}
