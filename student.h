/*student.h*/

//
// <<YOUR NAME HERE>>
// U. of Illinois, Chicago
// CS 341, Spring 2019
// HW #04: Student class
//

#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
  string  Name;
  int     Midterm;
  int     Final;

  Student(std::string name, int mid, int fnl)
    : Name(name), Midterm(mid), Final(fnl)
  { }

  Student(const Student& other)
    : Name(other.Name), Midterm(other.Midterm), Final(other.Final)
  { }

  double ExamAvg() const
  {
    return (this->Midterm + this->Final) / 2.0;
  }
};