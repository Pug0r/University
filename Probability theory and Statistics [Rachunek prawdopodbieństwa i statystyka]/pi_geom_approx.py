import turtle
import random
from math import sqrt

CIRCLE_RADIUS = 250


def draw_square(length):
    if length < 0:
        return -1
    diagram_turtle.forward(length / 2)
    diagram_turtle.left(90)
    diagram_turtle.forward(length)
    diagram_turtle.left(90)
    diagram_turtle.forward(length)
    diagram_turtle.left(90)
    diagram_turtle.forward(length)
    diagram_turtle.left(90)
    diagram_turtle.forward(length / 2)


def random_coord():
    ''' Returns a pair of random cooridnates in range <-1; 1>'''
    global inside
    sign = (-1, 1)
    x = random.random() * random.choice(sign)
    y = random.random() * random.choice(sign)
    if sqrt(x**2 + y**2) < 1.0:
        inside += 1
    return x, y


def normalize_coord(pair_of_coord):
    return pair_of_coord[0] * CIRCLE_RADIUS, pair_of_coord[1] * CIRCLE_RADIUS


def write_info(dots, pi_approx):
    info_turtle.clear()
    info_turtle.penup()
    info_turtle.goto(-300, -300)
    info_turtle.pendown()
    info_turtle.write("Dots: " + str(dots), move=False, align='left', font=('Arial', 8, 'normal'))
    info_turtle.penup()
    info_turtle.goto(150, -300)
    info_turtle.pendown()
    info_turtle.write("Current Pi approximation: " + str(pi_approx)[:11], move=False, align='left', font=('Arial', 8, 'normal'))


turtle.title("Approximation of pi")
diagram_turtle = turtle.Turtle()
diagram_turtle.hideturtle()

info_turtle = turtle.Turtle()
info_turtle.hideturtle()
turtle.tracer(False)


diagram_turtle.goto(0, -250)
diagram_turtle.circle(CIRCLE_RADIUS)
draw_square(2*CIRCLE_RADIUS)
diagram_turtle.color('red')

random.seed()

dots = 0
inside = 0


while True:
    diagram_turtle.penup()
    diagram_turtle.goto(normalize_coord(random_coord()))
    diagram_turtle.pendown()
    diagram_turtle.dot()
    dots += 1
    if not dots % 100:
        write_info(dots, 4*(inside)/dots)
    turtle.update()

turtle.Screen().exitonclick()