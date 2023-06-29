#include <iostream>
#include <string>
using namespace std;


typedef unsigned int HANDLE;

struct HandleData
{
	// 기본 값 0
	HANDLE h;
	char* str_p;
};


class HandleManager {
private:
	HANDLE m_maxValue, m_setValue;

	// 핸들 테이블
	HandleData* m_handleTable_p;
public:
	// 핸들의 최대개수를 전달 받음
	HandleManager(HANDLE max_value) {
		m_maxValue = max_value;
		// handle의 생성 기준값을 설정
		m_setValue = 1;
		
		//핸들 테이블을 생성하여 원하는 테이블 개수만큼.
		m_handleTable_p = new HandleData[m_maxValue];

		// 0으로 초기화:
		memset(m_handleTable_p, 0, sizeof(HandleData) * m_maxValue);


	}

	~HandleManager() {
		HandleData* p = m_handleTable_p;
		HANDLE i;
		for (i=0; i < m_maxValue; i++) {
			// 핸들 값이 0이 아니라는것은 그 자리에 값이 존재 한다는 의미
			if (p->h) delete[] p->str_p;
			// 포인터 다음 위치로 이동
			p++;
		}
		delete m_handleTable_p;
	}

	HANDLE InsertString(const char* str) {
		HandleData* p = m_handleTable_p;
		HANDLE i;
		for (i = 0; i < m_maxValue; i++) {
			// 핸들 테이블의 핸들 값이 0 이면 값이 존재하지 않는 것. 
			if (p->h == 0) break;

			// 만약 값이 존재한다면 다음 핸들 테이블로 넘어감.
			p++;
		}
		// 핸들에 저장공간이 여유가 있다면
		if (i < m_maxValue) {
			// 핸들 번호를 매겨 사용자에게 전달할 핸들 값을 부여한다. 이 값은 순차적이다.
			p->h = m_setValue++;
			// 데이터의 크기를 구해 어느 정도로 메모리를 할당할 지 정의한다
			int len = strlen(str)+1;
			// 메모리 할당후
			p->str_p = new char[len];
			// 할당 한 메모리에 문자열을 복사한다.
			memcpy(p->str_p, str, len);
			return p->h;
		}
		// 저장공간에 여유가 없을 때
		return 0xffffffff;
	}

	void PrintString(HANDLE h) {
		HandleData* p = m_handleTable_p;
		HANDLE i;
		for (i = 0; i < m_maxValue; i++) {
			if (p->h == h) { cout << p->str_p << endl; return; }
			p++;

		}
		cout << L"유효하지 않은 핸들 값을 사용 하셨슴당" << endl;
		return;
	}

	void DeleteString(HANDLE h) {
		HandleData* p = m_handleTable_p;
		HANDLE i;
		for (i = 0; i < m_maxValue; i++) {
			if (p->h == h) {
				delete[] p->str_p;
				p->h = 0;
				return;
			}
			p++;
		}
		cout << L"유효하지 않은 핸들 값을 사용 하셨슴당" << endl;
		return;
	}
	
};
int main() {

	// 생성자에 테이블 개수 50을 전달. 스택에 선언 할것 이므로 포인터는 사용하지 않음
	// 동적으로 생성시에만 포인터로 선언 new class()등;
	HandleManager hm(50);
	// 문자열을 메모리에 추가하고 핸들 번호를 받는다
	HANDLE num_handle = hm.InsertString("뭐 아무거나~");

	if (num_handle != 0xffffffff) {
		// 받은 핸들 번호로 다시 접근하여 출력한다.
		hm.PrintString(num_handle);
		// 핸들 번호로 문자열을 지운다.
		hm.DeleteString(num_handle);
	}
	// 제거 하고 난뒤 그 곳의 문자열을 출력해본다.
	// 출력시 그냥 그 곳의 메모리 주소가 출력이된다.
	hm.PrintString(num_handle);


	return 0;
}