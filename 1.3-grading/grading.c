#import <stdlib.h>
#import <string.h>
#import <stdio.h>
#import "grading.h"

// ID Generators
int CLASS_ID;
int NUM_CLASSES;
int STUDENT_ID;
int NUM_STUDENTS;
int ENROLLMENT_ID;
int NUM_ENROLLMENTS;

// Data Storage Arrays
Class **classArray = NULL;
Student **studentArray = NULL;
Enrollment **enrollmentArray = NULL;

// TODO: Periodically reallocate arrays when IDs breach the array size
static void **allocate_array(size_t elementSize, int count) {
  int bufferSize = count * elementSize;
  void **result = (void**)malloc(bufferSize);
  memset(result, 0, bufferSize);
  return result;
}

static void allocate_classes() {
  classArray = (Class **)allocate_array(sizeof(Class*), NUM_CLASSES);
}

static void allocate_students() {
  studentArray = (Student **)allocate_array(sizeof(Student*), NUM_STUDENTS);
}

static void allocate_enrollments() {
  enrollmentArray = (Enrollment **)allocate_array(sizeof(Enrollment*), NUM_ENROLLMENTS);
}

void initialize_grading() {
  CLASS_ID = STUDENT_ID = ENROLLMENT_ID = 0;
  NUM_CLASSES = 100;
  NUM_STUDENTS = 100;
  NUM_ENROLLMENTS = 100;
  allocate_classes();
  allocate_students();
  allocate_enrollments();
}

static void free_array(int size, void **array) {
  for (int i = 0; i < size; i++)
    if (array[i] != NULL)
      free(array[i]);
  free(array);
}

static void free_enrollment(Enrollment *enrollment) {
  if (enrollment->numAssignments)
    free_array(enrollment->numAssignments, (void**)enrollment->assignments);
  if (enrollment->numTests)
    free_array(enrollment->numTests, (void**)enrollment->tests);
}

void free_grading() {
  free_array(CLASS_ID, (void**)classArray);
  free_array(STUDENT_ID, (void**)studentArray);

  for (int i = 0; i < ENROLLMENT_ID; i++) {
    free_enrollment(enrollmentArray[i]);
  }
  free_array(ENROLLMENT_ID, (void**)enrollmentArray);
}

/**
 * Constructors
 */
static Student *create_student(char *name) {
   Student *student = (Student*)malloc(sizeof(Student));
   student->name = name;
   student->id = ++STUDENT_ID;
   return student;
 }

static Class *create_class(char *name) {
  Class *class = (Class*)malloc(sizeof(Class));
  class->name = name;
  class->id = ++CLASS_ID;
  return class;
}

static Enrollment *create_enrollment(int classId, int studentId) {
  Enrollment *enrollment = (Enrollment*)malloc(sizeof(Enrollment));
  enrollment->id = ++ENROLLMENT_ID;
  enrollment->classId = classId;
  enrollment->studentId = studentId;
  enrollment->numTests = 0;
  enrollment->numAssignments = 0;
  return enrollment;
}

static Assignment *create_assignment(double percentCorrect, Grade grade) {
  Assignment *newAssignment = (Assignment *)malloc(sizeof(Assignment));
  newAssignment->percentCorrect = percentCorrect;
  newAssignment->grade = grade;
  return newAssignment;
}

/**
 * Adds a new class
 */
Class *add_class(char *name) {
  Class *class = create_class(name);
  classArray[class->id - 1] = class;
  return class;
}

/**
 * Adds a student
 */
Student *add_student(char *name) {
  Student *student = create_student(name);
  studentArray[student->id - 1] = student;
  return student;
}

/**
 * Adds a new Enrollment
 */
Enrollment *add_enrollment(int classId, int studentId) {
  Enrollment *enrollment = create_enrollment(classId, studentId);
  enrollmentArray[enrollment->id - 1] = enrollment;
  return enrollment;
}

Class *get_class_by_id(int id) {
  return classArray[id-1];
}

Student *get_student_by_id(int id) {
  return studentArray[id-1];
}

Enrollment *get_enrollment_by_id(int id) {
  return enrollmentArray[id-1];
}

Class **list_classes() {
  return classArray;
}

Student **list_students() {
  return studentArray;
}

Enrollment **list_enrollments() {
  return enrollmentArray;
}

int get_class_count() {
  return CLASS_ID;
}

int get_student_count() {
  return STUDENT_ID;
}

int get_enrollment_count() {
  return ENROLLMENT_ID;
}

int count_enrollments_for_class(int classId) {
  int count = 0;
  for (int i = 0; i < NUM_ENROLLMENTS && enrollmentArray[i] != NULL; i++) {
    if (enrollmentArray[i]->classId == classId) {
      count++;
    }
  }
  return count;
}

/**
 * Gets the Enrollments for a Class - O(n) time where n is the number of enrollments
 */
Enrollment **get_enrollments_for_class(int classId) {
  int count = count_enrollments_for_class(classId);
  Enrollment **result = (Enrollment**)malloc(count * sizeof(Enrollment*));
  int resultIndex = 0;
  for (int i = 0; i < NUM_ENROLLMENTS && enrollmentArray[i] != NULL; i++) {
    if (enrollmentArray[i]->classId == classId) {
      result[resultIndex++] = enrollmentArray[i];
    }
  }
  return result;
}

int count_enrollments_for_student(int studentId) {
  int count = 0;
  for (int i = 0; i < NUM_ENROLLMENTS && enrollmentArray[i] != NULL; i++) {
    if (enrollmentArray[i]->studentId == studentId) {
      count++;
    }
  }
  return count;
}

Enrollment **get_enrollments_for_student(int studentId) {
  int count = count_enrollments_for_student(studentId);
  Enrollment **result = (Enrollment**)malloc(count * sizeof(Enrollment*));
  int resultIndex = 0;
  for (int i = 0; i < NUM_ENROLLMENTS && enrollmentArray[i] != NULL; i++) {
    if (enrollmentArray[i]->studentId == studentId) {
      result[resultIndex++] = enrollmentArray[i];
    }
  }
  return result;
}

Assignment *add_assignment_result(int enrollmentId, double percentCorrect, Grade grade) {
  Enrollment *enrollment = get_enrollment_by_id(enrollmentId);
  Assignment **assignments = (Assignment**)malloc((enrollment->numAssignments + 1) * sizeof(Assignment*));

  if (enrollment->numAssignments > 0) {
    for (int i = 0; i < enrollment->numAssignments; i++) {
      assignments[i] = enrollment->assignments[i];
    }
    free(enrollment->assignments);
    enrollment->assignments = NULL;
  }

  Assignment *newAssignment = create_assignment(percentCorrect, grade);
  assignments[enrollment->numAssignments++] = newAssignment;
  enrollment->assignments = assignments;
  return newAssignment;
}

Assignment *add_test_result(int enrollmentId, double percentCorrect, Grade grade) {
  Enrollment *enrollment = get_enrollment_by_id(enrollmentId);
  Assignment **tests = (Assignment**)malloc((enrollment->numTests + 1) * sizeof(Assignment*));

  if (enrollment->numTests > 0) {
    for (int i = 0; i < enrollment->numTests; i++) {
      tests[i] = enrollment->tests[i];
    }
    free(enrollment->tests);
    enrollment->tests = NULL;
  }

  Assignment *newTest = create_assignment(percentCorrect, grade);
  tests[enrollment->numTests++] = newTest;
  enrollment->tests = tests;
  return newTest;
}
