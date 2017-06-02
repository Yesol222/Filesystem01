#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include <io.h>
#include <time.h>
#include<algorithm>



using namespace std;

typedef pair<string, long long> pss;
typedef pair<pss, char *> psi;
#define mp(a,b,c) make_pair(make_pair(a,b),c)

vector<psi> arr;

#define MSIZE 16777216

int fileCopy(const char* src, const char* dst);

int main() {




	string filename; //입력 받는 값
	string spath, spath1; //소스경로
	string dpath, dpath1; //목적경로
	string date;
	int sp; //공백이 있는 곳

	getline(cin, filename); //입력받음
	sp = filename.find(" "); //공백조사
	spath = filename.substr(0, sp); //공백기준쪼갬
	spath1 = spath + "*.*"; //파일리스트출력을 위해 *.*붙임 
	dpath = filename.substr(sp + 1, filename.size());
	dpath1 = dpath + "*.*";


	//cin >> filename;

	struct _finddata_t fd;

	intptr_t handle;


	//dpath 파싱;
	if ((handle = _findfirst(dpath1.c_str(), &fd)) == -1L)

		cout << "No file in directory!" << endl;

	do

	{
		string b = fd.name;


		psi c = mp(b, fd.time_write, ctime(&(fd.time_write)));
		arr.push_back(c);


	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);


	//spath 파싱
	if ((handle = _findfirst(spath1.c_str(), &fd)) == -1L)

		cout << "No file in directory!" << endl;

	do

	{
		int i;
		string copypath1 = spath + fd.name;
		string copypath2 = dpath + fd.name;


		for (i = 0; i < arr.size(); i++)
		{
			//파일이름이 같을 때
			if (fd.name == arr[i].first.first) {

				//데스티네이션폴더의 파일이 더 최근이라면
				if (fd.time_write < arr[i].first.second) {
					// 파일 입력 (쓰기)
					ofstream outFile( dpath+"mybackup.log", ios::app);
					outFile << fd.name << arr[i].second << "\n" << endl;
					outFile.close();
					i = -1;
					break; // 복사안함
				}
				else { //소스파일이 더 최근이면 복사함
					int e = fileCopy(copypath1.c_str(), copypath2.c_str());
					i = -2;

				}
			}
			else { continue; }
		}

		if (i == -2) {

			ofstream outFile(dpath + "mybackup.log", ios::app);
			outFile << fd.name << ctime(&(fd.time_write)) << "\n" << endl;
			outFile.close();
		}
		if (i != -1 && i != -2 ) {

			int e = fileCopy(copypath1.c_str(), copypath2.c_str());

			if (e == 0)

				printf("파일이 복사되었습니다.\n");
			else {
				switch (e) {
				case  1: fputs("원본 파일을 열 수 없습니다.\n", stderr); break;
				case  2: fputs("대상 파일에 쓸 수 없습니다. 읽기 전용?\n", stderr); break;
				case  3: fputs("쓰기 에러, 디스크 용량 초과?\n", stderr); break;
				case  4: fputs("원본 경로와 대상 경로가 동일합니다\n", stderr); break;
				case 10: fputs("메모리가 부족합니다\n", stderr); break;
				default: fputs("알 수 없는 에러\n", stderr); break;
				}

			}
		}


	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);



	//테스트용
	cin >> filename;



}


//파일복사 함수
int fileCopy(const char* src, const char* dst) {
	FILE *in, *out;
	char* buf;
	size_t len;

	if (!strcmpi(src, dst)) return 4; // 원본과 사본 파일이 동일하면 에러

	if ((in = fopen(src, "rb")) == NULL) return 1; // 원본 파일 열기
	if ((out = fopen(dst, "wb")) == NULL) { fclose(in); return 2; } // 대상 파일 만들기

	if ((buf = (char *)malloc(MSIZE)) == NULL) { fclose(in); fclose(out); return 10; } // 버퍼 메모리 할당

	while ((len = fread(buf, sizeof(char), sizeof(buf), in)) != NULL)
		if (fwrite(buf, sizeof(char), len, out) == 0) {
			fclose(in); fclose(out);
			free(buf);
			_unlink(dst); // 에러난 파일 지우고 종료
			return 3;
		}

	fclose(in); fclose(out);
	free(buf); // 메모리 할당 해제

	return 0;
}