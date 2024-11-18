import os
import subprocess
import difflib

def compile_program():
    #try compiling the program
    compile_cmd = ["g++", "-o", "AirportDriver", "AirportDriver.cpp"]
    result = subprocess.run(compile_cmd, capture_output=True, text=True)

    #if compilation was not successful print error
    if result.returncode != 0:
        print("Compilation failed:")
        print(result.stderr)
        return False
    else:
        print("Compilation successful.")
        return True

#now need to iterate through the test files and compare to cpp output
def run_test(test_input_path, test_output_path, test_number):
    #run exe with test input
    with open(test_input_path, 'r') as infile:
        result = subprocess.run(["./AirportDriver"], stdin=infile, capture_output=True, text=True)

    #check expected output
    with open(test_output_path, 'r') as outfile:
        expected_output = outfile.read()

    #get cpp output
    actual_output = result.stdout

    #normalize ends of the lines so the files can be matched up
    expected_output_lines = expected_output.strip().splitlines()
    actual_output_lines = actual_output.strip().splitlines()

    #now to compare
    if expected_output_lines == actual_output_lines:
        return True, ""
    else:
        #create a diff so i see exactly what the issue was with the test
        diff = difflib.unified_diff(
            expected_output_lines,
            actual_output_lines,
            fromfile='Expected Output',
            tofile='Actual Output',
            lineterm=''
        )
        diff_text = "\n".join(list(diff))
        return False, diff_text

def main():
    #now to handle all of the inputs
    #first compile
    if not compile_program():
        return

    test_cases_dir = "test_cases"
    passed_tests = []
    failed_tests = []

    #scrape directory for all .in files
    test_files = [f for f in os.listdir(test_cases_dir) if f.endswith('.in')]
    #sort the files to run in order
    test_files.sort()

    for test_file in test_files:
        test_number = test_file[:-3]
        test_input_path = os.path.join(test_cases_dir, test_file)
        test_output_path = os.path.join(test_cases_dir, f"{test_number}.out")

        if not os.path.exists(test_output_path):
            print(f"Missing output file for {test_file}, skipping.")
            continue

        print(f"Running {test_number}... ", end='')
        passed, diff_text = run_test(test_input_path, test_output_path, test_number)

        if passed:
            print("PASSED")
            passed_tests.append(test_number)

        else:
            print("FAILED")
            failed_tests.append((test_number, diff_text))
    #now final summary of all tests
    print("\nTest Summary:")
    print(f"Total Tests Run: {len(passed_tests) + len(failed_tests)}")
    print(f"Tests Passed: {len(passed_tests)}")
    print(f"Tests Failed: {len(failed_tests)}")

    #output the file differences for each failed test for debugging
    if failed_tests:
        print("\nFailed Tests Details:")
        for test_number, diff_text in failed_tests:
            print(f"\nTest {test_number} Failed:")
            print(diff_text)

if __name__ == "__main__":
    main()
