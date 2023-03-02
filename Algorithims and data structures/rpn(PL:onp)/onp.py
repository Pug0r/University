import operator
from math import sqrt


def reverse_polish_notation(expression: str) -> str:
    string_to_operator = {'+': operator.add,
                          '-': operator.sub,
                          '*': operator.mul,
                          '/': operator.truediv,
                          'sqrt': sqrt,
                          '^': operator.pow}
    stack = []
    cleaned_expression = expression.split()

    for symbol in cleaned_expression:
        if symbol.isnumeric():
            stack.append(symbol)

        elif symbol in list(string_to_operator.keys()):
            if symbol == 'sqrt':
                stack.append(sqrt(float(stack.pop())))
                continue
            try:
                right_element = float(stack.pop())
                left_element = float(stack.pop())
            except IndexError:
                raise ValueError('That sequence is not valid reverse polish notation')

            try:
                result = string_to_operator[symbol](left_element, right_element)
            except ZeroDivisionError:
                raise ValueError('Division by zero occurs in this sequence')
            stack.append(result)

        else:
            raise ValueError(f'Illegal symbol found in the expression: {symbol}')

    return stack[0]


if __name__ == '__main__':
    TEST = reverse_polish_notation('1 5            2 1 * * *')
    print(TEST)
