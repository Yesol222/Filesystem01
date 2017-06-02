#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <vector>
#include <sys/stat.h>
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>


using namespace std;
using namespace stdext;


class students {
    
private:
    char name[20];
    unsigned studentID;
    float score;
    unsigned advisorID;
    hash_map<unsigned, students> H;
    hash_map<unsigned, students>::iterator Iter1;
    
public:
    
    
    students::students() {}
    
    students::students(char Name[20], unsigned int StudentID, float Score, unsigned int AdvisorID)
    {
        for (int i = 0; i < 20; i++) name[i] = Name[i];
        studentID = StudentID;
        score = Score;
        advisorID = AdvisorID;
    }
    
    
    bool is_empty(std::ifstream& pFile)
    {
        return pFile.peek() == std::ifstream::traits_type::eof();
    }
    
    void studentIDTable(students S) {
        
        H.insert(hash_map<unsigned, students>::value_type(studentID, S));
        
        ofstream outfile("E://students.hash", std::ofstream::binary);
        ifstream infile("E://students.hash", std::ifstream::binary);
        
        
        if (is_empty(infile)) {
            Iter1 = H.begin();
        }
        
        outfile << Iter1->second.name << Iter1->second.score << Iter1->second.advisorID << endl;
        ++Iter1;
        
        
        
    }
    
    void scoreTree() {
        
        
    }
    void readdata() {
        
    }
    
};

int main()
{
    char name[20];
    unsigned int studentID;
    float score;
    unsigned int advisorID;
    
    //이름
    char studentdata[20];
    char s_name[20];
    
    
    int N; //데이터의 수
    int K; //K번째
    
    ofstream fout("E:\\Students.DB");
    FILE *out;
    
    out = fopen("E:\\Student.csv", "r");
    fscanf(out, "%d\n", &N);
    printf("입력받는 수 : %d\n", N);
    
    
    for (int i = 0; i <= N; i++) {
        fscanf(out, "%s\n", s_name);
        if (i == 0) {
            continue;
        }
        //공백단위로 끊어지므로 한번 더 조사해서 이름을 붙여줌
        fscanf(out, "%s\n", studentdata);
        strcat(s_name, " ");
        strcat(s_name, studentdata);
        fout << s_name << endl;
        
        //s_name 가 이름,학번,점수,일련번호 이런 형식의 문자열이라서 ,기준으로 쪼개서
        //students *NewStudent = new students(name, studentID, score, advisorID);
        //NewStudent->studentIDTable(*NewStudent);
        //로 넣어주면 hash에 인서트 됨.
    }
    
    fout.close();
    fclose(out);
    //읽어오기 끝
    
     
     //해시 작동하는지 테스트
     int id;
     int advisor;
     
     
     cout << "이름,ID,점수,advisorID 순으로 입력하세요" << endl;
     cin >> name >> studentID >> score >> advisorID;
     cout << name<<" " << studentID << " " << score << " " << advisorID<<endl;
     
     students *NewStudent = new students(name, studentID, score, advisorID);
     NewStudent->studentIDTable(*NewStudent);
    
    
    return 0;
}
