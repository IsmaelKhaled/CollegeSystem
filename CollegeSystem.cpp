#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>
using namespace std;

//Test Argument: [HUM001,English,15/10/2015,HallB;HUM002,Maths,15/12/2016,HallB;HUM003,Geo,5/1/2016,HallH;PHY242,Physics,3/1/2016,HallF;MRE442,Physics,25/6/2016,HallB;FOR343,Physics,10/3/2016,HallF]
// Student Test Argument: [12001,Ahmed Fathy,(HUM001,PHY242);12004,Mohamed 3ab3al,(HUM001,HUM002);12006,Hesham Mohamed,(HUM002)]



class MyDate
{
private:
	int Day, Month, Year;
	int MonthsInDays1 = 0, MonthsInDays2 = 0;

public:
	void setDate(int d, int m, int y)
	{
		Day = d;
		Month = m;
		Year = y;
	}
	int isgreater(MyDate d)
	{
		if (Year > d.Year)
			return 1;
		else if (Year < d.Year)
			return 0;
		else
			if (Month > d.Month)
				return 1;
			else if (Month < d.Month)
				return 0;
			else
			{
				if (Day>d.Day)
					return 1;
				else if (Day < d.Day)
					return 0;
			}
	}
	int islesser(MyDate d)
	{
		if (Year < d.Year)
			return 1;
		else if (Year > d.Year)
			return 0;
		else
			if (Month < d.Month)
				return 1;
			else if (Month > d.Month)
				return 0;
			else
				if (Day<d.Day)
					return 1;
				else if (Day > d.Day)
					return 0;
	}
	int isequal(MyDate d)
	{
		if (Day == d.Day&& Month == d.Month&& Year == d.Year)
			return 1;
		else 
			return 0;
	}
	int getDay()
	{
		return Day;
	}
		
	int getMonth()
	{
		return Month;
	}
	int getYear()
	{
		return Year;
	}
	void print()
	{
		cout << Day << "/" << Month << "/" << Year << endl;
	}
	double DaysBetween(MyDate d, int days_in_month_leap[], int days_in_month[])
	{
		double difference;
		if (Year % 400 == 0 || (Year % 100 != 0 && Year % 4 == 0))
		{
			for (int i = 0; i < Month-1; i++)
			{
				MonthsInDays1 += days_in_month_leap[i];
			}
			for (int i = 0; i < d.Month-1; i++)
			{
				MonthsInDays2 += days_in_month_leap[i];
			}

			difference = (Day + MonthsInDays1) - (d.Day + MonthsInDays2);
		}
		else
		{
			for (int i = 0; i < Month-1; i++)
			{
				MonthsInDays1 += days_in_month[i];
			}
			for (int i = 0; i < d.Month-1; i++)
			{
				MonthsInDays2 += days_in_month[i];
			}
			difference = (Day + MonthsInDays1 + (Year*365)) - (d.Day + MonthsInDays2+(d.Year*365));
		}
		return fabs(difference);
	}
	
};



int main()
{
	int n = 0, i, j, k, ExamHallCount = 0, ExamMonth[100], ExamDay[100], ExamYear[100], CoursesCount, NumberOfStudents = 0, MinStudentID, MaxStudentID;
	int required_student, required_course, student_attending_count=0,flag[100];
	string::size_type  courseCodeComma, courseNameComma, courseExamDateComma, courseEnd, courseStart;
	string::size_type studentIDComma, studentNameComma, studentCoursesBracket, studentStart, studentEnd, studentCourseComma ;
	string courses, courseCode[100], courseName[100], courseExamDate[100], courseExamHall[100];
	string students, studentID[100], studentName[100], studentCourses[100], studentCoursesCodes;
	string Command, CommandArgument, CommandValue;
	MyDate ExamDate[100], ExamDateMin, ExamDateMax;
	int days_in_month_leap[12] = {  31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int days_in_month[12] = {  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	//--------------------------------------------------------------------------------
	getline(cin, courses, ']');
	//courses = "[HUM001,English,15/10/2015,HallB;HUM002,Maths,15/10/2015,HallB;HUM003,Geo,5/1/2016,HallH;PHY242,Physics,15/10/2015,HallF;MRE442,Physics,25/6/2016,HallB;FOR343,Physics,10/3/2016,HallF]";
	courseStart = courses.find('[', 0);
	for (i=0;i<100;i++) //Loop For Courses
	{
		courseCodeComma = courses.find(",", courseStart);	//Comma after Course Code
		courseNameComma = courses.find(",", courseCodeComma + 1);	//Comma after Course Name
		courseExamDateComma = courses.find(",", courseNameComma + 1);	 // Comma after Exam Date
		courseEnd = courses.find(";", courseStart); //End of this course data
		if (courseEnd == string::npos) // Last Course Condition
		{
			courseEnd = courses.find("]", courseStart);
			courseCode[i] = courses.substr(courseStart, courseCodeComma - courseStart); //Course Code substring
			courseName[i] = courses.substr(courseCodeComma + 1, courseNameComma - courseCodeComma - 1); //Course Name substring
			courseExamDate[i] = courses.substr(courseNameComma + 1, courseExamDateComma - courseNameComma - 1); //Course Exam Date substring
			courseExamHall[i] = courses.substr(courseExamDateComma + 1, courseEnd - courseExamDateComma - 1); //Course Exam Hall substring
			courseStart = courseEnd + 1;
			ExamDay[i] = atof(courseExamDate[i].substr(0, courseExamDate[i].find("/", 0)).c_str());
			ExamMonth[i] = atof(courseExamDate[i].substr(courseExamDate[i].find("/", 0) + 1, courseExamDate[i].find("/", courseExamDate[i].find("/", 0) + 1) - courseExamDate[i].find("/", 0) - 1).c_str());
			ExamYear[i] = atof(courseExamDate[i].substr(courseExamDate[i].find("/", courseExamDate[i].find("/", 0) + 1) + 1, 4).c_str());
			ExamDate[i].setDate(ExamDay[i], ExamMonth[i], ExamYear[i]);
			break;
		}
		if (i == 0)
			courseCode[i] = courses.substr(courseStart + 1, courseCodeComma - 1 - courseStart);
		else
			courseCode[i] = courses.substr(courseStart, courseCodeComma - courseStart); //Course Code substring

		courseName[i] = courses.substr(courseCodeComma + 1, courseNameComma - courseCodeComma - 1); //Course Name substring
		courseExamDate[i] = courses.substr(courseNameComma + 1, courseExamDateComma - courseNameComma - 1); //Course Exam Date substring
		courseExamHall[i] = courses.substr(courseExamDateComma + 1, courseEnd - courseExamDateComma - 1); //Course Exam Hall substring
		courseStart = courseEnd + 1;

		ExamDay[i] = atof(courseExamDate[i].substr(0, courseExamDate[i].find("/", 0)).c_str());
		ExamMonth[i] = atof(courseExamDate[i].substr(courseExamDate[i].find("/", 0)+1, courseExamDate[i].find("/", courseExamDate[i].find("/", 0) + 1) - courseExamDate[i].find("/", 0) -1).c_str());
		ExamYear[i] = atof(courseExamDate[i].substr(courseExamDate[i].find("/", courseExamDate[i].find("/", 0) + 1)+1, 4).c_str());
		ExamDate[i].setDate(ExamDay[i], ExamMonth[i], ExamYear[i]);
		
	}
	CoursesCount = i + 1;

	for (int h = 0; h < CoursesCount; h++) // Loop To Find Hall Count
	{
		for (int f = h+1; f < CoursesCount; f++)
		{
			if (courseExamHall[h] == courseExamHall[f]&&flag[h]!=1)
			{ 
				ExamHallCount++;
				flag[h] = 1;
				break;
			}
		}

	}
	ExamHallCount = CoursesCount - ExamHallCount;
	//----------------------------------------------------------------------------------------------

	 getline(cin, students, ']');
	//students = "[12001,Ahmed Fathy,(HUM001,PHY242,MRE442);12004,Mohamed 3ab3al,(HUM001,HUM002,PHY242);12006,Hesham Mohamed,(HUM002,HUM003,MRE442)]";
	studentStart = students.find("[");
	for (int b = 0; b < students.length(); b++)
	{
		if (students[b] == ';')
			NumberOfStudents++;
	}
	NumberOfStudents++;
	for (j = 0; j < 100; j++) // Loop for Students
	{
		studentEnd = students.find(";", studentStart);
		studentIDComma = students.find(",", studentStart);
studentNameComma = students.find(",", studentIDComma + 1);
studentCoursesBracket = students.find("(", studentNameComma + 1);
if (j == 0)
studentID[j] = students.substr(studentStart + 1, studentIDComma - studentStart - 1);
else
studentID[j] = students.substr(studentStart, studentIDComma - studentStart);
studentName[j] = students.substr(studentIDComma + 1, studentNameComma - studentIDComma - 1);
studentCourses[j] = students.substr(studentCoursesBracket + 1, students.find(")", studentStart) - studentNameComma - 2);


studentStart = studentEnd + 1;
	}
	MaxStudentID = atof(studentID[0].c_str()); //Getting MaxStudentID
	for (int MaxStudentCounter = 1; MaxStudentCounter < NumberOfStudents; MaxStudentCounter++)
	{
		if (atof(studentID[MaxStudentCounter].c_str()) > MaxStudentID)
			MaxStudentID = atof(studentID[MaxStudentCounter].c_str());
	}
	MinStudentID = atof(studentID[0].c_str()); //Getting MinStudentID
	for (int n = 1; n < NumberOfStudents; n++)
	{
		if (atof(studentID[n].c_str()) < MinStudentID)
			MinStudentID = atof(studentID[n].c_str());
	}
	//-----------------------------------------------------------------------------------

	cin.ignore();
	while (1)
	{

		getline(cin, Command);
		CommandValue = Command.substr(Command.find(" ", Command.find(" ", 0) + 1) + 1, Command.length());
		CommandArgument = Command.substr(Command.find(" ", 0) + 1, Command.find(" ", Command.find(" ", 0) + 1) - Command.find(" ", 0) - 1);
		Command = Command.substr(0, Command.find(" ", 0));

		if (Command == "Number_Courses") //Completed
			cout << CoursesCount << endl;
		else if (Command == "Number_Halls") //Completed
			cout << ExamHallCount << endl;
		else if (Command == "Number_Students")
		{
			cout << NumberOfStudents << endl;
		}
		else if (Command == "Quit") //Completed
		{
			cout << "Thanks!\n";
			return 0;
		}
		else if (Command == "Student_ID_Min") //Completed
		{
			cout << MinStudentID << endl;
		}
		else if (Command == "Student_ID_Max") //Completed
		{
			cout << MaxStudentID << endl;
		}
		else if (Command == "Student_Courses") //Completed
		{

			for (int x = 0; x <= NumberOfStudents; x++)
			{
				if (studentID[x] == CommandArgument)
					required_student = x;
			}
			istringstream ss(studentCourses[required_student]);
			while (getline(ss, studentCoursesCodes, ','))
			{
				cout << studentCoursesCodes << endl;
			}
		}
		else if (Command == "Course_Students") //Completed
		{
			for (int x = 0; x <= CoursesCount; x++)
			{
				if (courseCode[x] == CommandArgument)
					required_course = x;
			}
			for (int x = 0; x <NumberOfStudents; x++)
			{
				if (studentCourses[x].find(CommandArgument, 0) != string::npos)
					cout << studentID[x] << endl;
			}
		}
		else if (Command == "List_Course_Students") //Completed
		{
			int counter = 0;
			for (int x = 0; x < CoursesCount; x++)
			{
				student_attending_count = 0;
				for (int z = 0; z < NumberOfStudents; z++)
				{
					if (studentCourses[z].find(courseCode[x], 0) != string::npos)
					{
						student_attending_count++;
					}
				}
				if (CommandArgument == "More")
				{
					if (student_attending_count > atof(CommandValue.c_str()))
					{
						cout << courseCode[x] << endl;
						counter++;
					}
				}
				else if (CommandArgument == "Less")
				{
					if (student_attending_count < atof(CommandValue.c_str()))
					{
						cout << courseCode[x] << endl;
						counter++;
					}
				}
				else if (CommandArgument == "Equal")
				{
					if (student_attending_count == atof(CommandValue.c_str()))
					{
						cout << courseCode[x] << endl;
						counter++;
					}

				}

			}
			if (counter == 0)
				cout << "none"<<endl;
		}
		else if (Command == "List_Exam_InSameHall") //Completed
		{
			int counter = 0;
			int flagC[100];
			for (int x = 0; x < 100; x++)
			{
				flagC[x] = 0;
			}
			for (int x = 0; x < CoursesCount; x++)
			{
				for (int y = 0; y < CoursesCount; y++)
				{
					if (courseExamHall[x] == courseExamHall[y] && courseExamDate[x] == CommandArgument &&  courseExamDate[y] == CommandArgument && x != y && flagC[x] != 1)
					{
						cout << courseCode[x] << endl;
						flagC[x] = 1;
						counter++;
					}
				}
			}
			if (counter == 0)
				cout << "none" << endl;
			
		}
		else if (Command == "List_Exams") //Completed
		{
			for (int x = 0; x < CoursesCount; x++)
			{
				if (courseExamDate[x] == CommandArgument)
					cout << courseCode[x] << endl;
			}

		}
		else if (Command == "List_Hall_Students_InAnyday") //Completed
		{
			int flagZ[100];
			for (int x = 0; x < 100; x++)
			{
				flagZ[x] = 0;
			}
			for (int x = 0; x < NumberOfStudents; x++)
			{
				for (int y = 0; y < CoursesCount; y++)
				{
					if (studentCourses[x].find(courseCode[y], 0) != string::npos && courseExamHall[y] == CommandArgument && flagZ[x] != 1)
					{
						cout << studentID[x] << endl;
						flagZ[x] = 1;
					}
				}
			}
		}
		else if (Command == "List_Day_Students_InAnyHall") //Completed
		{
			int flagX[100];
			for (int x = 0; x < 100; x++)
			{
				flagX[x] = 0;
			}
			for (int x = 0; x < NumberOfStudents; x++)
			{
				for (int y = 0; y < CoursesCount; y++)
				{
					if (studentCourses[x].find(courseCode[y], 0) != string::npos && courseExamDate[y] == CommandArgument &&flagX[x] != 1)
					{
						cout << studentID[x] << endl;
						flagX[x] = 1;
					}
				}
			}				
		}
		else if (Command == "Students_Dropped_IDs") //Completed
		{
			int a = 0;
			for (int x = MinStudentID; x <= MaxStudentID; x++)
			{
				if (students.find(to_string(x), 0) == string::npos)
				{
					cout << x << endl;
					a++;
				}
				
			}
			if (a == 0)
				cout << "none"<<endl;
		}
		else if (Command == "Exams_Start_Date")//Completed
		{
			ExamDateMin = ExamDate[0];
			for (int x = 0; x < CoursesCount; x++)
			{
				if (ExamDate[x].islesser(ExamDateMin))
					ExamDateMin = ExamDate[x];
			}
			ExamDateMin.print();
		}
		else if (Command == "Exams_End_Date")//Completed
		{
			ExamDateMax = ExamDate[0];
			for (int x = 1; x < CoursesCount; x++)
			{
				if (ExamDate[x].isgreater(ExamDateMax))
					ExamDateMax = ExamDate[x];
			}
			ExamDateMax.print();
		}
		else if (Command == "Exams_Period_InDays")//Completed
		{
			ExamDateMin = ExamDate[0];
			for (int x = 0; x < CoursesCount; x++)
			{
				if (ExamDate[x].islesser(ExamDateMin))
					ExamDateMin = ExamDate[x];
			}
			ExamDateMax = ExamDate[0];
			for (int x = 1; x < CoursesCount; x++)
			{
				if (ExamDate[x].isgreater(ExamDateMax))
					ExamDateMax = ExamDate[x];
			}
			cout << ExamDateMin.DaysBetween(ExamDateMax, days_in_month_leap, days_in_month) << endl;
		}
		else if (Command == "List_Student_Courses") //Completed
		{
			int counter = 0;
			int CommaCount = 0, studentCoursesCount[100], flagX[100];
			for (int x = 0; x < 100; x++)
			{
				flagX[x] = 0;
			}
			for (int y = 0; y < NumberOfStudents; y++)
			{
				
				for (int x = 0; x < studentCourses[y].length(); x++)
				{
					if (studentCourses[y][x] == ',')
						CommaCount++;
				}
				studentCoursesCount[y] = CommaCount + 1;
				CommaCount = 0;
			}
			if (CommandArgument == "More")
			{
				counter = 0;
				for (int x = 0; x < NumberOfStudents; x++)
				{
					if (studentCoursesCount[x]>atof(CommandValue.c_str()))
					{
						cout << studentID[x] << endl;
						flagX[x] = 1;
						counter++;
					}
				}
				if (counter == 0)
				{
					cout << "none" <<endl;
				}
			}
			else if (CommandArgument == "Less")
			{
				counter = 0;
				for (int x = 0; x < NumberOfStudents; x++)
				{
					if (studentCoursesCount[x] < atof(CommandValue.c_str()))
					{ 
					cout << studentID[x] << endl; 
					flagX[x] = 1;
					counter++;
					}
				}
				if (counter == 0)
				{
					cout << "none"<<endl;
				}
			}
			else if (CommandArgument == "Equal")
			{
				counter = 0;
				for (int x = 0; x < NumberOfStudents; x++)
				{
					if (studentCoursesCount[x] == atof(CommandValue.c_str()))
					{
						cout << studentID[x] << endl;
						flagX[x] = 1;
						counter++;
					}
				}
				if (counter == 0)
				{
					cout << "none"<<endl;
				}
				
		}
		}
		else if (Command == "List_Hall_Students") //Completed
		{
			int flagY[100];
			for (int x = 0; x < 100; x++)
			{
				flagY[x] = 0;
			}
			string required_hall = CommandArgument.substr(0, CommandArgument.find(",", 0));
			string required_date = CommandArgument.substr(CommandArgument.find(",", 0) + 1, CommandArgument.length());
			for (int x = 0; x < NumberOfStudents; x++)
			{
				istringstream ss(studentCourses[x]);
				while (getline(ss, studentCoursesCodes, ','))
				{
					for (int y = 0; y < CoursesCount; y++)
					{
						if (studentCoursesCodes.find(courseCode[y])!=string::npos && studentCourses[x].find(courseCode[y])!=string::npos&&flagY[x]!=1)
						{
							if (courseExamHall[y] == required_hall && courseExamDate[y] == required_date)
							{
								cout << studentID[x] <<endl;
								flagY[x] = 1;
							}
						}
					}
				}
			}
		}
		else if (Command == "List_StudyDays")// Completed
		{
			int index, studydays, deletedcount = 0,daydifference[100];
			int h = 0, flagR=1;
			MyDate StudentCoursesDates[10];
			string StudentCourses_x[10];
			MyDate required_date;
			string required_student = CommandArgument.substr(0, CommandArgument.find(',', 0));
			string required_courses = CommandArgument.substr(CommandArgument.find(',', 0) + 1, CommandArgument.length()-required_student.length());
			for (int x = 0; x < CoursesCount; x++)
			{
				if (courseCode[x] == required_courses)
				{
					required_date = ExamDate[x];
					break;
				}

			}
			for (int x = 0; x < NumberOfStudents; x++)//to find dates of courses the student attends
			{
				
				if (studentID[x] == required_student)
				{
					for (int z = 0; z < CoursesCount; z++)
						if (studentCourses[x].find(courseCode[z], 0) != string::npos)
						{
							StudentCoursesDates[h] = ExamDate[z];
							h++;
						}
				}
			}
			if (h == 1)
			{
				cout << "7" << endl;
				continue;
			}
			flagR = 1;
				for (int x = 0; x < h; x++)
				{
					
					if (StudentCoursesDates[x].isgreater(required_date) && !StudentCoursesDates[x].isequal(required_date))
					{
						daydifference[x] = -1;
					}
					else if (StudentCoursesDates[x].islesser(required_date) && !StudentCoursesDates[x].isequal(required_date))
					{
						daydifference[x] = StudentCoursesDates[x].DaysBetween(required_date, days_in_month_leap, days_in_month);
						flagR = 0;
					}
					else if (StudentCoursesDates[x].isequal(required_date))
					{
						daydifference[x] = 0;
					}
					else
						daydifference[x] = -1;
				}
				for (int x = 0; x < h; x++)
				{
					if (daydifference[x] != -1 && daydifference[x] >= 0)
					{
						studydays = daydifference[x];
						break;
					}
				}
				for (int x = 0; x < h; x++)
				{
					if (daydifference[x] < studydays && daydifference[x] >= 0)
							studydays = daydifference[x];
					
				}			
				if (flagR == 1)
					cout << "7" << endl;
				else if (studydays == 0)
					cout << "0" << endl;
				
				else
				cout << studydays-1 <<endl;
		
		}
		else if (Command == "List_StudyDays_ForEveryStudent") //Not Completed
		{
			MyDate StudentCoursesDates[10], required_date;
			int h = 0 ,daydifference[100],flagR=1, studydays;
			string required_courses = CommandArgument;
			for (int x = 0; x < CoursesCount; x++)
			{
				if (courseCode[x] == required_courses)
				{
					required_date = ExamDate[x];
					break;
				}
			}
			for (int x = 0; x < NumberOfStudents; x++)
			{
				h = 0;
				flagR = 1;
				if (studentCourses[x].find(required_courses,0)!=string::npos)
				{ 
					for (int z = 0; z < CoursesCount; z++)
						if (studentCourses[x].find(courseCode[z], 0) != string::npos)
						{
							StudentCoursesDates[h]=ExamDate[z];
							h++;	
						}
					for (int w = 0; w< h; w++)
					{
						if (StudentCoursesDates[w].isgreater(required_date))
						{
							daydifference[w] = -1;
						}
						else if (StudentCoursesDates[w].islesser(required_date) && StudentCoursesDates[w].getDay() > 0 && !StudentCoursesDates[w].isequal(required_date))
						{
							daydifference[w] = StudentCoursesDates[w].DaysBetween(required_date, days_in_month_leap, days_in_month);
							flagR = 0;
						}
						else if (StudentCoursesDates[w].isequal(required_date))
						{
							daydifference[w] = 0;
							flagR = 0;
						}
			
					}
					
					for (int w = 0; w < h; w++)
					{
						if (daydifference[w] >= 0)
						{
							studydays = daydifference[w];
							break;
						}
					}
					for (int w = 0; w < h; w++)
					{
						for (int z = 0; z < h; z++)
						{
							if (daydifference[w] == -1 || daydifference[z] == -1)
								continue;
							else if (daydifference[w] < studydays && daydifference[w] >= 0)
							{
								studydays = daydifference[w];
							}
						}
					}
					if (flagR == 1 && studentCourses[x].find(required_courses, 0) != string::npos)
						cout << studentID[x] << " " << "7" << endl;
					else if (studydays > 0)
						cout << studentID[x] << " " << studydays - 1 << endl;
					else if (studydays == 0)
						cout << "0" << endl;
				}
				
			}
		}
		else if (Command == "List_StudyDays_ForEveryCourse")//Completed
		{
			int req_student, h=0,daydifference[100], studydays,flagR=1;
			MyDate StudentCoursesDates[10],required_date;
			for (int x = 0; x < NumberOfStudents; x++)
			{
				if (studentID[x] == CommandArgument)
				{
					req_student = x;
					break;
				}
			}
			for (int x = 0; x < CoursesCount; x++)
			{
				flagR = 1;
				if (studentCourses[req_student].find(courseCode[x], 0) != string::npos)
				{
					required_date = ExamDate[x];
					for (int z = 0; z < CoursesCount; z++)
					{ 
						if (studentCourses[req_student].find(courseCode[z], 0) != string::npos)
						{
							StudentCoursesDates[h].setDate(ExamDate[z].getDay(),ExamDate[z].getMonth(),ExamDate[z].getYear());
							h++;
							
						}
					}
					for (int w = 0; w < h; w++)
					{
						{ 
						if (StudentCoursesDates[w].isgreater(required_date))
						{
							daydifference[w] = -1;
						}
						else if (StudentCoursesDates[w].islesser(required_date) && StudentCoursesDates[w].getDay() > 0 && !StudentCoursesDates[w].isequal(required_date))
						{
							daydifference[w] = StudentCoursesDates[w].DaysBetween(required_date, days_in_month_leap, days_in_month);
							flagR = 0;
						}
						else 
							daydifference[w]=0;
						}
					}
					for (int w = 0; w < h; w++)
					{
						if (daydifference[w] >=0)
							studydays = daydifference[w];
					}
					if (flagR==0)
					{ 
					for (int w = 0; w < h; w++)
					{
						for (int z = 0; z < h; z++)
						{
							if (daydifference[w] == -1 || daydifference[z] == -1)
								continue;
							if ((daydifference[w] < studydays && daydifference[w] >= 0 ))
							{
								studydays = daydifference[w];
							}
						}
					}
					cout << courseCode[x] << " " << studydays-1 << endl;
					}
					else
						cout << courseCode[x] << " " << "7" << endl;
					h = 0;
					
				}
				
			}
		}
		else if (Command == "List_Exam_InSameDay") //Completed
		{
			MyDate StudentCoursesDates[10];
			int h = 0;
			int required_student;
			int flagB[100];
			int counter = 0;
			for (int x = 0; x < NumberOfStudents; x++)
			{
				h = 0;
				if (studentID[x] == CommandArgument)
				{
					required_student = x;
					break;
				}
			}
			for (int x = 0; x < CoursesCount; x++)
			{
				for (int z = 0; z < CoursesCount;z++)
				if (studentCourses[required_student].find(courseCode[x]) != string::npos && studentCourses[required_student].find(courseCode[z])!=string::npos)
				{
					if (ExamDate[x].isequal(ExamDate[z]) && x != z)
					{
						if (flagB[x] != 1)
						{
							cout << courseCode[x] <<endl;
							flagB[x] = 1;
							counter++;
						}
						if (flagB[z] != 1)
						{
							cout << courseCode[z]<<endl;
							flagB[z] = 1;
							counter++;
						}

					}
				}
			}
			if (counter == 0)
				cout << "none"<<endl;

		}
		else if (Command == "List_Exam_InSameDay_ForEveryStudent") //Completed
		{
			MyDate StudentCoursesDates[10];
			int h = 0;
			int required_student;
			int flagB[100];
			for (int w = 0;w < NumberOfStudents; w++)
			{
				h = 0;
				cout << studentID[w] << " ";
				for (int f = 0; f < 100; f++)
				{
					flagB[f] = 0;
				}
			
			for (int x = 0; x < CoursesCount; x++)
			{
				for (int z = 0; z < CoursesCount; z++)
					if (studentCourses[w].find(courseCode[x]) != string::npos && studentCourses[w].find(courseCode[z]) != string::npos)
					{
						if (ExamDate[x].isequal(ExamDate[z]) && x != z)
						{
							if (flagB[x] != 1)
							{
								cout << courseCode[x] << " ";
								flagB[x] = 1;
								h++;
							}
							if (flagB[z] != 1)
							{
								cout << courseCode[z] << " ";
								flagB[z] = 1;
								h++;
							}

						}
				}	
			}
			if (h == 0)
				cout << "none";
			cout << endl;
			}

		}



	}
	return 0;
}