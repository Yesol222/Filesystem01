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




	string filename; //�Է� �޴� ��
	string spath, spath1; //�ҽ����
	string dpath, dpath1; //�������
	string date;
	int sp; //������ �ִ� ��

	getline(cin, filename); //�Է¹���
	sp = filename.find(" "); //��������
	spath = filename.substr(0, sp); //��������ɰ�
	spath1 = spath + "*.*"; //���ϸ���Ʈ����� ���� *.*���� 
	dpath = filename.substr(sp + 1, filename.size());
	dpath1 = dpath + "*.*";


	//cin >> filename;

	struct _finddata_t fd;

	intptr_t handle;


	//dpath �Ľ�;
	if ((handle = _findfirst(dpath1.c_str(), &fd)) == -1L)

		cout << "No file in directory!" << endl;

	do

	{
		string b = fd.name;


		psi c = mp(b, fd.time_write, ctime(&(fd.time_write)));
		arr.push_back(c);


	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);


	//spath �Ľ�
	if ((handle = _findfirst(spath1.c_str(), &fd)) == -1L)

		cout << "No file in directory!" << endl;

	do

	{
		int i;
		string copypath1 = spath + fd.name;
		string copypath2 = dpath + fd.name;


		for (i = 0; i < arr.size(); i++)
		{
			//�����̸��� ���� ��
			if (fd.name == arr[i].first.first) {

				//����Ƽ���̼������� ������ �� �ֱ��̶��
				if (fd.time_write < arr[i].first.second) {
					// ���� �Է� (����)
					ofstream outFile( dpath+"mybackup.log", ios::app);
					outFile << fd.name << arr[i].second << "\n" << endl;
					outFile.close();
					i = -1;
					break; // �������
				}
				else { //�ҽ������� �� �ֱ��̸� ������
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

				printf("������ ����Ǿ����ϴ�.\n");
			else {
				switch (e) {
				case  1: fputs("���� ������ �� �� �����ϴ�.\n", stderr); break;
				case  2: fputs("��� ���Ͽ� �� �� �����ϴ�. �б� ����?\n", stderr); break;
				case  3: fputs("���� ����, ��ũ �뷮 �ʰ�?\n", stderr); break;
				case  4: fputs("���� ��ο� ��� ��ΰ� �����մϴ�\n", stderr); break;
				case 10: fputs("�޸𸮰� �����մϴ�\n", stderr); break;
				default: fputs("�� �� ���� ����\n", stderr); break;
				}

			}
		}


	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);



	//�׽�Ʈ��
	cin >> filename;



}


//���Ϻ��� �Լ�
int fileCopy(const char* src, const char* dst) {
	FILE *in, *out;
	char* buf;
	size_t len;

	if (!strcmpi(src, dst)) return 4; // ������ �纻 ������ �����ϸ� ����

	if ((in = fopen(src, "rb")) == NULL) return 1; // ���� ���� ����
	if ((out = fopen(dst, "wb")) == NULL) { fclose(in); return 2; } // ��� ���� �����

	if ((buf = (char *)malloc(MSIZE)) == NULL) { fclose(in); fclose(out); return 10; } // ���� �޸� �Ҵ�

	while ((len = fread(buf, sizeof(char), sizeof(buf), in)) != NULL)
		if (fwrite(buf, sizeof(char), len, out) == 0) {
			fclose(in); fclose(out);
			free(buf);
			_unlink(dst); // ������ ���� ����� ����
			return 3;
		}

	fclose(in); fclose(out);
	free(buf); // �޸� �Ҵ� ����

	return 0;
}