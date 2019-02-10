#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

int main() {
	setlocale(LC_ALL, "");							// ��������� ��������� � ������� Windows
	IpAddress ip = IpAddress::getLocalAddress();	//��������� ip ������
	TcpSocket socket;//����������� ��������� ��� ����������� ������ ������� ����� ����������
	Packet packet;	//��� ������������� �������� �������� ������
	char type;
	char mode = ' ';//��� s- ������, � - ������
	int x = 0;      //���������� ����
	int y = 0;
	int cx = 0;
	int cy = 100;
	char buffer[2000];
	size_t received;	//??
	string text = "connect to: ";

	//***********�����������***************//
	cout << ip << endl;
	cout << "������� ��� �����������:  c -������, s -������" << endl;
	cin >> type;
	if (type == 's') {
		TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);    //������� ����� ��������� ����� ����������
		text += "Serwer";
		mode = 's';

	}
	else if (type == 'c') {
		cout << "new ip:";
		cin >> ip;

		socket.connect(ip, 2000); //ip � ����
		text += "client";
		mode = 'r';
	}
	socket.send(text.c_str(), text.length() + 1);
	socket.receive(buffer, sizeof(buffer), received);
	cout << buffer << endl;



	//**********��������� �����***********************//
	RenderWindow window(sf::VideoMode(800, 600), "Network");//������� ������ �������� ����
															//*******��������********************//
	CircleShape shape(10);     //������� ��� � �������� 50
	CircleShape shape1(10);

	shape1.setFillColor(Color(100, 250, 250));

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}


		}
		if (mode == 's') {
			socket.receive(packet); //������� ������� ������� ������ � ���� ������ �� ���������� �����
			if (packet >> x >> y) { //����������� �������� �� ������ � ���������� x � � (�������� ��� ����������)
				cout << x << ":" << y << endl; //..� ���� ��� ������ ������� �� ������� � ����������
				//packet << cx << cy;
				//socket.send(packet);
			}
		}

		if (mode == 'r') {
			
				if (Keyboard::isKeyPressed(Keyboard::Right)) { //������ ���������� � ������������ =>��� �����
					x++;
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) { //������ ���������� � ������������ =>��� �����
					x--;
				}

				if (Keyboard::isKeyPressed(Keyboard::Down)) { //������ ���������� � ������������ =>��� �����
					y++;
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) { //������ ���������� � ������������ =>��� �����
					y--;
				}
			

			packet << x << y; //������ �������� ��������� � �����
			socket.send(packet); //�������� ������
			packet.clear(); //������ �����
		}
		window.clear();
		shape.setPosition(x, y); //���������� ��� �� ����������
		//if (mode == 's')
			window.draw(shape1); //������������ ���
		//else if (mode == 'r')
			window.draw(shape);
		
		window.display();
		if (mode == 'r')
			sleep(sf::milliseconds(10));//��������
	}//END

	system("pause");
	return 0;
}