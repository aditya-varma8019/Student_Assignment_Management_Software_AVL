# Student_Assignment_Management_Software_AVL

You need to develop a system for managing student assignments and submissions. Assume
that students will form groups each containing 2 students. The teacher may decide to give the
same or different assignments to different groups. The teacher may evaluate the assignments
offline, also teacher can conduct viva for each group, but may decide to give different marks
to students in the same group.
One database to be maintained for students. Each student record contains student-id, name,

group-partner, group-id, assignment-name/id, deadline, status-of-assignment (submitted/not-
submitted/evaluated), offline-evaluation-marks, viva-marks.

Another database is maintained for assignment records. Each record contains assignment-id,
topic-name, status (declared/due-date-over/evaluated). The same assignment may be given to
multiple student groups. Each assignment-record in turn can have a separate database inside,
each record containing student-group-id, status (declared/submitted/not-submitted/evaluated),
marks given.
Following operations are to be defined :

1. Insert a student record in the student-database. After every insertion of a student-
record, appropriate changes/insertion needs to be done in the assignment-database

also.
2. Insert assignment-record in the assignment-record-database. The insertion function
can take a list of students and allocate the assignment to multiple student groups, thus
resulting into insertions in student-database as well.
3. Change status of assignment and student database based on different events
a. Student-group submitting the assignment
b. Assignment for one specific student group is evaluated. Once a particular
assignment is evaluated for all student-groups to whom the assignment was
given, the status of the assignment itself changes to “evaluated”.
4. Print the details of assignments that are declared but not evaluated.
5. Print the details of student groups who have not submitted the assignments even if the
due-date is over.
6. Print the details of student groups for whom the assignment is yet-to-be-evaluated
even though they have been submitted. In case viva is remaining to be taken, that is
explicitly to be mentioned.
7. For a given assignment id, print the details of student-groups, in the decreasing order
of marks they have received in the assignment.
8. Print student groups receiving top marks in each of the assignment given.
9. Range-search – Search and print the details of assignments having assignment-id
between assignment-id-1 and assignment-id-2.
You can decide to create a menu-driven program (not compulsory, but extra credits may be
given) where students and the teacher can log in (password not mandatory) and perform all
the above operations.
