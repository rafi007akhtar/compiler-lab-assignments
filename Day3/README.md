# Day3

- Questions: [assignment3_ques.jpeg](https://github.com/rafi007akhtar/compiler-lab-assignments/blob/master/Day3/day_3_assignment.docx)


- Functions written for each question in this file: [assignment_3.h](https://github.com/rafi007akhtar/compiler-lab-assignments/blob/master/Day1/assignment_3.h)

- These functions are tested in this file: [test_3.c](https://github.com/rafi007akhtar/compiler-lab-assignments/blob/master/Day1/assignment_3.h)

## Instructions for Running

1. Follow steps 1 and 2 in root [README](https://github.com/rafi007akhtar/compiler-lab-assignments/blob/master/README.md) that invlove cloning and entering the repository.

2. Enter `Day3` folder.
	```sh
	cd Day3
	```

3. Compile the test file.
	```sh
	cd test_3.c -o test3
	```

4. Run the executable
	```sh
	./test3  # For Linux
	# OR
	./test3.exe  # For Windows
	```

## Test files for this assignment

- **Question 1**. `hello-world.c`, `incorrect.c` 
- **Question 3**. `findSize.c`
- **Question 4**. `return_types.c`
- **Question 5**. `structs.c`
- **Question 7**. `initialize.c`

## Important note

**Most functions in this assignment will _not_ run on Windows.**

Reason: Most files are file programs, and as such, I have used the `getline` function defined in `stdio.h` to manipulate them. The `gcc` compiler defined for Windows does not contain a `getline` function, which is why these programs won't work there.

If you want to run these programs on Windows, you may want to try running a Linux Ubuntu OS or a Linux subsystem if your OS has one.
