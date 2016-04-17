## README
Tay Kang Sheng
1000591


INPUT: (Tested and known parameters)
	‘File_Name’ ‘timestepper_type’ ‘tilmestep’ ‘system_type’

	Cloth Mode: 	“./a3 r 0.05 clo”
	Pendulum Mode: “./a3 r 0.05 pen”
	Simple Mode :	“./a3 r 0.05 sim”

	Euler:		“./a3 e 0.01 pen”
	Trapezoidal:	“./a3 t 0.01 pen”
	RK4:		“./a3 r 0.01 pen”


key press:
	’s’ : SWING.
	‘w’ : Toggle wireframe. Smooth shading only when length = 4 and in cloth mode!
	‘r’ : Reset
	’t’ : Toggle between SimpleSystem, PendulumSystem and ClothSystem.
	‘x’ : Extend number of Particles. Only work for PendulumSystem and ClothSystem! Loop from 1 particle to 8 particles.
	‘q’ : WIND!

Never collaborate wth anyone. No help received, tried helping ng ping and nikhil a little.

No References.

Known problems: 
	Smooth shading can only be done with length is 4. Because smooth shading is done with bezier, if length is more than 4, smooth shading has to be done with bspline instead. However i couldn’t make bspline interpolate the first and last point.

Extra Credits:
	1) Random Wind Force
	2) Smooth Shading (When Length == 4)
	3) 4th Order Runge-Kutta time stepper

Physical simulation is quite fun!



