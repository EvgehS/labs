#include <iostream>

template<typename type>
void print_average_mark(const char* name, type mark_1, type mark_2, type mark_3)
{
	std::cout << name << "'s average mark: " << (mark_1 + mark_2 + mark_3) / 3.0 << std::endl;
}

template<typename type>
void print_average_mark(const char* name, type mark_1, type mark_2)
{
	std::cout << name << "'s average mark: " << (mark_1 + mark_2) / 2.0 << std::endl;
}

int char_to_mark(const char mark)
{
	int return_mark;
	switch(mark)
	{
		case 'A': return 5;
		case 'B': return 4;
		case 'C': return 3;
		case 'D': return 3;
		case 'F': return 2;
		default: return 0;
	}
}
void print_average_mark(const char* name, const char mark_1, const char mark_2, const char mark_3)
{
	
	std::cout << name << "'s average mark (American grading system): " << (char_to_mark(mark_1) + char_to_mark(mark_2) + char_to_mark(mark_3)) / 3.0 << std::endl;
}
void print_average_mark(const char* name, const char mark_1, const char mark_2)
{
	
	std::cout << name << "'s average mark (American grading system): " << (char_to_mark(mark_1) + char_to_mark(mark_2)) / 2.0 << std::endl;
}
int main()
{
	// student1
	const char *name1 = "Ivan";
	const int mark1_1 = 5;
	const int mark1_2 = 4;
	const int mark1_3 = 5;
	// student2
	const char* name2 = "Alex";
	const double mark2_1 = 4.45;
	const double mark2_2 = 3.55;
	const double mark2_3 = 2.0;
	// // student 3
	const char* name3 = "Max";
	const float mark3_1 = 5.0;
	const float mark3_2 = 4.455;
	const float mark3_3 = 1.5;
	// // student 4
	const char* name4 = "Jack";
	const char mark4_1 = 'A';
	const char mark4_2 = 'B';
	const char mark4_3 = 'C';
	print_average_mark(name1, mark1_1, mark1_2, mark1_3);
	print_average_mark(name2, mark2_1, mark2_2, mark2_3);
	print_average_mark(name3, mark3_1, mark3_2, mark3_3);
	print_average_mark(name4, mark4_1, mark4_2, mark4_3);
	print_average_mark(name3, mark3_1, mark3_2);
	print_average_mark(name4, mark4_1, mark4_2);
	return 0;
}
