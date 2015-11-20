#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "grading.h"

void test_can_add_class();
void test_can_get_class_by_id();
void test_can_list_classes();
void test_can_get_student_by_id();
void test_can_add_student();
void test_can_list_students();
void test_can_add_enrollment();
void test_get_enrollments_for_class();
void test_get_enrollments_for_student();
void test_add_assignment_result();
void test_add_test_result();

int main() {
  // Class Tests
  test_can_add_class();
  test_can_get_class_by_id();
  test_can_list_classes();

  // Student Tests
  test_can_add_student();
  test_can_get_student_by_id();
  test_can_list_students();

  // Enrollment Management
  test_can_add_enrollment();
  test_get_enrollments_for_class();
  test_get_enrollments_for_student();

  // Test/Assignment Management
  test_add_assignment_result();
  test_add_test_result();
}

void test_can_add_class() {
  initialize_grading();
  char *class_name = "Philosophy 101";
  Class *class = add_class(class_name);
  assert(strcmp(class->name, class_name) == 0 && "test_can_add_class()");
  free_grading();
}

void test_can_get_class_by_id() {
  initialize_grading();
  char *class_name = "Philosophy 101";
  Class *created = add_class(class_name);
  Class *found = get_class_by_id(created->id);
  assert(strcmp(created->name, found->name) == 0 && "test_can_get_class_by_id()");
  free_grading();
}

void test_can_list_classes() {
  initialize_grading();
  add_class("Philosophy 101");
  add_class("Calculus 1");
  Class **classes = list_classes();
  assert(get_class_count() == 2 && "test_can_list_classes");
  assert(strcmp(classes[0]->name, "Philosophy 101") == 0 && "test_can_list_classes()");
  assert(strcmp(classes[1]->name, "Calculus 1") == 0 && "test_can_list_classes()");
  free_grading();
}

void test_can_add_student() {
  initialize_grading();
  Student *student = add_student("John Jones");
  assert(strcmp(student->name, "John Jones") == 0 && "name should be equal");
  free_grading();
}

void test_can_get_student_by_id() {
  initialize_grading();
  Student *student = add_student("John Jones");
  Student *found = get_student_by_id(student->id);
  assert(student->id == found->id && "expected to find student");
  free_grading();
}

void test_can_list_students() {
  initialize_grading();
  add_student("Joe Test");
  add_student("Marcy Test");
  Student **students = list_students();
  assert(get_student_count() == 2 && "test_can_list_students");
  assert(strcmp(students[0]->name, "Joe Test") == 0 && "test_can_list_students()");
  assert(strcmp(students[1]->name, "Marcy Test") == 0 && "test_can_list_students()");
  free_grading();
}

void test_can_add_enrollment() {
  initialize_grading();
  Class *class = add_class("Philosophy 101");
  Student *student = add_student("Joe Test");
  Enrollment *enrollment = add_enrollment(class->id, student->id);
  assert(enrollment->classId == class->id && "test_can_add_enrollment()");
  assert(enrollment->studentId == student->id && "test_can_add_enrollment()");
  free_grading();
}

void test_get_enrollments_for_class() {
  initialize_grading();
  Class *class = add_class("Philosophy 101");
  Student *student1 = add_student("Joe Test");
  Student *student2 = add_student("Mary Test");
  Enrollment *enrollment1 = add_enrollment(class->id, student1->id);
  Enrollment *enrollment2 = add_enrollment(class->id, student2->id);

  Enrollment **enrollments = get_enrollments_for_class(class->id);
  assert(count_enrollments_for_class(class->id) == 2 && "enrollment count");
  assert(enrollments[0]->studentId == student1->id && "enrollment check 1");
  assert(enrollments[1]->studentId == student2->id && "enrollment check 2");
  free(enrollments);
  free_grading();
}

void test_get_enrollments_for_student() {
  initialize_grading();
  Class *class1 = add_class("Philosophy 101");
  Class *class2 = add_class("Philosophy 200");
  Student *student = add_student("Joe Test");
  Enrollment *enrollment1 = add_enrollment(class1->id, student->id);
  Enrollment *enrollment2 = add_enrollment(class2->id, student->id);

  Enrollment **enrollments = get_enrollments_for_student(student->id);
  assert(count_enrollments_for_student(student->id) == 2 && "enrollment count");
  assert(enrollments[0]->classId == class1->id && "enrollment check 1");
  assert(enrollments[1]->classId == class2->id && "enrollment check 2");
  free(enrollments);
  free_grading();
}

void test_add_assignment_result() {
  initialize_grading();
  Class *class = add_class("Philosophy 101");
  Student *student = add_student("Joe Test");
  Enrollment *enrollment = add_enrollment(class->id, student->id);
  assert(enrollment->numAssignments == 0);
  Assignment *assignment = add_assignment_result(enrollment->id, 80.0, B);
  assert(enrollment->numAssignments == 1);
  assert(fabs(assignment->percentCorrect - 80.0) < 0.000001);
  assert(assignment->grade == B);
  free_grading();
}

void test_add_test_result() {
  initialize_grading();
  Class *class = add_class("Philosophy 101");
  Student *student = add_student("Joe Test");
  Enrollment *enrollment = add_enrollment(class->id, student->id);
  assert(enrollment->numTests == 0);
  Assignment *assignment = add_test_result(enrollment->id, 90.0, A);
  assert(enrollment->numTests == 1);
  assert(fabs(assignment->percentCorrect - 90.0) < 0.000001);
  assert(assignment->grade == A);
  free_grading();
}
