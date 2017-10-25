import sys, os
sys.path.insert(0, '/')
import cs_grading as CS

text_editor = "subl"

run_hw4 = 1
suppress_valgrind_errors = 0

student_name = ""                      # Change it to actual student name

run_hw4_test     = 1                   # Change to 0 to turn off these tests .
hw4_use_valgrind = 1                   # Change to 0 if you don't want valgrind to be run.
hw4_open_results = 1                   # Change to 0 if you don't want the results files opened automatically.
hw4_remove_files = 1                   # Change to 0 if you don't want intermediary files to be removed. 
hw4_gtest_count = 1
hw4_generate_grading = 1               # A new feature I add to generate the final grading file 

#####################################################
# Nothing should need to be edited below this line. #
#####################################################

if suppress_valgrind_errors:
	if CS.check_file_existence('~/gcc.supp'):
		CS.remove_file('~/gcc.supp')
	CS.generate_valgrind_suppression()
	CS.VALGRIND = 'valgrind --tool=memcheck --leak-check=yes --suppressions=/home/student/gcc.supp'

#####################################################

###################################################################################################################
# Purpose: Runs an executable with additional options. 
# Arguments:
#       executable_path: The path to the executable. For example, './'.
#       executable_name: The name of the executable that will be run.
#       input_csv: A file that list the input 
#       use_valgrind:   An optional argument to run an executable with valgrind. By default, it is not used. 
###################################################################################################################
def run_tests (executable_path, executable_name, input_csv, grading_file='GR#_student', result_file='result', use_valgrind=0, valgrind_file='valgrind'):
    input_file = open(input_csv, 'r')
    # os.system('rm '+grading_file)
    grading_output = open (grading_file, 'w')

    total = 0
    try:
        os.mkdir('student-output')
    except:
        pass
        
    CS.write_message(grading_file, '| Test Input | Score | \n')
    CS.write_message(grading_file, '|:--|:-:|  \n')
    for line in input_file:
        line = line.strip()
        lines = line.split(',')
        input_file = lines[0]
        output_file = lines[1]
        student_output = lines[2]
        weight = lines[3]
        CS.write_message(result_file, "Test " + input_file + ": \n")
        CS.run_executable(executable_path, 
                        executable_name, ' ' + input_file + ' > ' + student_output, 
                        use_valgrind=use_valgrind, 
                        valgrind_log_filename=valgrind_file)
        results = CS.compare_files_with_order (output_file, student_output, result_file, skip_white_space=1, detailed_results=1)
        if (results[1] ==0 and results[2]==0):
            CS.write_message(grading_file, '| ' + input_file + ' | ' + weight + '| \n')
            CS.write_message(result_file, '\n\nTest ' + input_file.replace('input/', '').replace('.txt','') + ' passed!\n\n')
            total += float(weight)
        else:
            CS.write_message(grading_file, '| ' + input_file + ' | <span style="color:red"> 0 </span> | \n')
            CS.write_message(result_file, '\n\nTest ' + input_file.replace('input/', '').replace('.txt','') + ' failed!\n\n')

    CS.write_message(grading_file, ' \n\n Total Score: ' + str(total) )
 

hw4_executable        = 'hw4'
hw4_gtest_executable  = 'hw4'                # The name of the executable that will be created.
hw4_gtest_file        = 'hw4_gtest.cpp'            # Update this variable with any extra source files needed.
hw4_source_files	  = '../hw4.cpp'
hw4_remove_files      = 1                               # Change to 0 if you don't want the executable to be automatically removed.
hw4_results_file      = 'hw4_results.txt'          # The file where the results will be stored.
hw4_valgrind_log      = 'hw4_valgrind.txt'         # The file where the valgrind results will be stored. 
hw4_grading_file      = 'GR4_' + student_name + '.md'

if run_hw4_test:
    if CS.check_file_existence(hw4_results_file):
        CS.remove_file(hw4_results_file)
    if CS.check_file_existence(hw4_valgrind_log):
        CS.remove_file(hw4_valgrind_log)
    os.chdir('../')
    os.system('make')
    if CS.check_file_existence('bin/hw5'):
        os.system('mv ./bin/hw4 ./')

    if (not CS.check_file_existence('hw5')):
        os.system('make hw4')
        if CS.check_file_existence('bin/hw5'):
            os.system('mv ./bin/hw4 ./')


    if CS.check_file_existence('hw5'):
        os.chdir('hw4-tests')
        run_tests ('../', hw5_executable, 'input/input.csv', use_valgrind=1, valgrind_file=hw4_valgrind_log, grading_file=hw4_grading_file, result_file=hw4_results_file)

    if hw4_open_results:
        CS.open_file(hw4_results_file, text_editor)
        CS.open_file(hw4_grading_file, text_editor)
        if hw4_use_valgrind:
            CS.open_file(hw4_valgrind_log, text_editor)

		# Clean up
    if hw4_remove_files:
        os.rmdir('student-output')
        CS.remove_file('../hw5')