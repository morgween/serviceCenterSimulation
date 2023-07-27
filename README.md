# Student Services Center Simulation
This project simulates the operation of a Student Services Center (SSC) that houses the registrar, cashier, and financial aid offices. The simulation aims to calculate metrics on student wait times and window idle times given a specific traffic flow of students through the SSC.


# Simulation Input:
    The input to the simulation is provided through a text file. The file format is as follows:

    <Number of Registrar Windows>
    <Number of Cashier Windows>
    <Number of Financial Aid Windows>
    <Next Student Arrival Time>
    <Number of Students>
    <Student1 Registrar Time> <Student1 Cashier Time> <Student1 Financial Aid Time> <Student1 Office Order>
    <Student2 Registrar Time> <Student2 Cashier Time> <Student2 Financial Aid Time> <Student2 Office Order>
    ...
    <Next Student Arrival Time>
    <Number of Students>
    <Student1 Registrar Time> <Student1 Cashier Time> <Student1 Financial Aid Time> <Student1 Office Order>
    <Student2 Registrar Time> <Student2 Cashier Time> <Student2 Financial Aid Time> <Student2 Office Order>
    ...
    END


# Simulation Output:
    At the end of the simulation, the program will display the following metrics for each office:

    Mean student wait time
    Longest student wait time
    Mean window idle time
    Longest window idle time
    Additionally, the program will display the following overall metrics across all offices:

    Number of students waiting over 10 minutes
    Number of windows idle for over 5 minutes
   The output will be displayed on the standard output.
# Usage:
    To run the simulation, follow these steps:

    • Compile the code using a C++ compiler.
    • Execute the compiled program, providing the input specification file as a command-line argument.
    • Example command: ./simulation *filePath*/input.txt

    

