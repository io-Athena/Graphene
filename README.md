# Graphene

A simple CLI program that functions as a simple graphing calculator

## Usage

Upon running a list of available functions will be shown:

### 1 - Linear
Graphs a line using the function - ```f(x) = mx + b```

###  2 - Quadratic
Graphs a parabola/quadratic using the function - ```f(x) = a(x-h)² + k```

###  3 - Sine Wave
Graphs a sine wave using the function - ```f(x) = a⋅sin(b(x-c)) + d```

###  4 - Tangent
Graphs a tangent using the function - ```f(x) = a⋅tan(bx)```

## Configuration

The color of any graphed function can be changed

The currently available colors are: Red, Magenta, and Blue

## Installation
Download and extract [Graphene.zip](Graphene.zip)
### Make
Inside the program directory, run ```Make main``` to compile and ```./main``` to run
>Requires GNU/Make
### GCC
Run ```gcc -o main main.c -lm``` to compile and ```./main``` to run
>Requires GCC
### PATH
the project directory can be added to ```PATH``` to make ```main``` exectuable globally
