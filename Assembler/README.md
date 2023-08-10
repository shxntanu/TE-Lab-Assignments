# Pass 1 Assembler

`pass1.py` : Assembler code

## Input Files

`program.asm` : Test assembly file

`mnemonics.json` : Mnemonics Table

`mnemonic-size.json` : Mnemonic Size Table

`condition-codes.json` : Condition codes table

`directives.json` : Directives Table

`registers.json` : Registers Table

## Output Files

`ic.txt` : Intermediate Code file

`symbols.json` : Symbol Table

`literals.json` : Literal Table

## Structures

1. Symbol Table
```
{
  symbol : [
    symbol-index,
    symbol,
    line-count-location
  ],
  ...
}
```
2. Literal Table
```
{
  literal-index : [
    literal-index,
    literal,
    line-count-location
  ],
  ...
}
```
