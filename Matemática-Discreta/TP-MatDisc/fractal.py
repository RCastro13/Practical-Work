import turtle
import math
import tkinter as tk
from PIL import Image, ImageTk

window = turtle.Screen()
window.title("Fractal com Turtle")

def draw_fractal(fractal_str, step_length, angle):
    for move in fractal_str:
        if move == "F" or move == "S" or move == "R":
            pen.forward(step_length)
        elif move == "+":
            pen.right(angle)
        elif move == "-":
            pen.left(angle)

with open("arq1.txt", "r") as file:
    lines = file.readlines()
    fractal_string = lines[0].strip()
    angle = float(lines[1])
    fractal_number = int(lines[2].strip())

if fractal_number == 1:
    window.setworldcoordinates(-300,-1000,2600,1200)
elif fractal_number == 2:
    window.setworldcoordinates(-100,-100,300,300)
elif fractal_number == 3:
    window.setworldcoordinates(-50,-200,200,100)

step_length = 10

pen = turtle.Turtle()
pen.speed(0)
pen.width(1)

draw_fractal(fractal_string, step_length, angle)
# Capturar a tela de desenho
ts = pen.getscreen()
ts.getcanvas().postscript(file="fractal.eps")
# Converter o arquivo EPS para PNG usando a biblioteca Pillow
image = Image.open("fractal.eps")
image.save("fractal.png", "PNG")
image.show()