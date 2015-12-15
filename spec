MAX PROGRAM SIZE: 2**16
MEMORY SIZE: 2**16

All registers and memory addresses are integers.

{+-/*} <register1> <register2>

    (Where {+-*/} means any of the operations in it. Replace as needed)

    register2 = register2 {+-*/} register1

} <register>

    Copy value of accumulator to register

> <register> <memory address>

    memory[<memory address>] = <register>

< <register> <memory address>

    <register> = memory[<memory address>]

x <register> <hex value>

    <register> = <hex value>

    Hex value's max length is 8 characters. Intepretation of the value will
    stop if an unrecognised character is seen. (To allow for things like

        xa1337+a

    without having to pad it to 8 characters)

: <label>

    Set a jump point with the specified label. Note that this does not allow
    you to jump forward to skip bits of code (yet), the point is set when the
    label is defined

@ <label>

    Sets the program counter to the point of the label.

    Note that this does technically execute the label again, but this has no
    effect.

? <register> <comp> <register> <label>

    = is equality

    > is greater than

    < is less than

    ! is not equal
    
    Compares the registers using the comparison given. If it is true, jumps to
    the given label. If false, continue as normally.

    Kinda needed for Turing completeness.

d

    Prints out all non-zero registers and memory addresses (as well as the
    accumulator). Useful for debugging.
