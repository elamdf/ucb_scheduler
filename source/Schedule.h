/** @file main.cpp
 * da main program
 */
// The previous block is needed in every file for which you want to generate documentation

/* #include <fmt/format.h> */

// This should be in the headers

/**
 * @brief main loop, text-based interaction
 * @return nada
 */
#ifndef Schedule_H
#define Schedule_H
#define N_SEMESTERS 8
#include <iostream>
#include <string>
#include <unordered_map>
#include<vector>

using namespace std;

enum course_prefix {cs, philo};
class Course {
	public:
		bool nocourse;
		float grade; // in gpa points version
		course_prefix prefix;
		int course_number;
		string modifier;
		float units;
		string m_notes;
		vector<Course> prereqs;
		bool isUpperDivision(){return (course_number >= 100);}
		Course(){nocourse = true;}
		Course(course_prefix p, int c_n, char const * mod, float u, char const * m_n, vector<Course> prq);
		bool operator ==(const Course compare_to){
			return (prefix == compare_to.prefix && course_number == compare_to.course_number && modifier== compare_to.modifier);
		}
		string toString();
};

class Semester {
	public:
	float sem_units;
	bool complete;
	float sem_gpa;
	vector<Course> taking ;
	Semester(){
		sem_units = 0;
		complete = false;
		sem_gpa = 0;
	}
	Semester(vector<Course> t){
		sem_units = 0;
		complete = false;
		sem_gpa = 0;
		taking = t;
		for (Course c : t)
			sem_units += c.units;
	}
	string toString(){
		string tmp = "";
		for (int i=0; i < taking.size(); i++)
			tmp += taking[i].toString() + "\n";

		return tmp;
	}
	int add_course(Course c){ // TODO check previous semesters / warn if retaking and previously passed
		for (int i=0; i < taking.size(); i++)
			if (taking[i] == c)
				return -1;
		taking.push_back(c);
		return 0;
	}




};

class Schedule {

	private:
		int sem_idx;
		float gpa;
		void enter_final_grades(int idx);
		vector<Semester> m_sem_list;
		static float parse_grade_input(string input);
		void calculate_sem_gpa(int idx);
		void recalculate_overall_gpa();
	public:
		Schedule(){
			sem_idx = 0;


		};
		unordered_map<string, Course> catalog; //TODO make a constructor lol
		bool can_take(Course c);
		bool can_take(Course c, int sem_idx);
		float getGpa();
		void add_sem(int idx);
		vector<Course> enter_sem_courses(int idx);
		void add_sem(); // current idx
		void add_sem(Semester s, int idx); // future sem
		void finish_sem();
		void finish_sem(int idx);
};
#endif
