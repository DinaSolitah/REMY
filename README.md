# REMY Maze Solver

REMY Maze Solver is Line Maze solving robot which uses the LSRB Algorithm to solve the maze
<br>
<br>
This is the algorithm by which the robot solves the maze. In "LSRB" L stands for 'LEFT', S for 'STRAIGHT', R for RIGHT, and B for 'BACK' or BACKWARD. These LEFT, RIGHT, STRAIGHT, and BACK are the directions that the robot follows. 

<br>
<br>
This Algorithm is simply is:
<br>
- Step 1: Always follow LEFT whenever there is a turn possible
<br>
- Step 2: If LEFT is not possible go STRAIGHT.
<br>
- Step 3: If LEFT and STRAIGHT both are not possible take RIGHT.
<br>
- Step 4: if LEFT, STRAIGHT, and RIGHT are not possible go BACK( or it means take a U-Turn)
