#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

map<string,int> studentsInGroup; // this is to store the number of people in every group, key is "Group#" and value is the amount of people
map<string,bool> groupIsBusy; // this is to keep track of whether group can take any course at the current time

int main() {

  unsigned int yearOfstudy, major;
  cout<<"============== MENU =============="<<endl;
  cout<<"1.     ELECTRICAL ENGINEERING \n2.     MECHANICAL ENGINEERING \n3.     CIVIL      ENGINEERING \n4.     CHEMICAL   ENGINEERING \n5.     UNDECLARED\nChoose the major: ";
  cin>>major;
  cout<<"Enter the year of study: ";
  cin>>yearOfstudy;
  cout<<endl;

   // input using freopen() and vectors
   if(major>5 || major<=0){
    cout<<"Wrong input of major...Run again"<<endl;
   }
   else
   {
       if(yearOfstudy==1){
        freopen("1year ENGINEERING.txt", "r", stdin); // "r" stands for read
      }
      else
        {
           if(yearOfstudy==2)
           {
               if(major==1){freopen("2year ELECTRICAL.txt", "r", stdin);}
               if(major==2){freopen("2year MECHANICAL.txt", "r", stdin);}
               if(major==3){freopen("2year CIVIL.txt", "r", stdin);}
               if(major==4){freopen("2year CHEMICAL.txt", "r", stdin);}
           }
           else
           {
               if(yearOfstudy==3)
               {
                   if(major==1){freopen("3year ELECTRICAL.txt", "r", stdin);}
                   if(major==2){freopen("3year MECHANICAL.txt", "r", stdin);}
                   if(major==3){freopen("3year CIVIL.txt", "r", stdin);}
                   if(major==4){freopen("3year CHEMICAL.txt", "r", stdin);}
               }
               else
               {
                  if(yearOfstudy==4)
                  {
                       if(major==1){freopen("4year ELECTRICAL.txt", "r", stdin);}
                       if(major==2){freopen("4year MECHANICAL.txt", "r", stdin);}
                       if(major==3){freopen("4year CIVIL.txt", "r", stdin);}
                       if(major==4){freopen("4year CHEMICAL", "r", stdin);}
                  }
                  else
                  {
                      cout<<"Wrong input of year of study...Run again"<<endl;
                  }
               }
           }
        }
   }

  int numberOfGroups;
  cin >> numberOfGroups;
  vector<string> groupName(numberOfGroups); // string vector for groupName with size "numberOfGroups"
  vector<int> groupCapacity(numberOfGroups);//int type vector for group capacity with size "numberOfGroups"
  for(int i = 0; i < numberOfGroups; i++) {
    cin >> groupName[i];
    cin >> groupCapacity[i];
    studentsInGroup[groupName[i]] = groupCapacity[i];//assigning the group capacity to given group through int typed map called "studentsInGroup"
    groupIsBusy[groupName[i]] = false; // making available each group at the given time through boolean typed map called "groupIsBusy"
  }

  int numberOfRooms;
  cin >> numberOfRooms;//assigning the number of rooms from the text file
  vector<string> room(numberOfRooms);//vector for room name
  vector<string> roomType(numberOfRooms);//vector for room type (e.g. lecture or lab)
  vector<int> roomCapacity(numberOfRooms);//vector for room capacity
  vector<bool> roomIsBusy(numberOfRooms);// boolean typed vector for keeping the track of room business
  for(int i = 0; i < numberOfRooms; i++) {
    cin >> room[i];
    cin >> roomType[i];
    cin >> roomCapacity[i];
    roomIsBusy[i] = false;
  }

  int numberOfCourses;
  cin >> numberOfCourses;//assigning the number of courses from the text file
  vector<string> courseName(numberOfCourses);//string vector for keeping the name of the course
  vector<int> numberOfGroupsTaking(numberOfCourses);//vector for number of groups taking the above course
  vector<string> groupNameTaking[numberOfCourses];//vector for group name taking the above course
  vector<bool> courseIsBusy(numberOfCourses);
  vector<bool> lectureTaken(numberOfCourses);
  for(int i = 0; i < numberOfCourses; i++) { // for loop for assigning courseName and number of groups taking the above course
    cin >> courseName[i];
    cin >> numberOfGroupsTaking[i];
    courseIsBusy[i] = false;
    lectureTaken[i] = false;
    for(int j = 0; j < numberOfGroupsTaking[i]; j++) {
      string group;
      cin >> group;
      groupNameTaking[i].push_back(group);
    }
  }
  map<string,bool> labTaken[numberOfCourses]; // here we are keeping track whether some group have taken lab of some course
  for(int i = 0; i < numberOfCourses; i++) {
    for(int j = 0; j < numberOfGroupsTaking[i]; j++) {
      labTaken[i][groupNameTaking[i][j]] = false;
    }
  }

  int numberOfFaculties;
  cin >> numberOfFaculties;
  vector<string> facultyName(numberOfFaculties);//string vector for faculty name
  vector<int> numberOfLectures(numberOfFaculties);//integer vector for number of lectures
  vector<string> lectureCode[numberOfFaculties];//string vector for course taught by faculty professor
  vector<bool> facultyIsBusy(numberOfFaculties);
  for(int i = 0; i < numberOfFaculties; i++) {// for loop for assigning Faculty name
    cin >> facultyName[i];
    cin >> numberOfLectures[i];
    facultyIsBusy[i] = false;
    for(int j = 0; j < numberOfLectures[i]; j++) {//for loop for adding (giving inputs) the course name taught by faculty professor
      string lecture;
      cin >> lecture;
      lectureCode[i].push_back(lecture);
    }
  }

  for(int day = 1; day <= 5; day++) {
    if(day == 1) cout << "=========================MONDAY=========================\n";
    if(day == 2) cout << "\n\n=========================TUESDAY=========================\n";
    if(day == 3) cout << "\n\n=========================WEDNESDAY=========================\n";
    if(day == 4) cout << "\n\n=========================THURSDAY=========================\n";
    if(day == 5) cout << "\n\n=========================FRIDAY=========================\n";
    for(int startTime = 9; startTime <= 16; startTime += 2) {
      if(startTime == 13) startTime++; // because of lunch, lecture must start at 14:00 instead of 13:00
      cout << startTime << ":00 - " << startTime + 2 << ":00\n";
      for(int room_i = 0; room_i < numberOfRooms; room_i++) {   // iteration through all the rooms
        if(!roomIsBusy[room_i]) { // if room is not occupied, go further
          for(int course_i = 0; course_i < numberOfCourses; course_i++) { // iteration through all the courses
            if(!courseIsBusy[course_i]) { // if course is not already occupying another room, go further
              for(int faculty_i = 0; faculty_i < numberOfFaculties; faculty_i++) { // iteration through all the faculties
                if(!facultyIsBusy[faculty_i]) { // if faculty is not busy, go further
                  for(int lecture_i = 0; lecture_i < numberOfLectures[faculty_i]; lecture_i++) { // iteration through all the lectures taught by faculties for every faculty
                    if(courseName[course_i] == lectureCode[faculty_i][lecture_i]) { // this means that the faculty teaches the course considered at this iteration
                      if(roomType[room_i] == "lecture" && lectureTaken[course_i]) continue; // if lecture for this course is already taken and room type is "lecture", we iterate further
                      int numberOfStudents = 0; // counting number of students taking the course
                      int groupTakingLabIndex = -1; // number -1 means that the group for lab is not assigned yet
                      string groupTakingLabName;
                      if(roomType[room_i] == "lab") {
                        for(int group_i = 0; group_i < numberOfGroupsTaking[course_i]; group_i++) {
                          if(studentsInGroup[groupNameTaking[course_i][group_i]] <= roomCapacity[room_i] && !labTaken[course_i][groupNameTaking[course_i][group_i]] && !groupIsBusy[groupNameTaking[course_i][group_i]]) { // here we check if the capacity of room allows allocating the group or not and whether lab was taken by the group or not
                            groupTakingLabIndex = group_i;
                            groupTakingLabName = groupName[group_i];
                            break;
                          }
                        }
                      }
                      if(roomType[room_i] == "lecture") {
                        for(int group_i = 0; group_i < numberOfGroupsTaking[course_i]; group_i++) { // simply adding up
                          numberOfStudents += studentsInGroup[groupNameTaking[course_i][group_i]];
                          if(groupIsBusy[groupNameTaking[course_i][group_i]]) {
                            numberOfStudents = 1e9; // this will make sure that the room capacity will be smaller than number of students and code will not enter to next if statement
                            break;
                          }
                        }
                      }
                      if(numberOfStudents <= roomCapacity[room_i] && !roomIsBusy[room_i] && !courseIsBusy[course_i] && !facultyIsBusy[faculty_i]) { // checking once again availability of course, room and faculty, also checking if all the students can be allocated in the room, go further and cout the information about the class
                        if(roomType[room_i] == "lecture") {
                          lectureTaken[course_i] = true; // if room type is "lecture", making lectureTaken[course_i] true
                          for(int group_i = 0; group_i < numberOfGroupsTaking[course_i]; group_i++) { // making groups busy at the current time, since they are having course at that time
                            groupIsBusy[groupNameTaking[course_i][group_i]] = true;
                          }
                        }
                        if(roomType[room_i] == "lab" && groupTakingLabIndex != -1) {
                          labTaken[course_i][groupNameTaking[course_i][groupTakingLabIndex]] = true; // if groupTakingLab == -1, it means that there is no group that can take the lab in this room
                          groupIsBusy[groupTakingLabName] = true; // making the group taking lab busy
                        }
                        if(!(roomType[room_i] == "lab" && groupTakingLabIndex == -1)) { // here we just make sure that we will not use the room if room type is "lab" and no group can take lab in this room
                          roomIsBusy[room_i] = true; // room becomes occupied by students, so roomIsBusy[room_i] must be true
                          courseIsBusy[course_i] = true; // course is taken by students, so courseIsBusy[course_i] must be true
                          facultyIsBusy[faculty_i] = true; // faculty is busy, so facultyIsBusy[faculty_i] must be true
                          cout <<"\t"<< room[room_i] << ' ' << roomType[room_i] << ' ' << courseName[course_i] << ' ' << facultyName[faculty_i] << ' ';
                          if(roomType[room_i] == "lecture") {
                            for(int group_i = 0; group_i < numberOfGroupsTaking[course_i]; group_i++) {
                              cout << groupNameTaking[course_i][group_i] << ' ';
                            }
                          }
                          if(roomType[room_i] == "lab") {
                            cout << groupTakingLabName;
                          }
                          cout << "\n";//this is to begin new line for next time slot
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      // here all the values are recovered to false, because at the new time everything is not busy
      for(int room_i = 0; room_i < numberOfRooms; room_i++) {
        roomIsBusy[room_i] = false;
      }
      for(int course_i = 0; course_i < numberOfCourses; course_i++) {
        courseIsBusy[course_i] = false;
      }
      for(int faculty_i = 0; faculty_i < numberOfFaculties; faculty_i++) {
        facultyIsBusy[faculty_i] = false;
      }
      for(int group_i = 0; group_i < numberOfGroups; group_i++) {
        groupIsBusy[groupName[group_i]] = false;
      }

    }
  }


    getchar();
     system("pause");
return 0;
}
