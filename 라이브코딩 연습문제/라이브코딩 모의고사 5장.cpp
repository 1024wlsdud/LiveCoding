
#include <iostream>
#include <string.h>

using namespace std;
// ���� ������, �������� ���� ������ ȣ��, ��(��ü)�� ���� �Լ�ȣ��,
// ��ü �����ڿ� ���� �Լ� ȣ��, ��ü�� ����, ��ü ������ ���� ���� Ȱ���� �� �ִ� �ɷ� ����

class Container {
private:
	string title; // �����̳� Ÿ��Ʋ
	char* author; // �����̳� �ۼ��� �̸� (���� �Ҵ�)
	int size; // �����̳ʿ� ����� ���� �迭 ũ��
	int* arr; // ������ �����ϴ� �迭 (���� �Ҵ�)
public:
	void display();
	Container(string title, const char* author,
		int size, int* arr = nullptr);
	~Container();
	Container(const Container& c);
	void replace_subtitle(string from, string to);
	void replace_first_last();
	void add(int value);
	void set_title(string title);
	void print_title();
};

// ���⿡ Container Ŭ���� ��� �Լ����� ������ ��
Container::Container(string title, const char* author, int size, int* arr)
{
	int len = strlen(author);
	this->title = title;
	this->author = new char[len + 1];
	strcpy(this->author, author);
	this->size = size;
	this->arr = new int[size];

	for (int i = 0; i < size; i++)
	{
		this->arr[i] = ((arr != nullptr) ? arr[i] : 0);
	}
	cout << "Container ������ ȣ��" << endl;
	display();

}
Container::Container(const Container& c)
{
	int len = strlen(c.author);
	this->title = c.title;
	this->author = new char[len + 1];
	strcpy(this->author, c.author);
	this->size = c.size;
	this->arr = new int[c.size];

	for (int i = 0; i < size; i++)
	{
		this->arr[i] = c.arr[i];
	}
	cout << "Container ���� ������ ȣ��" << endl;
	display();

}
void Container::display() {
	cout << "title:" << title << "," << endl;
	cout << "author:" << author << ", size:" << size << endl;
	cout << "arr[] = ";

	for (int i = 0; i < size - 1; i++)
		cout << arr[i] << ", ";
	cout << arr[size - 1];
	cout << endl << endl;

}

Container::~Container() {
	cout << "Container �Ҹ��� ȣ��" << endl;
	display();
	delete author;
	delete arr;
}
void Container::replace_subtitle(string from, string to) {

	int i = title.find(from);
	while (i != -1)
	{
		title.replace(i, from.size(), to);
		i = title.find(from);
	}
	display();
}
void Container::replace_first_last() {
	int i = title.find(" ");
	if (i != -1) {
		string first = title.substr(0, i);
		i = title.rfind(" ");
		string last = title.substr(i + 1);
		title.replace(0, first.size(), last);
		title.replace(i, last.size(), first);

		// replace(���� �ε��� ��ġ, ����, ���ڿ�)
		// string.find("a") => string���ڿ����� a��� ���ڸ� ã�� �� �� �ε����� ��ȯ��
	}
	display();
}

void Container::add(int value) {
	for (int i = 0; i < size; ++i)
		arr[i] += value;
}
void Container::set_title(string title) {
	this->title = title;
}

void Container::print_title() {
	cout << "print_title ȣ��: " << title << endl << endl;
}

class Manager {
public:
	Manager();
	static void call_by_value(Container c1); // ���� ���� ȣ�� ���
	static void call_by_reference(Container& c1);
	static Container return_value();
	static Container &return_reference(Container& rc);
};

void Manager::call_by_value(Container c1) {
	cout << "call_by_value(Container c1)ȣ�� " << endl;
	c1.set_title("c1");
	c1.add(100);
	c1.display();
}
void Manager::call_by_reference(Container& c1) {
	cout << "call_by_reference(Container c1)ȣ�� " << endl;
	c1.add(200);
	c1.display();
}

Container Manager::return_value() {
	cout << "return_value() ȣ��" << endl << endl;
	Container c2("d", "return_value()", 3); // 4��° ���ڴ� ����Ʈ �Ű����� ����
	cout << "return_value()���� ����" << endl << endl;
	return c2;
}

Container & Manager::return_reference(Container& rc) {
	cout << "return_reference(Container & rc) ȣ��" << endl;
	rc.add(3000);
	rc.display();
	return rc;
}
int main() {
	int arr[5] = { 1, 2, 3, 4, 5 };
	char author[] = "main()";
	Container c("c", "author", 5, arr);

	// �Լ� ���� c�� ���� �����ڿ� ���� �Ű����� c1�� �����
	Manager::call_by_value(c);
	cout << "call_by_value(c)���� ���ϵǾ���. ���� ��ü c�� ����:" << endl;
	c.display(); // c ��ü�� ������ ������ ����� ��

	Manager::call_by_reference(c);
	cout << "call_by_reference(c)���� ���ϵǾ���. ���� ��ü c�� ���� : " << endl;
	c.display(); // c ��ü�� ������ ����Ǿ� �־�� ��

	// �������� ���� ������ ȣ��
	Container d = Manager::return_value();
	cout << "���� ��ü d�� ����:" << endl;
	d.display(); // d�� arrp[���� ��� 1000 Ȯ��

	cout << "return_value().print_title() ����" << endl;
	Manager::return_value().print_title();


	Container& e = Manager::return_reference(d); // �ᱹ e�� d�� �����ϰ� �ȴ�.
	cout << "return_reference(d)���� ���ϵǾ���. ���� ��ü d�� ���� : " << endl;
	d.display();	// d ��ü�� arr[]�� ������ ��� 3000���� ����Ǿ� �־�� ��

	cout << "���� ������ e�� ����:" << endl;
	e.display();	// e�� ���� ��ü d�� �����ϴ� ������: d�� ������ ���븦 ������
	cout << "main()���� ������" << endl << endl;
}