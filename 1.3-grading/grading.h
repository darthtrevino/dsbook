
typedef enum {
  A,
  B,
  C,
  D,
  F
} Grade;

typedef struct {
  double percentCorrect;
  Grade grade;
} Assignment;


/**
 * Student Structure
 */
typedef struct {
  int id;
  char *name;
} Student;

typedef struct {
  int id;
  int studentId;
  int classId;
  int numAssignments;
  int numTests;
  Assignment **assignments;
  Assignment **tests;
} Enrollment;

/**
 * Students in the class
 */
typedef struct {
  int id;
  char *name;
  Student *students;
} Class;

void initialize_grading();
void free_grading();

/**
 * Class Creation and Retrieval
 */
Class *add_class(char *name);
Class *get_class_by_id(int id);
Class **list_classes();
int get_class_count();

/**
 * Student Creation and Retrieval
 */
Student *add_student(char *name);
Student *get_student_by_id(int id);
Student **list_students();
Student **list_students_in_class(int class_id);
int get_student_count();

/**
 * Student Enrollment Creation and Retrieval
 */
Enrollment *add_enrollment(int classId, int studentId);
Enrollment *get_enrollment_by_id(int enrollmentId);
int count_enrollments_for_class(int enrollmentId);
Enrollment **get_enrollments_for_class(int classId);
int count_enrollments_for_student(int studentId);
Enrollment **get_enrollments_for_student(int studentId);
Assignment *add_assignment_result(int enrollmentId, double percentCorrect, Grade grade);
Assignment *add_test_result(int enrollmentId, double percentCorrect, Grade grade);
