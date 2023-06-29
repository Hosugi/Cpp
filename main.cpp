#include <iostream>
#include <string>
using namespace std;


typedef unsigned int HANDLE;

struct HandleData
{
	// �⺻ �� 0
	HANDLE h;
	char* str_p;
};


class HandleManager {
private:
	HANDLE m_maxValue, m_setValue;

	// �ڵ� ���̺�
	HandleData* m_handleTable_p;
public:
	// �ڵ��� �ִ밳���� ���� ����
	HandleManager(HANDLE max_value) {
		m_maxValue = max_value;
		// handle�� ���� ���ذ��� ����
		m_setValue = 1;
		
		//�ڵ� ���̺��� �����Ͽ� ���ϴ� ���̺� ������ŭ.
		m_handleTable_p = new HandleData[m_maxValue];

		// 0���� �ʱ�ȭ:
		memset(m_handleTable_p, 0, sizeof(HandleData) * m_maxValue);


	}

	~HandleManager() {
		HandleData* p = m_handleTable_p;
		HANDLE i;
		for (i=0; i < m_maxValue; i++) {
			// �ڵ� ���� 0�� �ƴ϶�°��� �� �ڸ��� ���� ���� �Ѵٴ� �ǹ�
			if (p->h) delete[] p->str_p;
			// ������ ���� ��ġ�� �̵�
			p++;
		}
		delete m_handleTable_p;
	}

	HANDLE InsertString(const char* str) {
		HandleData* p = m_handleTable_p;
		HANDLE i;
		for (i = 0; i < m_maxValue; i++) {
			// �ڵ� ���̺��� �ڵ� ���� 0 �̸� ���� �������� �ʴ� ��. 
			if (p->h == 0) break;

			// ���� ���� �����Ѵٸ� ���� �ڵ� ���̺�� �Ѿ.
			p++;
		}
		// �ڵ鿡 ��������� ������ �ִٸ�
		if (i < m_maxValue) {
			// �ڵ� ��ȣ�� �Ű� ����ڿ��� ������ �ڵ� ���� �ο��Ѵ�. �� ���� �������̴�.
			p->h = m_setValue++;
			// �������� ũ�⸦ ���� ��� ������ �޸𸮸� �Ҵ��� �� �����Ѵ�
			int len = strlen(str)+1;
			// �޸� �Ҵ���
			p->str_p = new char[len];
			// �Ҵ� �� �޸𸮿� ���ڿ��� �����Ѵ�.
			memcpy(p->str_p, str, len);
			return p->h;
		}
		// ��������� ������ ���� ��
		return 0xffffffff;
	}

	void PrintString(HANDLE h) {
		HandleData* p = m_handleTable_p;
		HANDLE i;
		for (i = 0; i < m_maxValue; i++) {
			if (p->h == h) { cout << p->str_p << endl; return; }
			p++;

		}
		cout << L"��ȿ���� ���� �ڵ� ���� ��� �ϼ̽���" << endl;
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
		cout << L"��ȿ���� ���� �ڵ� ���� ��� �ϼ̽���" << endl;
		return;
	}
	
};
int main() {

	// �����ڿ� ���̺� ���� 50�� ����. ���ÿ� ���� �Ұ� �̹Ƿ� �����ʹ� ������� ����
	// �������� �����ÿ��� �����ͷ� ���� new class()��;
	HandleManager hm(50);
	// ���ڿ��� �޸𸮿� �߰��ϰ� �ڵ� ��ȣ�� �޴´�
	HANDLE num_handle = hm.InsertString("�� �ƹ��ų�~");

	if (num_handle != 0xffffffff) {
		// ���� �ڵ� ��ȣ�� �ٽ� �����Ͽ� ����Ѵ�.
		hm.PrintString(num_handle);
		// �ڵ� ��ȣ�� ���ڿ��� �����.
		hm.DeleteString(num_handle);
	}
	// ���� �ϰ� ���� �� ���� ���ڿ��� ����غ���.
	// ��½� �׳� �� ���� �޸� �ּҰ� ����̵ȴ�.
	hm.PrintString(num_handle);


	return 0;
}