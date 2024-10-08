#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>
#include "training.hpp"
using namespace std;

istream& operator>>(istream& is, Student& student)
{
    is >> student.nume;
    is >> student.program;
    is.clear();
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    return is;
}

istream& operator>>(istream& is, ProgramTraining& program)
{
    string name;
    int numCourses;
    int pondereExamen=0;

    if (!getline(is, name))
    {
        return is;
    }
    if (!(is >> numCourses))
    {
        return is;
    }
    program.setNume(name);
    program.setNumCourses(numCourses);
    is.clear();
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    int nr=program.nrCursuri;
    program.nrCursuri=0;
    for (int i = 0; i < nr; ++i)
    {
        string courseName;
        int nrLucrari;
        if (!getline(is, courseName))
        {
            break;
        }
        cout << "Read course name: " << courseName << endl;
        Curs* course = nullptr;
        if (courseName == "Limba straina")
        {
            string language;
            if (!getline(is, language))
            {
                break;
            }
            course = new LimbaStraina(courseName, language);
        }
        else if (courseName == "Programare elementara")
        {
            bool oop;
            string limbaj;
            float examen=0;
            int pondereExamen;
            if (!(is >> oop >> limbaj >> pondereExamen))
            {
                break;
            }
            course = new ProgramareElementara(courseName, oop, limbaj, examen, pondereExamen);
        }
        else if (courseName == "Matematica")
        {
            vector<string> topics;
            for (int i = 0; i < 3; ++i)
            {
                string topic;
                if (!getline(is, topic))
                {
                    break;
                }
                if (!topic.empty())
                {
                    topics.push_back(topic);
                }
            }

            float examen=0;
            int pondereExamen;
            if (!(is >> pondereExamen))
            {
                break;
            }

            course = new Matematica(courseName, topics, examen, pondereExamen);
        }
        else if (courseName == "Sofat auto practic")
        {
            string tipVehicul;
            if (!getline(is, tipVehicul))
            {
                break;
            }
            course = new SofatAutoPractic(courseName, tipVehicul);
        }
        else if (courseName == "Comunicare NLP")
        {
            float examen=0;
            int pondereExamen;

            if (!(is >> pondereExamen))
            {
                break;
            }
            course = new ComunicareNLP(courseName, examen, pondereExamen);
        }
        else
        {

            course = new Curs(courseName);
        }

        if (!(is >> nrLucrari))
        {
            break;
        }
        course->setNrLucrariPractice(nrLucrari);
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        int totalPonders = 0;
        int pondersArray[100];
        for (int j = 0; j < nrLucrari; ++j)
        {
            int ponder;
            if (!(is >> ponder))
            {
                break;
            }
            if (pondereExamen > 0)
            {

                if (totalPonders + pondereExamen > 100)
                {
                    cout << "Error: Sum of ponders and exam ponder exceeds 100 for course " << courseName << endl;
                    cout << "Please provide ponders for practical works again." << endl;
                    for (int j = 0; j < nrLucrari; ++j)
                    {
                        if (!(is >> pondersArray[j]))
                        {
                            cout << "Error reading ponder for course " << courseName << endl;
                            break;
                        }
                        totalPonders += pondersArray[j];
                    }
                }
            }

            if (totalPonders + ponder > 100)
            {
                cout << "Error: Sum of ponders exceeds 100 for course " << courseName << endl;
                cout << "Please provide ponders again." << endl;
                j = -1;
                totalPonders = 0;
                continue;
            }

            pondersArray[j] = ponder;
            totalPonders += ponder;
        }


        course->setPonders(pondersArray, nrLucrari);

        if (course)
        {

            program.addCourse(course);
        }
        else
        {
            break;
        }
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return is;
}




/*void displayMenu()
{
    cout << "Menu:" << endl;
    cout << "1. Add a student to the database" << endl;
    cout << "2. Check if student was added" << endl;
    cout << "3. Add a program to the database" << endl;
    cout << "4. Exit program" << endl;
    cout << "5. Add the grades for a student to the database" << endl;
    cout << "6. Display competence for a student" << endl;
    cout << "7. Display name and competence of students who followed a certain program" << endl;
    cout << "8. Update grades" << endl;
}*/
int main(int argc, char* argv[])

{
    int citire;
    char* nume_fisier;
    if(argc <= 1)
    {
        cout << "Trebuie sa folosesti cifra 1 pentru input de la tastatura sau numele fisierului daca citesti din fisier.";
        return 1;
    }
    else
    {
        nume_fisier = argv[1];
        citire = 0;
    }

    citire = argv[1][0] - '0';
    istream *in;
    if(citire == 1)
    {
        in = &cin;
        cout<<"Test conversie nlp to advaced"<<endl;
        ComunicareNLP nlp("ComunicareNLP Course", 8.5, 30);
        nlp.Creare();
        AdvancedCourse advanced = nlp;
        advanced.printInfo();
        cout<<endl;
        advanced.Creare();
        cout<<endl;
        const int MAX_STUDENTS = 1000;
        const int MAX_PROGRAMS = 8;
        Student students[MAX_STUDENTS];
        int numStudents = 0;
        int numPrograms = 0;
        int choice;
        bool exitProgram = false;
        Curs* resurseUmane = new Curs("Resurse Umane");
        Curs* financiar = new Curs("Financiar");
        Curs* manager = new Curs("Manager");
        Curs* legislatieAuto = new Curs("Legislatie auto");
        Curs* programareElementara = new ProgramareElementara("Programare elementara", true, "C++", 0, 30);
        Curs* limbaStraina = new LimbaStraina("Limba straina", "Engleza");
        Curs* matematica = new Matematica("Matematica", {"Algebra", "Analiza", "Geometrie"}, 0, 30);
        Curs* sofatAutoPractic = new SofatAutoPractic("Sofat auto practic", "tir");
        Curs* comunicareaNLP = new ComunicareNLP("Comunicarea NLP", 0, 30);
        Curs* matf = new Matematica("Matematica", {"Algebra"}, 0, 30);
        programareElementara->setNrLucrariPractice(2);
        matematica->setNrLucrariPractice(3);
        comunicareaNLP->setNrLucrariPractice(3);
        matf->setNrLucrariPractice(4);
        resurseUmane->setNrLucrariPractice(3);
        financiar->setNrLucrariPractice(2);
        manager->setNrLucrariPractice(1);
        legislatieAuto->setNrLucrariPractice(3);
        limbaStraina->setNrLucrariPractice(1);
        sofatAutoPractic->setNrLucrariPractice(2);
        //ponderi
        resurseUmane->setpondere(0,35);
        resurseUmane->setpondere(1,35);
        resurseUmane->setpondere(2,30);
        sofatAutoPractic->setpondere(0,50);
        sofatAutoPractic->setpondere(1,50);
        programareElementara->setpondere(0,50);
        programareElementara->setpondere(1,50);
        matematica->setpondere(0,35);
        matematica->setpondere(1,35);
        matematica->setpondere(2,30);
        comunicareaNLP->setpondere(0,30);
        comunicareaNLP->setpondere(1,30);
        comunicareaNLP->setpondere(2,40);
        matf->setpondere(0,25);
        matf->setpondere(1,25);
        matf->setpondere(2,25);
        matf->setpondere(3,25);
        financiar->setpondere(0,30);
        financiar->setpondere(1,30);
        financiar->setpondere(2,40);
        manager->setpondere(0,100);
        legislatieAuto->setpondere(0,35);
        legislatieAuto->setpondere(1,35);
        legislatieAuto->setpondere(2,30);
        limbaStraina->setpondere(0,100);
        //programareElementara->setPonders({30,30,40},3);
// Declaram toate programele separat si adaugam cursurile
        ProgramTraining finantist;
        finantist.setNume("Finantist");
        finantist.setNumCourses(0);
        finantist.addCourse(matf);
        finantist.addCourse(financiar);

        ProgramTraining managernormal;
        managernormal.setNume("Manager");
        managernormal.setNumCourses(0);
        managernormal.addCourse(resurseUmane);
        managernormal.addCourse(financiar);
        managernormal.addCourse(limbaStraina);

        ProgramTraining programator;
        programator.setNume("Programator");
        programator.setNumCourses(0);
        programator.addCourse(matematica);
        programator.addCourse(programareElementara);
        programator.addCourse(limbaStraina);

        ProgramTraining managerEchipaProgramatori;
        managerEchipaProgramatori.setNume("Manager Echipa Programatori");
        managerEchipaProgramatori.setNumCourses(0);
        managerEchipaProgramatori.addCourse(manager);
        managerEchipaProgramatori.addCourse(programareElementara);
        managerEchipaProgramatori.addCourse(comunicareaNLP);

        ProgramTraining sofer;
        sofer.setNume("Sofer");
        sofer.setNumCourses(0);
        sofer.addCourse(legislatieAuto);
        sofer.addCourse(sofatAutoPractic);

        ProgramTraining managerTiristi;
        managerTiristi.setNume("Manager echipa de tiristi");
        managerTiristi.setNumCourses(0);
        managerTiristi.addCourse(limbaStraina);
        managerTiristi.addCourse(manager);
        managerTiristi.addCourse(legislatieAuto);


        ProgramTraining* programs[MAX_PROGRAMS] = {nullptr};


        programs[numPrograms++] = new ProgramTraining(finantist);
        programs[numPrograms++] = new ProgramTraining(managernormal);
        programs[numPrograms++] = new ProgramTraining(programator);
        programs[numPrograms++] = new ProgramTraining(managerEchipaProgramatori);
        programs[numPrograms++] = new ProgramTraining(sofer);
        programs[numPrograms++] = new ProgramTraining(managerTiristi);
         MenuSingleton& menu1 = MenuSingleton::getInstance();
    menu1.displayMenu();
    /*MenuSingleton& menu2 = MenuSingleton::getInstance();
    menu2.displayMenu();
    if (&menu1 == &menu2)
    {
        cout << "Same instance" << endl;
    }
    else
    {
        cout << "Not the same instance" << endl;
    }*/
        while (!exitProgram)
        {
            try
    {
        *(in) >> choice;
        in->ignore();

        if (choice < 1 || choice > 8)
        {
            throw "Invalid choice. Please select a number between 1 and 8.";
        }
            switch (choice)
            {
            case 1:
            {
                if (numStudents < MAX_STUDENTS)
                {
                    string studentName, programName;
                    getline(*in, studentName);
                    getline(*in, programName);
                    in->clear();
                    in->ignore(numeric_limits<streamsize>::max(), '\n');
                    bool programFound = false;
                    for (int i = 0; i < numPrograms; ++i)
                    {
                        if (programs[i] != nullptr && programs[i]->getNume() == programName)
                        {
                            programFound = true;
                            Student newStudent;
                            newStudent.setNume(studentName);
                            newStudent.program = ProgramTraining(*programs[i]);
                            students[numStudents++] = newStudent;
                            cout << "Student added successfully!" << endl;
                            break;
                        }
                    }

                    if (!programFound)
                    {
                        cout << "Program not found." << endl;
                    }
                }
                else
                {
                    cout << "Maximum number of students reached!" << endl;
                }
                break;
            }
            case 2:
            {
                string studentName;
                getline(*in, studentName);
                in->ignore();
                bool found = false;
                cout << "Searching for student: " << studentName << endl;
                for (int i = 0; i < numStudents; ++i)
                {
                    if (students[i].getNume() == studentName)
                    {
                        cout << "Program: " << students[i].getProgram().getNume() << endl;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Student not found!" << endl;
                }
                break;
            }
            case 3:
            {
                try
    {
        if (numPrograms <= MAX_PROGRAMS)
        {
        programs[numPrograms] = new ProgramTraining;
        *(in) >> *(programs[numPrograms]);
        numPrograms++;
        cout << "Program added successfully." << endl;
        }
        else
            {

            throw("Maximum number of programs reached!");
        }
    }
    catch (const char* msg)
    {
        cout << "Error: " << msg << endl;
    }
    break;
            }
            case 4:
            {

                exitProgram = true;
                cout << "Exiting program..." << endl;
                break;
            }
            case 5:
            {
                string studentName;
                cout << "Enter student name: ";
                getline(*in, studentName);
                in->clear();
                in->ignore(numeric_limits<streamsize>::max(), '\n');
                bool studentFound = false;
                Student* studentPtr = nullptr;
                for (int i = 0; i < numStudents; ++i)
                {
                    if (students[i].getNume() == studentName)
                    {
                        studentFound = true;
                        studentPtr = &students[i];
                        break;
                    }
                }
                if (studentFound)
                {
                    cout << "Student found. Input grades for each course." << endl;
                    cout << studentPtr->program.getNumCourses() << endl;
                    for (int i = 0; i < studentPtr->program.getNumCourses(); ++i)
                    {
                        Curs* course = studentPtr->program.getCourse(i);
                        cout << "Enter grades for course " << course->getNume() << ":" << endl;
                        for (int j = 0; j < course->getNrLucrariPractice(); ++j)
                        {
                            double grade;
                            cout << "Grade " << (j + 1) << ": ";
                            *in >> grade;
                            course->setGrade(j, grade);
                            cout << grade << endl;
                        }
                    }
                    cout << "Grades added successfully for student " << studentName << endl;
                    for (int i = 0; i < studentPtr->program.getNumCourses(); ++i)
                    {
                        Curs* course = studentPtr->program.getCourse(i);


                        cout<<course->getNume()<<endl;
                        if (auto nlpCourse = dynamic_cast<Matematica*>(course))
                        {
                            float ex;
                            if (!(*in >> ex))
                            {
                                cout << "Error reading exam grade for the course." << endl;
                                continue;
                            }
                            nlpCourse->setExamen(ex);
                            cout << "Exam grade: " << nlpCourse->getExamen() << endl;
                            nlpCourse->calculateMean();
                            cout<<"Media este     "<<nlpCourse->getMedieCurs()<<endl;
                        }
                        else if (auto nlpCourse = dynamic_cast<ComunicareNLP*>(course))
                        {

                            float ex;
                            if (!(*in >> ex))
                            {
                                cout << "Error reading exam grade for the course." << endl;
                                continue;
                            }
                            nlpCourse->setExamen(ex);
                            cout << "Exam grade: " << nlpCourse->getExamen() << endl;
                            nlpCourse->calculateMeanNLP();
                            cout<<"Media este     "<<nlpCourse->getMedieCurs()<<endl;
                        }
                        else if (auto nlpCourse = dynamic_cast<ProgramareElementara*>(course))
                        {
                            float ex;
                            if (!(*in >> ex))
                            {
                                cout << "Error reading exam grade for the course." << endl;
                                continue;
                            }
                            nlpCourse->setExamen(ex);
                            cout << "Exam grade: " << nlpCourse->getExamen() << endl;
                            nlpCourse->calculateMean();
                            cout<<"Media este    "<<nlpCourse->getMedieCurs()<<endl;
                        }
                        else
                        {
                            course->calculateMean();
                            cout<<"Medie:"<<course->getMedieCurs()<<endl;
                        }
                        in->clear();
                        in->ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    studentPtr->calculateAndAssignCompetence();
                    studentPtr->setcomp(studentPtr->program.getNume());
                }
                else
                {
                    cout << "Student not found." << endl;
                }
                break;
            }
            case 6:
            {
                string studentName;
                cout << "Enter student name: ";
                getline(*in, studentName);
                in->clear();
                in->ignore(numeric_limits<streamsize>::max(), '\n');
                for (int i = 0; i < numStudents; ++i)
                {
                    if (students[i].getNume() == studentName)
                    {
                        cout<<students[i].competence<<endl;
                    }
                }
                break;
            }
            case 7:
            {

                string competenceName;
                cout << "Enter competence name: ";
                getline(*in, competenceName);
                in->clear();
                in->ignore(numeric_limits<streamsize>::max(), '\n');
                for (int i = 0; i < numStudents; ++i)
                {
                    if (students[i].competence.getNume() == competenceName)
                    {
                        cout << "Name: " << students[i].getNume() << ", Nivel: " << students[i].competence.getNivel() << endl;
                    }
                }
                break;

            }
            case 8:
            {
                bool found = false;
                string studentName;
                cout << "Enter the name of the student whose grades you want to update: ";
                getline(*in, studentName);
                in->clear();
                in->ignore(numeric_limits<streamsize>::max(), '\n');
                for (int i = 0; i < numStudents; ++i)
                {
                    if (students[i].getNume() == studentName && students[i].competence.getNivel()=="Refacere")
                    {
                        cout << "Enter the grades for each course:" << endl;
                        for (int j = 0; j < students[i].program.getNumCourses(); ++j)
                        {
                            Curs* course = students[i].program.getCourse(j);
                            cout << "Enter grades for course " << course->getNume() << ":" << endl;
                            for (int k = 0; k < course->getNrLucrariPractice(); ++k)
                            {
                                double grade;
                                cout << "Grade " << (k + 1) << ": ";
                                *in >> grade;
                                course->setGrade(k, grade);
                                cout << grade << endl;
                            }
                        }
                        cout << "Grades re-added successfully for student " << studentName << endl;
                        for (int j = 0; j < students[i].program.getNumCourses(); ++j)
                        {
                            Curs* course = students[i].program.getCourse(i);
                            cout<<course->getNume()<<endl;
                            if (auto nlpCourse = dynamic_cast<Matematica*>(course))
                            {
                                float ex;
                                if (!(*in >> ex))
                                {
                                    cout << "Error reading exam grade for the course." << endl;
                                    continue;
                                }
                                nlpCourse->setExamen(ex);
                                cout << "Exam grade: " << nlpCourse->getExamen() << endl;
                                nlpCourse->calculateMean();
                                cout<<"Media este     "<<nlpCourse->getMedieCurs()<<endl;
                            }
                            else if (auto nlpCourse = dynamic_cast<ComunicareNLP*>(course)) // Check if the course is of type ComunicareaNLP
                            {

                                float ex;
                                if (!(*in >> ex))
                                {
                                    cout << "Error reading exam grade for the course." << endl;
                                    continue;
                                }
                                nlpCourse->setExamen(ex);
                                cout << "Exam grade: " << nlpCourse->getExamen() << endl;
                                nlpCourse->calculateMeanNLP();
                                cout<<"Media este     "<<nlpCourse->getMedieCurs()<<endl;
                            }
                            else if (auto nlpCourse = dynamic_cast<ProgramareElementara*>(course))
                            {
                                float ex;
                                if (!(*in >> ex))
                                {
                                    cout << "Error reading exam grade for the course." << endl;
                                    continue;
                                }
                                nlpCourse->setExamen(ex);
                                cout << "Exam grade: " << nlpCourse->getExamen() << endl;
                                nlpCourse->calculateMean();
                                cout<<"Media este     "<<nlpCourse->getMedieCurs()<<endl;
                            }
                            else
                            {
                                course->calculateMean();
                                cout<<"Medie:"<<course->getMedieCurs()<<endl;
                            }
                            in->clear();
                            in->ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        students[i].calculateAndAssignCompetence();
                        students[i].setcomp(students[i].program.getNume());
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Student with name " << studentName << " not apt for retaking his tests and exams." << endl;
                }

                break;
            }
            default:
                cout << "Invalid choice! Please choose again." << endl;
            }
        }
        catch (const char* errorMsg)
    {
        cout << "Error: " << errorMsg << endl;
    }
}
        delete resurseUmane;
        delete financiar;
        delete manager;
        delete legislatieAuto;
        delete limbaStraina;
        delete matematica;
        delete sofatAutoPractic;
        delete comunicareaNLP;
        delete matf;
        for (int i = 0; i < numPrograms; ++i)
        {
            delete programs[i];
        }
    }
    else
    {
        /*fstream *fin = new fstream(nume_fisier);
        in = fin;
        int numarStudenti;
        *(in) >> numarStudenti;
        Student student[100];
        ProgramTraining program[100];
        cout<<numarStudenti<<endl;
        in->ignore();
        for (int i = 0; i < numarStudenti; ++i) {

            *(in) >> student[i];
            cout<<student[i].getNume()<<endl;
            *(in) >> program[i];
            cout<<i<<" "<<program[i].getNume()<<endl;
            int nrCursuri;
            *(in) >> nrCursuri;

            for (int j = 0; j < nrCursuri; ++j) {
                char numeCurs[100];
                streampos pos = in->tellg();
                *(in) >> numeCurs;
                if (strcmp(numeCurs, "Comunicare") == 0) {
                    NLP nlp;
                    in->seekg(pos);
                    *(in) >> nlp;
                    nlp.printCourseName();
                } else {
                    Curs curs;
                    in->seekg(pos);
                   *(in) >> curs;
                    curs.printCourseName();
                }
            }
        }
        */
    }
    return 0;
}

