```
UsosWebPage page = Student.show()
courses = page.getGradeInfo().getCourses()
for each course in courses
  marks.append( getMark(Student, course) )
return page.send(marks)
```