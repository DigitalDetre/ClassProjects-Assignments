"""
Navigation paradigm in PyOpenGL
Needs to have PyOpenGl e.g., pip install pyopengl.
It draws a scene for navigation paradigm to test
if it is possible to transfer it to MALTAB with
Psychtoolbox installed.
Michael Tesar 2017
Ceske Budejovice
"""
# Will need to install PyOpenGL for these libraries to work.
from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys

name = 'Python Test Sphere generation'


"""
Code that is given to you should not be changed.
Only write code in the marked areas.
"""
def main():
	# Setting up window to output on.
	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
	glutInitWindowSize(800, 800)
	glutInitWindowPosition(350, 200)
	glutCreateWindow(name)

	#GL Shader for coloring background and output.
	glClearColor(0.2, 0., 0.2, 1.)
	glShadeModel(GL_SMOOTH)
	
    # Lighting Model
	glEnable(GL_CULL_FACE)
	glEnable(GL_DEPTH_TEST)
	glEnable(GL_LIGHTING)
	lightZeroPosition = [10., 4., 10., 1.]
	lightZeroColor = [1.0, 1.0, 1.0, 1.0]
	glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor)
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1)
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05)
	glEnable(GL_LIGHT0)
	
	#Function to display Spheres.
	glutDisplayFunc(displayscene)
    
	# Camera definition
	glMatrixMode(GL_PROJECTION)
	gluPerspective(40., 1., 1., 40.) #angle, aspect ratio, near clip, far clip.
	glMatrixMode(GL_MODELVIEW)
	gluLookAt(0, 0, 10,# camera position
			  0, 0, 0, # where camera points
			  0, 1, 0) # which direction is up
	glPushMatrix()
	
	# Loop for GLUT
	glutMainLoop()
    
	return

'''
In this function you will be creating your three spheres
to look like the attached image. This is the life giving
molecule you all know as H2O. You will need to have your
center sphere be a white color and be at the center of
the screen. This will then be accompanied by two smaller
spheres that in the top left and right areas of your 
center sphere similar to how the picture shows them.

I would recommend looking into glMaterial for adding
a color to your sphere.
'''
def displayscene():
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
	glPushMatrix()
	'''
		Insert code below:
	'''
	color = [1.0, 1.0, 1.0, 1.0] # White
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color)
	glTranslatef(0.,0.,0.) #move to where we want to put object
	glutSolidSphere(1.,20.,20.) # make radius 1 sphere of res 10x10

	color = [1.0, 0.0, 0.0, 1.0] # Red
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color)
	glTranslatef(-0.5,0.5,0.) #move to where we want to put object
	glutSolidSphere(0.5,20.,20.) # make radius 1 sphere of res 10x10

	color = [1.0, 0.0, 0.0, 1.0] # Red
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color)
	glTranslatef(0.5,0.5,0.) #move to where we want to put object
	glutSolidSphere(0.5,20.,20.) # make radius 1 sphere of res 10x10
	
	'''
		End of code.
    '''
	glPopMatrix()
	glutSwapBuffers()
	return

if __name__ == '__main__':
	main()