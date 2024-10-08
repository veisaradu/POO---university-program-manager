#define TRAINING_HPP
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
const int MAX_COURSES = 10;
class MenuSingleton
{
private:
    MenuSingleton() {}
    MenuSingleton(const MenuSingleton&) = delete;
    MenuSingleton& operator=(const MenuSingleton&) = delete;

public:
    static MenuSingleton& getInstance()
    {
        static MenuSingleton instance;
        return instance;
    }
    void displayMenu()
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
    }
};
class BazaCurs
{
public:
    virtual void Creare() = 0;
    virtual ~BazaCurs() {}
};
class Curs:public BazaCurs
{
protected:
    string nume;
    int nrLucrariPractice;
    float noteLucrariPractice[100];
    int ponders[100];
    float medieCurs;

public:
     Curs() : nume(""), nrLucrariPractice(0), medieCurs(0) {}
    Curs(const string& nume) : nume(nume), nrLucrariPractice(0), medieCurs(0) {}
    virtual void setPonders(const int* pondersArray, int numProjects)
    {
        if (numProjects > 100)
        {
            cout << "Error: Number of projects exceeds the maximum allowed size." << endl;
            return;
        }
        nrLucrariPractice = numProjects;

        for (int i = 0; i < numProjects; ++i)
        {
            ponders[i] = pondersArray[i];
        }
    }

    virtual Curs* createCourse() const
    {
        return new Curs(*this);
    }

    virtual const int* getPonders() const
    {
        return ponders;
    }
    virtual void setpondere(int i,int j)
    {
        ponders[i]=j;
    }

    const string& getNume() const
    {
        return nume;
    }
    void setGrade(int projectIndex, double grade)
    {
        if (projectIndex >= 0 && projectIndex < nrLucrariPractice)
        {
            noteLucrariPractice[projectIndex] = grade;
        }
        else
        {
            cout << "Invalid project index!" << endl;
        }
    }
    void setNrLucrariPractice(int nrLucrari)
    {
        nrLucrariPractice = nrLucrari;
    }
    int getNrLucrariPractice() const
    {
        return nrLucrariPractice;
    }
    void printCourseName() const
    {
        cout << "Course Name: " << nume << endl;
    }
    float getMedieCurs() const
    {
        return medieCurs;
    }
    virtual void calculateMean()
    {
        double sum = 0;
        double totalPonders = 0;
        for (int i = 0; i < nrLucrariPractice; ++i)
        {
            sum += noteLucrariPractice[i] * ponders[i];
            totalPonders += ponders[i];
        }
        if (totalPonders > 0)
        {
            medieCurs = sum / totalPonders;
        }
        else
        {
            medieCurs = 0;
        }
    }
 virtual void Creare() override {
        cout << "Creare Curs normal" << endl;
    }
    friend istream& operator>>(istream& is, Curs& curs);
    friend ostream& operator<<(ostream& os, Curs& curs);
    virtual ~Curs() {}
};

class ProgramTraining
{
private:
    string nume;
    Curs* cursuri[MAX_COURSES]= {nullptr};
    int nrCursuri;
public:
    ProgramTraining() : nume(""), nrCursuri(0)
    {

        for (int i = 0; i <MAX_COURSES; ++i)
        {
            cursuri[i] = nullptr;
        }
    }
    Curs* getCourse(int index) const
    {
        if (index >= 0 && index < nrCursuri)
        {
            return cursuri[index];
        }
        else
        {
            return nullptr;
        }
    }

    void setNume(const string& name)
    {
        nume = name;
    }
    int getNumCourses() const
    {
        return nrCursuri;
    }

    void setNumCourses(int num)
    {
        nrCursuri = num;
    }
    void addCourse(Curs* curs)
    {
        if (nrCursuri < MAX_COURSES)
        {
            cursuri[nrCursuri] = curs;
            cursuri[nrCursuri]->Creare();
            nrCursuri++;
        }
        else
        {
            cout << "Maximum number of courses reached!" << endl;
        }
    }
    void printProgramName() const
    {
        cout << nume << endl;
    }
    friend istream& operator>>(istream& is, ProgramTraining& program);
    const string& getNume() const
    {
        return nume;
    }
    ProgramTraining(const ProgramTraining& other) : nume(other.nume), nrCursuri(other.nrCursuri)
    {
        for (int i = 0; i < nrCursuri; ++i)
        {
            if (other.cursuri[i])
            {
                cursuri[i] = other.cursuri[i]->createCourse();
            }
            else
            {
                cursuri[i] = nullptr;
            }
        }
    }

    ProgramTraining& operator=(const ProgramTraining& other)
    {
        if (this != &other)
        {
            nume = other.nume;
            nrCursuri = other.nrCursuri;
            for (int i = 0; i < nrCursuri; ++i)
            {
                if (other.cursuri[i])
                {
                    cursuri[i] = other.cursuri[i]->createCourse();
                }
                else
                {
                    cursuri[i] = nullptr;
                }
            }
        }
        return *this;
    }



    ~ProgramTraining()
    {
        for (int i = 0; i < nrCursuri; ++i)
        {
            if (cursuri[i] != nullptr)
            {
                delete cursuri[i];
                cursuri[i] = nullptr;
            }
        }
    }

};
class Competenta
{
private:
    string nume;
    string nivel;

public:
    void determinaNivelCompetenta(int nota)
    {
        if (nota >= 9)
        {
            nivel = "Nivel mare";
        }
        else if (nota >= 7 && nota < 9)
        {
            nivel = "Nivel mediu";
        }
        else if (nota >= 5 && nota < 7)
        {
            nivel = "Nivel mic";
        }
        else if (nota >= 3 && nota < 5)
        {
            nivel = "Refacere";
        }
        else
        {
            nivel = "Picat";
        }
    }

    const string& getNume() const
    {
        return nume;
    }
    void setNume(const string& name)
    {
        nume = name;
    }
    const string& getNivel() const
    {
        return nivel;
    }
    friend ostream& operator<<(ostream& os, const Competenta& comp)
    {
        os << "Competence: " << comp.getNume() << ", Nivel: " << comp.getNivel();
        return os;
    }
};
class Student
{
public:
    string nume;
    ProgramTraining program;
    Competenta competence;

public:

    Student() : nume(""), program(), competence() {}
    friend istream& operator>>(istream& is, Student& student);
    void setNume(const string& name)
    {
        nume = name;
    }

    void setProgram(const string& programName)
    {
        program.setNume(programName);
    }

    const string& getNume() const
    {
        return nume;
    }
    void setcomp(const string& name)
    {
        competence.setNume(program.getNume());
    }
    const ProgramTraining& getProgram() const
    {
        return program;
    }
    void calculateAndAssignCompetence()
    {
        double totalMean = 0.0;
        int numCourses = program.getNumCourses();
        for (int i = 0; i < numCourses; ++i)
        {
            Curs* course = program.getCourse(i);
            if (course)
            {
                course->calculateMean();
                totalMean += course->getMedieCurs();
            }
        }
        double studentMean = numCourses > 0 ? totalMean / numCourses : 0.0;

        if (studentMean >= 9)
        {
            competence.determinaNivelCompetenta(9);
        }
        else if (studentMean >= 7)
        {
            competence.determinaNivelCompetenta(7);
        }
        else if (studentMean >= 5)
        {
            competence.determinaNivelCompetenta(5);
        }
        else if(studentMean >= 3)
        {
            competence.determinaNivelCompetenta(3);
        }
        else
        {
            competence.determinaNivelCompetenta(0);
        }
    }


};

class ProgramareElementara : public Curs
{
private:
    bool oop;
    string limbaj;
    float examen;
    int pondereExamen;
public:
    ProgramareElementara(const string& nume, bool oop, const string& limbaj, float examen, int pondereExamen)
        : Curs(nume), oop(oop), limbaj(limbaj), examen(examen), pondereExamen(pondereExamen) {}

    virtual ProgramareElementara* createCourse() const override
    {
        return new ProgramareElementara(*this);
    }
    void setExamen(double ex)
    {
        examen=ex;
    }
    float getExamen() const
    {
        return examen;
    }
    virtual void calculateMean()
    {
        double sum = 0;
        double totalPonders = 0;
        for (int i = 0; i < nrLucrariPractice; ++i)
        {
            sum += noteLucrariPractice[i] * ponders[i];
            totalPonders += ponders[i];
        }
        sum=sum+examen*pondereExamen;
        totalPonders+=pondereExamen;
        medieCurs = sum / totalPonders;
    }
    virtual void Creare() override {
        cout << "Creare curs tip ProgramareElementara" << endl;
    }

};

class LimbaStraina : public Curs
{
private:
    string limba;
public:
    LimbaStraina(const string& nume, const string& limba)
        : Curs(nume), limba(limba) {}
    virtual LimbaStraina* createCourse() const override
    {
        return new LimbaStraina(*this);
    }
    virtual void Creare() override {
        cout << "Creare curs Limba Straina" << endl;
    }

};
class Matematica : public Curs
{
private:
    vector<string> matematici;
    float examen;
    int pondereExamen;

public:
    Matematica(const string& nume, const vector<string>& matematici, float examen, int pondereExamen)
        : Curs(nume), matematici(matematici), examen(examen), pondereExamen(pondereExamen) {}

    virtual Matematica* createCourse() const override
    {
        return new Matematica(*this);
    }
    float getExamen() const
    {
        return examen;
    }
    virtual void Creare() override {
        cout << "Creare curs tip Matematica" << endl;
    }
    void setExamen(float examen)
    {
        this->examen = examen;
    }

    int getPondereExamen() const
    {
        return pondereExamen;
    }

    void setPondereExamen(int pondereExamen)
    {
        this->pondereExamen = pondereExamen;
    }
    virtual void calculateMean()
    {
        double sum = 0;
        double totalPonders = 0;
        for (int i = 0; i < nrLucrariPractice; ++i)
        {
            sum += noteLucrariPractice[i] * ponders[i];
            totalPonders += ponders[i];
        }
        sum=sum+examen*pondereExamen;
        totalPonders+=pondereExamen;
        medieCurs = sum / totalPonders;
    }
    const vector<string>& getMatematici() const
    {
        return matematici;
    }

    void setMatematici(const vector<string>& matematici)
    {
        this->matematici = matematici;
    }
};


class SofatAutoPractic : public Curs
{
private:
    string tipVehicul;
public:
    SofatAutoPractic(const string& nume, const string& tipVehicul)
        : Curs(nume), tipVehicul(tipVehicul) {}
    virtual SofatAutoPractic* createCourse() const override
    {
        return new SofatAutoPractic(*this);
    }

    virtual void Creare() override {
        cout << "Creare curs tip Sofat Auto" << endl;
    }
};

class ComunicareNLP : public Curs
{
public:
    float examen;
    int pondereExamen;
    ComunicareNLP(const string& nume, float examen, int pondereExamen)
        : Curs(nume), examen(examen), pondereExamen(pondereExamen) {}
    virtual ComunicareNLP* createCourse() const override
    {
        return new ComunicareNLP(*this);
    }
    void setMedie(double ex)
    {
        medieCurs=ex;
    }
    void calculateMeanNLP()
    {
        Curs::calculateMean();
        double currentMedie = getMedieCurs();
        if (currentMedie < 5)
        {
            medieCurs = 1;
        }
        else
        {
            setMedie(examen);
        }
    }

    void setExamen(double ex)
    {
        examen=ex;
    }
    float getExamen() const
    {
        return examen;
    }
    virtual void Creare() override {
        cout << "Creare curs tip ComunicareNLP" << endl;
    }

};

class AdvancedCourse : public Curs {
public:
    float examen;
    int pondereExamen;
    virtual void Creare() override {
        cout << "Creare curs tip Advanced" << endl;
    }
    AdvancedCourse(const ComunicareNLP& ob) {
        this->nume = ob.getNume();
        this->examen = ob.getExamen();
        this->pondereExamen = ob.pondereExamen;
        this->nrLucrariPractice = ob.getNrLucrariPractice();
        for (int i = 0; i < ob.getNrLucrariPractice(); ++i) {
            this->ponders[i] = ob.getPonders()[i];
        }
    }

     AdvancedCourse& operator=(const AdvancedCourse& other) {
        if (this != &other) {
            Curs::operator=(other); // Call base class assignment
            this->examen = other.examen;
            this->pondereExamen = other.pondereExamen;
        }
        return *this;
    }

    void printInfo() const {
        cout << "Advanced Course Info:" << endl;
        cout << "Nume: " << nume << endl;
        cout << "Examen: " << examen << endl;
        cout << "Pondere Examen: " << pondereExamen << endl;
        cout << "Number of Lucrari Practice: " << nrLucrariPractice << endl;
        cout << "Ponders: ";
        for (int i = 0; i < nrLucrariPractice; ++i) {
            cout << ponders[i] << " ";
        }
        cout << endl;
    }
};
