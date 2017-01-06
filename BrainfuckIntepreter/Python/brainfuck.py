"""
Created by: Carl-Fredrik Lidgren, AKA Daing100
"""
import numpy as np


class O:
    """
    Contains the operators and other information associated with
    the interpretation of a Brainfuck command.
    """
    add = '+'
    sub = '-'
    movr = '>'
    movl = '<'
    brackl = '['
    brackr = ']'
    outbyte = '.'
    inbyte = ','

    ascii_str = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0¡¢£¤¥¦§¨©ª«¬\xad®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"

    cells = np.zeros(256, np.int8)
    pointer = np.int8(0)
    commands = []

    def clear(self):
        self.cells = np.zeros(256, np.int8)
        self.pointer = np.int8(0)


def get_brack_contents(string, start_pos):
    bcounter = 1
    pos = start_pos + 1
    for char in string[start_pos+1:]:
        if char == '[':
            bcounter += 1
        if char == ']':
            bcounter -= 1
        if bcounter == 0:
            break
        pos += 1
    return (string[start_pos+1:pos], start_pos, pos)


def interpret_string(string, o):
    i = 0
    if "exit" in string:
        return 1
    if "clear" in string:
        o.clear()
        return 2
    while i < len(string):
        if string[i] == O.add:
            o.cells[o.pointer] += 1
        if string[i] == O.sub:
            o.cells[o.pointer] -= 1
        if string[i] == O.movr:
            o.pointer += 1
        if string[i] == O.movl:
            o.pointer -= 1
        if string[i] == O.brackl:
            temp = get_brack_contents(string, i)
            if o.cells[o.pointer] == 0:
                i = temp[2]
            else:
                interpret_string(temp[0], o)
                if o.cells[o.pointer] != 0:
                    i = temp[1]
            continue
        if string[i] == O.outbyte:
            print(O.ascii_str[o.cells[o.pointer]], end="")
        if string[i] == O.inbyte:
            o.cells[o.pointer] = O.ascii_str.find(input('input: '))
        i += 1
    return 0


def main(mode=None, container=None):
    if container is None:
        container = O()
    if mode is None:
        mode = input("Selection (number):\n1) Interpret String\n2) Console Session\n3) Exit\n")
    if int(mode.lower()) == 1:
        inp1 = input("String:\n")
        return_val = interpret_string(inp1, container)
        if return_val == 2:
            container.clear()
            main('1')
        container.commands.append(inp1)
        return container

#
# if __name__ == "__main__":
#     main()
